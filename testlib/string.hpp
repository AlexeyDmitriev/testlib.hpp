#pragma once
#include "istream.hpp"
#include "reader.hpp"
#include <string>

template <>
class DefaultReader<std::string>: public Reader<std::string>{
public:
	std::string read(IStream& stream) const {
		return stream.readToken();
	}
	std::string read(IStream& stream, std::size_t maxLength) const {
		std::string ret = read(stream);
		if(ret.length() > maxLength)
			stream.quit(Verdict::WA, "Too long string");
		return ret;
	}
};

class LineReader: public Reader<std::string> {
public:
	std::string read(IStream& stream) const {
		std::string ret;
		while(!lineEnd(stream.peek())){
			ret += (char)stream.get();
		}
		if(stream.peek() != EOF || stream.getMode() == IStream::Mode::STRICT)
			stream.readEoln();
		return ret;
	}
	std::string read(IStream& stream, std::size_t maxLength) const {
		std::string ret = read(stream);
		if(ret.length() > maxLength)
			stream.quit(Verdict::WA, "Too long line");
		return ret;
	}
private:
	bool lineEnd(int c) const {
		return c == '\n' || c == '\r' || c == EOF;
	}
};
