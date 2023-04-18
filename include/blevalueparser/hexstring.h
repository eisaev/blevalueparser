#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

struct HexStringStruct
{
    std::string rawString;
};

class HexString final : public BaseValueSpec<HexStringStruct>
{
public:
    BVP_GETTER(std::string, rawString, HexStringStruct)
    {
        return btSpecObject.rawString;
    }

private:
    BVP_CTORS(BaseValueSpec, HexString, HexStringStruct)

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }

    BVP_PARSE(HexStringStruct)
    {
        bool result{true};

        btSpecObject.rawString = parser.parseString();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
// Stringstreams is too slooooOOO00OOOoooow!
#if 0  // x1: ~239ns, x8: ~938ns, x64: ~5526ns, x512: ~40468ns
        std::ostringstream ossTmp;
        ossTmp << configuration().hexPrefix;
        for (auto c : m_btSpecObject.rawString)
        {
            ossTmp << std::uppercase
                   << std::setfill('0')
                   << std::setw(2)
                   << std::hex
                   << static_cast<int>(c)
                   << configuration().hexSeparator;
        }
        std::string hexString = ossTmp.str();
#else  // x1: ~98ns (x2.4), x8: ~274ns (x3.4), x64: ~1061ns (x5.2), x512: ~5455ns (x7.4)
        std::string hexString = configuration().hexPrefix;

        constexpr std::array<char, 16> hexChars{
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        for (auto c : m_btSpecObject.rawString)
        {
            hexString.push_back(hexChars[(c & 0xF0) >> 4]);
            hexString.push_back(hexChars[c & 0x0F]);
            hexString.append(configuration().hexSeparator);
        }
#endif
        hexString.pop_back();

        oss << hexString;
    }
};

}  // namespace bvp
