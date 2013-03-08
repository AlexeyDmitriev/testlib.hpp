#include <deque>
#include <vector>
#include <string>
#include "testlib/generator.hpp"

template<class T>
auto reserveIfExists(T& v, size_t n, int)
	-> decltype(v.reserve(n), void())
{
	v.reserve(n);
}

template<class T>
void reserveIfExists(T&, size_t, long){}

template<typename T>
class PushBackGenerator : public Generator<T> {
	typedef typename T::value_type value_type;
	typedef typename T::size_type size_type;
public:
	template<typename... Args>
	T generate(Random& rnd, size_type n, Args&&... args){
		T result;
		reserveIfExists(result, n, 0);
		for(size_t i = 0; i < n; ++i){
			result.push_back(rnd.next<value_type>(std::forward<Args>(args)...));
		}
		return result;
	}
};

template<typename T>
class DefaultGenerator<std::vector<T>> : public PushBackGenerator<std::vector<T>> {
};

template <>
class DefaultGenerator<std::string> : public PushBackGenerator<std::string> {
};

template<typename T>
class DefaultGenerator<std::deque<T>> : public PushBackGenerator<std::deque<T>> {
};

template<typename T>
class DefaultGenerator<std::list<T>> : public PushBackGenerator<std::list<T>> {
};
