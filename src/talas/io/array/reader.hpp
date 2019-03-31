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
///   Date: 3/30/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ARRAY_READER_HPP
#define _TALAS_IO_ARRAY_READER_HPP

#include "xos/io/array/reader.hpp"
#include "talas/io/reader.hpp"
#include "talas/base/array.hpp"

namespace talas {
namespace io {
namespace array {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TArray, class TReader, 
 class TExtends = ::xos::io::array::readert<TArray, TReader> >

class _EXPORT_CLASS readert: public TExtends {
public:
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TArray array_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy): Extends(copy) {
    }
    readert(const array_t& array): Extends(array) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS readert

typedef readert<byte_array_t, io::byte_reader> byte_reader;

} /// namespace array
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ARRAY_READER_HPP
