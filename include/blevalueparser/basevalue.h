#pragma once

#include <cmath>
#include <string>
#include <sstream>
#include <map>
#include <fmt/format.h>


#define BVP_GETTER(TReturn, Name, TStruct)\
    TReturn Name() const\
    {\
        return Name(m_btSpecObject);\
    }\
    static TReturn Name(const TStruct &btSpecObject)
#define BVP_GETTER_CONF(TReturn, Name, TStruct)\
TReturn Name() const\
    {\
        return Name(m_btSpecObject, configuration());\
    }\
    static TReturn Name(const TStruct &btSpecObject, const Configuration &configuration)

#define BVP_CTORS(TBase, T, TStruct)\
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

#define BVP_PARSE(TStruct)\
    virtual bool parse(Parser &parser) override\
    {\
        return parse(parser, m_btSpecObject);\
    }\
    static bool parse(Parser &parser, TStruct &btSpecObject)

#define BVP_TO_STRING(TStruct)\
    virtual std::string toStringInternal() const override\
    {\
        return toStringInternal(m_btSpecObject);\
    }\
    static std::string toStringInternal(const TStruct &btSpecObject)
#define BVP_TO_STRING_CONF(TStruct)\
    virtual std::string toStringInternal() const override\
    {\
        return toStringInternal(m_btSpecObject, configuration());\
    }\
    static std::string toStringInternal(const TStruct &btSpecObject, const Configuration &configuration)


namespace bvp
{

// Table F.3—SFLOAT-Type special values
constexpr uint16_t MF16_NAN             = 0x07FF;
constexpr uint16_t MF16_NRES            = 0x0800;
constexpr uint16_t MF16_PLUS_INFINITY   = 0x07FE;
constexpr uint16_t MF16_MINUS_INFINITY  = 0x0802;
constexpr uint16_t MF16_RESERVED        = 0x0801;

// ISO/IEEE FDIS 11073-20601:2022(E)
// F.7 Short floating point data structure—SFLOAT-Type
class MedFloat16
{
public:
    MedFloat16() :
        m_mantissa{MF16_NAN},
        m_exponent{0}
    {}

    MedFloat16(int16_t mantissa, int8_t exponent) :
        m_mantissa{mantissa},
        m_exponent{exponent}
    {}

    float toFloat() const
    {
        if (isNaN() || isNres() || isReserved())
        {
            return std::numeric_limits<float>::quiet_NaN();
        }

        if (isMinusInfinity())
        {
            return -std::numeric_limits<float>::infinity();
        }

        if (isPlusInfinity())
        {
            return std::numeric_limits<float>::infinity();
        }

        return float(m_mantissa * std::pow(10, m_exponent));
    }

    bool isNaN() const
    {
        return 0 == m_exponent && (m_mantissa & 0b0000111111111111) == MF16_NAN;
    }

    bool isNres() const
    {
        return 0 == m_exponent && (m_mantissa & 0b0000111111111111) == MF16_NRES;
    }

    bool isPlusInfinity() const
    {
        return 0 == m_exponent && (m_mantissa & 0b0000111111111111) == MF16_PLUS_INFINITY;
    }

    bool isMinusInfinity() const
    {
        return 0 == m_exponent && (m_mantissa & 0b0000111111111111) == MF16_MINUS_INFINITY;
    }

    bool isReserved() const
    {
        return 0 == m_exponent && (m_mantissa & 0b0000111111111111) == MF16_RESERVED;
    }

    int16_t mantissa() const
    {
        return m_mantissa;
    }

    int16_t exponent() const
    {
        return m_exponent;
    }

    std::string toString() const
    {
        if (0 == m_exponent)
        {
            switch (m_mantissa & 0b0000111111111111)
            {
                case MF16_NAN:              return "<NaN>";
                case MF16_NRES:             return "<Nres>";
                case MF16_PLUS_INFINITY:    return "<+Inf>";
                case MF16_MINUS_INFINITY:   return "<-Inf>";
                case MF16_RESERVED:         return "<Reserved>";
            }
        }

        return fmt::format("{:g}", toFloat());
    }

private:
    int16_t m_mantissa;
    int8_t m_exponent;

