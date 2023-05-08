#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.154 New Alert
BVP_STRUCT(NewAlert)
{
    Struct<AlertCategoryID> categoryID;
    uint8_t numberOfNewAlert{0};
    std::string textStringInformation;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.2 New Alert
class NewAlert final : public BaseValueSpec<NewAlert>
{
public:
    BVP_GETTER(AlertCategoryIDEnum, categoryID, NewAlert)
    {
        return btSpecObject.categoryID.categoryID;
    }

    BVP_GETTER(uint8_t, numberOfNewAlert, NewAlert)
    {
        return btSpecObject.numberOfNewAlert;
    }

    BVP_GETTER(std::string, recentAlertBrief, NewAlert)
    {
        return btSpecObject.textStringInformation;
    }

private:
    BVP_CTORS(BaseValueSpec, NewAlert)

    BVP_PARSE(NewAlert)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.numberOfNewAlert = parser.parseUInt8();
        btSpecObject.textStringInformation = parser.parseString();

        return result;
    }

    BVP_TO_STRING(NewAlert)
    {
        (void)configuration;
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
