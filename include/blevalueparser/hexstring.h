#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

struct HexStringStruct
{
    std::string hexString;
};

class HexString final : public BaseValueSpec<HexStringStruct>
{
public:
    std::string hexString() const
    {
        return m_btSpecObject.hexString;
    }

private:
    BVP_CTORS(BaseValueSpec, HexString, HexStringStruct)

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }

    virtual bool parse(Parser &parser) override
    {
// Don't use stringstreams in parser! It's slooooOOO00OOOoooow!
#if 0  // x1: ~187ns, x8: ~820ns, x64: ~5303ns, x512: ~41865ns
        std::ostringstream oss;
        oss << configuration.hexPrefix;
        while (!parser.atEnd())
        {
            oss << std::uppercase
                << std::setfill('0')
                << std::setw(2)
                << std::hex
                << static_cast<int>(parser.parseUInt8())
                << configuration.hexSeparator;
        }
        m_btSpecObject.hexString = oss.str();
#else  // x1: ~40ns (x4.6), x8: ~157ns (x5.2), x64: ~743ns (x7.1), x512: ~4504ns (x9.3)
        m_btSpecObject.hexString = configuration.hexPrefix;

        constexpr std::array<char, 16> hexChars{
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        while (!parser.atEnd())
        {
            uint8_t byte = parser.parseUInt8();
            m_btSpecObject.hexString.push_back(hexChars[(byte & 0xF0) >> 4]);
            m_btSpecObject.hexString.push_back(hexChars[byte & 0x0F]);
            m_btSpecObject.hexString.append(configuration.hexSeparator);
        }
#endif
        m_btSpecObject.hexString.pop_back();

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.hexString;
    }
};

}  // namespace bvp
