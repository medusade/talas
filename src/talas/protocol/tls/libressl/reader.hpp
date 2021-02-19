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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 2/19/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_TLS_LIBRESSL_READER_HPP
#define TALAS_PROTOCOL_TLS_LIBRESSL_READER_HPP

#include "talas/protocol/tls/libressl/libressl.hpp"
#include "talas/io/reader.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace libressl {

///////////////////////////////////////////////////////////////////////
/// class readert
///////////////////////////////////////////////////////////////////////
template 
<class TReader = talas::io::reader,  typename TTls = struct tls,
 class TImplements = TReader, class TExtends = talas::base>
class EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TTls tls_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::char_t char_t;
    typedef typename Implements::end_t end_t;
    enum { end = Implements::end };

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy): Extends(copy) {
    }
    readert(tls_t* tls): tls_(tls) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        return read(this->tls(), what, size);
    }
    virtual ssize_t read(tls_t* tls, what_t* what, size_t size) {
        size_t count = 0;
        if ((what) && (size)) {
            count = recv(tls, what, size);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t recv(what_t* what, size_t size) {
        return recv(this->tls(), what, size);
    }
    virtual ssize_t recv(tls_t* tls, what_t* what, size_t size) {
        size_t count = 0;

        if ((tls) && (what) && (size)) {
            size_t size_of = (1 < sizeof(sized_t))?(sizeof(sized_t)*size):(size);
            ssize_t amount = 0;

            if (((ssize_t)sizeof(sized_t)) <= (amount = tls_read(tls, what, size_of))) {
                if ((2 > sizeof(sized_t))) {
                    count = amount;
                } else {
                    size_t length = ((size_t)amount);
                    if (0 < (length % sizeof(sized_t))) {
                        TALAS_LOG_ERROR("...failed (0 < (" << length << " % " << sizeof(sized_t) << ")) on " << amount << " = socket_.recv(what, " << size_of << ",...)");
                    } else {
                        count = ((ssize_t)(length / sizeof(sized_t)));
                    }
                }
            } else {
                TALAS_LOG_ERROR("...failed " << amount << " = tls_read(tls, what, " << size_of << ",...)");
                if (0 > (amount)) {
                    count = amount;
                }
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual tls_t* set_tls(tls_t* to) {
        tls_ = to;
        return (tls_t*)tls_;
    }
    virtual tls_t* tls() const {
        return (tls_t*)tls_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    tls_t* tls_;
}; /// class readert
typedef readert<> reader;

} /// namespace libressl 
} /// namespace tls 
} /// namespace protocol 
} /// namespace talas 

#endif /// ndef TALAS_PROTOCOL_TLS_LIBRESSL_READER_HPP 