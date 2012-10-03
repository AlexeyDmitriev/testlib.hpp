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
		return toFloat(token);
	}
	T read(IStream& stream, T min, T max) {
		T result = read(stream);
		if(result < min + EPS || result > max - EPS)
			throw ReadingException(Verdict::WA, "Float violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	T read(IStream& stream, T min, T max, std::string name) {
		T result = read(stream);
		if(result < min + EPS || result > max - EPS)
			throw ReadingException(Verdict::WA, "Float " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}

	T toFloat(const std::string& input) {

		std::string usedValue = input;
		bool negative = false;
		if (input.size() >= MAX_LENGTH)
			throw ReadingException(Verdict::PE, expectation("Float", input));
		if(input[0] == '-') {
			negative = true;
			usedValue = usedValue.substr(1);
		}
		if(usedValue.empty())
			throw ReadingException(Verdict::PE, expectation("Float", input));

		if(usedValue[0] == '0' && usedValue.size() > 1 && usedValue[1] != '.')
			throw ReadingException(Verdict::PE, expectation("Float", input));
		if(usedValue[0] == '.')
			throw ReadingException(Verdict::PE, expectation("Float", input));

		bool wasPoint = false;
		T integerPart = 0, fractionalPart = 0;
		T fractionMultiplyer = 1;

		for (char digit: usedValue) {
			if(digit == '.') {
				if (wasPoint)
					throw ReadingException(Verdict::PE, expectation("Float", input));
				wasPoint = true;
			}
			else {
				if(digit < '0' || digit > '9')
					throw ReadingException(Verdict::PE, expectation("Float", input));
				if (wasPoint) {
					fractionMultiplyer /= 10.0;
					fractionalPart += (digit - '0') * fractionMultiplyer;
				}
				else {
					integerPart = integerPart * 10 + (digit - '0');
				}
			}
		}

		T result = integerPart + fractionalPart;

		if(negative) {
			result = -result;
		}

		return result;
	}
private:
	static constexpr T EPS = 1e-10;
	static constexpr size_t MAX_LENGTH = 50;
};

template<typename T>
class DefaultReader<T, typename std::is_floating_point<T>::type> : public FloatReader<T> {};

