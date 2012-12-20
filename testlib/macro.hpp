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
	Options(): inf(std::unique_ptr<StreamReader>(new StdStreamReader(input)), IStream::Mode::NON_STRICT),
	           ouf(std::unique_ptr<StreamReader>(new StdStreamReader(output)), IStream::Mode::NON_STRICT),
	           ans(std::unique_ptr<StreamReader>(new StdStreamReader(answer)), IStream::Mode::NON_STRICT)
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

		input.open(argv[1]);
		output.open(argv[2]);
		answer.open(argv[3]);

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
	std::ifstream input, output, answer;
	std::ofstream fileOutput;
};

#define TESTLIB_CHECK() void check(IStream& inf, IStream& ouf, IStream& ans); \
int main(int argc, char** argv){ \
	Verdict verdict = Verdict::FAIL; \
	std::string message = "No message provided"; \
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
	FailIStream input(std::unique_ptr<StreamReader>(new StdStreamReader(std::cin)), IStream::Mode::STRICT); \
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
	std::cout << message << std::endl; \
	return verdict.exitCode(); \
} \
void validate(IStream& inf)
