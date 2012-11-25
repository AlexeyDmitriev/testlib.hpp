#pragma once
#include "reader.hpp"
#include <type_traits>

template <typename T, typename R>
class Alias {
	static_assert(std::is_base_of<Reader<T>, R>::value, "R must be reader of T");
public:
	/*implicit*/ Alias(const T& value): value(value){}
	operator T () const {
		return value;
	}
private:
	T value;
};

template <typename T, typename R>
class DefaultReader<Alias<T,R>> : public Reader<Alias<T,R>> {
	typedef Reader<Alias<T,R>> Base;
public:
	typedef typename Base::type type;
	template<typename... Args>
	type read(Args&&... args){
		return R().read(std::forward<Args>(args)...);
	}
};
