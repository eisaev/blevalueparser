#pragma once

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
inline std::string enumToString(const VendorIdSourceEnum value)
{
    std::string str;

    switch (value)
    {
        case VendorIdSourceEnum::Unknown:   str = "<Unknown>";  break;
        case VendorIdSourceEnum::Bluetooth: str = "Bluetooth";  break;
        case VendorIdSourceEnum::USB:       str = "USB";        break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const VendorIdSourceEnum value)
{
    os << enumToString(value);
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
BVP_STRUCT(PnPID)
{
    VendorIdSourceStruct vendorIdSource;
    uint16_t vendorId{0};
    uint16_t productId{0};
    uint16_t productVersion{0};
};

// DIS_SPEC_V11r00.pdf
// Device Information Service v11r00
// 3.9 PnPID
class PnPID final : public BaseValueSpec<PnPID>
{
public:
    BVP_GETTER(VendorIdSourceEnum, vendorIdSource, PnPID)
    {
        return btSpecObject.vendorIdSource.vendorIdSource;
    }

    BVP_GETTER(uint16_t, vendorId, PnPID)
    {
        return btSpecObject.vendorId;
    }

    BVP_GETTER(uint16_t, productId, PnPID)
    {
        return btSpecObject.productId;
    }

    BVP_GETTER(uint8_t, majorVersion, PnPID)
    {
        return btSpecObject.productVersion >> 8;
    }

    BVP_GETTER(uint8_t, minorVersion, PnPID)
    {
        return btSpecObject.productVersion >> 4 & 0b1111;
    }

    BVP_GETTER(uint8_t, subMinorVersion, PnPID)
    {
        return btSpecObject.productVersion & 0b1111;
    }

private:
    BVP_CTORS(BaseValueSpec, PnPID)

    BVP_PARSE(PnPID)
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

    BVP_TO_STRING(PnPID)
    {
        (void)configuration;
        std::string str;

        str.append("(");
        str.append(enumToString(btSpecObject.vendorIdSource.vendorIdSource));
        str.append(")");

        fmt::format_to(
            std::back_inserter(str),
            // TODO: try to replace by local implementation (see HexString)
            " VID: 0x{:04X}",
            btSpecObject.vendorId
        );

        fmt::format_to(
            std::back_inserter(str),
            // TODO: try to replace by local implementation (see HexString)
            ", PID: 0x{:04X}",
            btSpecObject.productId
        );

        fmt::format_to(
            std::back_inserter(str),
            ", Version: {}.{}.{}",
            majorVersion(btSpecObject),
            minorVersion(btSpecObject),
            subMinorVersion(btSpecObject)
        );

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }
};

}  // namespace bvp
