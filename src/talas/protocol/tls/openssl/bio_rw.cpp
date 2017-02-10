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
///   File: bio_rw.cpp
///
/// Author: $author$
///   Date: 12/27/2015
///////////////////////////////////////////////////////////////////////
#include "talas/protocol/tls/openssl/bio_rw.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

int BIO_rw_write(BIO *bio, const char *buf, int num) {
    BIO_RW* rw = 0;
    if ((bio) && (rw = ((BIO_RW*)(bio->ptr)))) {
        return rw->BIO_write(bio, buf, num);
    }
    return -1;
}
int BIO_rw_read(BIO *bio, char *buf, int size) {
    BIO_RW* rw = 0;
    if ((bio) && (rw = ((BIO_RW*)(bio->ptr)))) {
        return rw->BIO_read(bio, buf, size);
    }
    return -1;
}
int BIO_rw_puts(BIO *bio, const char *str) {
    BIO_RW* rw = 0;
    if ((bio) && (rw = ((BIO_RW*)(bio->ptr)))) {
        return rw->BIO_puts(bio, str);
    }
    return -1;
}
long BIO_rw_ctrl(BIO *bio, int cmd, long arg1, void *arg2) {
    BIO_RW* rw = 0;
    if ((bio) && (rw = ((BIO_RW*)(bio->ptr)))) {
        return rw->BIO_ctrl(bio, cmd, arg1, arg2);
    }
    return -1;
}
int BIO_rw_new(BIO *bio) {
    TALAS_LOG_MESSAGE_DEBUG("...BIO_rw_new(BIO *bio)");
    bio->ptr = 0;
    bio->init = 0;
    return 1;
}
int BIO_rw_free(BIO *bio) {
    TALAS_LOG_MESSAGE_DEBUG("...BIO_rw_free(BIO *bio)");
    bio->ptr = 0;
    bio->init = 0;
    return 1;
}

static BIO_METHOD BIO_rw_methods = {
    //BIO_TYPE_SOURCE_SINK,
    BIO_TYPE_MEM,
    "talas read/write",
    BIO_rw_write,
    BIO_rw_read,
    BIO_rw_puts,
    NULL, /* fd_gets, */
    BIO_rw_ctrl,
    BIO_rw_new,
    BIO_rw_free,
    NULL,
    };

BIO_METHOD *BIO_rw(void) {
    return &BIO_rw_methods;
}
BIO* BIO_new_rw(BIO_RW* rw) {
    if ((rw)) {
        BIO* bio = 0;
        if ((bio = BIO_new(BIO_rw()))) {
            bio->ptr = rw;
            bio->init = 1;
            return bio;
        }
    }
    return 0;
}

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 