    friend std::ostream &operator<<(std::ostream &os, const MedFloat16 &rhs)
    {
        os << rhs.toString();
        return os;
    }
};

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
    std::string stringPrefix{""};
    std::string stringSuffix{""};
    std::string hexPrefix{"0x "};
    std::string hexSeparator{":"};
    MeasurementUnitsEnum measurementUnits{MeasurementUnitsEnum::SI};

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

        std::string str;

        str.append(configuration().stringPrefix);
        str.append(toStringInternal());
        str.append(configuration().stringSuffix);

        return str;
    }

    virtual Configuration configuration() const
    {
        return m_configuration;
    }

protected:
    explicit BaseValue(const Configuration &configuration) :
        m_configuration{configuration}
    {}

    bool m_isValid{false};

    mutable Configuration m_configuration;

    // For testing protected Parser class
    friend class InternalParserTest;
    friend class InternalParserTest_Raw_Test;
    friend class InternalParserTest_String_Test;
    friend class InternalParserTest_StringLast_Test;
    friend class InternalParserTest_StringEmpty_Test;
    friend class InternalParserTest_StringLastEmpty_Test;
    friend class InternalParserTest_UInt8_Test;
    friend class InternalParserTest_UInt16_Test;
    friend class InternalParserTest_UInt24_Test;
    friend class InternalParserTest_UInt32_Test;
    friend class InternalParserTest_UInt48_Test;
    friend class InternalParserTest_UInt64_Test;
    friend class InternalParserTest_Int8_Test;
    friend class InternalParserTest_Int16_Test;
    friend class InternalParserTest_Int24_Test;
    friend class InternalParserTest_Int32_Test;
    friend class InternalParserTest_Int48_Test;
    friend class InternalParserTest_Int64_Test;
    friend class InternalParserTest_Raw_OutOfData_Test;
    friend class InternalParserTest_Int_OutOfData_Test;
    friend class MedFloat16NormalTest_Convert_Test;
    friend class MedFloat16InfinityTest_Convert_Test;
    friend class MedFloat16NaNTest_Convert_Test;

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
            std::string result{m_data + m_offset, m_size - m_offset};
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

        uint32_t parseUInt24()
        {
            constexpr uint8_t size = 24 / 8;
            return parseInt<uint32_t>(size);
        }

        uint32_t parseUInt32()
        {
            return parseInt<uint32_t>();
        }

        uint64_t parseUInt48()
        {
            constexpr uint8_t size = 48 / 8;
            return parseInt<uint64_t>(size);
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

        int32_t parseInt24()
        {
            constexpr uint8_t size = 24 / 8;
            constexpr uint8_t shift = 8 * (sizeof(int32_t) - size);
            constexpr uint16_t divider = 1 << shift;
            return (parseInt<int32_t>(size) << shift) / divider;
        }

        int32_t parseInt32()
        {
            return parseInt<int32_t>();
        }

        int64_t parseInt48()
        {
            constexpr uint8_t size = 48 / 8;
            constexpr uint8_t shift = 8 * (sizeof(int64_t) - size);
            constexpr uint32_t divider = 1 << shift;
            return (parseInt<int64_t>(size) << shift) / divider;
        }

        int64_t parseInt64()
        {
            return parseInt<int64_t>();
        }

        MedFloat16 parseMedFloat16()
        {
            uint8_t hi = parseInt<uint8_t>();
            uint8_t lo = parseInt<uint8_t>();

            const int8_t exponent_sign = hi & 0b10000000;
            int8_t exponent = (hi & 0b01110000) >> 4;
            if (exponent_sign)
            {
                exponent |= 0b10000000;
                exponent ^= 0b01111000;
            }

            int16_t mantissa_sign = (hi & 0b00001000) << 12;
            int16_t mantissa = ((hi & 0b00000111) << 8) | lo;
            if (mantissa_sign)
            {
                mantissa |= 0b1000000000000000;
                mantissa ^= 0b0111100000000000;
            }

            return MedFloat16(mantissa, exponent);
        }

    private:
        const char *m_data;
        size_t m_size;
        size_t m_offset;
        bool m_outOfData;

        template <typename T>
        T parseInt(size_t offsetDiff = sizeof(T))
        {
            uint64_t result = 0;

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

    virtual bool parse(Parser &parser) = 0;
    virtual std::string toStringInternal() const = 0;
    virtual bool checkSize(size_t size) = 0;

    friend std::ostream &operator<<(std::ostream &os, const BaseValue &rhs)
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
