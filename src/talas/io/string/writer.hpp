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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 3/26/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_STRING_WRITER_HPP
#define _TALAS_IO_STRING_WRITER_HPP

#include "xos/io/string/writer.hpp"

namespace talas {
namespace io {
namespace string {

///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template 
<class TString, 
 class TExtends = ::xos::io::string::writert<TString> >

class _EXPORT_CLASS writert: public TExtends {
public:
    typedef TExtends Extends;
    typedef writert Derives;

    typedef TString string_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(const writert& copy): Extends(copy) {
    }
    writert(string_t& string): Extends(string) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS writert

} /// namespace string
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_STRING_WRITER_HPP
