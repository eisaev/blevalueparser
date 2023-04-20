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

    BVP_PARSE(NewAlertStruct)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.numberOfNewAlert = parser.parseUInt8();
        btSpecObject.textStringInformation = parser.parseString();

        return result;
    }

    BVP_TO_STRING(NewAlertStruct)
    {
        std::string str;

        str.append("Category: ");
        str.append(enumToString(btSpecObject.categoryID.categoryID));

        fmt::format_to(
            std::back_inserter(str),
            ", NumberOfNewAlert: {}",
            btSpecObject.numberOfNewAlert
        );

        str.append(", RecentAlertBrief: '");
        str.append(btSpecObject.textStringInformation);
        str.append("'");

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 1 && size < 21;
    }
};

}  // namespace bvp
