#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <limits>
#include <string>
#include <type_traits>
#include <math.h>

template <typename T>
class FloatReader : public Reader<T> {
public:
    T read(IStream& stream) {
        std::string token = stream.readToken();
        return toDouble(token);
    }
    T read(IStream& stream, T min, T max) {
        T result = read(stream);
        if(result < min + EPS || result > max - EPS)
            throw ReadingException(Verdict::WA, "Double violates the range [" + toString(min) + "," + toString(max) + "]");
        return result;
    }
    T read(IStream& stream, T min, T max, std::string name) {
        T result = read(stream);
        if(result < min || result > max)
            throw ReadingException(Verdict::WA, "Double " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
        return result;
    }

    T toDouble(const std::string& input) {

        std::string usedValue = input;
        bool negative = false;
        if (input.size() >= MAX_DOUBLE_LENGTH)
            throw ReadingException(Verdict::PE, expectation("Double", input));
        if(input[0] == '-') {
            negative = true;
            usedValue = usedValue.substr(1);
        }
        if(usedValue.empty())
            throw ReadingException(Verdict::PE, expectation("Double", input));

        if(usedValue[0] == '0' && usedValue.size() > 1 && usedValue[1] != '.')
            throw ReadingException(Verdict::PE, expectation("Double", input));
        if(usedValue[0] == '.')
            throw ReadingException(Verdict::PE, expectation("Double", input));
        
        bool wasPoint = false;
        T integerPart = 0, fractionalPart = 0;
        T result = 0;
        size_t qDigitsAfterPoint = 0;

        for (char digit: usedValue) {
            if(digit == '.') {
                if (wasPoint)
                    throw ReadingException(Verdict::PE, expectation("Double", input));
                wasPoint = true;
            } 
            else {
                if(digit < '0' || digit > '9')
                    throw ReadingException(Verdict::PE, expectation("Double", input));
                if (wasPoint) {
                    ++qDigitsAfterPoint;
                    fractionalPart += (digit - '0') * pow(0.1, qDigitsAfterPoint);
                } 
                else {
                    integerPart = integerPart * 10 + (digit - '0');
                }
            }
        }

        result = integerPart + fractionalPart;

        if(negative) {
            if (fabs(result) < EPS)
                throw ReadingException(Verdict::PE, expectation("Double", input));
            result = -result;
        }

        return result;
    }
private:
    static constexpr T EPS = 1e-10;
    static constexpr size_t MAX_DOUBLE_LENGTH = 50;
};

template<typename T>
class DefaultReader<T, typename std::is_floating_point<T>::type> : public FloatReader<T> {};

