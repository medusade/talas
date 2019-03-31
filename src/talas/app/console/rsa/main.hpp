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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/28/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_RSA_MAIN_HPP
#define _TALAS_APP_CONSOLE_RSA_MAIN_HPP

#include "talas/app/console/rsa/public_key.hpp"
#include "talas/app/console/rsa/private_key.hpp"

#include "talas/crypto/console/mpinteger/main.hpp"

#include "talas/crypto/rsa/public_key.hpp"
#include "talas/crypto/rsa/private_key.hpp"

#include "talas/crypto/rsa/bn/public_key.hpp"
#include "talas/crypto/rsa/bn/private_key.hpp"

#include "talas/crypto/rsa/mp/public_key.hpp"
#include "talas/crypto/rsa/mp/private_key.hpp"

#include "talas/io/read/file.hpp"
#include "talas/io/delegated/reader.hpp"
#include "talas/io/asn1/reader.hpp"
#include "talas/io/asn1/reader_events.hpp"
#include "talas/io/asn1/block.hpp"
#include "talas/io/asn1/type.hpp"
#include "talas/io/asn1/form.hpp"
#include "talas/io/asn1/class.hpp"
#include "talas/io/asn1/length.hpp"
#include "talas/io/asn1/base.hpp"
#include "talas/io/pem/reader.hpp"
#include "talas/io/pem/read_to_string.hpp"
#include "talas/io/array/reader.hpp"
#include "talas/io/string/reader.hpp"
#include "talas/io/string/writer.hpp"
#include "talas/io/main/out/writer.hpp"

