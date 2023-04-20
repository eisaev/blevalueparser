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

    BVP_PARSE(EstimatedServiceDateStruct)
    {
        bool result{true};

        result &= DateUTC::parse(parser, btSpecObject.estimatedServiceDate);

        return result;
    }

    BVP_TO_STRING(EstimatedServiceDateStruct)
    {
        return DateUTC::toStringInternal(btSpecObject.estimatedServiceDate);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }
};

}  // namespace bvp
