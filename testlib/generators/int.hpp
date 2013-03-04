#include "testlib/generator.hpp"

template<typename T>
class DefaultGenerator<T, typename std::is_integral<T>::type> {
	uintmax_t generateMax(Random& rnd) {
		return rnd.nextBits(rnd.MAX_BITS);
	}

	T generateTo (Random& rnd, uintmax_t to){
		uintmax_t disallowed = std::numeric_limits<uintmax_t>::max() / to * to;
		uintmax_t number;
		do {
			number = rnd.nextBits(rnd.MAX_BITS);
		}
		while(number >= disallowed);
		return number % to;
	}
public:
	T generate(Random& rnd){
		return rnd.nextBits(sizeof(T) * CHAR_BIT);
	}

	T generate(Random& rnd, T l, T r){
		if(l > r)
			throw VerdictException(Verdict::FAIL, "DefaultGenerator<int>::generate(): l > r");
		if(l == std::numeric_limits<T>::min() && r == std::numeric_limits<T>::max())
			return generate(rnd);

		return generateTo(rnd, uintmax_t(r) - uintmax_t(l) + uintmax_t(1)) + l;
	}
};