namespace talas {
namespace app {
namespace console {
namespace rsa {

typedef crypto::console::mpinteger::main_implements main_implements;
typedef crypto::console::mpinteger::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): run_(0), run_test_(0) {
    }
    virtual ~main() {
    }
private:
    main(const main& copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;

        TALAS_LOG_DEBUG("try {...");
        try {
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = run_default(argc, argv, env);
            }
            TALAS_LOG_DEBUG("...} try");
        } catch (...) {
            TALAS_LOG_DEBUG("...catch (...)");
        }
        return err;
    }
    virtual int run_default(int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = run_read(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_read(int argc, char_t** argv, char_t** env) {
        int err = 0;
        char_t* arg = 0;
        /*
        io::main::out::writert<Derives> out(*this);
        string_t b64;
        io::string::writert<string_t> writer(b64);
        io::string::readert<string_t> reader(b64);
        */
        if ((optind < (argc)) && (argv) && (arg = (argv[optind])) && (arg[0])) {
            io::read::file file;

            if ((file.open(arg))) {
                io::pem::read_to_string b64;
                io::pem::reader pem(b64, file);
                ssize_t count = 0;
                size_t length = 0;

                if ((0 < (count = pem.read())) && (0 < (length = b64.length()))) {
                    io::string::reader reader(b64);
                    byte_array_t array(length+1);
                    byte_t* bytes = 0;
                    size_t size = 0;

                    if ((bytes = array.elements()) && (length < (size = array.size()))) {
                        if (0 < (count = reader.read64(bytes, size))) {
                            if (0 < (length = array.set_length(count))) {
                                io::array::byte_reader reader(array);
                                io::asn1::reader asn1;
                                
                                if (0 < (count = asn1.read(reader))) {
                                    
                                }
                            }
                        }
                    }
                }
                file.close();
            }
        } else {
            err = run_test(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*run_test_)(int argc, char_t** argv, char_t** env);
    virtual int run_test(int argc, char_t** argv, char_t** env) {
        int err = 0;
        time_t t = 0;

        ::srand(::time(&t));
        //::srand(2018);
        
        if ((run_test_)) {
            err = (this->*run_test_)(argc, argv, env);
        } else {
            err = run_test_default(argc, argv, env);
        }
        return err;
    }
    virtual int run_test_default(int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = run_test_bn(argc, argv, env);
        return err;
    }
    virtual int run_test_bn(int argc, char_t** argv, char_t** env) {
        int err = 0;
        
        crypto::rsa::bn::public_key pub
        (rsa_public_modulus, sizeof(rsa_public_modulus),
         rsa_public_exponent, sizeof(rsa_public_exponent));

        crypto::rsa::bn::private_key prv
        (rsa_private_p, rsa_private_q, rsa_private_dmp1, 
         rsa_private_dmq1, rsa_private_iqmp, sizeof(rsa_private_p));
        
        err = test(pub, prv);
        return err;
    }
    virtual int run_test_mp(int argc, char_t** argv, char_t** env) {
        int err = 0;
        
        crypto::rsa::mp::public_key pub
        (rsa_public_modulus, sizeof(rsa_public_modulus),
         rsa_public_exponent, sizeof(rsa_public_exponent));

        crypto::rsa::mp::private_key prv
        (rsa_private_p, rsa_private_q, rsa_private_dmp1, 
         rsa_private_dmq1, rsa_private_iqmp, sizeof(rsa_private_p));
        
        err = test(pub, prv);
        return err;
    }
    virtual int run_test_mbu(int argc, char** argv, char** env) {
        int err = 0;
        err = run_test_unimplemented(argc, argv, env);
        return err;
    }
    virtual int run_test_null(int argc, char** argv, char** env) {
        int err = 0;

        crypto::rsa::public_key pub
        (rsa_public_modulus, sizeof(rsa_public_modulus),
         rsa_public_exponent, sizeof(rsa_public_exponent));

        crypto::rsa::private_key prv
        (rsa_private_p, rsa_private_q, rsa_private_dmp1, 
         rsa_private_dmq1, rsa_private_iqmp, sizeof(rsa_private_p));
        
        err = test(pub, prv);
        return err;
    }
    virtual int run_test_unimplemented(int argc, char_t** argv, char_t** env) {
        int err = 1;
        LOG_ERROR("...unimplemented");
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    template <typename rsa_public_key_t, typename rsa_private_key_t>
    int test(rsa_public_key_t& pub, rsa_private_key_t& prv) {
        int err = 0;
        ssize_t modbytes = pub.modbytes();
        ssize_t size = 0;

        if ((modbytes >= modbytes_min) && (modbytes <= modbytes_max)) {

            if ((size = this->random(plain, modbytes))) {
                plain[0] &= 0x7F;
                this->out("plain = ");
                this->outx(plain, modbytes);
                this->outln();
                this->outln();

                if (modbytes == (size = pub(cipher, sizeof(cipher), plain, modbytes))) {
                    this->out("cipher = ");
                    this->outx(cipher, size);
                    this->outln();
                    this->outln();
                    
                    if (modbytes == (size = prv(decipher, sizeof(decipher), cipher, size))) {
                        this->out("decipher = ");
                        this->outx(decipher, size);
                        this->outln();
                        this->outln();
                        
                        this->out("pub --> prv ");

                        if (!(::memcmp(plain, decipher, size))) {
                            this->outln("success");
                        } else {
                            this->outln("failure");
                        }
                        this->outln();
                    }
                }
                if (modbytes == (size = prv(cipher, sizeof(cipher), plain, modbytes))) {
                    this->out("cipher = ");
                    this->outx(cipher, size);
                    this->outln();
                    this->outln();
                    
                    if (modbytes == (size = pub(decipher, sizeof(decipher), cipher, size))) {
                        this->out("decipher = ");
                        this->outx(decipher, size);
                        this->outln();
                        this->outln();
                        
                        this->out("prv --> pub ");

                        if (!(::memcmp(plain, decipher, size))) {
                            this->outln("success");
                        } else {
                            this->outln("failure");
                        }
                        this->outln();
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_mp_integer_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_BN[1])) {
                run_test_ = &Derives::run_test_bn;
            } else {
                if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_MP[1])) {
                    run_test_ = &Derives::run_test_mp;
                } else {
                    if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_MBU[1])) {
                        run_test_ = &Derives::run_test_mbu;
                    } else {
                        if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_NULL[1])) {
                            run_test_ = &Derives::run_test_null;
                        } else {
                            err = on_invalid_option_arg
                            (optval, optarg, optname, optind, argc, argv, env);
                        }
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:    
    enum {
        modbytes_min = 512/8,
        modbytes_max = 4096/8
    };
    byte_t plain[modbytes_max], 
           cipher[modbytes_max], 
           decipher[modbytes_max];
};

} // namespace rsa 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_RSA_MAIN_HPP 
