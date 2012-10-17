#pragma once
#include <utility>
#include <type_traits>
#include <string>
#include "istream.hpp"
#include "int.hpp"

template<typename T, typename U>
class DefaultReader<std::pair<T, U>> : Reader<std::pair<T, U>>{
public:
	class Separator{
	private:
		std::string separator;
	public:
		Separator(char c): separator(c, 1){
		}
		Separator(const char* s): separator(s){
			
		}
		Separator(const std::string& s): separator(std::move(s)){}
		void read(IStream& stream) const {
			for(char c: separator){
				stream.readChar(c);
			}
		}
	};
	typedef std::pair<T, U> type;
	type read(IStream& stream){
		return read(stream, defaultSeparator(stream));
	}
	type read(IStream& stream, const Separator& separator){
		return read(stream, DefaultReader<T>(), DefaultReader<U>(), separator);
	}
	
	template <typename ReaderT, typename ReaderU>
	type read(IStream& stream, const ReaderT& readerT, const ReaderU& readerU){
		static_assert(std::is_base_of<Reader<T>, ReaderT>::value, "Argument must be Reader");
		static_assert(std::is_base_of<Reader<U>, ReaderU>::value, "Argument must be Reader");
		return read(stream, readerT, readerU, defaultSeparator(stream));
	}
	
	template <typename ReaderT, typename ReaderU>
	type read(IStream& stream, const ReaderT& readerT, const ReaderU& readerU, const Separator& separator){
		static_assert(std::is_base_of<Reader<T>, ReaderT>::value, "Argument must be Reader");
		static_assert(std::is_base_of<Reader<U>, ReaderU>::value, "Argument must be Reader");
		T t = stream.read<T>(readerT);
		separator.read(stream);
		U u = stream.read<U>(readerU);
		return std::make_pair(std::move(t), std::move(u));
	}
		
private:
	Separator defaultSeparator(IStream& stream){
		return stream.getMode() == IStream::Mode::STRICT ? " " : "";
	}
};
