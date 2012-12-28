#pragma once
#include <type_traits>
#include "reader.hpp"
#include "istream.hpp"
template <typename T>
struct is_char : public std::false_type{};

template <>
struct is_char<char> : public std::true_type{};

template <>
struct is_char<signed char> : public std::true_type{};

template <>
struct is_char<unsigned char> : public std::true_type{};


template<typename T>
class DefaultReader<T, typename is_char<T>::type> : Reader<T>{
public:
	T read(IStream& stream) const {
		return stream.readChar();
	}
	T read(IStream& stream, const std::string& allowed) const {
		T result = read(stream);
		for(char c: allowed)
			if(result == c)
				return result;
		stream.quit(Verdict::PE, expectation("One of \"" + allowed + "\"", result));
		assert(false);
	}
};
