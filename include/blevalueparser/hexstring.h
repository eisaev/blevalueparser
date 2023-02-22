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
        std::stringstream ss;
        ss << configuration.hexPrefix;
        while (!parser.atEnd())
        {
            ss << std::uppercase
               << std::setfill('0')
               << std::setw(2)
               << std::hex
               << static_cast<int>(parser.parseUInt8())
               << configuration.hexSeparator;
        }
        m_btSpecObject.hexString = ss.str();
        m_btSpecObject.hexString.pop_back();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_btSpecObject.hexString;
    }
};

}  // namespace bvp
