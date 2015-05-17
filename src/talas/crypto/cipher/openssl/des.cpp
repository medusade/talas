///////////////////////////////////////////////////////////////////////
/// Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
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
///   File: des.cpp
///
/// Author: $author$
///   Date: 5/16/2015
///
/// Eric Young's implementation of DES and 3DES modified to be C++ class
/// implementations.
///////////////////////////////////////////////////////////////////////
#include "talas/crypto/cipher/openssl/des.hpp"
#include "talas/crypto/cipher/openssl/des_constants.cpp"

namespace talas {
namespace crypto {
namespace cipher {
namespace openssl {

///////////////////////////////////////////////////////////////////////
///  Class: des
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ssize_t des::initialize
(const void* key, size_t keylen,
 const void* iv, size_t ivlen,
 const void* padd, size_t paddlen) {
    ssize_t length = KEYMAX+IVMAX;
    const uint8_t* keyBytes;
    const uint8_t* ivBytes;
    const uint8_t* paddBytes;

    if (!(keyBytes = ((const uint8_t*)key)))
        return 0;

    if (KEYMIN > keylen)
        return 0;

    if (KEYMAX < keylen)
        return 0;

    CopyRepeat(m_key, KEYMAX, keyBytes, keylen);

    if ((ivBytes = ((const uint8_t*)iv))) {
        if (IVMIN > ivlen)
            return 0;

        if (IVMAX < ivlen)
            return 0;

        CopyRepeat(m_iv, IVMAX, ivBytes, ivlen);
    } else {
        if (IVMAX < keylen)
            keylen = IVMAX;

        CopyRepeat(m_iv, IVMAX, keyBytes, keylen);
    }

    Bytes::Set(m_padd, 0, BLOCKSIZE);

    if ((paddBytes = ((const uint8_t*)padd))) {
        if (BLOCKSIZE < paddlen)
            paddlen = BLOCKSIZE;

        if (0 < paddlen)
            CopyRepeat(m_padd, BLOCKSIZE, paddBytes, paddlen);
    }

    InitSchedule(m_schedule[0], m_key);
    return length;
}

void des::clear() {
    Bytes::Set(m_key, 0, sizeof(m_key));
    Bytes::Set(m_iv, 0, sizeof(m_iv));
    Bytes::Set(m_padd, 0, sizeof(m_padd));
    Bytes::Set(m_schedule, 0, sizeof(m_schedule));
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ssize_t des::encrypt(void* out, size_t outsize, const void* in, size_t inlen) {
    tBlock block;
    ssize_t outlen,size;
    uint8_t* outBytes;
    const uint8_t* inBytes;

    if (!(outBytes = ((uint8_t*)out))
        || !(inBytes = ((const uint8_t*)in)))
        return 0;

    outlen = ((inlen+BLOCKSIZE-1)/BLOCKSIZE)*BLOCKSIZE;

    if (outsize < outlen)
        return 0;

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

ssize_t des::decrypt(void* out, size_t outsize, const void* in, size_t inlen) {
    tBlock block;
    ssize_t outlen,size;
    uint8_t* outBytes;
    const uint8_t* inBytes;

    if (!(outBytes = ((uint8_t*)out))
        || !(inBytes = ((const uint8_t*)in)))
        return 0;

    outlen = ((inlen+BLOCKSIZE-1)/BLOCKSIZE)*BLOCKSIZE;

    if (outsize < outlen)
        return 0;

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
void des::InitSchedule(tSchedule schedule, const tBlock key) {
    uint32_t c,d,t,s,t2,*sch;
    unsigned i,shift;

    c = LSBToU32(key);
    d = LSBToU32(key+4);

    /* I now do it in 47 simple operations :-)
     * Thanks to John Fletcher (john_fletcher@lccmail.ocf.llnl.gov)
     * for the inspiration. :-)
     */
    PERM_OP (d,c,t,4,0x0f0f0f0fL);
    HPERM_OP(c,t,-2,0xcccc0000L);
    HPERM_OP(d,t,-2,0xcccc0000L);
    PERM_OP (d,c,t,1,0x55555555L);
    PERM_OP (c,d,t,8,0x00ff00ffL);
    PERM_OP (d,c,t,1,0x55555555L);
    d=    (((d&0x000000ffL)<<16L)| (d&0x0000ff00L)     |
         ((d&0x00ff0000L)>>16L)|((c&0xf0000000L)>>4L));
    c&=0x0fffffffL;

    sch=schedule;
    shift=0x7efc;
    for (i=0; i<16; i++) {
        if (shift & 1) {
            c=((c>>2L)|(c<<26L));
            d=((d>>2L)|(d<<26L));
        } else {
            c=((c>>1L)|(c<<27L));
            d=((d>>1L)|(d<<27L));
        }
        c&=0x0fffffffL;
        d&=0x0fffffffL;
        /* could be a few less shifts but I am to lazy at this
         * point in time to investigate
         */
        s=  m_setkey[0][(c)&0x3f]|
            m_setkey[1][((c>> 6)&0x03)|((c>> 7L)&0x3c)]|
            m_setkey[2][((c>>13)&0x0f)|((c>>14L)&0x30)]|
            m_setkey[3][((c>>20)&0x01)|((c>>21L)&0x06)|((c>>22L)&0x38)];

        t=  m_setkey[4][(d)&0x3f]|
            m_setkey[5][((d>>7L)&0x03)|((d>> 8L)&0x3c)]|
            m_setkey[6][(d>>15L)&0x3f]|
            m_setkey[7][((d>>21L)&0x0f)|((d>>22L)&0x30)];

        /* table contained 0213 4657
         */
        t2=((t<<16L)|(s&0x0000ffffL))&0xffffffffL;
        *(sch++)=ROTATE(t2,30)&0xffffffffL;

        t2=((s>>16L)|(t&0xffff0000L));
        *(sch++)=ROTATE(t2,26)&0xffffffffL;

        shift>>=1;
    }
}

void des::Encode(uint32_t data[2], tSchedule schedule) {
    uint32_t l,r,t,u,*s;

    r=data[0];
    l=data[1];
    s=(uint32_t*)schedule;

    /* Things have been modified so that the initial rotate is
     * done outside the loop.  This required the
     * des_SPtrans values in sp.h to be rotated 1 bit to the right.
     * One perl script later and things have a 5% speed up on a sparc2.
     * Thanks to Richard Outerbridge <71755.204@CompuServe.COM>
     * for pointing this out.
     */
    /* clear the top bits on machines with 8byte longs
     * shift left by 2
     */
    r=ROTATE(r,29)&0xffffffffL;
    l=ROTATE(l,29)&0xffffffffL;

    /* I don't know if it is worth the effort of loop unrolling the
     * inner loop.
     */
#if defined(DES_NO_UNROLL)
    for (int i=0; i<32; i+=8) {
        D_ENCRYPT(l,r,i+0 ,u,t,s); /*  1 */
        D_ENCRYPT(r,l,i+2 ,u,t,s); /*  2 */
        D_ENCRYPT(l,r,i+4 ,u,t,s); /*  3 */
        D_ENCRYPT(r,l,i+6 ,u,t,s); /*  4 */
    }
#else /* defined(DES_NO_UNROLL) */
    /* but...
     */
    D_ENCRYPT(l,r, 0, u,t,s); /*  1 */
    D_ENCRYPT(r,l, 2, u,t,s); /*  2 */
    D_ENCRYPT(l,r, 4, u,t,s); /*  3 */
    D_ENCRYPT(r,l, 6, u,t,s); /*  4 */
    D_ENCRYPT(l,r, 8, u,t,s); /*  5 */
    D_ENCRYPT(r,l,10, u,t,s); /*  6 */
    D_ENCRYPT(l,r,12, u,t,s); /*  7 */
    D_ENCRYPT(r,l,14, u,t,s); /*  8 */
    D_ENCRYPT(l,r,16, u,t,s); /*  9 */
    D_ENCRYPT(r,l,18, u,t,s); /*  10 */
    D_ENCRYPT(l,r,20, u,t,s); /*  11 */
    D_ENCRYPT(r,l,22, u,t,s); /*  12 */
    D_ENCRYPT(l,r,24, u,t,s); /*  13 */
    D_ENCRYPT(r,l,26, u,t,s); /*  14 */
    D_ENCRYPT(l,r,28, u,t,s); /*  15 */
    D_ENCRYPT(r,l,30, u,t,s); /*  16 */
#endif /* defined(DES_NO_UNROLL) */

    /* rotate and clear the top bits on machines with 8byte longs
     */
    l=ROTATE(l,3)&0xffffffffL;
    r=ROTATE(r,3)&0xffffffffL;

    data[0]=l;
    data[1]=r;
    l=r=t=u=0;
}

void des::Decode(uint32_t data[2], tSchedule schedule) {
    uint32_t l,r,t,u,*s;

    r=data[0];
    l=data[1];
    s=(uint32_t*)schedule;

    /* Things have been modified so that the initial rotate is
     * done outside the loop.  This required the
     * des_SPtrans values in sp.h to be rotated 1 bit to the right.
     * One perl script later and things have a 5% speed up on a sparc2.
     * Thanks to Richard Outerbridge <71755.204@CompuServe.COM>
     * for pointing this out.
     */
    /* clear the top bits on machines with 8byte longs
     * shift left by 2
     */
    r=ROTATE(r,29)&0xffffffffL;
    l=ROTATE(l,29)&0xffffffffL;

    /* I don't know if it is worth the effort of loop unrolling the
     * inner loop.
     */
#if defined(DES_NO_UNROLL)
    for (int i=30; i>0; i-=8) {
        D_ENCRYPT(l,r,i-0 ,u,t,s); /* 16 */
        D_ENCRYPT(r,l,i-2 ,u,t,s); /* 15 */
        D_ENCRYPT(l,r,i-4 ,u,t,s); /* 14 */
        D_ENCRYPT(r,l,i-6 ,u,t,s); /* 13 */
    }
#else /* defined(DES_NO_UNROLL) */
    /* but...
     */
    D_ENCRYPT(l,r,30 ,u,t,s); /* 16 */
    D_ENCRYPT(r,l,28 ,u,t,s); /* 15 */
    D_ENCRYPT(l,r,26 ,u,t,s); /* 14 */
    D_ENCRYPT(r,l,24 ,u,t,s); /* 13 */
    D_ENCRYPT(l,r,22 ,u,t,s); /* 12 */
    D_ENCRYPT(r,l,20 ,u,t,s); /* 11 */
    D_ENCRYPT(l,r,18 ,u,t,s); /* 10 */
    D_ENCRYPT(r,l,16 ,u,t,s); /*  9 */
    D_ENCRYPT(l,r,14 ,u,t,s); /*  8 */
    D_ENCRYPT(r,l,12 ,u,t,s); /*  7 */
    D_ENCRYPT(l,r,10 ,u,t,s); /*  6 */
    D_ENCRYPT(r,l, 8 ,u,t,s); /*  5 */
    D_ENCRYPT(l,r, 6 ,u,t,s); /*  4 */
    D_ENCRYPT(r,l, 4 ,u,t,s); /*  3 */
    D_ENCRYPT(l,r, 2 ,u,t,s); /*  2 */
    D_ENCRYPT(r,l, 0 ,u,t,s); /*  1 */
#endif /* defined(DES_NO_UNROLL) */

    /* rotate and clear the top bits on machines with 8byte longs
     */
    l=ROTATE(l,3)&0xffffffffL;
    r=ROTATE(r,3)&0xffffffffL;

    data[0]=l;
    data[1]=r;
    l=r=t=u=0;
}

void des::EncryptBlock(tBlock out, const tBlock in) {
    uint32_t l,r,t,u,data[2];

    r = LSBToU32(in);
    l = LSBToU32(in+4);
    t = LSBToU32(m_iv);
    u = LSBToU32(m_iv+4);
    r^=t;
    l^=u;
    IP(r,l,t);
    data[0]=r;
    data[1]=l;
    Encode(data,m_schedule[0]);
    l=data[0];
    r=data[1];
    FP(r,l,t);
    U32ToLSB(m_iv,l);
    U32ToLSB(m_iv+4,r);
    U32ToLSB(out,l);
    U32ToLSB(out+4,r);
    l=r=t=u=0;
}

void des::DecryptBlock(tBlock out, const tBlock in) {
    uint32_t l,r,t,u,data[2];

    r = LSBToU32(in);
    l = LSBToU32(in+4);
    IP(r,l,t);
    data[0]=r;
    data[1]=l;
    Decode(data,m_schedule[0]);
    l=data[0];
    r=data[1];
    FP(r,l,t);
    t = LSBToU32(m_iv);
    u = LSBToU32(m_iv+4);
    l^=t;
    r^=u;
    Copy8(m_iv,in);
    U32ToLSB(out,l);
    U32ToLSB(out+4,r);
    l=r=t=u=0;
}

///////////////////////////////////////////////////////////////////////
///  Class: des3
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ssize_t des3::initialize
(const void* key, size_t keylen,
 const void* iv, size_t ivlen,
 const void* padd, size_t paddlen) {
    ssize_t length = KEYMAX+IVMAX;
    const uint8_t* keyBytes;
    const uint8_t* ivBytes;
    const uint8_t* paddBytes;

    if (!(keyBytes = ((const uint8_t*)key)))
        return 0;

    if (KEYMIN > keylen)
        return 0;

    if (KEYMAX < keylen)
        return 0;

    CopyRepeat(m_key, KEYMAX, keyBytes, keylen);

    if ((ivBytes = ((const uint8_t*)iv))) {
        if (IVMIN > ivlen)
            return 0;

        if (IVMAX < ivlen)
            return 0;

        CopyRepeat(m_iv, IVMAX, ivBytes, ivlen);
    } else {
        if (IVMAX < keylen)
            keylen = IVMAX;

        CopyRepeat(m_iv, IVMAX, keyBytes, keylen);
    }

    Bytes::Set(m_padd, 0, BLOCKSIZE);

    if ((paddBytes = ((const uint8_t*)padd))) {
        if (BLOCKSIZE < paddlen)
            paddlen = BLOCKSIZE;

        if (0 < paddlen)
            CopyRepeat(m_padd, BLOCKSIZE, paddBytes, paddlen);
    }

    InitSchedule(m_schedule[0], m_key);
    InitSchedule(m_schedule[1], m_key+8);
    InitSchedule(m_schedule[2], m_key+16);
    return length;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void des3::EncryptBlock(tBlock out, const tBlock in) {
    uint32_t l,r,t,u,data[2];

    l = LSBToU32(in);
    r = LSBToU32(in+4);
    t = LSBToU32(m_iv);
    u = LSBToU32(m_iv+4);
    l^=t;
    r^=u;
    IP(l,r,t);
    data[0]=l;
    data[1]=r;
    Encode(data,m_schedule[0]);
    Decode(data,m_schedule[1]);
    Encode(data,m_schedule[2]);
    l=data[0];
    r=data[1];
    FP(r,l,t);
    U32ToLSB(m_iv,l);
    U32ToLSB(m_iv+4,r);
    U32ToLSB(out,l);
    U32ToLSB(out+4,r);
    l=r=t=u=0;
}

void des3::DecryptBlock(tBlock out, const tBlock in) {
    uint32_t l,r,t,u,data[2];

    l = LSBToU32(in);
    r = LSBToU32(in+4);
    IP(l,r,t);
    data[0]=l;
    data[1]=r;
    Decode(data,m_schedule[2]);
    Encode(data,m_schedule[1]);
    Decode(data,m_schedule[0]);
    l=data[0];
    r=data[1];
    FP(r,l,t);
    t = LSBToU32(m_iv);
    u = LSBToU32(m_iv+4);
    l^=t;
    r^=u;
    Copy8(m_iv,in);
    U32ToLSB(out,l);
    U32ToLSB(out+4,r);
    l=r=t=u=0;
}

} // namespace openssl
} // namespace cipher 
} // namespace crypto 
} // namespace talas 

