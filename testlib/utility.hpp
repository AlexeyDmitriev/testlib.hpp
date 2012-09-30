#pragma once

#include <sstream>
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

template<typename T, typename U>
inline std::string expectation(T expected, U found){
	return toPrint(expected) + " expected,  " + toPrint(found) + " found";
}
