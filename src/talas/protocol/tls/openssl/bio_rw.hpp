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
///   File: bio_rw.hpp
///
/// Author: $author$
///   Date: 12/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_BIO_RW_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_BIO_RW_HPP

#include "talas/protocol/tls/openssl/openssl.hpp"
#include "talas/io/write/file.hpp"
#include "talas/io/read/file.hpp"
#include "talas/io/writer.hpp"
#include "talas/io/reader.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

class _EXPORT_CLASS BIO_RW;

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

int BIO_rw_write(BIO *bio, const char *buf, int num);
int BIO_rw_read(BIO *bio, char *buf, int size);
int BIO_rw_puts(BIO *bio, const char *str);
long BIO_rw_ctrl(BIO *bio, int cmd, long arg1, void *arg2);
int BIO_rw_new(BIO *bio);
int BIO_rw_free(BIO *bio);
BIO_METHOD *BIO_rw(void);
BIO *BIO_new_rw(BIO_RW* rw);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BIO_RW {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BIO_RW(talas::io::reader* reader, talas::io::writer* writer)
    : reader_(reader), writer_(writer) {
    }
    virtual ~BIO_RW() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BIO_read(BIO *bio, char *buf, int size) {
        TALAS_LOG_MESSAGE_DEBUG("...BIO_RW::BIO_read(..., int size = " << size << ")");
        BIO_clear_retry_flags(bio);
        if ((reader_)) {
            if ((buf) && (0 < size)) {
                return reader_->read(buf, size);
            } else {
                if (!((buf) || (size))) {
                    return 0;
                }
            }
        }
        return -1;
    }
    virtual int BIO_write(BIO *bio, const char *buf, int num) {
        TALAS_LOG_MESSAGE_DEBUG("...BIO_RW::BIO_write(..., int num = " << num << ")");
        BIO_clear_retry_flags(bio);
        if ((writer_)) {
            if ((buf) && (0 < num)) {
                if (num <= (writer_->write(buf, num))) {
                    writer_->flush();
                    return num;
                }
            } else {
                if (!((buf) || (num))) {
                    return 0;
                }
            }
        }
        return -1;
    }
    virtual int BIO_puts(BIO *bio, const char *buf) {
        if ((buf)) {
            int num = talas::chars_t::count(buf);
            if ((num)) {
                return BIO_write(bio, buf, num);
            }
        }
        return 0;
    }
    virtual long BIO_ctrl(BIO *bio, int cmd, long arg1, void *arg2) {
        long ret = 1;
        TALAS_LOG_MESSAGE_DEBUG("...BIO_RW::BIO_ctrl(..., int cmd = " << cmd << ", ...)");
        switch (cmd) {
        case BIO_CTRL_GET_CLOSE:
            ret = ((long)bio->shutdown);
            break;
        case BIO_CTRL_SET_CLOSE:
            bio->shutdown = ((int)arg1);
            break;
        case BIO_CTRL_DUP:
        case BIO_CTRL_FLUSH:
            break;
        case BIO_CTRL_INFO:
        case BIO_CTRL_GET:
        case BIO_CTRL_SET:
        default:
            ret = ::BIO_ctrl(bio->next_bio, cmd, arg1, arg2);
        }
        return ret;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    talas::io::reader* reader_;
    talas::io::writer* writer_;
};

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_BIO_RW_HPP 
