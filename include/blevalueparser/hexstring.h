#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

class HexString final : public BaseValue
{
public:
    std::string hexString() const
    {
        return m_hexString;
    }

private:
    friend class BLEValueParser;

    explicit HexString(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit HexString(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    std::string m_hexString;

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
        m_hexString = ss.str();
        m_hexString.pop_back();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_hexString;
    }
};

}  // namespace bvp
