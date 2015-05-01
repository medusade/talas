///////////////////////////////////////////////////////////////////////
/// FIPS-197 compliant AES implementation
///
/// Copyright (C) 2006-2007  Christophe Devine
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
///
/// The AES block cipher was designed by Vincent Rijmen and Joan Daemen.
///
/// http://csrc.nist.gov/encryption/aes/rijndael/Rijndael.pdf
/// http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
///
///   File: aes.cpp
///
/// Author: $author$
///   Date: 4/30/2015
///
/// Christophe Devine's implementation of AES modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/cipher/devine/aes.hpp"
#include "talas/crypto/cipher/devine/aes_constants.cpp"

namespace talas {
namespace crypto {
namespace cipher {
namespace devine {

///////////////////////////////////////////////////////////////////////
///  Class: aes
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ssize_t aes::initialize
(const void* key, size_t keylen,
 const void* iv, size_t ivlen,
 const void* padd, size_t paddlen) {
    ssize_t length = IVMAX;
    const uint8_t* keyBytes;
    const uint8_t* ivBytes;
    const uint8_t* paddBytes;

    if (!(keyBytes = ((const uint8_t*)key)))
        return 0;

    if (0 > keylen)
        keylen = Bytes::Count(key);

    if (KEYMIN > keylen)
        return -ERROR_KEY_SIZE_UNDER;

    if (KEYMAX < keylen)
        return -ERROR_KEY_SIZE_OVER;

    CopyRepeat(m_key, KEYMAX, keyBytes, keylen);

    m_keysize = KEYMIN;

    while (m_keysize < ((unsigned)keylen))
        m_keysize += KEYINC;

    length += m_keysize;

    if ((ivBytes = ((const uint8_t*)iv))) {
        if (0 > ivlen)
            ivlen = Bytes::Count(ivBytes);

        if (IVMIN > ivlen)
            return -ERROR_IV_SIZE_UNDER;

        if (IVMAX < ivlen)
            return -ERROR_IV_SIZE_OVER;

        CopyRepeat(m_iv, IVMAX, ivBytes, ivlen);
    } else {
        if (IVMAX < keylen)
            keylen = IVMAX;

        CopyRepeat(m_iv, IVMAX, keyBytes, keylen);
    }

    Bytes::Set(m_padd, 0, BLOCKSIZE);

    if ((paddBytes = ((const uint8_t*)padd))) {
        if (0 > paddlen) {
            if (BLOCKSIZE < (paddlen = Bytes::Count(paddBytes)))
                paddlen = BLOCKSIZE;
        }
        if (0 < paddlen)
            CopyRepeat(m_padd, BLOCKSIZE, paddBytes, paddlen);
    }
    return length;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ssize_t aes::encrypt
(void* out, size_t outsize, const void* in, size_t inlen) {
    tBlock block;
    ssize_t outlen, size;
    uint8_t* outBytes;
    const uint8_t* inBytes;

    if (!(outBytes = ((uint8_t*)out))
        || !(inBytes = ((const uint8_t*)in))
        || !(inlen))
        return 0;

    outlen = ((inlen+BLOCKSIZE-1)/BLOCKSIZE)*BLOCKSIZE;

    if (outsize < outlen)
        return -ERROR_OUT_SIZE_UNDER;

    if (0 > (size = InitEncryptKeySchedule(m_key, m_keysize)))
        return size;

    for (outlen=0; inlen>0; inlen-=size, outlen+=BLOCKSIZE) {
        if ((size=inlen) >= BLOCKSIZE) {
            size=BLOCKSIZE;
            EncryptBlock(outBytes+outlen, inBytes+outlen);
        } else {
            Bytes::Copy(block, inBytes+outlen, size);
            Bytes::Copy(block+size, m_padd, BLOCKSIZE-size);
            EncryptBlock(outBytes+outlen, block);
        }
    }
    return outlen;
}

ssize_t aes::decrypt
(void* out, size_t outsize, const void* in, size_t inlen) {
    tBlock block;
    size_t outlen, size;
    uint8_t* outBytes;
    const uint8_t* inBytes;

    if (!(outBytes = ((uint8_t*)out))
        || !(inBytes = ((const uint8_t*)in))
        || !(inlen))
        return 0;

    outlen = ((inlen+BLOCKSIZE-1)/BLOCKSIZE)*BLOCKSIZE;

    if (outsize < outlen)
        return -ERROR_OUT_SIZE_UNDER;

    if (0 > (size = InitDecryptKeySchedule(m_key, m_keysize)))
        return size;

    for (outlen=0; inlen>0; inlen-=size, outlen+=BLOCKSIZE) {
        if ((size=inlen) >= BLOCKSIZE) {
            size=BLOCKSIZE;
            DecryptBlock(outBytes+outlen, inBytes+outlen);
        } else {
            Bytes::Copy(block, inBytes+outlen, size);
            Bytes::Copy(block+size, m_padd, BLOCKSIZE-size);
            DecryptBlock(outBytes+outlen, block);
        }
    }
    return outlen;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void aes::ClearKey() {
    m_keysize = 0;
    Bytes::Set(m_key, 0, sizeof(m_key));
    Bytes::Set(m_iv, 0, sizeof(m_iv));
    Bytes::Set(m_padd, 0, sizeof(m_padd));
}
ssize_t aes::InitDecryptKeySchedule
(const uint8_t* key, unsigned keysize) {
    unsigned i, j;
    uint32_t *RK;
    uint32_t *SK;
    aes_base aes;
    ssize_t size;

    if (0 > (size = aes.InitEncryptKeySchedule(key, keysize)))
        return size;

    RK = (rk = buf);
    SK = aes.rk + (nr = aes.nr)*4;

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

    for( i = nr, SK -= 8; i > 1; i--, SK -= 8 ) {
        for( j = 0; j < 4; j++, SK++ ) {
            *RK++ = RT0[ FSb[ ( *SK       ) & 0xFF ] ] ^
                    RT1[ FSb[ ( *SK >>  8 ) & 0xFF ] ] ^
                    RT2[ FSb[ ( *SK >> 16 ) & 0xFF ] ] ^
                    RT3[ FSb[ ( *SK >> 24 ) & 0xFF ] ];
        }
    }

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

    return keysize;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void aes::EncryptBlock
(tBlock output, const tBlock input) {
    unsigned i;

    for( i = 0; i < 16; i++ )
        output[i] = ( input[i] ^ m_iv[i] );

    EncodeBlock(output, output);

    Copy8(m_iv, output);
    Copy8(m_iv+8, output+8);
}

void aes::DecryptBlock
(tBlock output, const tBlock input) {
    unsigned i;
    tBlock temp;

    Copy8(temp, input);
    Copy8(temp+8, input+8);

    DecodeBlock(output, input);

    for( i = 0; i < 16; i++ )
        output[i] = ( output[i] ^ m_iv[i] );

    Copy8(m_iv, temp);
    Copy8(m_iv+8, temp+8);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void aes::EncodeBlock
(tBlock output, const tBlock input) {
    unsigned i;
    uint32_t *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

    RK = rk;

    X0 = LSBToU32(input)^(*RK++);
    X1 = LSBToU32(input+4)^(*RK++);
    X2 = LSBToU32(input+8)^(*RK++);
    X3 = LSBToU32(input+12)^(*RK++);

    for( i = (nr >> 1); i > 1; i-- ) {
        AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
        AES_FROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
    }

    AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

    X0 = *RK++ ^ ( FSb[ ( Y0       ) & 0xFF ]       ) ^
                 ( FSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( FSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                 ( FSb[ ( Y3 >> 24 ) & 0xFF ] << 24 );

    X1 = *RK++ ^ ( FSb[ ( Y1       ) & 0xFF ]       ) ^
                 ( FSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( FSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                 ( FSb[ ( Y0 >> 24 ) & 0xFF ] << 24 );

    X2 = *RK++ ^ ( FSb[ ( Y2       ) & 0xFF ]       ) ^
                 ( FSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( FSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                 ( FSb[ ( Y1 >> 24 ) & 0xFF ] << 24 );

    X3 = *RK++ ^ ( FSb[ ( Y3       ) & 0xFF ]       ) ^
                 ( FSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( FSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                 ( FSb[ ( Y2 >> 24 ) & 0xFF ] << 24 );

    U32ToLSB(output, X0);
    U32ToLSB(output+4, X1);
    U32ToLSB(output+8, X2);
    U32ToLSB(output+12, X3);
}

void aes::DecodeBlock
(tBlock output, const tBlock input) {
    unsigned i;
    uint32_t *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

    RK = rk;

    X0 = LSBToU32(input)^(*RK++);
    X1 = LSBToU32(input+4)^(*RK++);
    X2 = LSBToU32(input+8)^(*RK++);
    X3 = LSBToU32(input+12)^(*RK++);

    for( i = (nr >> 1); i > 1; i-- ) {
        AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
        AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
    }

    AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

    X0 = *RK++ ^ ( RSb[ ( Y0       ) & 0xFF ]       ) ^
                 ( RSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( RSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                 ( RSb[ ( Y1 >> 24 ) & 0xFF ] << 24 );

    X1 = *RK++ ^ ( RSb[ ( Y1       ) & 0xFF ]       ) ^
                 ( RSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( RSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                 ( RSb[ ( Y2 >> 24 ) & 0xFF ] << 24 );

    X2 = *RK++ ^ ( RSb[ ( Y2       ) & 0xFF ]       ) ^
                 ( RSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( RSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                 ( RSb[ ( Y3 >> 24 ) & 0xFF ] << 24 );

    X3 = *RK++ ^ ( RSb[ ( Y3       ) & 0xFF ]       ) ^
                 ( RSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                 ( RSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                 ( RSb[ ( Y0 >> 24 ) & 0xFF ] << 24 );

    U32ToLSB(output, X0);
    U32ToLSB(output+4, X1);
    U32ToLSB(output+8, X2);
    U32ToLSB(output+12, X3);
}

///////////////////////////////////////////////////////////////////////
///  Class: aes_base
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void aes_base::ClearKeySchedule() {
    nr = 0;
    rk = 0;
    Bytes::Set(buf, 0, sizeof(buf));
}
ssize_t aes_base::InitEncryptKeySchedule(const uint8_t* key, unsigned keysize) {
    unsigned i,j;
    uint32_t *RK;

    switch( keysize ) {
        case 16:
            nr = 10;
            break;
        case 24:
            nr = 12;
            break;
        case 32:
            nr = 14;
            break;
        default:
            return -ERROR_KEY_SIZE;
    }

    RK = (rk = buf);

    for( j = 0, i = 0; i < (keysize >> 2); i++, j+=4 )
        RK[i] = LSBToU32(key+j);

    switch( nr ) {
        case 10:
            for( i = 0; i < 10; i++, RK += 4 ) {
                RK[4]  = RK[0] ^ RCON[i] ^
                    ( FSb[ ( RK[3] >>  8 ) & 0xFF ]       ) ^
                    ( FSb[ ( RK[3] >> 16 ) & 0xFF ] <<  8 ) ^
                    ( FSb[ ( RK[3] >> 24 ) & 0xFF ] << 16 ) ^
                    ( FSb[ ( RK[3]       ) & 0xFF ] << 24 );

                RK[5]  = RK[1] ^ RK[4];
                RK[6]  = RK[2] ^ RK[5];
                RK[7]  = RK[3] ^ RK[6];
            }
            break;

        case 12:
            for( i = 0; i < 8; i++, RK += 6 ) {
                RK[6]  = RK[0] ^ RCON[i] ^
                    ( FSb[ ( RK[5] >>  8 ) & 0xFF ]       ) ^
                    ( FSb[ ( RK[5] >> 16 ) & 0xFF ] <<  8 ) ^
                    ( FSb[ ( RK[5] >> 24 ) & 0xFF ] << 16 ) ^
                    ( FSb[ ( RK[5]       ) & 0xFF ] << 24 );

                RK[7]  = RK[1] ^ RK[6];
                RK[8]  = RK[2] ^ RK[7];
                RK[9]  = RK[3] ^ RK[8];
                RK[10] = RK[4] ^ RK[9];
                RK[11] = RK[5] ^ RK[10];
            }
            break;

        case 14:
            for( i = 0; i < 7; i++, RK += 8 ) {
                RK[8]  = RK[0] ^ RCON[i] ^
                    ( FSb[ ( RK[7] >>  8 ) & 0xFF ]       ) ^
                    ( FSb[ ( RK[7] >> 16 ) & 0xFF ] <<  8 ) ^
                    ( FSb[ ( RK[7] >> 24 ) & 0xFF ] << 16 ) ^
                    ( FSb[ ( RK[7]       ) & 0xFF ] << 24 );

                RK[9]  = RK[1] ^ RK[8];
                RK[10] = RK[2] ^ RK[9];
                RK[11] = RK[3] ^ RK[10];

                RK[12] = RK[4] ^
                    ( FSb[ ( RK[11]       ) & 0xFF ]       ) ^
                    ( FSb[ ( RK[11] >>  8 ) & 0xFF ] <<  8 ) ^
                    ( FSb[ ( RK[11] >> 16 ) & 0xFF ] << 16 ) ^
                    ( FSb[ ( RK[11] >> 24 ) & 0xFF ] << 24 );

                RK[13] = RK[5] ^ RK[12];
                RK[14] = RK[6] ^ RK[13];
                RK[15] = RK[7] ^ RK[14];
            }
            break;

        default:
            return -ERROR_KEY_SIZE;
    }
    return keysize;
}

} // namespace devine
} // namespace cipher 
} // namespace crypto 
} // namespace talas 
