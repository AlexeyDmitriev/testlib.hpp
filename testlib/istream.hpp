#pragma once
#include <iostream>
#include <functional>
#include <type_traits>
#include <cstdio>
#include <memory>
#include "streamReader.hpp"
#include "core.hpp"
#include "utility.hpp"
#include "reader.hpp"

class IStream {
public:
	enum class Mode{
		STRICT,
		NON_STRICT
	};
	IStream(std::unique_ptr<StreamReader> stream, Mode mode):stream(std::move(stream)), mode(mode){}
	
	template<typename T, typename... Args>
	typename std::enable_if<!std::is_base_of<Reader<T>, typename firstType<Args...>::type>::value,T>::type read(Args&&... args){
		return read<T>(DefaultReader<T>(), std::forward<Args>(args)...);
	}
	
	template<typename T, typename U, typename... Args>
	typename std::enable_if<std::is_base_of<Reader<T>, U>::value,T>::type read(U reader, Args&&... args){
		return reader.read(*this, std::forward<Args>(args)...);
	}
	
	template<typename T, typename... Args>
	T namedRead(const std::string& name, Args... args){
		try {
			return read<T>(std::forward<Args>(args)...);
		}
		catch(VerdictException& prev){
			throw VerdictException(prev.verdict, name + ": " + prev.message);
		}
	}
	
	template<typename T, typename... Args>
	void fill(T& result, Args&&... args){
		result = read<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	IStream& operator >> (T& result){
		fill(result);
		return *this;
	}
	
	char readChar(){
		skipUnused();
		int c = get();
		if(c == EOF)
			quit(Verdict::PE, expectation("Character", "EOF"));				
		return c;
	}
	
	void readChar(char expected){
		while (peek() != expected){
			if(peek() == EOF)
				quit(Verdict::PE, expectation(expected, "EOF"));
			else if (isSkippable(peek()))
				get();
			else 
				quit(Verdict::PE, expectation(expected, char(peek())));
		}
		get();
	}
	
	void readSpace(){
		readChar(' ');
	}
	
	void readEoln(){
	#ifdef ON_WINDOWS
		readChar('\r');
	#endif
		readChar('\n');
	}
	
	void readEof(){
		skipUnused();
		int c = get();
		if(c != EOF)
			quit(Verdict::PE, expectation("EOF", char(c)));
	}
	
	std::string readToken(){	
		skipUnused();
		buffer.clear();
		while(!isWhiteSpace(stream->peek()))
			buffer += stream->get();
		
		if(buffer.empty()){
			if(stream->peek() == EOF)
				quit(Verdict::PE, expectation("Token", "EOF"));
			else
				quit(Verdict::PE, expectation("Token", char(stream->peek())));
		}
		return buffer;
	}
	
	int peek() const {
		return stream->peek();
	}
	int get(){
		return stream->get();
	}
	
	void setStrict(){
		mode = Mode::STRICT;
	}
	void setNonStrict(){
		mode = Mode::NON_STRICT;
	}
	
	Mode getMode() const {
		return mode;
	}
	
	bool seekEoln(){
		char eoln = '\n';
		while (peek() != eoln){
			if (isSkippable(peek()) && peek() != EOF)
				get();
			else 
				return false;
		}
		return true;
	}
	
	bool seekEof(){
		while (peek() != EOF){
			if (isSkippable(peek()))
				get();
			else
				return false;
		}
		return true;
	}
	
	virtual void quit(Verdict verdict, const std::string& message) = 0;
	virtual ~IStream(){}
private:
	std::string buffer;
	std::unique_ptr<StreamReader> stream;
	Mode mode;
	bool isSkippable(int c) const {
		return isWhiteSpace(c) && (mode == Mode::NON_STRICT);
	}
	bool isWhiteSpace(int c) const {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF;
	}
	void skipUnused() {
		int c = peek();
		while (isSkippable(c) && c != EOF){
			get();
			c = peek();
		}
	}
};

class FailIStream : public IStream {
public:
	FailIStream(std::unique_ptr<StreamReader> stream, Mode mode):IStream(std::move(stream), mode){}
	virtual void quit(Verdict, const std::string& message) override {
		throw VerdictException(Verdict::FAIL, message);
	}
	virtual ~FailIStream(){}
};

class OutputIStream : public IStream {
public:
	OutputIStream(std::unique_ptr<StreamReader> stream, Mode mode):IStream(std::move(stream), mode){}
	virtual void quit(Verdict verdict, const std::string& message) override {
		throw VerdictException(verdict, message);
	}
	virtual ~OutputIStream(){}
};
