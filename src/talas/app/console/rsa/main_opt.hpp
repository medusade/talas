///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   Date: 2/28/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_RSA_MAIN_OPT_HPP
#define _TALAS_APP_CONSOLE_RSA_MAIN_OPT_HPP

#include "talas/crypto/console/mpinteger/main_opt.hpp"

namespace talas {
namespace app {
namespace console {
namespace rsa {

typedef crypto::console::mpinteger::main_opt_implements main_opt_implements;
typedef crypto::console::mpinteger::main_opt main_opt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_opt
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_opt: virtual public main_opt_implements, public main_opt_extends {
public:
    typedef main_opt_implements Implements;
    typedef main_opt_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_opt() {
    }
    virtual ~main_opt() {
    }
private:
    main_opt(const main_opt& copy) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace rsa 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_RSA_MAIN_OPT_HPP 

        

