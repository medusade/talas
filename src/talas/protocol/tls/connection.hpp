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
///   File: connection.hpp
///
/// Author: $author$
///   Date: 2/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_CONNECTION_HPP
#define _TALAS_PROTOCOL_TLS_CONNECTION_HPP

#include "talas/io/reader.hpp"
#include "talas/io/writer.hpp"
#include "talas/base/base.hpp"

namespace talas {
namespace protocol {
namespace tls {

typedef io::reader connectiont_reader_implements;
typedef io::writer connectiont_writer_implements;
///////////////////////////////////////////////////////////////////////
///  Class: connectiont
///////////////////////////////////////////////////////////////////////
template
<class TReaderImplements = connectiont_reader_implements,
 class TWriterImplements = connectiont_writer_implements>

class _EXPORT_CLASS connectiont
: virtual public TReaderImplements, virtual public TWriterImplements {
public:
    typedef TReaderImplements ReaderImplements;
    typedef TWriterImplements WriterImplements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ReaderImplements& reader() const {
        return ((ReaderImplements&)(*this));
    }
    virtual WriterImplements& writer() const {
        return ((WriterImplements&)(*this));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef connectiont<> connection;

} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_CONNECTION_HPP 
