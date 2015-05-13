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
///   File: miller_rabin.hpp
///
/// Author: $author$
///   Date: 5/4/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_MILLER_RABIN_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_MILLER_RABIN_HPP

#include "talas/crypto/random/prime/reader.hpp"

#define TALAS_CRYPTO_RANDOM_PRIME_MILLER_RABIN_REPS 25

namespace talas {
namespace crypto {
namespace random {
namespace prime {

///////////////////////////////////////////////////////////////////////
///  Class: miller_rabint
///////////////////////////////////////////////////////////////////////
template
<typename TBIGPRIME,
 class TReader, class TRandom,
 class TImplements, class TExtends = base>

class _EXPORT_CLASS miller_rabint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TReader reader_t;
    typedef TRandom random_t;
    typedef TBIGPRIME BIGPRIME;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    miller_rabint
    (unsigned reps = TALAS_CRYPTO_RANDOM_PRIME_MILLER_RABIN_REPS)
    : m_reps(reps) {
    }
    virtual ~miller_rabint() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool probably_prime
    (BIGPRIME* n, size_t bytes, random_t& random) {
        return this->probably_prime(n, bytes, reps(), random);
    }
    virtual bool probably_prime
    (BIGPRIME* n, size_t bytes, unsigned reps, random_t& random) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    /// deprecated
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProbablyPrime
    (BIGPRIME* n, size_t bytes, random_t& random) {
        return this->probably_prime(n, bytes, random);
    }
    virtual bool ProbablyPrime
    (BIGPRIME* n, size_t bytes, unsigned reps, random_t& random) {
        return this->probably_prime(n, bytes, reps, random);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned set_reps(unsigned to) {
        m_reps = to;
        return m_reps;
    }
    virtual unsigned reps() const {
        return m_reps;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_reps;
};

} // namespace prime
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_MILLER_RABIN_HPP 
