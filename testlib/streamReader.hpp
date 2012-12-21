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
	virtual ~StdStreamReader() {}
private:
	std::istream& stream;
};

class File {
public:
	File():stream(nullptr), opened(false){}
	File(FILE* stream): stream(stream), opened(false){}
	void open(const char* name, const char* format){
		opened = true;
		stream = fopen(name, format);
	}
	bool fail() const {
		return stream == nullptr;
	}
	~File() {
		if(opened && stream)
			fclose(stream);
	}
	FILE* stream;
private:
	bool opened;
};

class BufferedFileReader : public StreamReader{
public:
	BufferedFileReader(const File& file): file(file){}
	int get() {
		if(!fill())
			return EOF;
		return buffer[position++];
	}
	
	int peek() {
		if(!fill())
			return EOF;
		return buffer[position];
	}
	virtual ~BufferedFileReader(){}
private:
	bool fill(){
		if(position < bufferSize)
			return true;
		bufferSize = fread(buffer, 1, BUFFER_SIZE, file.stream);
		position = 0;
		return bufferSize > 0;
	}
	static const int BUFFER_SIZE = 100000;
	char buffer[BUFFER_SIZE];
	int position = 0;
	int bufferSize = 0;
	const File& file;
};
