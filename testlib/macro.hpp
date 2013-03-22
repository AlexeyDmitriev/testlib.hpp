#pragma once
#include "istream.hpp"
#include "core.hpp"
#include "exitCodes.hpp"
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>

void writeXml(std::ostream& stream, const std::string& str){
	for(char c: str){
		if(c == '&')
			stream << "&amp;";
		else if(c == '"')
			stream << "&quot;";
		else if(c == '<')
			stream << "&lt;";
		else if(c == '>')
			stream << "&gt;";
		else
			stream << c;
	}
}

struct Options{
	FailIStream inf;
	OutputIStream ouf;
	FailIStream ans;
	bool xml;
	Options(): inf(std::unique_ptr<StreamReader>(new BufferedFileReader(input)), IStream::Mode::NON_STRICT),
	           ouf(std::unique_ptr<StreamReader>(new BufferedFileReader(output)), IStream::Mode::NON_STRICT),
	           ans(std::unique_ptr<StreamReader>(new BufferedFileReader(answer)), IStream::Mode::NON_STRICT)
	{}
	std::ostream& out(){
		return fileOutput.is_open() ? fileOutput : std::cout;
	}
	
	void fill(int argc, char** argv){
		xml = false;
		if (argc  < 4 || argc > 6)
		{
			throw VerdictException(Verdict::FAIL,
				"Program must be run with the following arguments: \n" \
				"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"
			);
		}
		if(argc == 6){
			if(std::strcmp(argv[5], "-APPES") && std::strcmp(argv[5], "-appes")){
				throw VerdictException(Verdict::FAIL,
					"Program must be run with the following arguments: \n" \
					"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"
				);
			}

			xml = true;
		}

		input.open(argv[1], "r");
		output.open(argv[2], "r");
		answer.open(argv[3], "r");

		if(input.fail() || output.fail() || answer.fail())
			throw VerdictException(Verdict::FAIL, "Can't open files");


		if (argc > 4){
			fileOutput.open(argv[4]);
			if(fileOutput.fail()){
				throw VerdictException(Verdict::FAIL, "Can't open output file to write");
			}
		}
	}
private:
	File input, output, answer;
	std::ofstream fileOutput;
};

#define TESTLIB_CHECK() void check(IStream& inf, IStream& ouf, IStream& ans); \
int main(int argc, char** argv){ \
	Verdict verdict = Verdict::FAIL; \
	std::string message = "No verdict returned"; \
	Options options; \
	try { \
		options.fill(argc, argv); \
		check(options.inf, options.ouf, options.ans); \
	} \
	catch (VerdictException& ex){ \
		verdict = ex.verdict; \
		message = ex.message; \
	} \
	if(verdict == Verdict::OK && !options.ouf.seekEof()){ \
		verdict = Verdict::PE; \
		message = "Extra Information in the output file"; \
	} \
	\
	std::ostream& out = options.out(); \
	if(options.xml){ \
		out << "<?xml version=\"1.0\" encoding=\"windows-1251\"?>" \
			"<result outcome = \"" << verdict.outcome() << "\">"; \
		writeXml(out, message); \
		out << "</result>\n"; \
	} \
	else \
		out << verdict.shortMessage() << ' ' << message << std::endl; \
	return verdict.exitCode(); \
} \
void check(IStream& inf, IStream& ouf, IStream& ans)

#define TESTLIB_VALIDATE() void validate(IStream&); \
int main(){ \
	Verdict verdict = Verdict::OK; \
	std::string message = "No message provided"; \
	FailIStream input(std::unique_ptr<StreamReader>(new BufferedFileReader(File(stdin))), IStream::Mode::STRICT); \
	try { \
		validate(input); \
	} \
	catch(VerdictException& ex){ \
		verdict = ex.verdict; \
		message = ex.message; \
	} \
	if(verdict == Verdict::OK && !input.seekEof()){ \
		verdict = Verdict::FAIL; \
		message = "Extra information in input file"; \
	} \
	if(verdict != Verdict::OK && verdict != Verdict::FAIL){ \
		verdict = Verdict::FAIL; \
		message = "Wrong verdict: " + verdict.shortMessage() + ". Message: " + message; \
	} \
	std::cout << verdict.shortMessage() << " " << message << std::endl; \
	return verdict.exitCode(); \
} \
void validate(IStream& inf)

uint64_t getHash(size_t argc, char** argv)
{
	uint64_t seed = 0, multiplier = 0x5f17;
	uint64_t p = 1;
	for (size_t i = 1; i < argc; ++i) {
		for (size_t j = 0, n = strlen(argv[i]); j < n; ++j) {
			seed += argv[i][j] * p;
			p *= multiplier;
		}
		seed += p * ' ';
		p *= multiplier;
	}
	return seed;
}

class ArgumentsReader {
public:
	template<typename T, typename... Args>
	T get(Args&&... args) {
		rangeCheck();
		std::stringstream ss(argv[cur]);
		FailIStream in(std::unique_ptr<StreamReader>(new StdStreamReader(ss)), IStream::Mode::NON_STRICT);
		return in.read<T>(std::forward<Args>(args)...);
	}
	std::string getRaw() {
		rangeCheck();
		return argv[cur];
	}
	ArgumentsReader (int argc, char** argv): argc(argc), argv(argv), cur(0) {}
private:
	void rangeCheck() {
		++cur;
		if(cur == argc)
			throw VerdictException(Verdict::FAIL, "Too few command-line arguments");
	}
	int argc;
	char** argv;
	int cur;
};

#define TESTLIB_GENERATE() void generate(Random& rnd, ArgumentsReader& args); \
int main(int argc, char** argv) {\
	Verdict verdict = Verdict::OK; \
	\
	Random rnd(getHash(argc, argv)); \
	ArgumentsReader args(argc, argv); \
	try { \
		generate(rnd, args); \
	} \
	catch(VerdictException& ex) { \
		verdict = Verdict::FAIL; \
		std::cerr << "FAIL: " << ex.message << std::endl;\
	} \
	return verdict.exitCode(); \
} \
void generate(Random& rnd, ArgumentsReader& args)

