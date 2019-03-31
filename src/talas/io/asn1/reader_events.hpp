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
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_READER_EVENTS_HPP
#define _TALAS_IO_ASN1_READER_EVENTS_HPP

#include "talas/io/asn1/block.hpp"
#include "talas/io/asn1/length.hpp"
#include "talas/io/asn1/type.hpp"
#include "talas/io/asn1/form.hpp"
#include "talas/io/asn1/class.hpp"
#include "talas/io/asn1/base.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements reader_eventst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_eventst_implements>
class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef reader_eventst Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Block(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;
        
        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Block(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1PrimativeBlock(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;
        
        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1PrimativeBlock(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1ConstructBlock(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;
        
        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructBlock(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1UndefinedBlock(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;
        
        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1UndefinedBlock(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Construct(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Construct(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1ConstructBegin(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructBegin(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1ConstructEnd(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructEnd(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructAny(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructAny(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructBoolean(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructBoolean(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructInteger(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructInteger(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructBitString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructBitString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructOctetString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructOctetString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructNull(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructNull(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructObjectID(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructObjectID(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructObject(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructObject(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructExternal(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructExternal(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructReal(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructReal(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructEnum(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructEnum(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructSequence(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructSequence(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructSet(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructSet(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructNumericString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructNumericString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructPrintableString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructPrintableString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructTeletexString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructTeletexString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructVideotexString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructVideotexString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructIA5String(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructIA5String(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructUTCTime(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructUTCTime(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructGeneralizedTime(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructGeneralizedTime(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructGraphicString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructGraphicString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructVisibleString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructVisibleString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructGeneralString(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructGeneralString(reader, asn1Block))) {
                return count;
            }
        }
        count = onAsn1Construct(reader, asn1Block);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Primative(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Primative(byte, bytes, asn1Block))) {
                return count;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Any(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Any(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Boolean(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Boolean(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Integer(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Integer(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1BitString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1BitString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1OctetString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1OctetString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Null(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Null(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ObjectID(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ObjectID(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Object(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Object(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1External(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1External(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Real(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Real(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Enum(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Enum(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Sequence(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Sequence(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Set(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Set(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1NumericString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1NumericString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1PrintableString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1PrintableString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1TeletexString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1TeletexString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1VideotexString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1VideotexString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1IA5String(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1IA5String(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1UTCTime(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1UTCTime(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1GeneralizedTime(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1GeneralizedTime(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1GraphicString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1GraphicString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1VisibleString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1VisibleString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1GeneralString(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1GeneralString(byte, bytes, asn1Block))) {
                return count;
            }
        }
        count = onAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructDefault(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructDefault(reader, asn1Block))) {
                return count;
            }
        }
        return count;
    }
    virtual ssize_t onAsn1PrimativeDefault(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        reader_eventst* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_eventst&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1PrimativeDefault(byte, bytes, asn1Block))) {
                return count;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_eventst* delegatedTo(reader_eventst& events) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS reader_eventst

typedef reader_eventst<> reader_events;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_READER_EVENTS_HPP
