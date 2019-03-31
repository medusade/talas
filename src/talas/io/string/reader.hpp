///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   Date: 3/26/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_STRING_READER_HPP
#define _TALAS_IO_STRING_READER_HPP

#include "xos/io/string/reader.hpp"
#include "talas/base/string.hpp"

namespace talas {
namespace io {
namespace string {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<typename TString, class TExtends = ::xos::io::string::readert<TString> >

class _EXPORT_CLASS readert: public TExtends {
public:
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TString string_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy): Extends(copy) {
    }
    readert(string_t& string): Extends(string) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS readert

typedef readert<string_t> reader;

} /// namespace string
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_STRING_READER_HPP
