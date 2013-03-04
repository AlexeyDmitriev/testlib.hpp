#include "../generator.hpp"

template<typename T>
class DefaultGenerator<T, std::is_integral<T>> {
	uintmax_t generateMax(Random& rnd) {
		return rnd.nextBits(rnd.MAX_BITS);
	}
	T generateTo (uintmax_t to){
		uintmax_t disallowed = std::numeric_limits<uintmax_t>::min() / to * to;
		uintmax_t number;
		do {
			number = maxAllowed;
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

		return generateTo(uintmax_t(r) - uintmax_t(l) + uintmax_t(1)) + l;
	}
}
