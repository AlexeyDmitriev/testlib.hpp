#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <limits>
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>

template <typename T, int radix = 10>
class IntegerReader : public Reader<T>{
	static_assert(radix >= 2 && radix <= 36, "Radix must be in range [2..36]");
public:
	T read(IStream& stream) const {
		std::string token = stream.readToken();
		return toInt(token);
	}
	T read(IStream& stream, T min, T max) const {
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Integer violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	T read(IStream& stream, T min, T max, std::string name) const {
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Integer " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	
	std::vector<T> absToArray(T value) const {
		bool negative = std::less<T>()(value, 0);
		std::vector<T> result;
		while(value != 0){
			if(negative)
				result.push_back(- (value % radix));
			else
				result.push_back(value % radix);
			value /= radix;
		}
		std::reverse(result.begin(), result.end());
		return result;
	}

	T toInt(const std::string& input) const {
		bool is_signed = std::numeric_limits<T>::is_signed;
		if(!is_signed && input[0] == '-')
			throw ReadingException(Verdict::PE, expectation("Unsigned integer", input));
		
		std::string usedValue = input;
		bool negative = false;
		if(input[0] == '-'){
			negative = true;
			usedValue = usedValue.substr(1);
		}
		
		std::vector<T> digits(usedValue.length());
		
		for(size_t i = 0; i < usedValue.length(); ++i){
			digits[i] = digitValue(usedValue[i]);
			if(digits[i] >= radix)
				throw ReadingException(Verdict::PE, expectation("Digit in radix " + toString(radix), usedValue[i]));
		}
		
		if(negative && digits == absToArray(std::numeric_limits<T>::min())){
			return std::numeric_limits<T>::min();
		}
		
		if(digits.empty())
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		if(digits[0] == 0 && (negative || digits.size() > 1))
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		std::vector<T> maxArray = absToArray(std::numeric_limits<T>::max());
		if(usedValue.length() > maxArray.size())
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		if(usedValue.length() == maxArray.size() && digits > maxArray)
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		T result = 0;
		for(T digit: digits){
			result = result * radix + digit;
		}
		
		
		if(negative){
			result = -result;
		}
		
		return result;
		
	}
	
	T digitValue(char c) const {
		if(c >= '0' && c <= '9')
			return c - '0';
		if(c >= 'a' && c <= 'z')
			return c - 'a' + 10;
		if(c >= 'A' && c <= 'Z')
			return c - 'A' + 10;
		throw ReadingException(Verdict::PE, expectation("Digit", c));
	}
};

template<typename T>
struct is_integer {
	typedef typename std::is_integral<T>::type type;
};

template<>
struct is_integer<bool> {
	typedef std::false_type type;
};

template<>
struct is_integer<unsigned char> {
	typedef std::false_type type;
};

template<>
struct is_integer<signed char> {
	typedef std::false_type type;
};

template<>
struct is_integer<char> {
	typedef std::false_type type;
};


template<typename T>
class DefaultReader<T, typename is_integer<T>::type> : public IntegerReader<T>{};

template<typename T>
using HexReader = IntegerReader<T, 16>;
