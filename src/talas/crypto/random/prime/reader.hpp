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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 5/1/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_READER_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_READER_HPP

#include "talas/crypto/random/reader.hpp"

namespace talas {
namespace crypto {
namespace random {
namespace prime {

typedef crypto::base_implements reader_implements;
typedef crypto::random::reader reader_random;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<typename TBIGPRIME, class TImplements = reader_implements>

class _EXPORT_CLASS readert: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef TBIGPRIME BIGPRIME;
    typedef reader_random random_t;

    typedef base_implements observer_implements;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: observer
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS observer: virtual public observer_implements {
    public:
        typedef observer_implements Implements;

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t on_read(BIGPRIME* n, size_t bytes) {
            observer* delegated = observer_delegated(n);
            if ((delegated))
                return delegated->on_read(n, bytes);
            return bytes;
        }
        virtual observer* observer_delegated(BIGPRIME* n) const {
            return 0;
        }

        ///////////////////////////////////////////////////////////////////////
        /// deprecated
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t OnRead(BIGPRIME* n, size_t bytes) {
            observer* delegated = ObserverDelegated(n);
            if ((delegated))
                return delegated->OnRead(n, bytes);
            bytes = this->on_read(n, bytes);
            return bytes;
        }
        virtual observer* ObserverDelegated(BIGPRIME* n) const {
            return 0;
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_msb(BIGPRIME* n, size_t bytes, random_t& random) {
        return 0;
    }
    virtual ssize_t get(byte_t& byte, random_t& random) {
        ssize_t count = 0;
        if ((no_remove_zeros())) {
            count = random.read(&byte, 1);
        } else {
            do {
                if (0 >= (count = random.read(&byte, 1))) {
                    return count;
                }
            } while (!(byte & 0xF) || !(byte & 0xF0));
        }
        return count;
    }
    virtual bool no_remove_zeros() const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    /// deprecated
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadMSB(BIGPRIME* n, size_t bytes, random_t& random) {
        return this->read_msb(n, bytes, random);
    }
    virtual ssize_t Get(BYTE& byte, random_t& random) {
        return this->get(byte, random);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace prime
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_READER_HPP
