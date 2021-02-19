///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   File: string.hpp
///
/// Author: $author$
///   Date: 4/7/2015, 2/17/2021
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_BASE_STRING_HPP
#define _TALAS_BASE_STRING_HPP

#include "xos/base/string.hpp"
#include "xos/base/to_string.hpp"

namespace talas {

typedef xos::base::string_extends string_extends;
typedef xos::base::wstring_extends wstring_extends;

///////////////////////////////////////////////////////////////////////
///  Class: string
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TExtends = xos::base::stringt<TChar, TEnd, VEnd>, 
 class TImplements = typename TExtends::Implements>

class _EXPORT_CLASS stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef stringt Derives;

    typedef TChar Char;
    typedef Char char_t;
    typedef TEnd end_t;
    enum { End = VEnd, end = End };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    stringt(const wchar_t* chars, size_t length) {
        this->append(chars, length);
    }
    stringt(const wchar_t* chars) {
        this->append(chars);
    }
    stringt(const char* chars, size_t length) {
        this->append(chars, length);
    }
    stringt(const char* chars) {
        this->append(chars);
    }
    stringt(ssize_t value) {
        this->append_ssize(value);
    }
    stringt(size_t value) {
        this->append_size(value);
    }
    stringt(const wstring_extends& copy) {
        this->append(copy.c_str());
    }
    stringt(const string_extends& copy) {
        this->append(copy.c_str());
    }
    stringt(const stringt& copy): Extends(copy) {
    }
    stringt() {
    }
    virtual ~stringt() {
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::append;
    using Extends::assign;
    using Extends::compare;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef stringt<char> string_t, char_string_t;
typedef stringt<tchar_t> tstring_t, tchar_string_t;
typedef stringt<wchar_t> wstring_t, wchar_string_t;

typedef xos::base::unsigned_to_string unsigned_to_string;
typedef xos::base::signed_to_string signed_to_string;
typedef xos::base::pointer_to_string pointer_to_string;
typedef xos::base::bool_to_string bool_to_string;
typedef xos::base::char_to_string char_to_string;
typedef xos::base::x_to_string x_to_string;

} // namespace talas

#endif // _TALAS_BASE_STRING_HPP 
