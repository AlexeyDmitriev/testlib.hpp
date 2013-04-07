#pragma once
#include <functional>
#include <utility>
#include "reader.hpp"

template <typename T>
class ReaderWrapper : public Reader<typename T::type> {
public:
	typedef typename T::type type;
	
	template <typename... Args>
	ReaderWrapper(T reader, Args&& ... args) {
		using namespace std::placeholders;

		lambda = std::bind(
			[reader](IStream& stream, Args... args) {
				return reader.read(stream, args...);
			},
			_1,
			std::forward<Args> (args)...
		);
	}

	type read(IStream& stream) {
		return lambda(stream);
	}
private:
	std::function<type(IStream&)> lambda;
};

template <typename T, typename... Args>
ReaderWrapper<T> make_reader(T reader, Args&&... args) {
	return ReaderWrapper<T>(reader, std::forward<Args> (args)...);
}

template <typename T, typename... Args>
ReaderWrapper<DefaultReader<T>> make_default_reader(Args&&... args) {
	return make_reader(DefaultReader<T>(), std::forward<Args>(args)...);
}
