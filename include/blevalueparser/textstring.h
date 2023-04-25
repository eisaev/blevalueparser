#pragma once

#include "basevalue.h"


namespace bvp
{

BVP_STRUCT(TextString)
{
    std::string textString;
};

class TextString final : public BaseValueSpec<TextString>
{
public:
    BVP_GETTER(std::string, textString, TextString)
    {
        return btSpecObject.textString;
    }

private:
    BVP_CTORS(BaseValueSpec, TextString)

    BVP_PARSE(TextString)
    {
        bool result{true};

        btSpecObject.textString = parser.parseString();

        return result;
    }

    BVP_TO_STRING(TextString)
    {
        (void)configuration;
        return btSpecObject.textString;
    }

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }
};

}  // namespace bvp
