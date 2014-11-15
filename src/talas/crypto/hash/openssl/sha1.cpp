///////////////////////////////////////////////////////////////////////
/// Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
/// All rights reserved.
///
/// This package is an SSL implementation written
/// by Eric Young (eay@cryptsoft.com).
/// The implementation was written so as to conform with Netscapes SSL.
///
/// This library is free for commercial and non-commercial use as long as
/// the following conditions are aheared to.  The following conditions
/// apply to all code found in this distribution, be it the RC4, RSA,
/// lhash, DES, etc., code; not just the SSL code.  The SSL documentation
/// included with this distribution is covered by the same copyright terms
/// except that the holder is Tim Hudson (tjh@cryptsoft.com).
///
/// Copyright remains Eric Young's, and as such any Copyright notices in
/// the code are not to be removed.
/// If this package is used in a product, Eric Young should be given attribution
/// as the author of the parts of the library used.
/// This can be in the form of a textual message at program startup or
/// in documentation (online or textual) provided with the package.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
/// 1. Redistributions of source code must retain the copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. All advertising materials mentioning features or use of this software
///    must display the following acknowledgement:
///    "This product includes cryptographic software written by
///     Eric Young (eay@cryptsoft.com)"
///    The word 'cryptographic' can be left out if the rouines from the library
///    being used are not cryptographic related :-).
/// 4. If you include any Windows specific code (or a derivative thereof) from
///    the apps directory (application code) you must include an acknowledgement:
///    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
///
/// THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
///
/// The licence and distribution terms for any publically available version or
/// derivative of this code cannot be changed.  i.e. this code cannot simply be
/// copied and put under another distribution licence
/// [including the GNU Public Licence.]
///
///   File: sha1.cpp
///
/// Author: $author$
///   Date: 11/14/2014
///
/// Eric Young's implementation of SHA1 modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/hash/openssl/sha1.hpp"

#define ROTATE(a,n) (((a)<<(n))|(((a)&0xffffffff)>>(32-(n))))

#define K_00_19 0x5a827999L
#define K_20_39 0x6ed9eba1L
#define K_40_59 0x8f1bbcdcL
#define K_60_79 0xca62c1d6L

// As  pointed out by Wei Dai <weidai@eskimo.com>, F() below can be
// simplified to the code in F_00_19.  Wei attributes these optimisations
// to Peter Gutmann's SHS code, and he attributes it to Rich Schroeppel.
// #define F(x,y,z) (((x) & (y))  |  ((~(x)) & (z)))
// I've just become aware of another tweak to be made, again from Wei Dai,
// in F_40_59, (x&a)|(y&a) -> (x|y)&a
//
#define F_00_19(b,c,d) ((((c) ^ (d)) & (b)) ^ (d))
#define F_20_39(b,c,d) ((b) ^ (c) ^ (d))
#define F_40_59(b,c,d) (((b) & (c)) | (((b)|(c)) & (d)))
#define F_60_79(b,c,d) F_20_39(b,c,d)

#define UPDATE(a,i) \
    (a)=(X[(i)&0x0f]^X[((i)+2)&0x0f]^X[((i)+8)&0x0f]^X[((i)+13)&0x0f]); \
    X[(i)&0x0f]=(a)=ROTATE((a),1);

#define BODY_00_15(i,a,b,c,d,e,f) \
    (f)=X[i]+(e)+K_00_19+ROTATE((a),5)+F_00_19((b),(c),(d)); \
    (b)=ROTATE((b),30);

#define BODY_16_19(i,a,b,c,d,e,f) \
    UPDATE(f,i); \
    (f)+=(e)+K_00_19+ROTATE((a),5)+F_00_19((b),(c),(d)); \
    (b)=ROTATE((b),30);

#define BODY_20_39(i,a,b,c,d,e,f) \
    UPDATE(f,i); \
    (f)+=(e)+K_20_39+ROTATE((a),5)+F_20_39((b),(c),(d)); \
    (b)=ROTATE((b),30);

#define BODY_40_59(i,a,b,c,d,e,f) \
    UPDATE(f,i); \
    (f)+=(e)+K_40_59+ROTATE((a),5)+F_40_59((b),(c),(d)); \
    (b)=ROTATE((b),30);

#define BODY_60_79(i,a,b,c,d,e,f) \
    UPDATE(f,i); \
    (f)=X[(i)&0x0f]+(e)+K_60_79+ROTATE((a),5)+F_60_79((b),(c),(d)); \
    (b)=ROTATE((b),30);

