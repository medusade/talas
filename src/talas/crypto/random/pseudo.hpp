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
///   File: pseudo.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PSEUDO_HPP
#define _TALAS_CRYPTO_RANDOM_PSEUDO_HPP

#include "talas/crypto/random/generator.hpp"
#include "talas/io/logger.hpp"

#if defined(WINDOWS)
#include "rand_r.h"
#endif // defined(WINDOWS)

namespace talas {
namespace crypto {
namespace random {

typedef generator pseudo_implements;
typedef base pseudo_extends;
///////////////////////////////////////////////////////////////////////
///  Class: pseudot
///////////////////////////////////////////////////////////////////////
template
<class TImplements = pseudo_implements, class TExtends = pseudo_extends>

class _EXPORT_CLASS pseudot: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pseudot(unsigned seed): m_avail(0), m_seed(seed), m_rand(0) {
    }
    pseudot(): m_avail(0), m_seed(0), m_rand(0) {
    }
    virtual ~pseudot() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t generate(void* out, size_t size) {
        byte_t* bytes;

        if ((bytes = (byte_t*)(out))) {
            size_t i, j, count, length;

            for (length = 0; length < size; ) {

                if (1 > m_avail) {
                    if (!(m_seed)) {
                        time_t t = time(&t);
                        m_seed = (unsigned)(t);
                        TALAS_LOG_TRACE("seed = " << m_seed);
					}
                    m_rand = (unsigned)rand_r(&m_seed);
                    m_avail = sizeof(m_rand);
                    TALAS_LOG_TRACE("rand = " << m_rand);
                }

                if ((count = size-length) > m_avail)
                    count = m_avail;

                for (j = 0, i = 0; i < count; ++i) {
                    if ((bytes[length+j] = (byte_t)(m_rand & 0xFF))) {
                        ++j;
                    }
                    m_rand >>= 8;
                }

                length += j;
                m_avail -= count;
            }
            return size;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned seed(unsigned seed) {
        m_seed = seed;
        m_avail = 0;
        m_rand = 0;
        return m_seed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t m_avail;
    unsigned m_seed;
    unsigned m_rand;
};
typedef pseudot<> pseudo;

} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PSEUDO_HPP 
