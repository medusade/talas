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
///   Date: 2/15/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_IO_SOCKET_WRITER_HPP
#define TALAS_IO_SOCKET_WRITER_HPP

#include "talas/io/writer.hpp"
#include "xos/io/socket/writer.hpp"
#include "talas/network/os/sockets.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace io {
namespace socket {

///////////////////////////////////////////////////////////////////////
/// class writert
///////////////////////////////////////////////////////////////////////
template 
<class TWriter = talas::io::writer, class TSocket = ::xos::network::os::socket,
 class TImplements = ::xos::io::socket::writert<TWriter>,  class TExtends = talas::base>
class EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef writert Derives;

    typedef TSocket socket_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;
    typedef typename Implements::char_t char_t;
    typedef typename Implements::end_t end_t;
    enum { end = Implements::end };

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    writert(const writert& copy): socket_(copy.socket_) {
    }
    writert(socket_t& socket): socket_(socket) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t send(const what_t* what, size_t size) {
        ssize_t count = 0;

        if ((what) && (size)) {
            size_t size_of = (1<sizeof(sized_t))?(sizeof(sized_t)*size):(size);
            ssize_t amount = 0;

            TALAS_LOG_DEBUG("socket_.send(what, " << size_of << ",...)...");
            if (((ssize_t)size_of) == (amount = socket_.send(what, size_of, 0))) {
                TALAS_LOG_DEBUG("...socket_.send(what, " << size_of << ",...)");
                count = size;
            } else {
                TALAS_LOG_ERROR("...failed " << amount << " = socket_.send(what, " << size_of << ",...)");
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
}; /// class writert
typedef writert<> writer;

} /// namespace socket 
} /// namespace io 
} /// namespace talas 

#endif /// ndef TALAS_IO_SOCKET_WRITER_HPP 