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
///   File: read_to_string.hpp
///
/// Author: $author$
///   Date: 3/28/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_PEM_READ_TO_STRING_HPP
#define _TALAS_IO_PEM_READ_TO_STRING_HPP

#include "talas/io/pem/reader.hpp"
#include "talas/base/string.hpp"

namespace talas {
namespace io {
namespace pem {

///////////////////////////////////////////////////////////////////////
///  Class: read_to_stringt
///////////////////////////////////////////////////////////////////////
template 
<class TString, class TReaderEvents, 
 class TImplements = TReaderEvents, class TExtends = TString>

class _EXPORT_CLASS read_to_stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef read_to_stringt Derives;

    typedef TReaderEvents reader_events_t;
    typedef typename reader_events_t::what_t what_t;
    typedef typename reader_events_t::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    read_to_stringt(const read_to_stringt& copy): Extends(copy) {
    }
    read_to_stringt() {
    }
    virtual ~read_to_stringt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_begin(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_base64(what_t* what, size_t size) {
        const char_t* chars = 0;
        if ((chars = (const char_t*)(what)) && (size)) {
            this->append(chars, size);
        }
        return size;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS read_to_stringt

typedef read_to_stringt<string_t, reader_events> read_to_string;

} /// namespace pem
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_PEM_READ_TO_STRING_HPP
