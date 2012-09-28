#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <limits>
#include <string>
#include <type_traits>

template <typename T>
class IntegerReader : public Reader<T>{
public:
	T read(IStream& stream){
		std::string token = stream.readToken();
		return toInt(token);
	}
	T read(IStream& stream, T min, T max){
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Integer violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
	T read(IStream& stream, T min, T max, std::string name){
		T result = read(stream);
		if(result < min || result > max)
			throw ReadingException(Verdict::WA, "Integer " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}

	T toInt(const std::string& input){
		bool is_signed = std::numeric_limits<T>::is_signed;
		if(!is_signed && input[0] == '-')
			throw ReadingException(Verdict::PE, expectation("Unsigned integer", input));
		
		if(input == toString(std::numeric_limits<T>::min())){
			return std::numeric_limits<T>::min();
		}
		std::string usedValue = input;
		bool negative = false;
		if(input[0] == '-'){
			negative = true;
			usedValue = usedValue.substr(1);
		}
		
		if(usedValue.empty())
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		if(usedValue.size() > 1 && usedValue[0] == '0')
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		std::string maxString = toString(std::numeric_limits<T>::max());
		if(usedValue.length() > maxString.length())
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		if(usedValue.length() == maxString.length() && usedValue > maxString)
			throw ReadingException(Verdict::PE, expectation("Integer", input));
		
		T result = 0;
		for(char digit: usedValue){
			if(digit < '0' || digit > '9')
				throw ReadingException(Verdict::PE, expectation("Integer", input));
			result = result * 10 + (digit - '0');
		}
		
		
		if(negative){
			result = -result;
		}
		
		return result;
	}
};

<<<<<<< HEAD
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
<<<<<<< HEAD
class DefaultReader<T, typename is_integer<T>::type> : public IntegerReader<T>{};
=======
class DefaultReader<T, typename is_integer<T>::type> : public IntegerReader<T>{};
>>>>>>> change void + enable_if to boolean constants
