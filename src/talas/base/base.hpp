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

namespace talas {

typedef xos::base::implement_base implement_base;
typedef xos::base::base base;

} // namespace talas

#include "talas/io/logger.hpp"
#include "talas/io/write/file.hpp"
#include "talas/io/read/file.hpp"
#include "talas/base/array.hpp"
#include "talas/base/string.hpp"
#include "talas/base/types.hpp"

#endif // _TALAS_BASE_BASE_HPP
