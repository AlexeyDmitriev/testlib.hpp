#pragma once
#include <iostream>
#include <functional>
#include <type_traits>
#include <cstdio>
#include "core.hpp"
#include "utility.hpp"
#include "reader.hpp"

class IStream {
public:
	enum class Mode{
		STRICT,
		NON_STRICT
	};
	IStream(std::istream& stream, Mode mode):stream(stream), mode(mode){}
	
	template<typename T, typename... Args>
	typename std::enable_if<!std::is_base_of<Reader<T>, typename firstType<Args...>::type>::value,T>::type read(Args... args){
		return read<T>(DefaultReader<T>(), args...);
	}
	
	template<typename T, typename U, typename... Args>
	typename std::enable_if<std::is_base_of<Reader<T>, U>::value,T>::type read(U reader, Args... args){
		return reader.read(*this, args...);
	}
	
	template<typename T, typename... Args>
	void fill(T& result, Args... args){
		result = read<T>(args...);
	}
	
	template<typename T, typename... Args>
	IStream& operator >> (T& result){
		fill(result);
		return *this;
	}
	
	char readChar(){
		if (mode == Mode::NON_STRICT)
			skipWhiteSpaces();
		int c = get();
		if(c == EOF)
			throw ReadingException(Verdict::PE, expectation("Character", "EOF"));				
		return c;
	}
	
	void readChar(char expected){
		if (mode == Mode::STRICT){
			char c = readChar();
			if (c != expected){
				throw ReadingException(Verdict::PE, expectation(expected, c));	
			}
		}
		else{
			while (peek() != expected){
				if(peek() == EOF)
					throw ReadingException(Verdict::PE, expectation(expected, "EOF"));
				else if (isWhiteSpace(peek()))
					get();
				else 
					throw ReadingException(Verdict::PE, expectation(expected, char(peek())));
			}
		}
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
		if (mode == Mode::NON_STRICT) {
			skipWhiteSpaces();
		}
		int c = get();
		if(c != EOF)
			throw ReadingException(Verdict::PE, expectation("EOF", char(c)));
	}
	//TODO: maybe it should be changed to Reader<std:string>
	std::string readToken(){
		if (mode == Mode::NON_STRICT){
			skipWhiteSpaces();
		}
		
		std::string token;
		
		while(!isWhiteSpace(stream.peek()))
			token += stream.get();
		
		if(token.empty()){
			if(stream.peek() == EOF)
				throw ReadingException(Verdict::PE, expectation("Token", "EOF"));
			else
				throw ReadingException(Verdict::PE, expectation("Token", char(stream.peek())));
		}
		
		return token;
	}
	int peek(){
		return stream.peek();
	}
	int get(){
		return stream.get();
	}
	
	void setStrict(){
		mode = Mode::STRICT;
	}
	void setNonStrict(){
		mode = Mode::NON_STRICT;
	}
	
	Mode getMode(){
		return mode;
	}
	
	bool seekEoln(){
	#ifdef ON_WINDOWS
		char eoln = '\r';
	#endif
		char eoln = '\n';
	
		while (peek() != eoln){
			if (isWhiteSpace(peek()) && peek() != EOF)
				get();
			else 
				return false;
		}
		return true;
	}
	
	bool seekEof(){
		while (peek() != EOF){
			if (isWhiteSpace(peek()))
				get();
			else
				return false;
		}
		return true;
	}
private:
	std::istream& stream;
	Mode mode;
	bool isWhiteSpace(int c){
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF;
	}
	void skipWhiteSpaces(){ 
		int c = peek();
		while (isWhiteSpace(c) && c != EOF){
			get();
			c = peek();
		}
	}
};
