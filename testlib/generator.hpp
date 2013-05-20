#pragma once
#include <type_traits>

template<typename T>
class Generator {
public:
	typedef T type;
};

template<typename T, typename = std::true_type>
class DefaultGenerator;
