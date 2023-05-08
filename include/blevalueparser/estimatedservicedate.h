#pragma once

#include "basevalue.h"
#include "dateutc.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.88 Estimated Service Date

BVP_STRUCT(EstimatedServiceDate)
{
    Struct<DateUTC> estimatedServiceDate;
};

class EstimatedServiceDate final : public BaseValueSpec<EstimatedServiceDate>
{
public:
    BVP_GETTER(uint64_t, days, EstimatedServiceDate)
    {
        return DateUTC::days(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(time_t, date, EstimatedServiceDate)
    {
        return DateUTC::date(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint16_t, year, EstimatedServiceDate)
    {
        return DateUTC::year(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint8_t, month, EstimatedServiceDate)
    {
        return DateUTC::month(btSpecObject.estimatedServiceDate);
    }

    BVP_GETTER(uint8_t, day, EstimatedServiceDate)
    {
        return DateUTC::day(btSpecObject.estimatedServiceDate);
    }

private:
    BVP_CTORS(BaseValueSpec, EstimatedServiceDate)

    BVP_PARSE(EstimatedServiceDate)
    {
        bool result{true};

        result &= DateUTC::parse(parser, btSpecObject.estimatedServiceDate);

        return result;
    }

    BVP_TO_STRING(EstimatedServiceDate)
    {
        return DateUTC::toStringInternal(btSpecObject.estimatedServiceDate, configuration);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }
};

}  // namespace bvp
