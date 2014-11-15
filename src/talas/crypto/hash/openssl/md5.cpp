///////////////////////////////////////////////////////////////////////
/// This code has been heavily hacked by Tatu Ylonen <ylo@cs.hut.fi> to
/// make it compile on machines like Cray that don't have a 32 bit integer
/// type.
///
/// This code implements the MD5 message-digest algorithm.
/// The algorithm is due to Ron Rivest.  This code was
/// written by Colin Plumb in 1993, no copyright is claimed.
/// This code is in the public domain; do with it what you wish.
///
/// This software is provided by the author and contributors ``as is''
/// and any express or implied warranties, including, but not limited to,
/// the implied warranties of merchantability and fitness for a particular
/// purpose are disclaimed. In no event shall the author or contributors
/// be liable for any direct, indirect, incidental, special, exemplary,
/// or consequential damages (including, but not limited to, procurement
/// of substitute goods or services; loss of use, data, or profits; or
/// business interruption) however caused and on any theory of liability,
/// whether in contract, strict liability, or tort (including negligence
/// or otherwise) arising in any way out of the use of this software,
/// even if advised of the possibility of such damage.
///
///   File: md5.cpp
///
/// Author: $author$
///   Date: 11/14/2014
///
/// Colin Plumb's and Tatu Ylonen's implementation of MD5 modified to be
/// a C++ class implementation.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/hash/openssl/md5.hpp"

//
// The four core functions - F1 is optimized somewhat
//
// F1(x, y, z) (x & y | ~x & z)
//
#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

