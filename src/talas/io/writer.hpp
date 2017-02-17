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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 12/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_WRITER_HPP
#define _TALAS_IO_WRITER_HPP

#include "talas/base/base.hpp"
#if !defined(USE_NADIR_BASE)
#include "xos/io/writer.hpp"
#else // !defined(USE_NADIR_BASE)
#include "nadir/io/writer.hpp"
#endif // !defined(USE_NADIR_BASE)

namespace talas {
namespace io {

#if !defined(USE_NADIR_BASE)
typedef xos::io::writer writer;
typedef xos::io::char_writer char_writer;
typedef xos::io::byte_writer byte_writer;
#else // !defined(USE_NADIR_BASE)
typedef nadir::io::writer writer;
typedef nadir::io::char_writer char_writer;
typedef nadir::io::byte_writer byte_writer;
#endif // !defined(USE_NADIR_BASE)

} // namespace io
} // namespace talas 

#endif // _TALAS_IO_WRITER_HPP 
