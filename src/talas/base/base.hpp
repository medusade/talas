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

#if !defined(USE_NADIR_BASE)
#include "xos/base/base.hpp"
#else // !defined(USE_NADIR_BASE)
#include "nadir/base/base.hpp"
#include "nadir/base/attached.hpp"
#include "nadir/base/created.hpp"
#include "nadir/base/opened.hpp"
#endif // !defined(USE_NADIR_BASE)

namespace talas {

#if !defined(USE_NADIR_BASE)
typedef xos::base::implement_base implement_base;
typedef xos::base::base base;
#else // !defined(USE_NADIR_BASE)
typedef nadir::implement_base implement_base;
typedef nadir::base base;

typedef nadir::attach_status attach_status;
static const attach_status attach_failed = nadir::attach_failed;
static const attach_status detach_failed = nadir::detach_failed;
typedef nadir::attach_exception attach_exception;

typedef nadir::create_status create_status;
static const create_status create_failed = nadir::create_failed;
static const create_status destroy_failed = nadir::destroy_failed;
typedef nadir::create_exception create_exception;

typedef nadir::open_status open_status;
static const open_status open_failed = nadir::open_failed;
static const open_status close_failed = nadir::close_failed;
typedef nadir::open_exception open_exception;
#endif // !defined(USE_NADIR_BASE)

} // namespace talas

#include "talas/io/logger.hpp"
#include "talas/io/write/file.hpp"
#include "talas/io/read/file.hpp"
#include "talas/base/array.hpp"
#include "talas/base/string.hpp"
#include "talas/base/types.hpp"

#endif // _TALAS_BASE_BASE_HPP
