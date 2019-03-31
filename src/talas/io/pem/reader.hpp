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
#ifndef _TALAS_IO_PEM_READER_HPP
#define _TALAS_IO_PEM_READER_HPP

#include "talas/io/delegated/reader.hpp"

namespace talas {
namespace io {
namespace pem {

///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template 
<class TReader, 
 class TImplements = io::delegated::reader_eventst<TReader> >

class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TReader reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_begin(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_base64(what_t* what, size_t size) {
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
 class TExtends = io::delegated::readert<TReader, TReaderEvents> >

class _EXPORT_CLASS readert: virtual public TReaderEvents, public TExtends {
public:
    typedef TExtends Extends;
    typedef readert Derives;

    typedef TReader reader_t;
    typedef TReaderEvents reader_events_t;
    typedef typename Extends::what_t what_t;
    typedef typename Extends::sized_t sized_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(reader_events_t& reader_events, reader_t& reader)
    : Extends(reader_events, reader), on_read_(0), reader_events_(reader_events) {
    }
    readert(const readert& copy)
    : Extends(copy), on_read_(0), reader_events_(copy.reader_events_) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_begin(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_begin(what, size);
        }
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_end(what, size);
        }
        return size;
    }
    virtual ssize_t on_base64(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_base64(what, size);
        }
        return size;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ssize_t (Derives::*on_read_)(what_t* what, size_t size);
    virtual ssize_t on_read(what_t* what, size_t size) {
        ssize_t count = size;
        if ((on_read_)) {
            (this->*on_read_)(what, size);
        } else {
            this->on_read_begin(what, size);
        }
        return count;
    }
    virtual ssize_t on_read_begin(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what))) {
            switch (((char)(*sized))) {
            case '\n':
                on_read_ = &Derives::on_read_base64;
                break;
            }
        }
        return count;
    }
    virtual ssize_t on_read_end(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what))) {
            switch (((char)(*sized))) {
            default:
                break;
            }
        }
        return count;
    }
    virtual ssize_t on_read_base64(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what))) {
            switch (((char)(*sized))) {
            case '\n':
            case '\r':
            case '\t':
            case '\v':
                break;
            case'-':
                on_read_ = &Derives::on_read_end;
                break;
            default:
                this->on_base64(what, size);
                break;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_events_t& reader_events_;
}; /// class _EXPORT_CLASS readert

typedef readert<io::reader> reader;

} /// namespace pem
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_PEM_READER_HPP
