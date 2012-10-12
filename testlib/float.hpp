#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <limits>
#include <string>
#include <type_traits>
#include <cmath>

template <typename T>
class FloatReader : public Reader<T> {
public:
	T read(IStream& stream) const {
		std::string token = stream.readToken();
		return toFloat(token);
	}
	T read(IStream& stream, T min, T max) const {
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Float violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	T read(IStream& stream, T min, T max, std::string name) const {
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Float " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}

	T toFloat(const std::string& input) const {

		std::string usedValue = input;
		if (input.size() >= MAX_LENGTH)
			throw ReadingException(Verdict::PE, expectation("Float", input));
		if(input[0] == '-') {
			usedValue = usedValue.substr(1);
		}
		if(usedValue.empty())
			throw ReadingException(Verdict::PE, expectation("Float", input));

		if(usedValue[0] == '0' && usedValue.size() > 1 && usedValue[1] != '.')
			throw ReadingException(Verdict::PE, expectation("Float", input));
		if(usedValue[0] == '.')
			throw ReadingException(Verdict::PE, expectation("Float", input));

		bool wasPoint = false;
		for (char digit: usedValue) {
			if(digit == '.') {
				if (wasPoint)
					throw ReadingException(Verdict::PE, expectation("Float", input));
				wasPoint = true;
			}
			else {
				if(digit < '0' || digit > '9')
					throw ReadingException(Verdict::PE, expectation("Float", input));
			}
		}

		std::stringstream ss(input);
		T result;
		
		ss >> result;
		
		return result;
	}
private:
	static constexpr T EPS = 1e-10;
	static constexpr size_t MAX_LENGTH = 50;
};

template<typename T>
class DefaultReader<T, typename std::is_floating_point<T>::type> : public FloatReader<T> {};

