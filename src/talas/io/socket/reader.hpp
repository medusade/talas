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
///   Date: 2/15/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_IO_SOCKET_READER_HPP
#define TALAS_IO_SOCKET_READER_HPP

#include "talas/io/reader.hpp"
#include "xos/io/socket/reader.hpp"
#include "talas/network/os/sockets.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace io {
namespace socket {

///////////////////////////////////////////////////////////////////////
/// class readert
///////////////////////////////////////////////////////////////////////
template 
<class TReader = talas::io::reader, class TSocket = ::xos::network::os::socket,
 class TImplements = xos::io::socket::readert<TReader>, class TExtends = talas::base>
class EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TSocket socket_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::char_t char_t;
    typedef typename Implements::end_t end_t;
    enum { end = Implements::end };

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy): socket_(copy.socket_) {
    }
    readert(socket_t& socket): socket_(socket) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t recv(what_t* what, size_t size) {
        size_t count = 0;

        if ((what) && (size)) {
            size_t size_of = (1 < sizeof(sized_t))?(sizeof(sized_t)*size):(size);
            ssize_t amount = 0;

            if (((ssize_t)sizeof(sized_t)) <= (amount = socket_.recv(what, size_of, 0))) {
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
                TALAS_LOG_ERROR("...failed " << amount << " = socket_.recv(what, " << size_of << ",...)");
                if (0 > (amount)) {
                    count = amount;
                }
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    socket_t& socket_;
}; /// class readert
typedef readert<> reader;

} /// namespace socket 
} /// namespace io 
} /// namespace talas 

#endif /// ndef TALAS_IO_SOCKET_READER_HPP 