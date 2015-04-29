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
///   File: main.hpp
///
/// Author: $author$
///   Date: 4/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CONSOLE_MAIN_HPP
#define _TALAS_CRYPTO_CONSOLE_MAIN_HPP

#include "talas/console/main.hpp"
#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace console {

typedef ::talas::console::main_implements main_implements;
typedef ::talas::console::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_implements, class TExtends = main_extends>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::Extends::Extends::Extends::Extends MainExtends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int main(int argc, char** argv, char** env) {
        int err = 0;
        try {
            err = MainExtends::main(argc, argv, env);
        } catch (const crypto::error& e) {
            TALAS_LOG_ERROR("...caught crypto::error " << e);
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef maint<> main;

} // namespace console 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CONSOLE_MAIN_HPP 
