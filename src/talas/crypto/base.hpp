///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: base.hpp
///
/// Author: $author$
///   Date: 11/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_BASE_HPP
#define _TALAS_CRYPTO_BASE_HPP

#include "talas/base/base.hpp"

namespace talas {
namespace crypto {

typedef int error;
enum {
    error_none = 0,

    error_failed,
    error_not_implemented,
    error_invalid_parameter,
    error_invalid_parameter_size,

    next_error,
    first_error = error_none,
    last_error = (next_error - 1)
};

typedef talas::implement_base base_implements;
///////////////////////////////////////////////////////////////////////
///  Class: implement_baset
///////////////////////////////////////////////////////////////////////
template
<class TImplements = implement_base>

class _EXPORT_CLASS implement_baset: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline UINT64 MSBToU64(const BYTE* bytes) const {
        UINT64 value = (((((((((((((((UINT64)bytes[0])<<8) | bytes[1])<<8) | bytes[2])<<8) | bytes[3])<<8) | bytes[4])<<8) | bytes[5])<<8) | bytes[6])<<8) | bytes[7];
        return value;
    }
    inline BYTE* U64ToMSB(BYTE* bytes, UINT64 value) const {
        *(bytes+=7)=(BYTE)(value & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    inline UINT64 LSBToU64(const BYTE* bytes) const {
        UINT64 value = (((((((((((((((UINT64)bytes[7])<<8) | bytes[6])<<8) | bytes[5])<<8) | bytes[4])<<8) | bytes[3])<<8) | bytes[2])<<8) | bytes[1])<<8) | bytes[0];
        return value;
    }
    inline BYTE* U64ToLSB(BYTE* bytes, UINT64 value) const {
        *(bytes)=(BYTE)(value & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline UINT32 MSBToU32(const BYTE* bytes) const {
        UINT32 value = (((((((UINT32)bytes[0])<<8) | bytes[1])<<8) | bytes[2])<<8) | bytes[3];
        return value;
    }
    inline BYTE* U32ToMSB(BYTE* bytes, UINT32 value) const {
        *(bytes+=3)=(BYTE)(value & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    inline UINT32 LSBToU32(const BYTE* bytes) const {
        UINT32 value = (((((((UINT32)bytes[3])<<8) | bytes[2])<<8) | bytes[1])<<8) | bytes[0];
        return value;
    }
    inline BYTE* U32ToLSB(BYTE* bytes, UINT32 value) const {
        *(bytes)=(BYTE)(value & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline BYTE *Copy8(BYTE *to, const BYTE *from) const {
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline BYTE* CopyRepeat
    (BYTE* to, int tosize, const BYTE* from, int fromsize) const {
        for (int i=0; i<tosize; i+=fromsize)
        for (int j=0,k=i; (k<tosize) && (j<fromsize); k++,j++)
            to[k] = from[j];
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef implement_baset<> implement_base;

typedef talas::base base_extends;
///////////////////////////////////////////////////////////////////////
///  Class: baset
///////////////////////////////////////////////////////////////////////
template
<class TImplements = implement_base, class TExtends = base_extends>

class _EXPORT_CLASS baset: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    baset() {
    }
    virtual ~baset() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef baset<> base;

} // namespace crypto
} // namespace talas 

#endif // _TALAS_CRYPTO_BASE_HPP
