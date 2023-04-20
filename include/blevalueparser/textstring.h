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

    BVP_PARSE(TextStringStruct)
    {
        bool result{true};

        btSpecObject.textString = parser.parseString();

        return result;
    }

    BVP_TO_STRING(TextStringStruct)
    {
        return btSpecObject.textString;
    }

    virtual bool checkSize(size_t size) override
    {
        (void)size;
        return true;
    }
};

}  // namespace bvp
