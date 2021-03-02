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
///   File: file.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_IO_FILE_HPP
#define TALAS_IO_FILE_HPP

#include "xos/io/file/stream.hpp"

namespace talas {
namespace io {

///////////////////////////////////////////////////////////////////////
/// class filet
///////////////////////////////////////////////////////////////////////
template 
<typename TWhat = void, typename TSized = char, typename TEnd = int, TEnd VEnd = 0,
 class TExtends = xos::io::file::streamt<TWhat, TSized, TEnd, VEnd>, 
 class TImplements = typename TExtends::Implements>
class EXPORT_CLASS filet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef filet Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    filet(const filet& copy): Extends(copy) {
    }
    filet() {
    }
    virtual ~filet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class filet
typedef filet<> file;

} /// namespace io 
} /// namespace talas 

#endif /// ndef TALAS_IO_FILE_HPP 