#pragma once
#include "reader.hpp"
#include "generator.hpp"
#include <type_traits>
#include <iostream>

template <typename T, typename R, typename X>
class AliasImpl;

template<typename T, typename R>
class AliasImpl<T, R, std::true_type> : public T {
public:
	/*implicit*/ AliasImpl(const T& value): T(value){}
};

template <typename T, typename R>
class AliasImpl<T, R, std::false_type>{
public:
	/*implicit*/ AliasImpl(const T& value): value(value){}
	operator T () const {
		return value;
	}
private:
	T value;
};

template <typename T, typename R>
using Alias = AliasImpl<T, R, typename std::is_class<T>::type>;

template <typename T, typename R>
class DefaultReader<Alias<T,R>> : public Reader<Alias<T,R>> {
	typedef Reader<Alias<T,R>> Base;
public:
	typedef typename Base::type type;
	template<typename... Args>
	type read(Args&&... args) {
		return R().read(std::forward<Args>(args)...);
	}
};

template <typename T, typename G>
class DefaultGenerator<Alias<T,G>> : public Generator<Alias<T, G>> {
public:
	typedef typename Generator<Alias<T, G>>::type type;
	template<typename... Args>
	type generate(Args&&... args) {
		return G().generate(std::forward<Args>(args)...);
	}
};