//
// This is the central step in the MD5 algorithm.
//
#define MD5STEP(f, w, x, y, z, data, s) \
    ( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

namespace talas {
namespace crypto {
namespace hash {
namespace openssl {

///////////////////////////////////////////////////////////////////////
///  Class: md5
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/// Start MD5 accumulation.  Set bit count to 0 and buffer to mysterious
/// initialization constants.
///////////////////////////////////////////////////////////////////////
void md5::initial() {
    m_A = 0x67452301;
    m_B = 0xefcdab89;
    m_C = 0x98badcfe;
    m_D = 0x10325476;
    m_L = 0;
    m_H = 0;
}

///////////////////////////////////////////////////////////////////////
/// Final wrapup - pad to 64-byte boundary with the bit pattern
/// 1 0* (64-bit count of bits processed, LSB-first)
///////////////////////////////////////////////////////////////////////
void md5::final() {
    unsigned count;
    uint8_t *p;

    // Compute number of bytes mod 64
    //
    count = (m_L >> 3) & 0x3F;

    // Set the first char of padding to 0x80.  This is safe
    // since there is always at least one byte free
    //
    p = m_in + count;
    *p++ = 0x80;

    // Bytes of padding needed to make 64 bytes
    //
    count = 64 - 1 - count;

    // Pad out to 56 mod 64
    //
    if (count < 8) {
        // Pad the first block to 64 bytes then transform
        //
        memset(p, 0, count);
        transform();

        // Now fill the next block with 56 bytes
        //
        memset(m_in, 0, 56);
    } else  {
        // Pad block to 56 bytes
        //
        memset(p, 0, count - 8);
    }

    // Append length in bits in lsb format and transform
    //
    U32ToLSB(m_in + 56, m_L);
    U32ToLSB(m_in + 60, m_H);
    transform();

    U32ToLSB(m_hash, m_A);
    U32ToLSB(m_hash + 4, m_B);
    U32ToLSB(m_hash + 8, m_C);
    U32ToLSB(m_hash + 12, m_D);
    initial();
}

///////////////////////////////////////////////////////////////////////
/// Update context to reflect the concatenation of another buffer
/// of bytes.
///////////////////////////////////////////////////////////////////////
void md5::update(const uint8_t *in, size_t inlen) {
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
/// The core of the MD5 algorithm, this alters an existing MD5 hash to
/// reflect the addition of 16 longwords of new data. Update blocks
/// the data and converts bytes into longwords for this routine.
///////////////////////////////////////////////////////////////////////
void md5::transform() {
    unsigned i;
    uint8_t *in;
    uint32_t a, b, c, d, x[16];

    for (in=m_in, i = 0; i < 16; i++, in+=4)
        x[i] = LSBToU32(in);

    a = m_A;
    b = m_B;
    c = m_C;
    d = m_D;

    MD5STEP(F1, a, b, c, d, x[0] + 0xd76aa478, 7);
    MD5STEP(F1, d, a, b, c, x[1] + 0xe8c7b756, 12);
    MD5STEP(F1, c, d, a, b, x[2] + 0x242070db, 17);
    MD5STEP(F1, b, c, d, a, x[3] + 0xc1bdceee, 22);
    MD5STEP(F1, a, b, c, d, x[4] + 0xf57c0faf, 7);
    MD5STEP(F1, d, a, b, c, x[5] + 0x4787c62a, 12);
    MD5STEP(F1, c, d, a, b, x[6] + 0xa8304613, 17);
    MD5STEP(F1, b, c, d, a, x[7] + 0xfd469501, 22);
    MD5STEP(F1, a, b, c, d, x[8] + 0x698098d8, 7);
    MD5STEP(F1, d, a, b, c, x[9] + 0x8b44f7af, 12);
    MD5STEP(F1, c, d, a, b, x[10] + 0xffff5bb1, 17);
    MD5STEP(F1, b, c, d, a, x[11] + 0x895cd7be, 22);
    MD5STEP(F1, a, b, c, d, x[12] + 0x6b901122, 7);
    MD5STEP(F1, d, a, b, c, x[13] + 0xfd987193, 12);
    MD5STEP(F1, c, d, a, b, x[14] + 0xa679438e, 17);
    MD5STEP(F1, b, c, d, a, x[15] + 0x49b40821, 22);

    MD5STEP(F2, a, b, c, d, x[1] + 0xf61e2562, 5);
    MD5STEP(F2, d, a, b, c, x[6] + 0xc040b340, 9);
    MD5STEP(F2, c, d, a, b, x[11] + 0x265e5a51, 14);
    MD5STEP(F2, b, c, d, a, x[0] + 0xe9b6c7aa, 20);
    MD5STEP(F2, a, b, c, d, x[5] + 0xd62f105d, 5);
    MD5STEP(F2, d, a, b, c, x[10] + 0x02441453, 9);
    MD5STEP(F2, c, d, a, b, x[15] + 0xd8a1e681, 14);
    MD5STEP(F2, b, c, d, a, x[4] + 0xe7d3fbc8, 20);
    MD5STEP(F2, a, b, c, d, x[9] + 0x21e1cde6, 5);
    MD5STEP(F2, d, a, b, c, x[14] + 0xc33707d6, 9);
    MD5STEP(F2, c, d, a, b, x[3] + 0xf4d50d87, 14);
    MD5STEP(F2, b, c, d, a, x[8] + 0x455a14ed, 20);
    MD5STEP(F2, a, b, c, d, x[13] + 0xa9e3e905, 5);
    MD5STEP(F2, d, a, b, c, x[2] + 0xfcefa3f8, 9);
    MD5STEP(F2, c, d, a, b, x[7] + 0x676f02d9, 14);
    MD5STEP(F2, b, c, d, a, x[12] + 0x8d2a4c8a, 20);

    MD5STEP(F3, a, b, c, d, x[5] + 0xfffa3942, 4);
    MD5STEP(F3, d, a, b, c, x[8] + 0x8771f681, 11);
    MD5STEP(F3, c, d, a, b, x[11] + 0x6d9d6122, 16);
    MD5STEP(F3, b, c, d, a, x[14] + 0xfde5380c, 23);
    MD5STEP(F3, a, b, c, d, x[1] + 0xa4beea44, 4);
    MD5STEP(F3, d, a, b, c, x[4] + 0x4bdecfa9, 11);
    MD5STEP(F3, c, d, a, b, x[7] + 0xf6bb4b60, 16);
    MD5STEP(F3, b, c, d, a, x[10] + 0xbebfbc70, 23);
    MD5STEP(F3, a, b, c, d, x[13] + 0x289b7ec6, 4);
    MD5STEP(F3, d, a, b, c, x[0] + 0xeaa127fa, 11);
    MD5STEP(F3, c, d, a, b, x[3] + 0xd4ef3085, 16);
    MD5STEP(F3, b, c, d, a, x[6] + 0x04881d05, 23);
    MD5STEP(F3, a, b, c, d, x[9] + 0xd9d4d039, 4);
    MD5STEP(F3, d, a, b, c, x[12] + 0xe6db99e5, 11);
    MD5STEP(F3, c, d, a, b, x[15] + 0x1fa27cf8, 16);
    MD5STEP(F3, b, c, d, a, x[2] + 0xc4ac5665, 23);

    MD5STEP(F4, a, b, c, d, x[0] + 0xf4292244, 6);
    MD5STEP(F4, d, a, b, c, x[7] + 0x432aff97, 10);
    MD5STEP(F4, c, d, a, b, x[14] + 0xab9423a7, 15);
    MD5STEP(F4, b, c, d, a, x[5] + 0xfc93a039, 21);
    MD5STEP(F4, a, b, c, d, x[12] + 0x655b59c3, 6);
    MD5STEP(F4, d, a, b, c, x[3] + 0x8f0ccc92, 10);
    MD5STEP(F4, c, d, a, b, x[10] + 0xffeff47d, 15);
    MD5STEP(F4, b, c, d, a, x[1] + 0x85845dd1, 21);
    MD5STEP(F4, a, b, c, d, x[8] + 0x6fa87e4f, 6);
    MD5STEP(F4, d, a, b, c, x[15] + 0xfe2ce6e0, 10);
    MD5STEP(F4, c, d, a, b, x[6] + 0xa3014314, 15);
    MD5STEP(F4, b, c, d, a, x[13] + 0x4e0811a1, 21);
    MD5STEP(F4, a, b, c, d, x[4] + 0xf7537e82, 6);
    MD5STEP(F4, d, a, b, c, x[11] + 0xbd3af235, 10);
    MD5STEP(F4, c, d, a, b, x[2] + 0x2ad7d2bb, 15);
    MD5STEP(F4, b, c, d, a, x[9] + 0xeb86d391, 21);

    m_A += a;
    m_B += b;
    m_C += c;
    m_D += d;
}

} // namespace openssl
} // namespace hash 
} // namespace crypto 
} // namespace talas 
