#pragma once

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

    BVP_PARSE(HexStringStruct)
    {
        bool result{true};

        btSpecObject.rawString = parser.parseString();

        return result;
    }

    BVP_TO_STRING_CONF(HexStringStruct)
    {
        std::string str;

        const std::string separator{configuration.hexSeparator};

        str.append(configuration.hexPrefix);

        constexpr std::array<char, 16> hexChars{
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };

        const size_t rawStringSize{btSpecObject.rawString.size()};
        const size_t separatorSize{separator.size()};
        const size_t size{configuration.hexPrefix.size() + rawStringSize * (2 + separatorSize)};

#if 0
        // Easy to read version without stringstreams
        // String<HexString>/1         47.5 ns         47.5 ns     10804804
        // String<HexString>/8          151 ns          151 ns      4681147
        // String<HexString>/64         566 ns          566 ns      1232047
        // String<HexString>/512       4058 ns         4057 ns       172167
        str.reserve(size);

        for (auto c : btSpecObject.rawString)
        {
            str.push_back(hexChars[(c & 0xF0) >> 4]);
            str.push_back(hexChars[c & 0x0F]);
            str.append(separator);
        }
#else
        // Hacky version (next one is plain C or Assembler?)
        // String<HexString>/1         46.0 ns         46.0 ns     11073146
        // String<HexString>/8         98.1 ns         98.1 ns      7154611 (x1.54)
        // String<HexString>/64         191 ns          191 ns      3658046 (x2.96)
        // String<HexString>/512        965 ns          964 ns       728044 (x4.2)
        str.resize(size);

        size_t o{configuration.hexPrefix.size()};
        for (size_t i{0}; i < rawStringSize; ++i)
        {
            const char c{btSpecObject.rawString[i]};
            str[o] = hexChars[(c & 0xF0) >> 4];
            ++o;
            str[o] = hexChars[c & 0x0F];
            ++o;
            for (size_t s{0}; s < separatorSize; ++s)
            {
                str[o] = separator[s];
                ++o;
            }
        }
#endif

        str.pop_back();

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }
};

}  // namespace bvp
