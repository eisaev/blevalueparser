#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.239 User Index

struct UserIndexStruct
{
    uint8_t userIndex = 0;
};

class UserIndex final : public BaseValueSpec<UserIndexStruct>
{
public:
    friend class BodyCompositionMeasurement;

    uint8_t userIndex() const
    {
        return m_btSpecObject.userIndex;
    }

private:
    BVP_CTORS(BaseValueSpec, UserIndex, UserIndexStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.userIndex = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        if (0xFF == m_btSpecObject.userIndex)
        {
            ss << "<Unknown User>";
            return;
        }

        ss << static_cast<int>(m_btSpecObject.userIndex);
    }
};

}  // namespace bvp
