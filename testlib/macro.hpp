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

#define TESTLIB_CHECK() void check(IStream& inf, IStream& ouf, IStream& ans); \
int main(int argc, char** argv){ \
	Verdict verdict = Verdict::OK; \
	std::string message = "No message provided"; \
	std::ifstream input, output, answer; \
	FailIStream inf(input, IStream::Mode::NON_STRICT); \
	OutputIStream ouf(output, IStream::Mode::NON_STRICT); \
	FailIStream ans(answer, IStream::Mode::NON_STRICT); \
	try { \
		if (argc  < 4 || argc > 6) \
		{ \
			throw ReadingException(Verdict::FAIL, \
				"Program must be run with the following arguments: \n" \
				"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]" \
			); \
		} \
		\
		\
		if(argc == 6){ \
			if(std::strcmp(argv[5], "-APPES") && std::strcmp(argv[5], "-appes")){ \
				throw ReadingException(Verdict::FAIL, \
					"Program must be run with the following arguments: \n" \
					"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"\
				); \
			} \
		} \
		input.open(argv[1]); \
		output.open(argv[2]); \
		answer.open(argv[3]); \
		if(input.fail() || output.fail() || answer.fail()) \
			throw ReadingException(Verdict::FAIL, "Can't open files"); \
		\
		check(inf, ouf, ans); \
		\
	} \
	catch (ReadingException& ex){ \
		verdict = ex.verdict; \
		message = ex.message; \
	} \
	if(verdict == Verdict::OK && !ouf.seekEof()){ \
		verdict = Verdict::PE; \
		message = "Extra Information in the output file"; \
	} \
	std::ofstream file; \
	if (argc > 4){ \
		file.open(argv[4]); \
		if(file.fail()){ \
			verdict = Verdict::FAIL; \
			message = "Can't open output file to write"; \
		} \
	} \
	\
	\
	std::ostream& out = argc > 4 ? file : std::cout; \
	if(argc == 6){ \
		out << "<?xml version=\"1.0\" encoding=\"windows-1251\"?>" \
			"<result outcome = \"" << outcome(verdict) << "\">"; \
		writeXml(out, message); \
		out << "</result>\n"; \
	} \
	else \
		out << shortMessage(verdict) << ' ' << message << std::endl; \
	return exitCode(verdict); \
} \
void check(IStream& inf, IStream& ouf, IStream& ans)

#define TESTLIB_VALIDATE() void validate(IStream&); \
int main(){ \
	Verdict verdict = Verdict::OK; \
	std::string message = "No message provided"; \
	FailIStream input(std::cin, IStream::Mode::STRICT); \
	try { \
		validate(input); \
	} \
	catch(ReadingException& ex){ \
		verdict = ex.verdict; \
		message = ex.message; \
	} \
	if(verdict == Verdict::OK && !input.seekEof()){ \
		verdict = Verdict::FAIL; \
		message = "Extra information in input file"; \
	} \
	std::cout << message << std::endl; \
	return exitCode(verdict); \
} \
void validate(IStream& inf)

#define QUIT(verdict, msg) \
do { \
	std::stringstream ss; \
	ss << msg; \
	throw ReadingException(verdict, ss.str()); \
} \
while (false); \

#define OK(msg) QUIT(Verdict::OK, msg)
#define WA(msg) QUIT(Verdict::WA, msg)
#define FAIL(msg) QUIT(Verdict::FAIL, msg)
#define PE(msg) QUIT(Verdict::PE, msg)

#define ensure(condition) \
if(!(condition)) \
	FAIL("\"" #condition "\" on line "  << __LINE__ << " is false");
