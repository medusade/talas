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
///   File: logger.hpp
///
/// Author: $author$
///   Date: 4/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_LOGGER_HPP
#define _TALAS_IO_LOGGER_HPP

#include "talas/base/base.hpp"
#if !defined(USE_NADIR_BASE)
#include "xos/io/logger.hpp"
#else // !defined(USE_NADIR_BASE)
#include "nadir/io/logger.hpp"
#endif // !defined(USE_NADIR_BASE)

#if !defined(USE_NADIR_BASE)
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
#else // !defined(USE_NADIR_BASE)
#define TALAS_LOG_ANY LOG_ANY
#define TALAS_LOG_FATAL LOG_FATAL
#define TALAS_LOG_ERROR LOG_ERROR
#define TALAS_LOG_WARN LOG_WARN
#define TALAS_LOG_INFO LOG_INFO
#define TALAS_LOG_DEBUG LOG_DEBUG
#define TALAS_LOG_TRACE LOG_TRACE

#define TALAS_LOG_ANYF LOG_ANYF
#define TALAS_LOG_FATALF LOG_FATALF
#define TALAS_LOG_ERRORF LOG_ERRORF
#define TALAS_LOG_WARNF LOG_WARNF
#define TALAS_LOG_INFOF LOG_INFOF
#define TALAS_LOG_DEBUGF LOG_DEBUGF
#define TALAS_LOG_TRACEF LOG_TRACEF

#define TALAS_LOG_MESSAGE_ANY LOG_MESSAGE_ANY
#define TALAS_LOG_MESSAGE_FATAL LOG_MESSAGE_FATAL
#define TALAS_LOG_MESSAGE_ERROR LOG_MESSAGE_ERROR
#define TALAS_LOG_MESSAGE_WARN LOG_MESSAGE_WARN
#define TALAS_LOG_MESSAGE_INFO LOG_MESSAGE_INFO
#define TALAS_LOG_MESSAGE_DEBUG LOG_MESSAGE_DEBUG
#define TALAS_LOG_MESSAGE_TRACE LOG_MESSAGE_TRACE

#define TALAS_LOG_MESSAGE_ANYF LOG_MESSAGE_ANYF
#define TALAS_LOG_MESSAGE_FATALF LOG_MESSAGE_FATALF
#define TALAS_LOG_MESSAGE_ERRORF LOG_MESSAGE_ERRORF
#define TALAS_LOG_MESSAGE_WARNF LOG_MESSAGE_WARNF
#define TALAS_LOG_MESSAGE_INFOF LOG_MESSAGE_INFOF
#define TALAS_LOG_MESSAGE_DEBUGF LOG_MESSAGE_DEBUGF
#define TALAS_LOG_MESSAGE_TRACEF LOG_MESSAGE_TRACEF
#endif // !defined(USE_NADIR_BASE)

namespace talas {
namespace io {

} // namespace io 
} // namespace talas 

#endif // _TALAS_IO_LOGGER_HPP 
