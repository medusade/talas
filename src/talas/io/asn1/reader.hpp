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
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_READER_HPP
#define _TALAS_IO_ASN1_READER_HPP

#include "talas/io/asn1/reader_events.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef asn1::reader_events readert_implements;
typedef base_t readert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = readert_implements, class TExtends = readert_extends>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef reader_events::Derives ReaderEvents;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const readert& copy): m_delegatedTo(0) {
    }
    readert(): m_delegatedTo(0) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(io::byte_reader& reader) {
        ssize_t count = 0, amount = 0;
        asn1::block_t asn1Block;

        do {
            if (0 < (amount = asn1Block.read(reader))) {
                count += amount;

                if (0 < (amount = this->onAsn1Block(reader, asn1Block))) {
                    count += amount;
                }
            }
        } while (amount > 0);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Block(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_events&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1Block(reader, asn1Block))) {
                return count;
            }
        }
        asn1::form_t::value_t asn1FormValue = asn1Block.form_value();

        switch(asn1FormValue) {
        case asn1::form_t::Primative:
            count = this->onAsn1PrimativeBlock(reader, asn1Block);
            break;

        case asn1::form_t::Construct:
            count = this->onAsn1ConstructBlock(reader, asn1Block);
            break;

        default:
            count = this->onAsn1UndefinedBlock(reader, asn1Block);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1ConstructBlock(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        LOG_DEBUG("...");
        if ((delegatedTo = this->delegatedTo((reader_events&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1ConstructBlock(reader, asn1Block))) {
                return count;
            }
        }
        asn1::type_t::value_t asn1TypeValue = asn1Block.type_value();

        switch(asn1TypeValue) {

        case asn1::type_t::Any:
            count = this->onAsn1ConstructAny(reader, asn1Block);
            break;

        case asn1::type_t::Boolean:
            count = this->onAsn1ConstructBoolean(reader, asn1Block);
            break;

        case asn1::type_t::Integer:
            count = this->onAsn1ConstructInteger(reader, asn1Block);
            break;

        case asn1::type_t::BitString:
            count = this->onAsn1ConstructBitString(reader, asn1Block);
            break;

        case asn1::type_t::OctetString:
            count = this->onAsn1ConstructOctetString(reader, asn1Block);
            break;

        case asn1::type_t::Null:
            count = this->onAsn1ConstructNull(reader, asn1Block);
            break;

        case asn1::type_t::ObjectID:
            count = this->onAsn1ConstructObjectID(reader, asn1Block);
            break;

        case asn1::type_t::Object:
            count = this->onAsn1ConstructObject(reader, asn1Block);
            break;

        case asn1::type_t::External:
            count = this->onAsn1ConstructExternal(reader, asn1Block);
            break;

        case asn1::type_t::Real:
            count = this->onAsn1ConstructReal(reader, asn1Block);
            break;

        case asn1::type_t::Enum:
            count = this->onAsn1ConstructEnum(reader, asn1Block);
            break;

        case asn1::type_t::Sequence:
            count = this->onAsn1ConstructSequence(reader, asn1Block);
            break;

        case asn1::type_t::Set:
            count = this->onAsn1ConstructSet(reader, asn1Block);
            break;

        case asn1::type_t::NumericString:
            count = this->onAsn1ConstructNumericString(reader, asn1Block);
            break;

        case asn1::type_t::PrintableString:
            count = this->onAsn1ConstructPrintableString(reader, asn1Block);
            break;

        case asn1::type_t::TeletexString:
            count = this->onAsn1ConstructTeletexString(reader, asn1Block);
            break;

        case asn1::type_t::VideotexString:
            count = this->onAsn1ConstructVideotexString(reader, asn1Block);
            break;

        case asn1::type_t::IA5String:
            count = this->onAsn1ConstructIA5String(reader, asn1Block);
            break;

        case asn1::type_t::UTCTime:
            count = this->onAsn1ConstructUTCTime(reader, asn1Block);
            break;

        case asn1::type_t::GeneralizedTime:
            count = this->onAsn1ConstructGeneralizedTime(reader, asn1Block);
            break;

        case asn1::type_t::GraphicString:
            count = this->onAsn1ConstructGraphicString(reader, asn1Block);
            break;

        case asn1::type_t::VisibleString:
            count = this->onAsn1ConstructVisibleString(reader, asn1Block);
            break;

        case asn1::type_t::GeneralString:
            count = this->onAsn1ConstructGeneralString(reader, asn1Block);
            break;

        default:
            count = this->onAsn1Construct(reader, asn1Block);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Construct(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->onAsn1Construct(reader, asn1Block)))
            return count;

        io::sized::byte_reader sizedReader(reader, asn1Block.length());
        ssize_t amount = 0;

        if (0 > (amount = this->onAsn1ConstructBegin(reader, asn1Block)))
            return amount;

        if (0 > (count = read(sizedReader)))
            return count;

        if (0 > (amount = this->onAsn1ConstructEnd(reader, asn1Block)))
            return amount;

        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1PrimativeBlock(io::byte_reader& reader, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((reader_events&)(*this)))) {
            if (0 != (count = delegatedTo->onAsn1PrimativeBlock(reader, asn1Block))) {
                return count;
            }
        }
        size_t  asn1Length = asn1Block.length();
        ssize_t amount = 0;
        byte_t* bytes = 0;
        byte_array_t primativeData;

        LOG_DEBUG("length = " << asn1Length);
        if ((asn1Length == (primativeData.set_length(asn1Length)))
            && (bytes = primativeData.elements())) {

            if (asn1Length == (count = reader.read(bytes, asn1Length))) {

                if (0 > (amount = this->onAsn1Primative(*bytes, asn1Length, asn1Block))) {
                    return amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t onAsn1Primative(const byte_t& byte, size_t bytes, const asn1::block_t& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = this->delegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->onAsn1Primative(byte, bytes, asn1Block)))
            return count;

        asn1::type_t::value_t asn1TypeValue = asn1Block.type_value();
        const char* asn1TypeName = asn1Block.type_name();
        LOG_DEBUG("type = " << asn1TypeValue << " \"" << asn1TypeName << "\"");

        switch(asn1TypeValue) {

        case asn1::type_t::Any:
            count = this->onAsn1Any(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Boolean:
            count = this->onAsn1Boolean(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Integer:
            count = this->onAsn1Integer(byte, bytes, asn1Block);
            break;

        case asn1::type_t::BitString:
            count = this->onAsn1BitString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::OctetString:
            count = this->onAsn1OctetString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Null:
            count = this->onAsn1Null(byte, bytes, asn1Block);
            break;

        case asn1::type_t::ObjectID:
            count = this->onAsn1ObjectID(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Object:
            count = this->onAsn1Object(byte, bytes, asn1Block);
            break;

        case asn1::type_t::External:
            count = this->onAsn1External(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Real:
            count = this->onAsn1Real(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Enum:
            count = this->onAsn1Enum(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Sequence:
            count = this->onAsn1Sequence(byte, bytes, asn1Block);
            break;

        case asn1::type_t::Set:
            count = this->onAsn1Set(byte, bytes, asn1Block);
            break;

        case asn1::type_t::NumericString:
            count = this->onAsn1NumericString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::PrintableString:
            count = this->onAsn1PrintableString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::TeletexString:
            count = this->onAsn1TeletexString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::VideotexString:
            count = this->onAsn1VideotexString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::IA5String:
            count = this->onAsn1IA5String(byte, bytes, asn1Block);
            break;

        case asn1::type_t::UTCTime:
            count = this->onAsn1UTCTime(byte, bytes, asn1Block);
            break;

        case asn1::type_t::GeneralizedTime:
            count = this->onAsn1GeneralizedTime(byte, bytes, asn1Block);
            break;

        case asn1::type_t::GraphicString:
            count = this->onAsn1GraphicString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::VisibleString:
            count = this->onAsn1VisibleString(byte, bytes, asn1Block);
            break;

        case asn1::type_t::GeneralString:
            count = this->onAsn1GeneralString(byte, bytes, asn1Block);
            break;

        default:
            count = this->onAsn1PrimativeDefault(byte, bytes, asn1Block);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ReaderEvents* delegatedTo(ReaderEvents& events) const {
        return m_delegatedTo;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ReaderEvents* m_delegatedTo;
}; /// class _EXPORT_CLASS readert

typedef readert<> reader;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_READER_HPP
