#pragma once

#include <string>
#include <sstream>
#include <map>

#define BVP_CTORS(TBase, T, TStruct) \
    friend class BLEValueParser;\
\
    explicit T(Parser &parser, const Configuration &configuration) :\
        TBase{configuration}\
    {\
        create(parser);\
    }\
\
    explicit T(const char *data, size_t size, const Configuration &configuration) :\
        TBase{configuration}\
    {\
        create(data, size);\
    }\
\
    explicit T(const TStruct &btSpecObject, const Configuration &configuration) :\
        TBase{btSpecObject, configuration}\
    {}


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.34.1 Flags field (Table 3.57: Flags field, 1st bit)
// See also 3.250.1 Flags field (Table 3.366: Flags field, 1st bit)
enum class MeasurementUnitsEnum
{
    SI          = 0, // kg & m
    Imperial    = 1  // lb & in
};

struct Configuration
{
    std::string stringPrefix = "";
    std::string stringSuffix = "";
    std::string hexPrefix = "0x ";
    std::string hexSeparator = ":";
    MeasurementUnitsEnum measurementUnits = MeasurementUnitsEnum::SI;

    float massToUnits(uint16_t value) const
    {
        static const std::map<MeasurementUnitsEnum, float> massCoeff{
            { MeasurementUnitsEnum::SI, 0.005},
            { MeasurementUnitsEnum::Imperial, 0.01 }
        };
        return massCoeff.at(measurementUnits) * value;
    }

    std::string massUnits() const
    {
        static const std::map<MeasurementUnitsEnum, std::string> massAbbr{
            { MeasurementUnitsEnum::SI, "kg" },
            { MeasurementUnitsEnum::Imperial, "lb" }
        };
        return massAbbr.at(measurementUnits);
    }

    float lenghtToUnits(uint16_t value) const
    {
        static const std::map<MeasurementUnitsEnum, float> lenghtCoeff{
            { MeasurementUnitsEnum::SI, 0.001},
            { MeasurementUnitsEnum::Imperial, 0.1 }
        };
        return lenghtCoeff.at(measurementUnits) * value;
    }

    std::string lenghtUnits() const
    {
        static const std::map<MeasurementUnitsEnum, std::string> lenghtAbbr{
            { MeasurementUnitsEnum::SI, "m" },
            { MeasurementUnitsEnum::Imperial, "in" }
        };
        return lenghtAbbr.at(measurementUnits);
    }
};

class BaseValue
{
public:
    virtual ~BaseValue() = default;

    Configuration configuration;

    bool isValid() const
    {
        return m_isValid;
    }

    std::string toString() const
    {
        if (!m_isValid)
        {
            return "<Invalid>";
        }

        std::stringstream ss;
        ss << configuration.stringPrefix;
        toStringStream(ss);
        ss << configuration.stringSuffix;
        return ss.str();
    }

protected:
    explicit BaseValue(const Configuration &configuration) :
        configuration{configuration}
    {}

    bool m_isValid{false};

    // For testing protected Parser class
    friend class InternalParserTest;
    friend class InternalParserTest_Raw_Test;
    friend class InternalParserTest_String_Test;
    friend class InternalParserTest_UInt8_Test;
    friend class InternalParserTest_UInt16_Test;
    friend class InternalParserTest_UInt32_Test;
    friend class InternalParserTest_UInt64_Test;
    friend class InternalParserTest_Int8_Test;
    friend class InternalParserTest_Int16_Test;
    friend class InternalParserTest_Int32_Test;
    friend class InternalParserTest_Int64_Test;
    friend class InternalParserTest_Raw_OutOfData_Test;
    friend class InternalParserTest_Int_OutOfData_Test;

    class Parser
    {
    public:
        explicit Parser(const char* data, size_t size) :
            m_data{data},
            m_size{size},
            m_offset{0},
            m_outOfData{false}
        {}

        size_t offset() const
        {
            return m_offset;
        }

        bool atEnd() const
        {
            return m_offset >= m_size;
        }

        bool outOfData() const
        {
            return m_outOfData;
        }

        const char *getRawData(size_t size)
        {
            const char *result = m_data + m_offset;
            m_outOfData = m_offset + size > m_size;
            m_offset += size;
            return result;
        }

        std::string parseString()
        {
            std::string result{m_data, m_size};
            m_offset += m_size;
            return result;
        }

        uint8_t parseUInt8()
        {
            return parseInt<uint8_t>();
        }

        uint16_t parseUInt16()
        {
            return parseInt<uint16_t>();
        }

        uint32_t parseUInt32()
        {
            return parseInt<uint32_t>();
        }

        uint64_t parseUInt64()
        {
            return parseInt<uint64_t>();
        }

        int8_t parseInt8()
        {
            return parseInt<int8_t>();
        }

        int16_t parseInt16()
        {
            return parseInt<int16_t>();
        }

        int32_t parseInt32()
        {
            return parseInt<int32_t>();
        }

        int64_t parseInt64()
        {
            return parseInt<int64_t>();
        }

    private:
        const char *m_data;
        size_t m_size;
        size_t m_offset;
        bool m_outOfData;

        template <typename T>
        T parseInt()
        {
            uint64_t result = 0;

            constexpr size_t offsetDiff = sizeof(T);
            m_outOfData = m_offset + offsetDiff > m_size;
            if (!m_outOfData)
            {
                for (size_t i = 0; i < offsetDiff; ++i)
                {
                    uint8_t b = m_data[m_offset];
                    result += static_cast<uint64_t>(b) << 8 * i;
                    ++m_offset;
                }
            }

            return static_cast<T>(result);
        }
    };

    void create(Parser &parser)
    {
        m_isValid = parse(parser) && !parser.outOfData();
    }

    void create(const char *data, size_t size)
    {
        if (!checkSize(size))
        {
            return;
        }

        Parser parser{data, size};
        create(parser);
    }

    virtual bool checkSize(size_t size) = 0;
    virtual bool parse(Parser &parser) = 0;
    virtual void toStringStream(std::stringstream &ss) const = 0;

    friend std::ostream& operator<<(std::ostream &os, const BaseValue& rhs)
    {
        os << rhs.toString();
        return os;
    }
};

template<class TStruct>
class BaseValueSpec : public BaseValue
{
public:
    virtual ~BaseValueSpec() = default;

    TStruct getBtSpecObject() const
    {
        return m_btSpecObject;
    }

protected:
    explicit BaseValueSpec(const Configuration &configuration) :
        BaseValue{configuration}
    {}

    explicit BaseValueSpec(const TStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_btSpecObject{btSpecObject}
    {
        m_isValid = true;
    }

    TStruct m_btSpecObject;
};

}  // namespace bvp
