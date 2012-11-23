#pragma once

#include <sstream>
#include <type_traits>
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

template <typename T>
inline std::string rangeToString(T start, T end){
	std::stringstream ss;
	ss << '[';
	for(T current = start; current != end; ++current){
		if(current != start)
			ss << ", ";
		ss << *current;
	}
	ss << ']';
	return ss.str();
}

template <typename T>
inline std::string toPrint(T value){
	return "\"" + toString(value) + "\"";
}

template <>
inline std::string toPrint<char>(char value){
	if(value == '\n')
		return "EOLN";
	if(value == '\r')
		return "CR";
	if(value == ' ')
		return "' '";
	if(value < ' ')
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
