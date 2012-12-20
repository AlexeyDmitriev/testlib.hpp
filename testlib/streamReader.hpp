#pragma once
#include <iostream>
class StreamReader {
public:
	virtual int get() = 0;
	virtual int peek() = 0;
	
	virtual ~StreamReader() {}
};
class StdStreamReader : public StreamReader {
public:
	StdStreamReader(std::istream& stream):stream(stream){}
	
	int get(){
		return stream.get();
	}
	
	int peek(){
		return stream.peek();
	}
private:
	std::istream& stream;
};
