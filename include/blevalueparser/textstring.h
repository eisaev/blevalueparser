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
    BVP_GETTER(std::string, textString, TextStringStruct)
    {
        return btSpecObject.textString;
    }

private:
    BVP_CTORS(BaseValueSpec, TextString, TextStringStruct)

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }

    BVP_PARSE(TextStringStruct)
    {
        bool result{true};

        btSpecObject.textString = parser.parseString();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.textString;
    }
};

}  // namespace bvp
