#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.239 User Index

struct UserIndexStruct
{
    uint8_t userIndex{0};
};

class UserIndex final : public BaseValueSpec<UserIndexStruct>
{
public:
    friend class BodyCompositionMeasurement;

    BVP_GETTER(uint8_t, userIndex, UserIndexStruct)
    {
        return btSpecObject.userIndex;
    }

private:
    BVP_CTORS(BaseValueSpec, UserIndex, UserIndexStruct)

    BVP_PARSE(UserIndexStruct)
    {
        bool result{true};

        btSpecObject.userIndex = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(UserIndexStruct)
    {
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
