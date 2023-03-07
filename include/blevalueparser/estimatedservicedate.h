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
    uint64_t days() const
    {
        return DateUTC(m_btSpecObject.estimatedServiceDate, configuration).days();
    }

    time_t date() const
    {
        return DateUTC(m_btSpecObject.estimatedServiceDate, configuration).date();
    }

    uint16_t year() const
    {
        return DateUTC(m_btSpecObject.estimatedServiceDate, configuration).year();
    }

    uint8_t month() const
    {
        return DateUTC(m_btSpecObject.estimatedServiceDate, configuration).month();
    }

    uint8_t day() const
    {
        return DateUTC(m_btSpecObject.estimatedServiceDate, configuration).day();
    }

private:
    BVP_CTORS(BaseValueSpec, EstimatedServiceDate, EstimatedServiceDateStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.estimatedServiceDate = DateUTC(parser, configuration).getBtSpecObject();

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << DateUTC(m_btSpecObject.estimatedServiceDate, configuration);
    }
};

}  // namespace bvp
