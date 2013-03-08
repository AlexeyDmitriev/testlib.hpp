#include "testlib/generator.hpp"

template<typename T>
class DefaultGenerator<std::vector<T>> : Generator<std::vector<T>> {
public:
	template<typename... Args>
	std::vector<T> generate(Random& rnd, size_t n, Args&&... args){
		std::vector<T> result;
		result.reserve(n);
		for(size_t i = 0; i < n; ++i){
			result.push_back(rnd.next<T>(std::forward<Args>(args)...));
		}
		return result;
	}
};
