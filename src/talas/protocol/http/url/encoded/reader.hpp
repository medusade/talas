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
#ifndef TALAS_PROTOCOL_HTTP_URL_ENCODED_READER_HPP
#define TALAS_PROTOCOL_HTTP_URL_ENCODED_READER_HPP

#include "talas/io/reader.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace url {
namespace encoded {

/// class readert
template <class TImplements = io::reader, class TExtends = extend>
class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives;

    typedef implements reader_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::what_t what_t;
    
    /// constructor / destructor
    readert(const readert& copy): reader_(copy.reader_) {
    }
    readert(reader_t& reader): reader_(reader) {
    }
    virtual ~readert() {
    }

    /// read / fill
    virtual ssize_t read(what_t* what, size_t size) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what)) && (size)) {
            ssize_t count = 0, amount = 0;
            byte_t x1 = 0, x2 = 0;
            char c = 0;

            while (count < size) {
                if (0 < (amount = reader_.read(sized, 1))) {
                    switch (c = ((char)*sized)) {
                    case '%':
                        if (0 < (amount = read_x(x1, sized))) {
                            if (0 < (amount = read_x(x2, sized))) {
                                *sized = ((sized_t)((x1 << 4) | x2));
                            } else {
                                return amount;
                            }
                        } else {
                            return amount;
                        }
                        break;

                    case '+':
                        *sized = ((sized_t)' ');
                        break;

                    default:
                        break;
                    }
                    ++sized;
                    ++count;
                } else {
                    return amount;
                }
            }
            return count;
        }
        return 0;
    }    
    virtual ssize_t fill() {
        return reader_.fill();
    }    

protected:
    /// ...x...
    virtual ssize_t read_x(byte_t& x, what_t* what) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what))) {
            ssize_t amount = 0;

            if (0 < (amount = reader_.read(what, 1))) {
                const char c = ((char)*sized);

                if (is_x(c)) {
                    x = to_x(c);
                } else {
                    return 0;
                }
            }
            return amount;
        }
        return 0;
    }
    static inline bool is_x(char x) {
        bool is = (((x >= '0') && (x <= '9')) 
                  || ((x >= 'a') && (x <= 'f')) 
                  || ((x >= 'A') && (x <= 'F')));
        return is;
    }
    static inline char to_x(char x) {
        char to = (((x >= '0') && (x <= '9'))?(x - '0')
                  :(((x >= 'a') && (x <= 'f'))?((x -'a') + 10)
                  :((x -'A') + 10)));
        return to;
    }

protected:
    reader_t& reader_;
}; /// class readert
typedef readert<> reader;

} /// namespace encoded
} /// namespace url
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_URL_ENCODED_READER_HPP 
