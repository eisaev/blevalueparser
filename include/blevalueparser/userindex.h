#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.239 User Index

BVP_STRUCT(UserIndex)
{
    uint8_t userIndex{0};
};

class UserIndex final : public BaseValueSpec<UserIndex>
{
public:
    friend class BodyCompositionMeasurement;

    BVP_GETTER(uint8_t, userIndex, UserIndex)
    {
        return btSpecObject.userIndex;
    }

private:
    BVP_CTORS(BaseValueSpec, UserIndex)

    BVP_PARSE(UserIndex)
    {
        bool result{true};

        btSpecObject.userIndex = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(UserIndex)
    {
        (void)configuration;

        if (0xFF == btSpecObject.userIndex)
        {
            return "<Unknown User>";
        }

        return fmt::format("{}", btSpecObject.userIndex);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