namespace talas {
namespace crypto {
namespace hash {
namespace openssl {

///////////////////////////////////////////////////////////////////////
///  Class: sha1
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/// Start SHA accumulation.  Set bit count to 0 and buffer to mysterious
/// initialization constants.
///////////////////////////////////////////////////////////////////////
void sha1::initial() {
    m_A = 0x67452301L;
    m_B = 0xefcdab89L;
    m_C = 0x98badcfeL;
    m_D = 0x10325476L;
    m_E = 0xc3d2e1f0L;
    m_L = 0;
    m_H = 0;
}

///////////////////////////////////////////////////////////////////////
/// Final wrapup - pad to 64-byte boundary with the bit pattern
/// 1 0* (64-bit count of bits processed, MSB-first)
///////////////////////////////////////////////////////////////////////
void sha1::final() {
    unsigned count;
    uint8_t *p;

    // Compute number of bytes mod 64
    //
    count = (m_L >> 3) & 0x3F;

    // Set the first char of padding to 0x80.  This is safe since there is
    // always at least one byte free
    //
    p = m_in + count;
    *p++ = 0x80;

    // Bytes of padding needed to make 64 bytes
    //
    count = 64 - 1 - count;

    // Pad out to 56 mod 64
    //
    if (count < 8) {
        // Two lots of padding:  Pad the first block to 64 bytes
        //
        memset(p, 0, count);
        transform();

        // Now fill the next block with 56 bytes
        //
        memset(m_in, 0, 56);
    } else {
        // Pad block to 56 bytes
        //
        memset(p, 0, count - 8);
    }

    // Append length in bits and transform
    //
    U32ToMSB(m_in + 56, m_H);
    U32ToMSB(m_in + 60, m_L);
    transform();

    U32ToMSB(m_hash, m_A);
    U32ToMSB(m_hash + 4, m_B);
    U32ToMSB(m_hash + 8, m_C);
    U32ToMSB(m_hash + 12, m_D);
    U32ToMSB(m_hash + 16, m_E);
    initial();
}

///////////////////////////////////////////////////////////////////////
/// Update context to reflect the concatenation of another buffer
/// of bytes.
///////////////////////////////////////////////////////////////////////
void sha1::update(const uint8_t *in, size_t inlen) {
    uint32_t t;
    uint8_t *p;

    // Update bitcount
    //
    t = m_L;

    if ((m_L = (t + (inlen << 3)) & 0xffffffff) < t)
        // Carry from low to high
        //
        m_H++;

    m_H += inlen >> 29;

    // Bytes already in data
    //
    t = (t >> 3) & 0x3f;

    // Handle any leading odd-sized chunks
    //
    if (t) {
        p = m_in + t;
        t = 64 - t;

        if (inlen < t) {
            memcpy(p, in, inlen);
            return;
        }

        memcpy(p, in, t);
        transform();
        in += t;
        inlen -= t;
    }

    // Process data in 64-byte chunks
    //
    while (inlen >= 64) {
        memcpy(m_in, in, 64);
        transform();
        in += 64;
        inlen -= 64;
    }

    // Handle any remaining bytes of data.
    //
    memcpy(m_in, in, inlen);
}

///////////////////////////////////////////////////////////////////////
/// The core of the SHA algorithm, this alters an existing SHA hash to
/// reflect the addition of 16 longwords of new data. blocks
/// the data and converts bytes into longwords for this routine.
///////////////////////////////////////////////////////////////////////
void sha1::transform() {
    uint32_t A,B,C,D,E,T;
    uint32_t X[16];
    uint8_t *p;
    unsigned i;

    for (p=m_in, i=0; i<16; i++, p+=4)
        X[i] = MSBToU32(p);

    A = m_A;
    B = m_B;
    C = m_C;
    D = m_D;
    E = m_E;

    BODY_00_15( 0,A,B,C,D,E,T);
    BODY_00_15( 1,T,A,B,C,D,E);
    BODY_00_15( 2,E,T,A,B,C,D);
    BODY_00_15( 3,D,E,T,A,B,C);
    BODY_00_15( 4,C,D,E,T,A,B);
    BODY_00_15( 5,B,C,D,E,T,A);
    BODY_00_15( 6,A,B,C,D,E,T);
    BODY_00_15( 7,T,A,B,C,D,E);
    BODY_00_15( 8,E,T,A,B,C,D);
    BODY_00_15( 9,D,E,T,A,B,C);
    BODY_00_15(10,C,D,E,T,A,B);
    BODY_00_15(11,B,C,D,E,T,A);
    BODY_00_15(12,A,B,C,D,E,T);
    BODY_00_15(13,T,A,B,C,D,E);
    BODY_00_15(14,E,T,A,B,C,D);
    BODY_00_15(15,D,E,T,A,B,C);
    BODY_16_19(16,C,D,E,T,A,B);
    BODY_16_19(17,B,C,D,E,T,A);
    BODY_16_19(18,A,B,C,D,E,T);
    BODY_16_19(19,T,A,B,C,D,E);

    BODY_20_39(20,E,T,A,B,C,D);
    BODY_20_39(21,D,E,T,A,B,C);
    BODY_20_39(22,C,D,E,T,A,B);
    BODY_20_39(23,B,C,D,E,T,A);
    BODY_20_39(24,A,B,C,D,E,T);
    BODY_20_39(25,T,A,B,C,D,E);
    BODY_20_39(26,E,T,A,B,C,D);
    BODY_20_39(27,D,E,T,A,B,C);
    BODY_20_39(28,C,D,E,T,A,B);
    BODY_20_39(29,B,C,D,E,T,A);
    BODY_20_39(30,A,B,C,D,E,T);
    BODY_20_39(31,T,A,B,C,D,E);
    BODY_20_39(32,E,T,A,B,C,D);
    BODY_20_39(33,D,E,T,A,B,C);
    BODY_20_39(34,C,D,E,T,A,B);
    BODY_20_39(35,B,C,D,E,T,A);
    BODY_20_39(36,A,B,C,D,E,T);
    BODY_20_39(37,T,A,B,C,D,E);
    BODY_20_39(38,E,T,A,B,C,D);
    BODY_20_39(39,D,E,T,A,B,C);

    BODY_40_59(40,C,D,E,T,A,B);
    BODY_40_59(41,B,C,D,E,T,A);
    BODY_40_59(42,A,B,C,D,E,T);
    BODY_40_59(43,T,A,B,C,D,E);
    BODY_40_59(44,E,T,A,B,C,D);
    BODY_40_59(45,D,E,T,A,B,C);
    BODY_40_59(46,C,D,E,T,A,B);
    BODY_40_59(47,B,C,D,E,T,A);
    BODY_40_59(48,A,B,C,D,E,T);
    BODY_40_59(49,T,A,B,C,D,E);
    BODY_40_59(50,E,T,A,B,C,D);
    BODY_40_59(51,D,E,T,A,B,C);
    BODY_40_59(52,C,D,E,T,A,B);
    BODY_40_59(53,B,C,D,E,T,A);
    BODY_40_59(54,A,B,C,D,E,T);
    BODY_40_59(55,T,A,B,C,D,E);
    BODY_40_59(56,E,T,A,B,C,D);
    BODY_40_59(57,D,E,T,A,B,C);
    BODY_40_59(58,C,D,E,T,A,B);
    BODY_40_59(59,B,C,D,E,T,A);

    BODY_60_79(60,A,B,C,D,E,T);
    BODY_60_79(61,T,A,B,C,D,E);
    BODY_60_79(62,E,T,A,B,C,D);
    BODY_60_79(63,D,E,T,A,B,C);
    BODY_60_79(64,C,D,E,T,A,B);
    BODY_60_79(65,B,C,D,E,T,A);
    BODY_60_79(66,A,B,C,D,E,T);
    BODY_60_79(67,T,A,B,C,D,E);
    BODY_60_79(68,E,T,A,B,C,D);
    BODY_60_79(69,D,E,T,A,B,C);
    BODY_60_79(70,C,D,E,T,A,B);
    BODY_60_79(71,B,C,D,E,T,A);
    BODY_60_79(72,A,B,C,D,E,T);
    BODY_60_79(73,T,A,B,C,D,E);
    BODY_60_79(74,E,T,A,B,C,D);
    BODY_60_79(75,D,E,T,A,B,C);
    BODY_60_79(76,C,D,E,T,A,B);
    BODY_60_79(77,B,C,D,E,T,A);
    BODY_60_79(78,A,B,C,D,E,T);
    BODY_60_79(79,T,A,B,C,D,E);

    m_A += E;
    m_B += T;
    m_C += A;
    m_D += B;
    m_E += C;
}

} // namespace openssl
} // namespace hash 
} // namespace crypto 
} // namespace talas 
