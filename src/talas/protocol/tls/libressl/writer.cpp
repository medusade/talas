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
///   File: writer.cpp
///
/// Author: $author$
///   Date: 2/19/2021
///////////////////////////////////////////////////////////////////////
#include "talas/protocol/tls/libressl/writer.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace libressl {

///////////////////////////////////////////////////////////////////////
/// class writert
///////////////////////////////////////////////////////////////////////
#if defined(TALAS_PROTOCOL_TLS_LIBRESSL_WRITER_INSTANCE)
static writer the_writer;
#endif /// defined(TALAS_PROTOCOL_TLS_LIBRESSL_WRITER_INSTANCE) 

} /// namespace libressl 
} /// namespace tls 
} /// namespace protocol 
} /// namespace talas 
