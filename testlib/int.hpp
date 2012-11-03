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
	enum class Case {
		DEFAULT,
		LOWER,
		UPPER,
		BOTH,
	};
	explicit IntegerReader(Case allowedCase = Case::DEFAULT): allowedCase(allowedCase) {}
	T read(IStream& stream) const {
		Case streamCase = effectiveCase(stream);
		std::string input = stream.readToken();
		bool is_signed = std::numeric_limits<T>::is_signed;
		if(!is_signed && input[0] == '-')
			stream.quit(Verdict::PE, expectation("Unsigned integer", input));
		
		std::string usedValue = input;
		bool negative = false;
		if(input[0] == '-'){
			negative = true;
			usedValue = usedValue.substr(1);
		}
		
		std::vector<T> digits(usedValue.length());
		
		for(size_t i = 0; i < usedValue.length(); ++i){
			try {
				digits[i] = digitValue(usedValue[i], streamCase);
			}
			catch(NotDigitException& e){
				stream.quit(Verdict::PE, expectation("Digit", e.character));
			}
			if(digits[i] >= radix)
				stream.quit(Verdict::PE, expectation("Digit in radix " + toString(radix), usedValue[i]));
		}
		
		if(negative && digits == absToArray(std::numeric_limits<T>::min())){
			return std::numeric_limits<T>::min();
		}
		
		if(digits.empty())
			stream.quit(Verdict::PE, expectation("Integer", input));
		
		if(digits[0] == 0 && (negative || digits.size() > 1))
			stream.quit(Verdict::PE, expectation("Integer", input));
		
		std::vector<T> maxArray = absToArray(std::numeric_limits<T>::max());
		if(usedValue.length() > maxArray.size())
			stream.quit(Verdict::PE, expectation("Integer", input));
		if(usedValue.length() == maxArray.size() && digits > maxArray)
			stream.quit(Verdict::PE, expectation("Integer", input));
		
		T result = 0;
		for(T digit: digits){
			result = result * radix + digit;
		}
		
		
		if(negative){
			result = -result;
		}
		
		return result;
	}
	T read(IStream& stream, T min, T max) const {
		T result = read(stream);
		if(result < min || result > max)
			stream.quit(Verdict::WA, "Integer violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	T read(IStream& stream, T min, T max, const std::string& name) const {
		T result = read(stream);
		if(result < min || result > max)
			stream.quit(Verdict::WA, "Integer " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
private:
	struct NotDigitException : public std::exception {
		public:
			NotDigitException(char c):character(c){}
		char character;
	};
	Case effectiveCase(IStream& stream) const {
		if(allowedCase != Case::DEFAULT)
			return allowedCase;
		return stream.getMode() == IStream::Mode::STRICT ? Case::LOWER : Case::BOTH;
	}
	Case allowedCase;
	std::vector<T> absToArray(T value) const {
		bool negative = value < 0;
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
	
	T digitValue(char c, Case streamCase) const {
		if(c >= '0' && c <= '9')
			return c - '0';
		if(lowerAllowed(streamCase) && c >= 'a' && c <= 'z')
			return c - 'a' + 10;
		if(upperAllowed(streamCase) && c >= 'A' && c <= 'Z')
			return c - 'A' + 10;
		throw NotDigitException(c);
	}
	
	bool lowerAllowed(Case _case) const {
		return _case == Case::LOWER || _case == Case::BOTH;
	}
	
	bool upperAllowed(Case _case) const {
		return _case == Case::UPPER || _case == Case::BOTH;
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
