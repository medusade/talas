///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1998-2005 The OpenSSL Project.  All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
///
/// 1. Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
///
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in
///    the documentation and/or other materials provided with the
///    distribution.
///
/// 3. All advertising materials mentioning features or use of this
///    software must display the following acknowledgment:
///    "This product includes software developed by the OpenSSL Project
///    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
///
/// 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
///    endorse or promote products derived from this software without
///    prior written permission. For written permission, please contact
///    openssl-core@openssl.org.
///
/// 5. Products derived from this software may not be called "OpenSSL"
///    nor may "OpenSSL" appear in their names without prior written
///    permission of the OpenSSL Project.
///
/// 6. Redistributions of any form whatsoever must retain the following
///    acknowledgment:
///    "This product includes software developed by the OpenSSL Project
///    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
///
/// THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
/// EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
/// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
/// ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
/// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
/// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
/// OF THE POSSIBILITY OF SUCH DAMAGE.
/// ====================================================================
///
/// This product includes cryptographic software written by Eric Young
/// (eay@cryptsoft.com).  This product includes software written by Tim
/// Hudson (tjh@cryptsoft.com).
///
/// ====================================================================
///
///   File: sha256.cpp
///
/// Author: $author$
///   Date: 11/11/2014
///
/// OpenSSL Project's implementation of SHA256 modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/hash/openssl/sha256.hpp"

#undef U32_LROTATE
#undef U32_RROTATE

#define U32_LROTATE(a,n) (((a)<<(n&0x1f)) | (((a)&0xffffffff)>>(32-(n&0x1f))))
#define U32_RROTATE(a,n) (((a)<<(32-(n&0x1f))) | (((a)&0xffffffff)>>(n&0x1f)))

#define UINTbits uint32_t
#define UbitsMASK 0xffffffff
#define UbitsToMSB U32ToMSB
#define MSBToUbits MSBToU32

//
// FIPS specification refers to right rotations, while our ROTATE macro
// is left one. This is why you might notice that rotation coefficients
// differ from those observed in FIPS document by 32-N...
//
#define Sigma0(x) (U32_LROTATE((x),30) ^ U32_LROTATE((x),19) ^ U32_LROTATE((x),10))
#define Sigma1(x) (U32_LROTATE((x),26) ^ U32_LROTATE((x),21) ^ U32_LROTATE((x),7))
#define sigma0(x) (U32_LROTATE((x),25) ^ U32_LROTATE((x),14) ^ ((x)>>3))
#define sigma1(x) (U32_LROTATE((x),15) ^ U32_LROTATE((x),13) ^ ((x)>>10))

#define Ch(x,y,z)	(((x) & (y)) ^ ((~(x)) & (z)))
#define Maj(x,y,z)	(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define	ROUND_X_X(i,a,b,c,d,e,f,g,h) \
    T1 += h + Sigma1(e) + Ch(e,f,g) + K[i];	\
    h = Sigma0(a) + Maj(a,b,c);			\
    d += T1;	h += T1

#define	ROUND_00_15(i,a,b,c,d,e,f,g,h) \
    T1 = X[i]; ROUND_X_X(i,a,b,c,d,e,f,g,h)

#define	ROUND_16_KONSTSIZE(i,a,b,c,d,e,f,g,h,X) \
    s0 = X[(i+1)&0x0f];	s0 = sigma0(s0);	\
    s1 = X[(i+14)&0x0f];	s1 = sigma1(s1);	\
    T1 = X[(i)&0x0f] += s0 + s1 + X[(i+9)&0x0f];	\
    ROUND_X_X(i,a,b,c,d,e,f,g,h)

