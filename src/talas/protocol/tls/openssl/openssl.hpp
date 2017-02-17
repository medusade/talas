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
///   File: openssl.hpp
///
/// Author: $author$
///   Date: 12/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_OPENSSL_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_OPENSSL_HPP

#include "talas/io/logger.hpp"
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef char_array_t host_extends;
///////////////////////////////////////////////////////////////////////
///  Class: host
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS host: public host_extends {
public:
    typedef host_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    host(const char* name, int port) {
        assign(name, port);
    }
    virtual ~host() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char* assign(const char* name, int port) {
        const char null_char = 0;
        char_string_t s(name_.assign((name && name[0])?(name):("*")));
        s.append(":");
        s.append_int(port_ = port);
        Extends::assign(s.chars(), s.length());
        Extends::append(&null_char, 1);
        return elements();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* set_name(const char* to) {
        int port = port_;
        assign(to, port);
        return name_.chars();
    }
    virtual const char* name() const {
        return name_.chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int set_port(int to) {
        char_string_t name(name_);
        assign(name.chars(), to);
        return port_;
    }
    virtual int port() const {
        return port_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator char* () const {
        return elements();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char_string_t name_;
    int port_;
};

typedef host port_extends;
///////////////////////////////////////////////////////////////////////
///  Class: port
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS port: public port_extends {
public:
    typedef port_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    port(const char* host, int number): Extends(host, number) {
    }
    port(int number): Extends(0, number) {
    }
    virtual ~port() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int set_number(int to) {
        return Extends::set_port(to);
    }
    virtual int number() const {
        return Extends::port();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
bool startup();
bool cleanup();

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_OPENSSL_HPP 
