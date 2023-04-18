#pragma once

#include "basevalue.h"
#include "dateutc.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.88 Estimated Service Date

struct EstimatedServiceDateStruct
{
    DateUTCStruct estimatedServiceDate;
};

class EstimatedServiceDate final : public BaseValueSpec<EstimatedServiceDateStruct>
{
public:
    BVP_GETTER(uint64_t, days, EstimatedServiceDateStruct)
    {
        return DateUTC::days(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(time_t, date, EstimatedServiceDateStruct)
    {
        return DateUTC::date(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint16_t, year, EstimatedServiceDateStruct)
    {
        return DateUTC::year(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint8_t, month, EstimatedServiceDateStruct)
    {
        return DateUTC::month(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint8_t, day, EstimatedServiceDateStruct)
    {
        return DateUTC::day(btSpecObject.estimatedServiceDate);
    }

private:
    BVP_CTORS(BaseValueSpec, EstimatedServiceDate, EstimatedServiceDateStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }

    BVP_PARSE(EstimatedServiceDateStruct)
    {
        bool result{true};

        result &= DateUTC::parse(parser, btSpecObject.estimatedServiceDate);

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << DateUTC(m_btSpecObject.estimatedServiceDate, configuration());
    }
};

}  // namespace bvp
