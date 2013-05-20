/* This is autogenerated file
 * PLEASE DO NOT EDIT IT DIRECTLY!
 * You may clone our public repository, edit what you need and then rebuild.
 *
 * Repository URL: git://github.com/AlexeyDmitriev/testlib.hpp.git
 * Bug tracker: https://github.com/AlexeyDmitriev/testlib.hpp/issues
 *
 * testlib.hpp version 0.2.0
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 * You are free to use and change it without any fee.
 */
#include "testlib.hpp"
#pragma once

#include <iostream>

template<typename T>
class UnorderedPair {
public:
	UnorderedPair(): first(), second() {}
	UnorderedPair(const T& first, const T& second): first(first), second(second) {}

	T first, second;

private:

	T minElement() const {
		return std::min(first, second);
	}

	T maxElement() const {
		return std::max(first, second);
	}

	template<typename U>
	friend bool operator <(const UnorderedPair<U>& lhs, const UnorderedPair<U>& rhs);

	template<typename U>
	friend bool operator ==(const UnorderedPair<U>& lhs, const UnorderedPair<U>& rhs);

	template<typename U>
	friend bool operator !=(const UnorderedPair<U>& lhs, const UnorderedPair<U>& rhs);
};	

template<typename T>
bool operator <(const UnorderedPair<T>& lhs, const UnorderedPair<T>& rhs) {
	std::less<T> less;
	std::equal_to<T> equal;
	if (!equal(lhs.minElement(), rhs.minElement())) {
		return less(lhs.minElement(), rhs.minElement());
	}
	return less(lhs.maxElement(), rhs.maxElement());
}

template<typename T>
bool operator ==(const UnorderedPair<T>& lhs, const UnorderedPair<T>& rhs) {
	std::equal_to<T> equal;
	return (equal(lhs.first, rhs.first) && equal(lhs.second, rhs.second)) || 
					(equal(lhs.first, rhs.second) && equal(lhs.second, rhs.first));
}

template<typename T>
bool operator !=(const UnorderedPair<T>& lhs, const UnorderedPair<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
std::ostream& operator << (std::ostream& stream, UnorderedPair<T> const & p){
	return stream << '{' << p.first << ',' << p.second << '}' << std::endl;
}

template<typename T>
class DefaultGenerator<UnorderedPair<T>> : public Generator<UnorderedPair<T>> {
	typedef UnorderedPair<T> Pair;
public:
	Pair generate(Random& rnd) const {
		return generate(rnd, DefaultGenerator<T>());
	}

	template <typename Gen>
	Pair generate(Random& rnd, Gen gen) const {
		T first = rnd.next<T>(gen);
		T second = rnd.next<T>(gen);
		return Pair(std::move(first), std::move(second));
	}
};

template<typename T>
class DefaultReader<UnorderedPair<T>>: public Reader<UnorderedPair<T>> {
	typedef UnorderedPair<T> Pair;
public:
	template<typename... Args>
	Pair read(Args&&... args) const {
		std::pair<T, T> pair = DefaultReader<std::pair<T,T>>().read(std::forward<Args>(args)...);	
		return Pair(pair.first, pair.second);
	}
};
