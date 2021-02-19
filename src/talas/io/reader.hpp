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
///   Date: 4/27/2015, 2/15/2021
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_READER_HPP
#define _TALAS_IO_READER_HPP

#include "talas/base/base.hpp"
#include "xos/io/reader.hpp"
#include "xos/io/told.hpp"

namespace talas {
namespace io {

typedef xos::io::from_t from_t;
enum {
    from_begin   = xos::io::from_begin,
    from_end     = xos::io::from_end,
    from_current = xos::io::from_current
};

typedef xos::io::reader reader;
typedef xos::io::char_reader char_reader;
typedef xos::io::byte_reader byte_reader;

///////////////////////////////////////////////////////////////////////
/// class readert
///////////////////////////////////////////////////////////////////////
template 
<typename TWhat = void, typename TSized = char,  typename TEnd = int, TEnd VEnd = 0, 
 class TImplements = xos::io::readert<TWhat, TSized, TEnd, VEnd> >
class EXPORT_CLASS readert: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef readert Derives;

    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TSized char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_crlf(what_t* what, size_t size) { 
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size)) {
            static const sized_t cr = ((sized_t)'\r');
            static const sized_t lf = ((sized_t)'\n');
            sized_t c = ((sized_t)0);
            ssize_t amount = 0, count = 0;
            
            for (bool cr_read = false; size; --size, ++sized) {
                if (0 < (amount = this->read(sized, 1))) {
                    ++count;
                    if (lf == (c = *sized)) {
                        if ((cr_read)) {
                            return count;
                        } else {
                            cr_read = (cr == (c = *sized));
                        }
                    } else {
                        cr_read = (cr == (c = *sized));
                    }
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class readert

namespace sized {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TReader = reader, class TImplements = TReader, class TExtends = base>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TReader reader_t;
    typedef typename TImplements::what_t  what_t;
    typedef typename TImplements::sized_t  sized_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy)
    : m_reader(copy.m_reader), m_length(copy.m_length), m_size(copy.m_size), m_tell(0) {
    }
    readert(reader_t& reader, ssize_t length, size_t tell = 0)
    : m_reader(reader), m_length(length), m_size(length), m_tell(tell) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) { 
        if ((what) && (0 < size)) {
            ssize_t length = 0;
            if (0 > (length = this->length())) {
                length = m_reader.read(what, size);
            } else {
                size_t tell = 0;
                if (length < (((tell = this->tell()) + size))) {
                    size = length - tell;
                }
                if (0 < (length = m_reader.read(what, size))) {
                    this->set_tell(tell + length);
                }
            }
            return length;
        }
        return 0; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t seek(ssize_t offset, int whence = from_begin) { 
        return -1; 
    }
    virtual ssize_t set_tell(size_t to) {
        return m_tell = to;
    }
    virtual ssize_t tell() const {
        return m_tell;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_length(ssize_t to) {
        return m_length = to;
    }
    virtual ssize_t length() const {
        return m_length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_size(ssize_t to) {
        return m_size = to;
    }
    virtual ssize_t size() const {
        return m_size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_t& m_reader;
    ssize_t m_size, m_length;
    size_t m_tell;
}; /// class _EXPORT_CLASS readert

typedef readert<io::reader> reader;
typedef readert<io::char_reader> char_reader;
typedef readert<io::byte_reader> byte_reader;

} // namespace sized

} // namespace io
} // namespace talas 

#endif // _TALAS_IO_READER_HPP 
