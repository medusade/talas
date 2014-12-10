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
///   File: sha512.cpp
///
/// Author: $author$
///   Date: 12/9/2014
///
/// OpenSSL Project's implementation of SHA512 modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/hash/openssl/sha512.hpp"

#undef U64
#undef U64_LROTATE
#undef U64_RROTATE

#define U64(x) x##ULL

#define U64_LROTATE(a,n) (((a)<<(n&0x3f)) | (((a)&0xffffffffffffffff)>>(64-(n&0x3f))))
#define U64_RROTATE(a,n) (((a)<<(64-(n&0x3f))) | (((a)&0xffffffffffffffff)>>(n&0x3f)))

#define UINTbits uint64_t
#define UbitsMASK 0xffffffffffffffff
#define UbitsToMSB U64ToMSB
#define MSBToUbits MSBToU64

#define Sigma0(x) (U64_RROTATE((x),28) ^ U64_RROTATE((x),34) ^ U64_RROTATE((x),39))
#define Sigma1(x) (U64_RROTATE((x),14) ^ U64_RROTATE((x),18) ^ U64_RROTATE((x),41))
#define sigma0(x) (U64_RROTATE((x),1)  ^ U64_RROTATE((x),8)  ^ ((x)>>7))
#define sigma1(x) (U64_RROTATE((x),19) ^ U64_RROTATE((x),61) ^ ((x)>>6))

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
///  Class: sha512
///////////////////////////////////////////////////////////////////////
uint64_t sha512::m_K[KONSTSIZE] = {
    U64(0x428a2f98d728ae22),U64(0x7137449123ef65cd),
    U64(0xb5c0fbcfec4d3b2f),U64(0xe9b5dba58189dbbc),
    U64(0x3956c25bf348b538),U64(0x59f111f1b605d019),
    U64(0x923f82a4af194f9b),U64(0xab1c5ed5da6d8118),
    U64(0xd807aa98a3030242),U64(0x12835b0145706fbe),
    U64(0x243185be4ee4b28c),U64(0x550c7dc3d5ffb4e2),
    U64(0x72be5d74f27b896f),U64(0x80deb1fe3b1696b1),
    U64(0x9bdc06a725c71235),U64(0xc19bf174cf692694),
    U64(0xe49b69c19ef14ad2),U64(0xefbe4786384f25e3),
    U64(0x0fc19dc68b8cd5b5),U64(0x240ca1cc77ac9c65),
    U64(0x2de92c6f592b0275),U64(0x4a7484aa6ea6e483),
    U64(0x5cb0a9dcbd41fbd4),U64(0x76f988da831153b5),
    U64(0x983e5152ee66dfab),U64(0xa831c66d2db43210),
    U64(0xb00327c898fb213f),U64(0xbf597fc7beef0ee4),
    U64(0xc6e00bf33da88fc2),U64(0xd5a79147930aa725),
    U64(0x06ca6351e003826f),U64(0x142929670a0e6e70),
    U64(0x27b70a8546d22ffc),U64(0x2e1b21385c26c926),
    U64(0x4d2c6dfc5ac42aed),U64(0x53380d139d95b3df),
    U64(0x650a73548baf63de),U64(0x766a0abb3c77b2a8),
    U64(0x81c2c92e47edaee6),U64(0x92722c851482353b),
    U64(0xa2bfe8a14cf10364),U64(0xa81a664bbc423001),
    U64(0xc24b8b70d0f89791),U64(0xc76c51a30654be30),
    U64(0xd192e819d6ef5218),U64(0xd69906245565a910),
    U64(0xf40e35855771202a),U64(0x106aa07032bbd1b8),
    U64(0x19a4c116b8d2d0c8),U64(0x1e376c085141ab53),
    U64(0x2748774cdf8eeb99),U64(0x34b0bcb5e19b48a8),
    U64(0x391c0cb3c5c95a63),U64(0x4ed8aa4ae3418acb),
    U64(0x5b9cca4f7763e373),U64(0x682e6ff3d6b2b8a3),
    U64(0x748f82ee5defb2fc),U64(0x78a5636f43172f60),
    U64(0x84c87814a1f0ab72),U64(0x8cc702081a6439ec),
    U64(0x90befffa23631e28),U64(0xa4506cebde82bde9),
    U64(0xbef9a3f7b2c67915),U64(0xc67178f2e372532b),
    U64(0xca273eceea26619c),U64(0xd186b8c721c0c207),
    U64(0xeada7dd6cde0eb1e),U64(0xf57d4f7fee6ed178),
    U64(0x06f067aa72176fba),U64(0x0a637dc5a2c898a6),
    U64(0x113f9804bef90dae),U64(0x1b710b35131c471b),
    U64(0x28db77f523047d84),U64(0x32caab7b40c72493),
    U64(0x3c9ebe0a15c9bebc),U64(0x431d67c49c100d4c),
    U64(0x4cc5d4becb3e42b6),U64(0x597f299cfc657e2a),
    U64(0x5fcb6fab3ad6faec),U64(0x6c44198c4a475817),
};

///////////////////////////////////////////////////////////////////////
/// Start accumulation. Set bit count to 0 and buffer to mysterious
/// initialization constants.
///////////////////////////////////////////////////////////////////////
void sha512::initial() {
    m_A = U64(0x6a09e667f3bcc908);
    m_B = U64(0xbb67ae8584caa73b);
    m_C = U64(0x3c6ef372fe94f82b);
    m_D = U64(0xa54ff53a5f1d36f1);
    m_E = U64(0x510e527fade682d1);
    m_F = U64(0x9b05688c2b3e6c1f);
    m_G = U64(0x1f83d9abfb41bd6b);
    m_H = U64(0x5be0cd19137e2179);
    m_l = 0;
    m_h = 0;
}

///////////////////////////////////////////////////////////////////////
/// Final wrapup - pad to BLOCKSIZE-byte boundary with the bit pattern
/// 1 0* (BLOCKSIZE-bit count of bits processed, MSB-first)
///////////////////////////////////////////////////////////////////////
void sha512::final() {
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
void sha512::update(const uint8_t* in, size_t inlen) {
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

    m_h += (((UINTbits)inlen) >> ((LENGTHSIZE<<2)-3));

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
/// The core of the algorithm, this alters an existing hash to
/// reflect the addition of 16 WORDSIZE words of new data. blocks
/// the data and converts bytes into WORDSIZE words for this routine.
///////////////////////////////////////////////////////////////////////
void sha512::transform() {
    UINTbits a,b,c,d,e,f,g,h,s0,s1,T1;
    UINTbits X[16];
    UINTbits* K;
    uint8_t *W;
    unsigned i;

    a = m_A;
    b = m_B;
    c = m_C;
    d = m_D;
    e = m_E;
    f = m_F;
    g = m_G;
    h = m_H;
    K = m_K;
    s0 = s1 = T1 = 0;

    for (W=m_in, i=0; i<16; i++, W+=WORDSIZE)
        X[i] = MSBToUbits(W);

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
