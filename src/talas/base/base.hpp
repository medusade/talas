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
#ifndef _TALAS_BASE_BASE_HPP
#define _TALAS_BASE_BASE_HPP

#include "xos/base/base.hpp"
#include "xos/base/string.hpp"
#include "xos/base/types.hpp"
#include "xos/io/read/file.hpp"
#include "xos/io/write/file.hpp"
#include "xos/io/logger.hpp"

#define TALAS_LOG_ANY XOS_LOG_ANY
#define TALAS_LOG_FATAL XOS_LOG_FATAL
#define TALAS_LOG_ERROR XOS_LOG_ERROR
#define TALAS_LOG_WARN XOS_LOG_WARN
#define TALAS_LOG_INFO XOS_LOG_INFO
#define TALAS_LOG_DEBUG XOS_LOG_DEBUG
#define TALAS_LOG_TRACE XOS_LOG_TRACE

#define TALAS_LOG_ANYF XOS_LOG_ANYF
#define TALAS_LOG_FATALF XOS_LOG_FATALF
#define TALAS_LOG_ERRORF XOS_LOG_ERRORF
#define TALAS_LOG_WARNF XOS_LOG_WARNF
#define TALAS_LOG_INFOF XOS_LOG_INFOF
#define TALAS_LOG_DEBUGF XOS_LOG_DEBUGF
#define TALAS_LOG_TRACEF XOS_LOG_TRACEF

#define TALAS_LOG_MESSAGE_ANY XOS_LOG_MESSAGE_ANY
#define TALAS_LOG_MESSAGE_FATAL XOS_LOG_MESSAGE_FATAL
#define TALAS_LOG_MESSAGE_ERROR XOS_LOG_MESSAGE_ERROR
#define TALAS_LOG_MESSAGE_WARN XOS_LOG_MESSAGE_WARN
#define TALAS_LOG_MESSAGE_INFO XOS_LOG_MESSAGE_INFO
#define TALAS_LOG_MESSAGE_DEBUG XOS_LOG_MESSAGE_DEBUG
#define TALAS_LOG_MESSAGE_TRACE XOS_LOG_MESSAGE_TRACE

#define TALAS_LOG_MESSAGE_ANYF XOS_LOG_MESSAGE_ANYF
#define TALAS_LOG_MESSAGE_FATALF XOS_LOG_MESSAGE_FATALF
#define TALAS_LOG_MESSAGE_ERRORF XOS_LOG_MESSAGE_ERRORF
#define TALAS_LOG_MESSAGE_WARNF XOS_LOG_MESSAGE_WARNF
#define TALAS_LOG_MESSAGE_INFOF XOS_LOG_MESSAGE_INFOF
#define TALAS_LOG_MESSAGE_DEBUGF XOS_LOG_MESSAGE_DEBUGF
#define TALAS_LOG_MESSAGE_TRACEF XOS_LOG_MESSAGE_TRACEF

namespace talas {

typedef xos::base::implement_base implement_base;
typedef xos::base::base base;

///////////////////////////////////////////////////////////////////////
/// string
///////////////////////////////////////////////////////////////////////
typedef xos::base::string_implement string_implements;
#if !defined(CPP_11)
#error Requires C++11
#else // !defined(CPP_11)
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TExtends = std::basic_string<TChar>, class TImplements = string_implements>

using stringt = typename xos::base::stringt
<TChar, TEnd, VEnd, TExtends, TImplements>;
#endif // !defined(CPP_11)
typedef xos::base::string string_t;
typedef xos::base::tstring tstring_t;
typedef xos::base::wstring wstring_t;

///////////////////////////////////////////////////////////////////////
/// types
///////////////////////////////////////////////////////////////////////
#if !defined(CPP_11)
#error Requires C++11
#else // !defined(CPP_11)
template
<class TWhat = char, class TEndWhat = TWhat, TEndWhat VEndWhat = 0,
 class TInt = int, class TUInt = unsigned, class TSize = size_t,
 class TLength = ssize_t, TLength VUndefinedLength = -1>

using typest = typename xos::base::typest
<TWhat, TEndWhat, VEndWhat, TInt, TUInt, TSize, TLength, VUndefinedLength>;
#endif // !defined(CPP_11)
typedef xos::base::chars_t chars_t;
typedef xos::base::tchars_t tchars_t;
typedef xos::base::wchars_t wchars_t;
typedef xos::base::bytes_t bytes_t;

namespace io {
namespace read {
typedef xos::io::read::file file;
} // namespace read
namespace write {
typedef xos::io::write::file file;
} // namespace write
} // namespace io

} // namespace talas

#endif // _TALAS_BASE_BASE_HPP
