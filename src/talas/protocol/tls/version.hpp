///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: version.hpp
///
/// Author: $author$
///   Date: 2/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_VERSION_HPP
#define _TALAS_PROTOCOL_TLS_VERSION_HPP

#include "talas/base/base.hpp"
#include <list>

namespace talas {
namespace protocol {
namespace tls {

typedef unsigned version_major_t;
typedef unsigned version_minor_t;

typedef implement_base versiont_implements;
typedef base versiont_extends;
///////////////////////////////////////////////////////////////////////
///  Class: versiont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = versiont_implements, class TExtends = versiont_extends>

class _EXPORT_CLASS versiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    versiont(version_major_t major, version_minor_t minor)
    : major_(major), minor_(minor) {
    }
    versiont(const versiont& copy)
    : major_(copy.major_), minor_(copy.minor_) {
    }
    versiont()
    : major_(0), minor_(0) {
    }
    virtual ~versiont() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual version_major_t major() const {
        return major_;
    }
    virtual version_minor_t minor() const {
        return minor_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator bool() const {
        if ((major_) || (minor_)) {
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    version_major_t major_;
    version_minor_t minor_;
};
typedef versiont<> version;

typedef implement_base versionst_implements;
typedef ::std::list<version> versionst_extends;
///////////////////////////////////////////////////////////////////////
///  Class: versionst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = versionst_implements, class TExtends = versionst_extends>

class _EXPORT_CLASS versionst: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    versionst(const tls::version& min, const tls::version& max) {
        this->push_back(min);
        this->push_back(max);
    }
    versionst(const tls::version& version) {
        this->push_back(version);
    }
    versionst() {
    }
    versionst(const versionst& copy): Extends(copy) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef versionst<> versions;

} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_VERSION_HPP 
