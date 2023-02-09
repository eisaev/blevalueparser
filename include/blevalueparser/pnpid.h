#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

/*
 * Device Information Service
 * DIS_SPEC_V11r00.pdf
 */

// 3.9.1.1 Vendor ID Source Field (Table 3.2)
// GATT_Specification_Supplement_v8.pdf
// 3.169.1 Vendor ID Source field (Table 3.267)
enum class VendorIdSourceEnum
{
    Unknown     = 0,  // 0, 3–255 - Reserved for Future Use
    Bluetooth   = 1,
    USB         = 2
};

// GATT_Specification_Supplement_v8.pdf
// 3.169.1 Vendor ID Source field
struct VendorIdSourceStruct
{
    VendorIdSourceEnum vendorIdSource = VendorIdSourceEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.169 PnP ID
struct PnPIDStruct
{
    VendorIdSourceStruct vendorIdSource;
    uint16_t vendorId = 0;
    uint16_t productId = 0;
    uint16_t productVersion = 0;
};

// 3.9 PnPID
class PnPID final : public BaseValue
{
public:
    PnPIDStruct getBtSpecObject() const
    {
        return m_pnpId;
    }

    VendorIdSourceEnum vendorIdSource() const
    {
        return m_pnpId.vendorIdSource.vendorIdSource;
    }

    uint16_t vendorId() const
    {
        return m_pnpId.vendorId;
    }

    uint16_t productId() const
    {
        return m_pnpId.productId;
    }

    uint8_t majorVersion() const
    {
        return m_pnpId.productVersion >> 8;
    }

    uint8_t minorVersion() const
    {
        return m_pnpId.productVersion >> 4 & 0b1111;
    }

    uint8_t subMinorVersion() const
    {
        return m_pnpId.productVersion & 0b1111;
    }

private:
    friend class BLEValueParser;
    explicit PnPID(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit PnPID(const PnPIDStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_pnpId{btSpecObject}
    {
        m_isValid = true;
    }

    PnPIDStruct m_pnpId;

    static size_t expectedSize()
    {
        return 7;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.9.1.1 Vendor ID Source Field
        m_pnpId.vendorIdSource.vendorIdSource = VendorIdSourceEnum(parser.parseUInt8());
        switch (m_pnpId.vendorIdSource.vendorIdSource)
        {
        case VendorIdSourceEnum::Unknown:
        case VendorIdSourceEnum::Bluetooth ... VendorIdSourceEnum::USB:
            break;
        default:
            m_pnpId.vendorIdSource.vendorIdSource = VendorIdSourceEnum::Unknown;
            break;
        }
        // 3.9.1.2 Vendor ID Field
        m_pnpId.vendorId = parser.parseUInt16();
        // 3.9.1.3 Product ID Field
        m_pnpId.productId = parser.parseUInt16();

               // 3.9.1.4 Product Version Field
               // The value of the field value is 0xJJMN for version JJ.M.N
               // (JJ – major version number, M – minor version number, N – sub-minor version number)
        m_pnpId.productVersion = parser.parseUInt16();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "(";
        switch (m_pnpId.vendorIdSource.vendorIdSource)
        {
        case VendorIdSourceEnum::Unknown:
            ss << "<Unknown>";
            break;
        case VendorIdSourceEnum::Bluetooth:
            ss << "Bluetooth";
            break;
        case VendorIdSourceEnum::USB:
            ss << "USB";
            break;
        }
        ss << ") ";
        auto originalFlags = ss.flags();
        ss << "VID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_pnpId.vendorId << ", ";
        ss << "PID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_pnpId.productId << ", ";
        ss.flags(originalFlags);
        ss << "Version: " << static_cast<int>(majorVersion()) << "." << static_cast<int>(minorVersion()) << "." << static_cast<int>(subMinorVersion());
    }
};

}  // namespace bvp
