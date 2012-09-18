#pragma once
#include <iostream>
#include <functional>
#include <type_traits>
#include "core.hpp"
#include "utility.hpp"
#include "reader.hpp"

//TODO: non-strict mode
class IStream {
public:
	IStream(std::istream& stream):stream(stream){
		
	}
	
	template<typename T, typename... Args>
	typename std::enable_if<!std::is_base_of<Reader<T>, typename firstType<Args...>::type>::value,T>::type read(Args... args){
		return read<T>(DefaultReader<T>(), args...);
	}
	
	template<typename T, typename U, typename... Args>
	typename std::enable_if<std::is_base_of<Reader<T>, U>::value,T>::type read(U reader, Args... args){
		return reader.read(*this, args...);
	}
	char readChar(){
		int c = stream.get();
		if(!stream){
			quit(Verdict::PE, expectation("Character", "EOF"));
					
		}
		return c;
	}
	
	void readChar(char expected){
		char found = readChar();
		if(found != expected)
			quit(Verdict::PE, expectation(expected, found));
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
		int c = stream.get();
		if(!stream.eof())
			quit(Verdict::PE, expectation("EOF", c));
	}
	//TODO: maybe it be changed to Reader<std:string>
	std::string readToken(){
		std::string token;
		char last;
		while(!isWhiteSpace(last = stream.get()) && !stream.eof())
			token += last;
		if(token.empty()){
			if(stream.eof())
				quit(Verdict::PE, expectation("Token", "EOF"));
			else
				quit(Verdict::PE, expectation("Token", last));
		}
		stream.unget();
		
		return token;
	}
private:
	bool isWhiteSpace(char c){
		return c == ' ' || c == '\n' || c == '\r';
	}
	std::istream& stream;
};
