#include "testlib/generator.hpp"
#include <type_traits>

template <typename T>
class DefaultGenerator<T, typename std::is_floating_point<T>::type> : public Generator<T> {
public:
	T generate(Random& rnd, T from, T to) const {
		T diff = to - from;
		T ans = from;
		while(from + diff != from){
			diff /= 2;
			if(rnd.nextBit())
				ans += diff;
		}
		return ans;
	}
};
