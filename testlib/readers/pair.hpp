#pragma once
#include <utility>
#include <string>
#include "testlib/istream.hpp"
#include "testlib/separator.hpp"

template<typename T, typename U>
class DefaultReader<std::pair<T, U>> : Reader<std::pair<T, U>>{
public:
	
	typedef std::pair<T, U> type;
	type read(IStream& stream) const {
		return read(stream, defaultSeparator(stream));
	}
	type read(IStream& stream, const Separator& separator) const {
		return read(stream, DefaultReader<T>(), DefaultReader<U>(), separator);
	}
	
	template <typename ReaderT, typename ReaderU>
	if_reader<ReaderT, T, if_reader<ReaderU, U, type>> read(IStream& stream, const ReaderT& readerT, const ReaderU& readerU) const {
		return read(stream, readerT, readerU, defaultSeparator(stream));
	}
	
	template <typename ReaderT, typename ReaderU>
	if_reader<ReaderT, T, if_reader<ReaderU, U, type>> read(IStream& stream, const ReaderT& readerT, const ReaderU& readerU, const Separator& separator) const {
		T t = stream.namedRead<T>("first", readerT);
		separator.read(stream);
		U u = stream.namedRead<U>("second", readerU);
		return std::make_pair(std::move(t), std::move(u));
	}
	template <typename ReaderT>
	if_reader<ReaderT, T, type> read(IStream& stream, const ReaderT& readerT) const {
		static_assert(std::is_same<T, U>::value, "You may use only reader only for pair<T, T>");
		return read(stream, readerT, defaultSeparator(stream));
	}
	
	template <typename ReaderT>
	if_reader<ReaderT, T, type> read(IStream& stream, const ReaderT& readerT, const Separator& separator) const {
		static_assert(std::is_same<T, U>::value, "You may use only reader only for pair<T, T>");
		return read(stream, readerT, readerT, separator);
	}
	
private:
	Separator defaultSeparator(IStream& stream) const {
		return stream.getMode() == IStream::Mode::STRICT ? " " : "";
	}
};
