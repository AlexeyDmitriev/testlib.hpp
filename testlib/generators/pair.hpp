#pragma once
#include <utility>
#include <string>
#include "testlib/random.hpp"
#include "testlib/generator.hpp"

template<typename T, typename U>
class DefaultGenerator<std::pair<T, U>> : Generator<std::pair<T, U>>{
public:
	typedef std::pair<T, U> type;
	type generate(Random& rnd) const {
		return generate(rnd, DefaultGenerator<T>(), DefaultGenerator<U>());
	}
	
	template <typename GeneratorT, typename GeneratorU>
	type generate(Random& rnd, const GeneratorT& generatorT, const GeneratorU& generatorU) const {
		//Can't inline here because order of argument calculation is unspecified
		//It would possibly break random stability on different compilers
		T first = rnd.next<T>(generatorT);
		U second = rnd.next<U>(generatorU);
		return std::make_pair(std::move(first), std::move(second));
	}
	
	template <typename GeneratorT>
	type generate(Random& rnd, const GeneratorT& generatorT) const {
		static_assert(std::is_same<T, U>::value, "You may use only generator only for pair<T, T>");
		return generate(rnd, generatorT, generatorT);
	}
};
