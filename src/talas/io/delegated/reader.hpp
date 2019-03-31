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
///   Date: 3/28/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_DELEGATED_READER_HPP
#define _TALAS_IO_DELEGATED_READER_HPP

#include "talas/io/reader.hpp"

namespace talas {
namespace io {
namespace delegated {

///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template 
<class TReader, class TImplements = implement_base>

class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TReader reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_read(what_t* what, size_t size) {
        return size;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS reader_eventst

typedef reader_eventst<io::reader> reader_events;

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TReader, 
 class TReaderEvents = reader_eventst<TReader>, 
 class TImplements = TReader, class TExtends = base>

class _EXPORT_CLASS readert
: virtual public TReaderEvents, virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TReader reader_t;
    typedef TReaderEvents reader_events_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(reader_events_t& reader_events, reader_t& reader)
    : reader_(reader), reader_events_(reader_events) {
    }
    readert(reader_t& reader): reader_(reader), reader_events_(*this) {
    }
    readert(const readert& copy)
    : reader_(copy.reader_), reader_events_(copy.reader_events_) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::read;
    virtual ssize_t read() {
        ssize_t count = 0, amount = 0;
        sized_t sized = (sized_t)(0);
        while (0 != (amount = this->read(&sized, 1))) {
            if (0 > (amount)) {
                return amount;
            }
            count += amount;
        }
        return count;
    }
    virtual ssize_t read(what_t* what, size_t size) {
        ssize_t count = 0;
        if (0 < (count = reader_.read(what, size))) {
            count = this->on_read(what, size);
        }
        return count;
    }
    virtual ssize_t fill() {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t seek(ssize_t offset, int whence) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t tell() {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t eof() {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_read(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_read(what, size);
        }
        return size;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_t& reader_;
    reader_events_t& reader_events_;
}; /// class _EXPORT_CLASS readert

typedef readert<io::reader> reader;

} /// namespace delegated
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_DELEGATED_READER_HPP
