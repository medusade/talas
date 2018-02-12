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
///   Date: 4/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_BASE_STRING_HPP
#define _TALAS_BASE_STRING_HPP

#include "talas/base/base.hpp"
#if !defined(USE_NADIR_BASE)
#include "xos/base/string.hpp"
#include "xos/base/to_string.hpp"
#else // !defined(USE_NADIR_BASE)
#include "nadir/base/string.hpp"
#endif // !defined(USE_NADIR_BASE)

namespace talas {

#if !defined(USE_NADIR_BASE)
///////////////////////////////////////////////////////////////////////
///  Class: string
///////////////////////////////////////////////////////////////////////
#if defined(USE_CPP_11)
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TExtends = std::basic_string<TChar>,
 class TImplements = xos::base::string_implement>

using stringt = typename xos::base::stringt
<TChar, TEnd, VEnd, TExtends, TImplements>;
#else // defined(USE_CPP_11)
#endif // defined(USE_CPP_11)

typedef xos::base::string string_t, char_string_t;
typedef xos::base::tstring tstring_t, tchar_string_t;
typedef xos::base::wstring wstring_t, wchar_string_t;

typedef xos::base::unsigned_to_string unsigned_to_string;
typedef xos::base::signed_to_string signed_to_string;
typedef xos::base::pointer_to_string pointer_to_string;
typedef xos::base::bool_to_string bool_to_string;
typedef xos::base::char_to_string char_to_string;
#else // !defined(USE_NADIR_BASE)
typedef nadir::char_string string_t, char_string_t;
typedef nadir::tchar_string tstring_t, tchar_string_t;
typedef nadir::wchar_string wstring_t, wchar_string_t;
#endif // !defined(USE_NADIR_BASE)

} // namespace talas

#endif // _TALAS_BASE_STRING_HPP 
