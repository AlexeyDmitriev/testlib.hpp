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
	
	template <typename Reader = DefaultReader<T> >
	if_reader<Reader, T, type> read(IStream& stream, size_t numberElements, Reader reader = DefaultReader<T>()){
		return read(stream, numberElements, defaultElementsSeparator(stream), reader);
	}
	
	template <typename Reader = DefaultReader<T> >
	if_reader<Reader, T, type> read(IStream& stream, size_t numberElements, const Separator& separator, Reader reader = DefaultReader<T>()){
		std::vector<T> res;
		for (size_t i = 0; i < numberElements; i++){
			res.push_back(stream.read<T>(reader));
			if (i != numberElements - 1)
				separator.read(stream);
		}
		return res;
	}
	
	
	template <typename Reader = DefaultReader<T> >
	if_reader<Reader, T, type> read(IStream& stream, Reader reader = DefaultReader<T>()){
		return read(stream, defaultSizeSeparator(stream), defaultElementsSeparator(stream), reader);
	}
	
	template <typename Reader = DefaultReader<T> >
	if_reader<Reader, T, type> read(IStream& stream, const Separator& separator1, const Separator& separator2, Reader reader = DefaultReader<T>()){
		size_t numberElements =  stream.read<size_t>();
		separator1.read(stream);
		return read(stream, numberElements, separator2, reader);
	}
	
private:
	Separator defaultSizeSeparator(IStream& stream){
		return stream.getMode() == IStream::Mode::STRICT ? "\n" : "";
	}
	Separator defaultElementsSeparator(IStream& stream){
		return stream.getMode() == IStream::Mode::STRICT ? " " : "";
	}	
};
