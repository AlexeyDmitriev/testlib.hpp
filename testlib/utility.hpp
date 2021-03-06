#pragma once

#include <sstream>
#include <type_traits>
#include <iterator>
#include "reader.hpp"

template <typename... All>
struct firstType;
template <typename First, typename... Other>
struct firstType<First, Other...>{
	typedef First type;
};

template <>
struct firstType<>{
	typedef void type;
};


template <typename T>
inline std::string toString(const T& value){
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template <>
inline std::string toString(const std::string& value){
	return value;
}

template <typename T, typename U>
inline std::string separated(T start, T end, U separator) {
	std::stringstream ss;
	for(T current = start; current != end; ++current) {
		if(current != start)
			ss << separator;
		ss << *current;
	}
	return ss.str();
}

template <typename T, typename U>
inline std::string separated(const T& collection, U&& separator) {
	return separated(std::begin(collection), std::end(collection), std::forward<U>(separator));
}

template <typename T>
inline std::string rangeToString(T start, T end) {
	return '[' + separated(start, end, ", ") + ']';
}
template <typename T>
inline std::string toPrint(T value){
	const size_t MAX_LENGTH = 70;
	std::string str = toString(value);
	if(str.length() <= MAX_LENGTH)
		return "\"" + str + "\"";
	else
		return "\"" + str.substr(0, MAX_LENGTH / 2) + "..." 
		            + str.substr(str.length() - MAX_LENGTH / 2) + "\"";
}

template <>
inline std::string toPrint<char>(char value){
	if(value == '\n')
		return "EOLN";
	if(value == '\r')
		return "CR";
	if(value == ' ')
		return "' '";
	if(value >= 0 && value < ' ')
		return "'#" + toString(static_cast<int>(value)) + "'";
	return "'" + toString(value) + "'";
}

template <>
inline std::string toPrint<const char*>(const char* string){
	return toString(string);
}

template<typename T, typename U>
inline std::string expectation(T&& expected, U&& found){
	return toPrint(expected) + " expected, " + toPrint(found) + " found";
}

template <typename ReaderT, typename T, typename Result>
using if_reader = typename std::enable_if<std::is_base_of<Reader<T>, ReaderT>::value,Result>::type;

template<typename Integral>
inline std::string englishEnding(Integral n){
    if (n / 10 % 10 == 1)
        return "th";
    if (n % 10 == 1)
        return "st";
    if (n % 10 == 2)
        return "nd";
    if (n % 10 == 3)
        return "rd";
    return "th";
}


#ifdef TESTLIB_DEBUG
	#define TESTLIB_ASSERT(x) \
		if(!(x)) { \
			std::cerr << "Assertion failed: " << #x << std::endl; \
			std::exit(1); \
		}
#else
	#define TESTLIB_ASSERT(x)
#endif
	
