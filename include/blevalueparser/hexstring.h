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
        const std::string separator{configuration().hexSeparator};

// Stringstreams is too slooooOOO00OOOoooow!
#if 0
        // C++ way using stringstreams
        // x1: ~277ns, x8: ~990ns, x64: ~5747ns, x512: ~42328ns
        std::ostringstream ossTmp;
        ossTmp << configuration().hexPrefix;
        for (auto c : m_btSpecObject.rawString)
        {
            ossTmp << std::uppercase
                   << std::setfill('0')
                   << std::setw(2)
                   << std::hex
                   << static_cast<int>(c)
                   << separator;
        }
        std::string hexString = ossTmp.str();
#else
        std::string hexString{configuration().hexPrefix};

        constexpr std::array<char, 16> hexChars{
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };

        const size_t rawStringSize{m_btSpecObject.rawString.size()};
        const size_t separatorSize{separator.size()};
        const size_t size{configuration().hexPrefix.size() + rawStringSize * (2 + separatorSize)};

#if 0
        // Easy to read version without stringstreams
        // x1: ~145ns (x1.9), x8: ~303ns (x3.3), x64: ~967ns (x5.9), x512: ~5283ns (x8)
        hexString.reserve(size);

        for (auto c : m_btSpecObject.rawString)
        {
            hexString.push_back(hexChars[(c & 0xF0) >> 4]);
            hexString.push_back(hexChars[c & 0x0F]);
            hexString.append(separator);
        }
#else
        // Hacky version (next one is plain C or Assembler?)
        // x1: ~146ns (x1.9), x8: ~253ns (x3.9), x64: ~554ns (x10.4), x512: ~1970ns (x21.5)
        hexString.resize(size);

        size_t o{configuration().hexPrefix.size()};
        for (size_t i{0}; i < rawStringSize; ++i)
        {
            const char c{m_btSpecObject.rawString[i]};
            hexString[o] = hexChars[(c & 0xF0) >> 4];
            ++o;
            hexString[o] = hexChars[c & 0x0F];
            ++o;
            for (size_t s{0}; s < separatorSize; ++s)
            {
                hexString[o] = separator[s];
                ++o;
            }
        }
#endif
#endif
        hexString.pop_back();

        oss << hexString;
    }
};

}  // namespace bvp
