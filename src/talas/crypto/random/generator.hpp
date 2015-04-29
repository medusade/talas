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
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_GENERATOR_HPP
#define _TALAS_CRYPTO_RANDOM_GENERATOR_HPP

#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace random {

typedef base_implements generator_implements;
///////////////////////////////////////////////////////////////////////
///  Class: generatort
///////////////////////////////////////////////////////////////////////
template <class TImplements = generator_implements>

class _EXPORT_CLASS generatort: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t generate(void* out, size_t size) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef generatort<> generator;

} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_GENERATOR_HPP
