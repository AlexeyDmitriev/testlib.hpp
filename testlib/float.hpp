#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <algorithm>
#include <limits>
#include <string>
#include <type_traits>
#include <cmath>

template<typename T>
inline bool isInfinite(T value){
	return value == std::numeric_limits<T>::infinity() || value == -std::numeric_limits<T>::infinity();
}
template<typename T>
inline bool isNaN(T value){
	return value != value;
}

template <typename T>
class FloatReader : public Reader<T> {
public:
	T read(IStream& stream) const {
		std::string input = stream.readToken();
		const char* usedValue = input.c_str();
		size_t length = input.length();
		if(input[0] == '-') {
			++usedValue;
			--length;
		}
		if(length == 0)
			stream.quit(Verdict::PE, expectation("Float", input));

		if(usedValue[0] == '0' && length > 1 && usedValue[1] != '.')
			stream.quit(Verdict::PE, expectation("Float", input));
		if(usedValue[0] == '.')
			stream.quit(Verdict::PE, expectation("Float", input));
		if(usedValue[length - 1] == '.')
			stream.quit(Verdict::PE, expectation("Float", input));

		bool wasPoint = false;
		for (size_t i = 0; i < length; ++i) {
			char digit = usedValue[i];
			if(digit == '.') {
				if (wasPoint)
					stream.quit(Verdict::PE, expectation("Float", input));
				wasPoint = true;
			}
			else {
				if(digit < '0' || digit > '9')
					stream.quit(Verdict::PE, expectation("Float", input));
			}
		}

		std::stringstream ss(input);
		T result;
		
		ss >> result;
		if(!ss || isNaN(result) || isInfinite(result))
			stream.quit(Verdict::PE, expectation("Float", input));
		return result;
	}
	T read(IStream& stream, T min, T max) const {
		T result = read(stream);
		if(result < min || result > max)
			stream.quit(Verdict::WA, "Float violates the range [" + toString(min) + "," + toString(max) + "]");
		return result; 
	}
};

template<typename T>
class DefaultReader<T, typename std::is_floating_point<T>::type> : public FloatReader<T> {};

template<typename T>
inline bool areClose(T expected, T value, T epsilon){
	return (std::abs(value - expected) / std::max(1.0, expected)) < epsilon;
}
