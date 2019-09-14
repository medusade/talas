///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: connection.hpp
///
/// Author: $author$
///   Date: 2/16/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_CONNECTION_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_CONNECTION_HPP

#include "talas/protocol/tls/connection.hpp"
#include "talas/protocol/tls/openssl/bio_rw.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef SSL* connection_attached_t;

typedef xos::base::attachert
<connection_attached_t, int, 0, tls::connection> connection_attacher;
typedef xos::base::attachedt
<connection_attached_t, int, 0, connection_attacher> connection_attached;

typedef connection_attacher connectiont_implements;
typedef connection_attached connectiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: connectiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = connectiont_implements, class TExtends = connectiont_extends>

class _EXPORT_CLASS connectiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    connectiont(io::reader& tp_reader, io::writer& tp_writer)
    : tp_reader_(tp_reader),
      tp_writer_(tp_writer),
      rw_(&tp_reader_, &tp_writer_) {
    }
    connectiont(const connectiont& copy)
    : tp_reader_(copy.tp_reader()),
      tp_writer_(copy.tp_writer()),
      rw_(&tp_reader_, &tp_writer_) {
    }
    virtual ~connectiont() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(void* what, size_t size) {
        SSL* ssl = 0;
        if ((ssl = this->attached_to()) && (what)) {
            ssize_t count = 0;
            if ((size)) {
                count = SSL_read(ssl, what, size);
            }
            return count;
        }
        return -1;
    }
    virtual ssize_t write(const void* what, ssize_t size) {
        SSL* ssl = 0;
        if ((ssl = this->attached_to()) && (what)) {
            ssize_t count = 0;
            if (0 < (size)) {
                count = SSL_write(ssl, what, size);
            } else {
                if (0 > (size)) {
                    ssize_t amount = 0;
                    for (const char* chars = (const char*)what; *chars; ++chars) {
                        if (1 > (amount = SSL_write(ssl, chars, 1))) {
                            return -1;
                        }
                        count += amount;
                    }
                }
            }
            return count;
        }
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual io::reader& tp_reader() const {
        return (io::reader&)tp_reader_;
    }
    virtual io::writer& tp_writer() const {
        return (io::writer&)tp_writer_;
    }
    virtual BIO_RW& rw() const {
        return (BIO_RW&)rw_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    io::reader& tp_reader_;
    io::writer& tp_writer_;
    BIO_RW rw_;
};
typedef connectiont<> connection;

} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_CONNECTION_HPP 
