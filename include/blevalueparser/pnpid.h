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
inline std::ostream &operator<<(std::ostream &os, const VendorIdSourceEnum value)
{
    switch (value)
    {
        case VendorIdSourceEnum::Unknown:   os << "<Unknown>";  break;
        case VendorIdSourceEnum::Bluetooth: os << "Bluetooth";  break;
        case VendorIdSourceEnum::USB:       os << "USB";        break;
    }

    return os;
}
inline VendorIdSourceEnum &operator%=(VendorIdSourceEnum &lhs, const VendorIdSourceEnum &rhs)
{
    lhs = VendorIdSourceEnum::Unknown;

    switch (rhs)
    {
        case VendorIdSourceEnum::Unknown:
        case VendorIdSourceEnum::Bluetooth:
        case VendorIdSourceEnum::USB:
            lhs = rhs;
            break;
    }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.169.1 Vendor ID Source field
struct VendorIdSourceStruct
{
    VendorIdSourceEnum vendorIdSource{VendorIdSourceEnum::Unknown};
};

// GATT_Specification_Supplement_v8.pdf
// 3.169 PnP ID
struct PnPIDStruct
{
    VendorIdSourceStruct vendorIdSource;
    uint16_t vendorId{0};
    uint16_t productId{0};
    uint16_t productVersion{0};
};

// DIS_SPEC_V11r00.pdf
// Device Information Service v11r00
// 3.9 PnPID
class PnPID final : public BaseValueSpec<PnPIDStruct>
{
public:
    BVP_GETTER(VendorIdSourceEnum, vendorIdSource, PnPIDStruct)
    {
        return btSpecObject.vendorIdSource.vendorIdSource;
    }

    BVP_GETTER(uint16_t, vendorId, PnPIDStruct)
    {
        return btSpecObject.vendorId;
    }

    BVP_GETTER(uint16_t, productId, PnPIDStruct)
    {
        return btSpecObject.productId;
    }

    BVP_GETTER(uint8_t, majorVersion, PnPIDStruct)
    {
        return btSpecObject.productVersion >> 8;
    }

    BVP_GETTER(uint8_t, minorVersion, PnPIDStruct)
    {
        return btSpecObject.productVersion >> 4 & 0b1111;
    }

    BVP_GETTER(uint8_t, subMinorVersion, PnPIDStruct)
    {
        return btSpecObject.productVersion & 0b1111;
    }

private:
    BVP_CTORS(BaseValueSpec, PnPID, PnPIDStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }

    BVP_PARSE(PnPIDStruct)
    {
        bool result{true};

        // 3.9.1.1 Vendor ID Source Field
        btSpecObject.vendorIdSource.vendorIdSource %= VendorIdSourceEnum(parser.parseUInt8());
        // 3.9.1.2 Vendor ID Field
        btSpecObject.vendorId = parser.parseUInt16();
        // 3.9.1.3 Product ID Field
        btSpecObject.productId = parser.parseUInt16();

        // 3.9.1.4 Product Version Field
        // The value of the field value is 0xJJMN for version JJ.M.N
        // (JJ – major version number, M – minor version number, N – sub-minor version number)
        btSpecObject.productVersion = parser.parseUInt16();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "(" << m_btSpecObject.vendorIdSource.vendorIdSource << ")";
        auto originalFlags = oss.flags();
        oss <<  " VID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_btSpecObject.vendorId;
        oss << ", PID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_btSpecObject.productId;
        oss.flags(originalFlags);
        oss << ", Version: "
            <<        static_cast<int>(majorVersion())
            << "." << static_cast<int>(minorVersion())
            << "." << static_cast<int>(subMinorVersion());
    }
};

}  // namespace bvp
