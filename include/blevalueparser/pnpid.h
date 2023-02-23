#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

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

// DIS_SPEC_V11r00.pdf
// Device Information Service v11r00
// 3.9 PnPID
class PnPID final : public BaseValueSpec<PnPIDStruct>
{
public:
    VendorIdSourceEnum vendorIdSource() const
    {
        return m_btSpecObject.vendorIdSource.vendorIdSource;
    }

    uint16_t vendorId() const
    {
        return m_btSpecObject.vendorId;
    }

    uint16_t productId() const
    {
        return m_btSpecObject.productId;
    }

    uint8_t majorVersion() const
    {
        return m_btSpecObject.productVersion >> 8;
    }

    uint8_t minorVersion() const
    {
        return m_btSpecObject.productVersion >> 4 & 0b1111;
    }

    uint8_t subMinorVersion() const
    {
        return m_btSpecObject.productVersion & 0b1111;
    }

private:
    BVP_CTORS(BaseValueSpec, PnPID, PnPIDStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.9.1.1 Vendor ID Source Field
        m_btSpecObject.vendorIdSource.vendorIdSource = VendorIdSourceEnum(parser.parseUInt8());
        switch (m_btSpecObject.vendorIdSource.vendorIdSource)
        {
            case VendorIdSourceEnum::Unknown:
            case VendorIdSourceEnum::Bluetooth:
            case VendorIdSourceEnum::USB:
                break;
            default:
                m_btSpecObject.vendorIdSource.vendorIdSource = VendorIdSourceEnum::Unknown;
                break;
        }
        // 3.9.1.2 Vendor ID Field
        m_btSpecObject.vendorId = parser.parseUInt16();
        // 3.9.1.3 Product ID Field
        m_btSpecObject.productId = parser.parseUInt16();

        // 3.9.1.4 Product Version Field
        // The value of the field value is 0xJJMN for version JJ.M.N
        // (JJ – major version number, M – minor version number, N – sub-minor version number)
        m_btSpecObject.productVersion = parser.parseUInt16();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "(";
        switch (m_btSpecObject.vendorIdSource.vendorIdSource)
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
        ss << "VID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_btSpecObject.vendorId << ", ";
        ss << "PID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_btSpecObject.productId << ", ";
        ss.flags(originalFlags);
        ss << "Version: " << static_cast<int>(majorVersion()) << "." << static_cast<int>(minorVersion()) << "." << static_cast<int>(subMinorVersion());
    }
};

}  // namespace bvp
