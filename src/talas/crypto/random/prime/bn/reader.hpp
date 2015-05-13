///////////////////////////////////////////////////////////////////////
/// Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
/// All rights reserved.
///
/// This package is an SSL implementation written
/// by Eric Young (eay@cryptsoft.com).
/// The implementation was written so as to conform with Netscapes SSL.
///
/// This library is free for commercial and non-commercial use as long as
/// the following conditions are aheared to.  The following conditions
/// apply to all code found in this distribution, be it the RC4, RSA,
/// lhash, DES, etc., code; not just the SSL code.  The SSL documentation
/// included with this distribution is covered by the same copyright terms
/// except that the holder is Tim Hudson (tjh@cryptsoft.com).
///
/// Copyright remains Eric Young's, and as such any Copyright notices in
/// the code are not to be removed.
/// If this package is used in a product, Eric Young should be given attribution
/// as the author of the parts of the library used.
/// This can be in the form of a textual message at program startup or
/// in documentation (online or textual) provided with the package.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
/// 1. Redistributions of source code must retain the copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. All advertising materials mentioning features or use of this software
///    must display the following acknowledgement:
///    "This product includes cryptographic software written by
///     Eric Young (eay@cryptsoft.com)"
///    The word 'cryptographic' can be left out if the rouines from the library
///    being used are not cryptographic related :-).
/// 4. If you include any Windows specific code (or a derivative thereof) from
///    the apps directory (application code) you must include an acknowledgement:
///    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
///
/// THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
///
/// The licence and distribution terms for any publically available version or
/// derivative of this code cannot be changed.  i.e. this code cannot simply be
/// copied and put under another distribution licence
/// [including the GNU Public Licence.]
///
///   File: reader.hpp
///
/// Author: $author$
///   Date: 5/2/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_BN_READER_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_BN_READER_HPP

#include "talas/crypto/random/prime/reader.hpp"
#include "talas/crypto/random/prime/bn/number.hpp"
#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace bn {

typedef crypto::random::prime::readert<BIGPRIME> reader_implements;
typedef reader_implements::observer reader_observer;
typedef crypto::base reader_extends;
///////////////////////////////////////////////////////////////////////
///  Class: reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS reader
: virtual public reader_observer, virtual public reader_implements, public reader_extends {
public:
    typedef reader_implements Implements;
    typedef reader_extends Extends;
    typedef reader_observer observer_t;
    typedef reader_random random_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    reader(observer_t* observer = 0): m_observer(observer) {
    }
    virtual ~reader() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_msb(number& n, size_t bytes, random_t& random) {
        BIGPRIME* detached = 0;
        if ((detached = n.attached_to())) {
            return read_msb(detached, bytes, random);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_msb(BIGPRIME* n, size_t bytes, random_t& random) {
        byte_t byte = 0;
        BN_set_word(n, 0);
        for (size_t i=0; i<bytes; i++) {
            if (0 >= (this->get(byte, random)))
                return 0;
            BN_lshift(n,n,8);
            BN_add_word(n,byte);
        }
        bytes = this->on_read(n, bytes);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual observer_t* observer_delegated(BIGPRIME* n) const {
        return m_observer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    observer_t* m_observer;
};

} // namespace bn
} // namespace prime
} // namespace random
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_BN_READER_HPP
