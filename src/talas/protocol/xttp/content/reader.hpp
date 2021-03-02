///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_READER_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_READER_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {

/// class readert
template <class TImplements = message::part::reader_t, class TExtends = extend>
class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives;

    typedef implements reader_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::what_t what_t;

    typedef io::from_t from_t;
    enum { from_begining = io::from_begining,
           from_end = io::from_end,
           from_current = io::from_current };

    /// constructor / destructor
    readert(const readert& copy): reader_(copy.reader_), length_(copy.length_), tell_(copy.length_) {
    }
    readert(reader_t& reader, size_t length): reader_(reader), length_(length), tell_(0) {
    }
    virtual ~readert() {
    }

    /// read / fill
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size)) {
            size_t length = this->length_;
            ssize_t count = 0;

            if (0 < (length)) {
                size_t tell = this->tell_;

                if ((length > (tell))) {
                    if (length < (tell + size)) {
                        if (1 > (size = length - tell)) {
                            return 0;
                        }
                    }
                    if (0 < (count = reader_.read(what, size))) {
                        this->tell_ += count;
                        return count;
                    }
                }
            } else {
                if (0 < (count = reader_.read(what, size))) {
                    this->tell_ += count;
                    return count;
                }
            }
        }
        return 0;
    }    
    virtual ssize_t fill() {
        return reader_.fill();
    }    

    /// reset / seek / tell
    virtual ssize_t reset() {
        ssize_t told = tell_;
        tell_ = 0;
        return told;
    }
    virtual ssize_t seek(size_t to) {
        return seek(to, from_begining);
    }
    virtual ssize_t seek(size_t to, int whence) {
        size_t length = 0;
        if (0 < (length = length_)) {
            if (from_end == (whence)) {
                if (length < (to)) {
                    to = 0;
                } else {
                    to = length - to;
                }
            } else {
                if (from_current == (whence)) {
                    if (length < (to += tell_)) {
                        to = length;
                    }
                } else {
                    if (length < (to)) {
                        to = length;
                    }
                }
            }
            tell_ = to;
        }
        return tell_;
    }
    virtual ssize_t tell() const {
        return tell_;
    }
    virtual size_t length() const {
        return length_;
    }

protected:
    reader_t& reader_;
    size_t length_, tell_;
}; /// class readert
typedef readert<> reader;

} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_READER_HPP 
