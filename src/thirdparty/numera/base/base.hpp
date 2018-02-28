///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   Date: 2/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NUMERA_BASE_BASE_HPP
#define _NUMERA_BASE_BASE_HPP

#include "xos/base/base.hpp"
#include "xos/base/attached.hpp"
#include "xos/base/created.hpp"
#include "xos/base/opened.hpp"
#include "xos/base/string.hpp"
#include "xos/base/to_string.hpp"
#include "xos/io/logger.hpp"

namespace numera {

typedef xos::base::implement_base implement_base;
typedef xos::base::base base;

typedef ::xos::base::attacher_exception attacher_exception;
static const attacher_exception failed_to_attach = ::xos::base::failed_to_attach;
static const attacher_exception failed_to_detach = ::xos::base::failed_to_detach;

typedef ::xos::base::creator_exception creator_exception;
static const creator_exception failed_to_create = ::xos::base::failed_to_create;
static const creator_exception failed_to_destroy = ::xos::base::failed_to_destroy;

typedef ::xos::base::opener_exception opener_exception;
static const opener_exception failed_to_open = ::xos::base::failed_to_open;
static const opener_exception failed_to_close = ::xos::base::failed_to_close;

typedef xos::base::string string_t, char_string_t;
typedef xos::base::tstring tstring_t, tchar_string_t;
typedef xos::base::wstring wstring_t, wchar_string_t;

typedef xos::base::unsigned_to_string unsigned_to_string;
typedef xos::base::signed_to_string signed_to_string;
typedef xos::base::pointer_to_string pointer_to_string;
typedef xos::base::bool_to_string bool_to_string;
typedef xos::base::char_to_string char_to_string;
typedef xos::base::x_to_string x_to_string;

} // namespace numera 

#endif // _NUMERA_BASE_BASE_HPP 
