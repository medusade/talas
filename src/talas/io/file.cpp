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
///   File: file.cpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#include "talas/io/file.hpp"

namespace talas {
namespace io {

///////////////////////////////////////////////////////////////////////
/// class filet
///////////////////////////////////////////////////////////////////////
#if defined(TALAS_IO_FILE_INSTANCE)
static file the_file;
#endif /// defined(TALAS_IO_FILE_INSTANCE) 

} /// namespace io 
} /// namespace talas 
