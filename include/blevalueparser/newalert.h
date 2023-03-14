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
    static AlertCategoryIDEnum categoryID(const NewAlertStruct &btSpecObject)
    {
        return btSpecObject.categoryID.categoryID;
    }
    AlertCategoryIDEnum categoryID() const
    {
        return categoryID(m_btSpecObject);
    }

    static uint8_t numberOfNewAlert(const NewAlertStruct &btSpecObject)
    {
        return btSpecObject.numberOfNewAlert;
    }
    uint8_t numberOfNewAlert() const
    {
        return numberOfNewAlert(m_btSpecObject);
    }

    static std::string recentAlertBrief(const NewAlertStruct &btSpecObject)
    {
        return btSpecObject.textStringInformation;
    }
    std::string recentAlertBrief() const
    {
        return recentAlertBrief(m_btSpecObject);
    }

private:
    BVP_CTORS(BaseValueSpec, NewAlert, NewAlertStruct)

    virtual bool checkSize(size_t size) override
    {
        return size > 1 && size < 21;
    }

    static bool parse(Parser &parser, NewAlertStruct &btSpecObject)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.numberOfNewAlert = parser.parseUInt8();
        btSpecObject.textStringInformation = parser.parseString();

        return result;
    }
    virtual bool parse(Parser &parser) override
    {
        return parse(parser, m_btSpecObject);
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Category: " << m_btSpecObject.categoryID.categoryID;
        oss << ", NumberOfNewAlert: " << static_cast<int>(m_btSpecObject.numberOfNewAlert);
        oss << ", RecentAlertBrief: '" << m_btSpecObject.textStringInformation << "'";
    }
};

}  // namespace bvp
