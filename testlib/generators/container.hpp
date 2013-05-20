#pragma once

#include <deque>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include "testlib/generator.hpp"

template<typename T, typename U>
inline auto reserveIfExists(T& container, U&& n, int)
	-> decltype(container.reserve(n), void())
{
	container.reserve(n);
}

template<typename T, typename U>
inline void reserveIfExists(T&, U&& n, long){}


template<typename T, typename U>
inline auto addToContainer(T& container, U&& value) -> decltype(container.push_back(value), void()) {
	container.push_back(value);
}

template<typename T, typename U>
inline auto addToContainer(T& container, U&& value) -> decltype(container.insert(value), void()) {
	container.insert(value);
}

template<typename T>
class ContainerGenerator : public Generator<T> {
	typedef typename T::value_type value_type;
	typedef typename T::size_type size_type;
public:
	template<typename... Args>
	T generate(Random& rnd, size_type n, Args&&... args) const {
		T result;
		reserveIfExists(result, n, 0);
		while(result.size() != n) {
			addToContainer(result, rnd.next<value_type>(std::forward<Args>(args)...));
		}
		return result;
	}
};

template<typename T>
class DefaultGenerator<std::vector<T>> : public ContainerGenerator<std::vector<T>> {
};

template <>
class DefaultGenerator<std::string> : public ContainerGenerator<std::string> {
};

template<typename T>
class DefaultGenerator<std::deque<T>> : public ContainerGenerator<std::deque<T>> {
};

template<typename T>
class DefaultGenerator<std::list<T>> : public ContainerGenerator<std::list<T>> {
};

template<typename T>
class DefaultGenerator<std::set<T>> : public ContainerGenerator<std::set<T>> {
};

template<typename K, typename V>
class DefaultGenerator<std::map<K, V>> : public ContainerGenerator<std::map<K, V>> {
};

template<typename T>
class DefaultGenerator<std::multiset<T>> : public ContainerGenerator<std::multiset<T>> {
};

template<typename K, typename V>
class DefaultGenerator<std::multimap<K, V>> : public ContainerGenerator<std::multimap<K, V>> {
};


