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
///   File: generator.hpp
///
/// Author: $author$
///   Date: 5/2/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_GENERATOR_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_GENERATOR_HPP

#include "talas/crypto/base.hpp"

//#define _RSA_NO_SMALL_PRIME_TEST
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
#include "talas/crypto/random/prime/small_primes.hpp"
#define _RSA_SMALL_PRIME_DIFFERENCE 0x7
#else // !defined(_RSA_NO_SMALL_PRIME_TEST)
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)

//#define _RSA_NO_MILLER_RABIN_TEST
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
#define _RSA_MILLER_RABIN_REPS 25
#else // !defined(_RSA_NO_MILLER_RABIN_TEST)
#endif // !defined(_RSA_NO_MILLER_RABIN_TEST)

namespace talas {
namespace crypto {
namespace random {
namespace prime {

typedef crypto::base_implements generator_implements;
typedef crypto::base generator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: generatort
///////////////////////////////////////////////////////////////////////
template
<typename TBIGPRIME,
 class TImplements = generator_implements,
 class TExtends = generator_extends>

class _EXPORT_CLASS generatort: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TBIGPRIME BIGPRIME;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    generatort():
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
      m_no_miller_rabin_test(false),
      m_miller_rabin_reps(_RSA_MILLER_RABIN_REPS),
#else // !defined(_RSA_NO_MILLER_RABIN_TEST)
      m_no_miller_rabin_test(true),
#endif // !defined(_RSA_NO_MILLER_RABIN_TEST)
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
      m_no_small_prime_test(false),
      m_small_primes(g_small_primes),
      m_small_prime_difference(_RSA_SMALL_PRIME_DIFFERENCE)
#else // !defined(_RSA_NO_SMALL_PRIME_TEST)
      m_no_small_prime_test(true)
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)
    {
    }
    virtual ~generatort() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_no_miller_rabin_test(bool to = true) {
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
        m_no_miller_rabin_test = to;
#endif // !defined(_RSA_NO_MILLER_RABIN_TEST)
        return m_no_miller_rabin_test;
    }
    virtual bool no_miller_rabin_test() const {
        return m_no_miller_rabin_test;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_no_small_prime_test(bool to = true) {
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
        m_no_small_prime_test = to;
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)
        return m_no_small_prime_test;
    }
    virtual bool no_small_prime_test() const {
        return m_no_small_prime_test;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
    bool m_no_miller_rabin_test;
    unsigned m_miller_rabin_reps;
#else // !defined(_RSA_NO_MILLER_RABIN_TEST)
    const bool m_no_miller_rabin_test;
#endif // !defined(_RSA_NO_MILLER_RABIN_TEST)
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
    bool m_no_small_prime_test;
    const unsigned short* m_small_primes;
    long m_small_prime_difference;
    long m_moduli[SMALL_PRIMES_SIZE];
#else // !defined(_RSA_NO_SMALL_PRIME_TEST)
    const bool m_no_small_prime_test;
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)
};

} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_GENERATOR_HPP
