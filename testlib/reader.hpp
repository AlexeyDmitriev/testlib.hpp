#pragma once
#include <type_traits>
template<typename T>
class Reader{
public:
	typedef T type;
};

template<typename T, typename = std::true_type>
class DefaultReader;