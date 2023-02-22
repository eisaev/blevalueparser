#pragma once

#include "basevalue.h"


namespace bvp
{

struct TextStringStruct
{
    std::string textString;
};

class TextString final : public BaseValueSpec<TextStringStruct>
{
public:
    std::string textString() const
    {
        return m_btSpecObject.textString;
    }

private:
    BVP_CTORS(BaseValueSpec, TextString, TextStringStruct)

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.textString = parser.parseString();
        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_btSpecObject.textString;
    }
};

}  // namespace bvp
