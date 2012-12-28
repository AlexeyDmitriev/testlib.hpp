#pragma once
#include <utility>
#include <type_traits>
#include "istream.hpp"
#include "int.hpp"
#include "separator.hpp"
#include <vector>
#include "reader.hpp"
#include "utility.hpp"

template<typename T>
class DefaultReader<std::vector<T>> : Reader<std::vector<T>>{
public:
	typedef std::vector<T> type;
	
	template <typename Reader = DefaultReader<T>>
	if_reader<Reader, T, type> read(IStream& stream, size_t numberElements, Reader reader = DefaultReader<T>()) const {
		return read(stream, numberElements, defaultElementsSeparator(stream), reader);
	}
	
	template <typename Reader = DefaultReader<T>>
	if_reader<Reader, T, type> read(IStream& stream, size_t numberElements, const Separator& separator, Reader reader = DefaultReader<T>()) const {
		std::vector<T> res;
		res.reserve(numberElements);
		for (size_t i = 0; i < numberElements; i++){
			res.push_back(stream.namedRead<T>("index " + toString(i), reader));
			if (i != numberElements - 1)
				separator.read(stream);
		}
		return res;
	}
	
	template <typename Reader = DefaultReader<T>>
	if_reader<Reader, T, type> read(IStream& stream, Reader reader = DefaultReader<T>()) const {
		return read(stream, defaultSizeSeparator(stream), defaultElementsSeparator(stream), reader);
	}
	
	template <typename Reader = DefaultReader<T>>
	if_reader<Reader, T, type> read(IStream& stream, const Separator& sizeSeparator, const Separator& elementsSeparator, Reader reader = DefaultReader<T>()) const {
		size_t numberElements =  stream.namedRead<size_t>("Size");
		sizeSeparator.read(stream);
		return read(stream, numberElements, elementsSeparator, reader);
	}
	
private:
	Separator defaultSizeSeparator(IStream& stream) const {
		return stream.getMode() == IStream::Mode::STRICT ? "\n" : "";
	}
	Separator defaultElementsSeparator(IStream& stream) const {
		return stream.getMode() == IStream::Mode::STRICT ? " " : "";
	}	
};
