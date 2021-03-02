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

#include "talas/io/io.hpp"
#include "xos/base/logged.hpp"
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

typedef xos::base::logged logged;

} // namespace talas 

#endif // _TALAS_IO_LOGGER_HPP 
