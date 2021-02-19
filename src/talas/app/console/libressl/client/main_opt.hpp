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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 2/18/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_OPT_HPP

#include "talas/app/console/libressl/base/main.hpp"
#include "talas/app/console/protocol/tls/client/main.hpp"

namespace talas {
namespace app {
namespace console {
namespace libressl {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template 
<class TExtends = protocol::tls::client::maint
 <protocol::tls::client::main_optt<network::client::maint
 <libressl::base::maint<libressl::base::main_optt
 <protocol::tls::base::maint<network::client::main_opt> > > > > >, 
 class TImplements = typename TExtends::Implements>
class EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef main_optt Derives;

    typedef typename TExtends::char_t char_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::writer_t writer_t;
    typedef talas::io::sized::readert<reader_t> sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    main_optt() {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy): Extends(copy) {
    }

protected:
    typedef typename TExtends::socket_t socket_t;
    typedef typename TExtends::socket_reader_t socket_reader_t;
    typedef typename TExtends::socket_writer_t socket_writer_t;
    typedef typename TExtends::tls_t tls_t;
    typedef typename TExtends::tls_writer_t tls_writer_t;
    typedef typename TExtends::tls_reader_t tls_reader_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace client 
} /// namespace libressl 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_OPT_HPP 