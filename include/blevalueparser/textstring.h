#pragma once

#include "basevalue.h"


namespace bvp
{

class TextString final : public BaseValue
{
public:
    std::string textString() const
    {
        return m_textString;
    }

private:
    friend class BLEValueParser;
    explicit TextString(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    std::string m_textString;

    virtual bool checkSize(size_t size) override
    {
        return true;
    }

    virtual bool parse(Parser &parser) override
    {
        m_textString = parser.parseString();
        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_textString;
    }
};

}  // namespace bvp
