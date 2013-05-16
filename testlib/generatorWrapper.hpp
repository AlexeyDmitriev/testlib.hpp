#pragma once
#include <functional>
#include <utility>
#include "random.hpp"
#include "generator.hpp"
#include "random.hpp"

template <typename T>
class GeneratorWrapper : public Generator<typename T::type> {
public:
	typedef typename T::type type;
	
	template <typename... Args>
	GeneratorWrapper(T generator, Args&& ... args) {
		using namespace std::placeholders;

		lambda = std::bind(
			[generator](Random& stream, Args... args) {
				return generator.generate(stream, args...);
			},
			_1,
			std::forward<Args> (args)...
		);
	}

	type generate(Random& stream) {
		return lambda(stream);
	}
private:
	std::function<type(Random&)> lambda;
};

template <typename T, typename... Args>
GeneratorWrapper<T> make_generator(T generator, Args&&... args) {
	return GeneratorWrapper<T>(generator, std::forward<Args> (args)...);
}

template <typename T, typename... Args>
GeneratorWrapper<DefaultGenerator<T>> make_default_generator(Args&&... args) {
	return make_generator(DefaultGenerator<T>(), std::forward<Args>(args)...);
}
