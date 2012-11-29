#pragma once
#include "istream.hpp"
#include "reader.hpp"

template <>
class DefaultReader<std::string>: public Reader<std::string>{
public:
	std::string read(IStream& stream){
		return stream.readToken();
	}
	std::string read(IStream& stream, std::size_t maxLength){
		std::string ret = read(stream);
		if(ret.length() > maxLength)
			stream.quit(Verdict::WA, "Too long string");
		return ret;
	}
};