namespace talas {
namespace crypto {
namespace hash {
namespace openssl {

///////////////////////////////////////////////////////////////////////
///  Class: sha256
///////////////////////////////////////////////////////////////////////
UINTbits sha256::m_K[KONSTSIZE] = {
    0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
    0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
    0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
    0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
    0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
    0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
    0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
    0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
    0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
    0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
    0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
    0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
    0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
    0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
    0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
    0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};

///////////////////////////////////////////////////////////////////////
/// Start SHA256 accumulation. Set bit count to 0 and buffer to mysterious
/// initialization constants.
///////////////////////////////////////////////////////////////////////
void sha256::initial() {
    m_A = 0x6a09e667UL;
    m_B = 0xbb67ae85UL;
    m_C = 0x3c6ef372UL;
    m_D = 0xa54ff53aUL;
    m_E = 0x510e527fUL;
    m_F = 0x9b05688cUL;
    m_G = 0x1f83d9abUL;
    m_H = 0x5be0cd19UL;
    m_l = 0;
    m_h = 0;
}

///////////////////////////////////////////////////////////////////////
/// Final wrapup - pad to 64-byte boundary with the bit pattern
/// 1 0* (64-bit count of bits processed, MSB-first)
///////////////////////////////////////////////////////////////////////
void sha256::final() {
    unsigned count;
    uint8_t *p;

    // Compute number of bytes mod BLOCKSIZE
    //
    count = (unsigned)((m_l >> 3) & (BLOCKSIZE-1));

    // Set the first char of padding to 0x80.  This is safe since there is
    // always at least one byte free
    //
    p = m_in + count;
    *p++ = 0x80;

    // Bytes of padding needed to make BLOCKSIZE bytes
    //
    count = (BLOCKSIZE-1) - count;

    // Pad out to (BLOCKSIZE-LENGTHSIZE) mod BLOCKSIZE
    //
    if (count < LENGTHSIZE) {
        // Two lots of padding:  Pad the first block to BLOCKSIZE bytes
        //
        memset(p, 0, count);
        transform();

        // Now fill the next block with BLOCKSIZE-LENGTHSIZE bytes
        //
        memset(m_in, 0, (BLOCKSIZE-LENGTHSIZE));
    } else {
        // Pad block to BLOCKSIZE-LENGTHSIZE bytes
        //
        memset(p, 0, count - LENGTHSIZE);
    }

    // Append length in bits and transform
    //
    UbitsToMSB(m_in + (BLOCKSIZE-LENGTHSIZE), m_h);
    UbitsToMSB(m_in + (BLOCKSIZE-LENGTHSIZE)+WORDSIZE, m_l);
    transform();

    UbitsToMSB(m_hash, m_A);
    UbitsToMSB(m_hash + WORDSIZE, m_B);
    UbitsToMSB(m_hash + WORDSIZE*2, m_C);
    UbitsToMSB(m_hash + WORDSIZE*3, m_D);
    UbitsToMSB(m_hash + WORDSIZE*4, m_E);
    UbitsToMSB(m_hash + WORDSIZE*5, m_F);
    UbitsToMSB(m_hash + WORDSIZE*6, m_G);
    UbitsToMSB(m_hash + WORDSIZE*7, m_H);
    initial();
}

///////////////////////////////////////////////////////////////////////
/// Update context to reflect the concatenation of another buffer
/// of bytes.
///////////////////////////////////////////////////////////////////////
void sha256::update(const uint8_t* in, size_t inlen) {
    unsigned len;
    UINTbits t;
    uint8_t *p;

    // Update bitcount
    //
    t = m_l;

    if ((m_l = (t + (inlen << 3)) & UbitsMASK) < t)
        // Carry from low to high
        //
        m_h++;

    m_h += (inlen >> ((LENGTHSIZE<<2)-3));

    // Bytes already in data
    //
    len = (unsigned)((t >> 3) & (BLOCKSIZE-1));

    // Handle any leading odd-sized chunks
    //
    if (len) {
        p = (m_in + len);
        len = (BLOCKSIZE - len);

        if (inlen < len) {
            memcpy(p, in, inlen);
            return;
        }

        memcpy(p, in, len);
        transform();
        in += len;
        inlen -= len;
    }

    // Process data in BLOCKSIZE-byte chunks
    //
    while (inlen >= BLOCKSIZE) {
        memcpy(m_in, in, BLOCKSIZE);
        transform();
        in += BLOCKSIZE;
        inlen -= BLOCKSIZE;
    }

    // Handle any remaining bytes of data.
    //
    memcpy(m_in, in, inlen);
}

///////////////////////////////////////////////////////////////////////
/// The core of the SHA256 algorithm, this alters an existing hash to
/// reflect the addition of 16 longwords of new data. blocks
/// the data and converts bytes into longwords for this routine.
///////////////////////////////////////////////////////////////////////
void sha256::transform() {
    UINTbits a,b,c,d,e,f,g,h,s0,s1,T1;
    UINTbits X[16];
    UINTbits* K;
    uint8_t *p;
    unsigned i;

    for (p=m_in, i=0; i<16; i++, p+=4)
        X[i] = MSBToUbits(p);

    K = m_K;
    a = m_A;
    b = m_B;
    c = m_C;
    d = m_D;
    e = m_E;
    f = m_F;
    g = m_G;
    h = m_H;
    s0 = s1 = T1 = 0;

    ROUND_00_15(0,a,b,c,d,e,f,g,h);
    ROUND_00_15(1,h,a,b,c,d,e,f,g);
    ROUND_00_15(2,g,h,a,b,c,d,e,f);
    ROUND_00_15(3,f,g,h,a,b,c,d,e);
    ROUND_00_15(4,e,f,g,h,a,b,c,d);
    ROUND_00_15(5,d,e,f,g,h,a,b,c);
    ROUND_00_15(6,c,d,e,f,g,h,a,b);
    ROUND_00_15(7,b,c,d,e,f,g,h,a);
    ROUND_00_15(8,a,b,c,d,e,f,g,h);
    ROUND_00_15(9,h,a,b,c,d,e,f,g);
    ROUND_00_15(10,g,h,a,b,c,d,e,f);
    ROUND_00_15(11,f,g,h,a,b,c,d,e);
    ROUND_00_15(12,e,f,g,h,a,b,c,d);
    ROUND_00_15(13,d,e,f,g,h,a,b,c);
    ROUND_00_15(14,c,d,e,f,g,h,a,b);
    ROUND_00_15(15,b,c,d,e,f,g,h,a);

    for (i=16; i<KONSTSIZE; i+=8) {
        ROUND_16_KONSTSIZE(i+0,a,b,c,d,e,f,g,h,X);
        ROUND_16_KONSTSIZE(i+1,h,a,b,c,d,e,f,g,X);
        ROUND_16_KONSTSIZE(i+2,g,h,a,b,c,d,e,f,X);
        ROUND_16_KONSTSIZE(i+3,f,g,h,a,b,c,d,e,X);
        ROUND_16_KONSTSIZE(i+4,e,f,g,h,a,b,c,d,X);
        ROUND_16_KONSTSIZE(i+5,d,e,f,g,h,a,b,c,X);
        ROUND_16_KONSTSIZE(i+6,c,d,e,f,g,h,a,b,X);
        ROUND_16_KONSTSIZE(i+7,b,c,d,e,f,g,h,a,X);
    }

    m_A += a;
    m_B += b;
    m_C += c;
    m_D += d;
    m_E += e;
    m_F += f;
    m_G += g;
    m_H += h;
}

} // namespace openssl 
} // namespace hash 
} // namespace crypto 
} // namespace talas 
