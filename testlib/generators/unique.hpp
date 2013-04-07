#pragma once
#include <set>
#include "collection.hpp"
template <typename T, typename Cmp = std::less<typename T::value_type>>
class UniqueGenerator : public Generator<T> {
	typedef typename T::value_type value_type;
	typedef typename T::size_type size_type;
	Cmp less;
public:
	UniqueGenerator(Cmp less = Cmp()): less(less) {}
	template<typename... Args>
	T generate(Random& rnd, size_type n, Args&&... args) {
		T result;
		std::set<value_type, Cmp> used(less);
		reserveIfExists(result, n, 0);
		while(used.size() != n){
			auto value = rnd.next<value_type>(std::forward<Args>(args)...);
			if(used.find(value) == used.end()) {
				result.push_back(value);
				used.insert(value);
			}
		}
		return result;
	}
};

