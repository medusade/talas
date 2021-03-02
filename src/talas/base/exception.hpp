///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: exception.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_BASE_EXCEPTION_HPP
#define TALAS_BASE_EXCEPTION_HPP

#include "talas/base/string.hpp"
#include "xos/base/exception.hpp"

namespace talas {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int exception_status;
enum {
    exception_success = (exception_status)xos::base::exception_success,
    exception_failed = (exception_status)xos::base::exception_failed,
    exception_unexpected
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
inline const char* exception_status_to_chars(exception_status status) {
    switch (status) {
    case exception_success: return "exception_success";
    case exception_failed: return "exception_failed";
    case exception_unexpected: return "exception_unexpected";
    }
    return "unknown";
}

///////////////////////////////////////////////////////////////////////
///  Class: exceptiont
///////////////////////////////////////////////////////////////////////
template
<typename TStatus = exception_status, typename TChar = char, class TString = stringt<TChar>, 
 class TExtends = xos::base::exceptiont<TStatus, TChar, TString>,
 class TImplements = typename TExtends::Implements>

class _EXPORT_CLASS exceptiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TStatus status_t;
    typedef TString string_t;
    typedef TChar char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    exceptiont(status_t status): Extends(status) {}
    virtual ~exceptiont() {}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* status_to_chars() const {
        return talas::exception_status_to_chars(((exception_status)this->status()));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};
typedef exceptiont<> exception;

} /// namespace talas 

#endif /// ndef TALAS_BASE_EXCEPTION_HPP 