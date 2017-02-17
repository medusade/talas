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
///   File: openssl.cpp
///
/// Author: $author$
///   Date: 12/27/2015
///////////////////////////////////////////////////////////////////////
#include "talas/protocol/tls/openssl/openssl.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
bool startup() {
    bool success = true;

    TALAS_LOG_DEBUG("ERR_load_BIO_strings()...");
    ERR_load_BIO_strings();

    TALAS_LOG_DEBUG("SSL_load_error_strings()...");
    SSL_load_error_strings();

    TALAS_LOG_DEBUG("SSL_library_init()...");
    SSL_library_init();
    return success;
}
bool cleanup() {
    bool success = true;

    TALAS_LOG_DEBUG("...EVP_cleanup()");
    EVP_cleanup();

    TALAS_LOG_DEBUG("...ERR_free_strings()");
    ERR_free_strings();
    return success;
}

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 
