#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.154 New Alert
struct NewAlertStruct
{
    AlertCategoryIDStruct categoryID;
    uint8_t numberOfNewAlert{0};
    std::string textStringInformation;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.2 New Alert
class NewAlert final : public BaseValueSpec<NewAlertStruct>
{
public:
    BVP_GETTER(AlertCategoryIDEnum, categoryID, NewAlertStruct)
    {
        return btSpecObject.categoryID.categoryID;
    }

    BVP_GETTER(uint8_t, numberOfNewAlert, NewAlertStruct)
    {
        return btSpecObject.numberOfNewAlert;
    }

    BVP_GETTER(std::string, recentAlertBrief, NewAlertStruct)
    {
        return btSpecObject.textStringInformation;
    }

private:
    BVP_CTORS(BaseValueSpec, NewAlert, NewAlertStruct)

    virtual bool checkSize(size_t size) override
    {
        return size > 1 && size < 21;
    }

    BVP_PARSE(NewAlertStruct)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.numberOfNewAlert = parser.parseUInt8();
        btSpecObject.textStringInformation = parser.parseString();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Category: " << m_btSpecObject.categoryID.categoryID;
        oss << ", NumberOfNewAlert: " << static_cast<int>(m_btSpecObject.numberOfNewAlert);
        oss << ", RecentAlertBrief: '" << m_btSpecObject.textStringInformation << "'";
    }
};

}  // namespace bvp
