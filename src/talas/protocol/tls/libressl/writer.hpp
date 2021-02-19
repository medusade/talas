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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 2/19/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_TLS_LIBRESSL_WRITER_HPP
#define TALAS_PROTOCOL_TLS_LIBRESSL_WRITER_HPP

#include "talas/protocol/tls/libressl/libressl.hpp"
#include "talas/io/writer.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace libressl {

///////////////////////////////////////////////////////////////////////
/// class writert
///////////////////////////////////////////////////////////////////////
template 
<class TWriter = talas::io::writer, typename TTls = struct tls,
 class TImplements = TWriter, class TExtends = talas::base>
class EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef writert Derives;

    typedef TTls tls_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::char_t char_t;
    typedef typename Implements::end_t end_t;
    enum { end = Implements::end };

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    writert(const writert& copy): Extends(copy) {
    }
    writert(tls_t* tls): tls_(tls) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size) {
        return write(this->tls(), what, size);
    }
    virtual ssize_t write(tls_t* tls, const what_t* what, ssize_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            if (0 > (size)) {
                const sized_t* sized = 0;
                if ((sized = ((const sized_t*)what))) {
                    for (size = 0; *sized; ++sized) {
                        ++size;
                    }
                }
            }
            if (0 < (size)) {
                count = send(tls, what, size);
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t send(const what_t* what, size_t size) {
        return send(this->tls(), what, size);
    }
    virtual ssize_t send(tls_t* tls, const what_t* what, size_t size) {
        ssize_t count = 0;
        
        if ((what) && (size) && (tls)) {
            size_t size_of = (1<sizeof(sized_t))?(sizeof(sized_t)*size):(size);
            ssize_t amount = 0;

            TALAS_LOG_DEBUG("socket_.send(what, " << size_of << ",...)...");
            if (((ssize_t)size_of) == (amount = tls_write(tls, what, size_of))) {
                TALAS_LOG_DEBUG("...tls_write(tls, what, " << size_of << ",...)");
                count = size;
            } else {
                TALAS_LOG_ERROR("...failed " << amount << " = tls_write(tls, what, " << size_of << ",...)");
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
}; /// class writert
typedef writert<> writer;

} /// namespace libressl 
} /// namespace tls 
} /// namespace protocol 
} /// namespace talas 

#endif /// ndef TALAS_PROTOCOL_TLS_LIBRESSL_WRITER_HPP 