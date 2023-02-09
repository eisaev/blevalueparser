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

class UserIndex final : public BaseValue
{
public:
    friend class BodyCompositionMeasurement;

    UserIndexStruct getBtSpecObject() const
    {
        return m_userIndex;
    }

    uint8_t userIndex() const
    {
        return m_userIndex.userIndex;
    }

private:
    friend class BLEValueParser;
    explicit UserIndex(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit UserIndex(const UserIndexStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_userIndex{btSpecObject}
    {
        m_isValid = true;
    }

    UserIndexStruct m_userIndex;

    static size_t expectedSize()
    {
        return 1;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        m_userIndex.userIndex = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        if (0xFF == m_userIndex.userIndex)
        {
            ss << "<Unknown User>";
            return;
        }

        ss << static_cast<int>(m_userIndex.userIndex);
    }
};

}  // namespace bvp
