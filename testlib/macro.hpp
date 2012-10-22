#pragma once
#include "istream.hpp"
#include <fstream>
#include <cstdlib>
#include <cstring>
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

#define TESTLIB_CHECK() void check(IStream& inf, IStream& ouf, IStream& ans);            \
int main(int argc, char** argv){                                                         \
	Verdict verdict = Verdict::OK;                                                       \
	std::string message = "No message provided";                                         \
	std::ifstream input, output, answer;                                                 \
	FailIStream inf(input, IStream::Mode::NON_STRICT);                                   \
	OutputIStream ouf(output, IStream::Mode::NON_STRICT);                                \
	FailIStream ans(answer, IStream::Mode::NON_STRICT);                                  \
	try {                                                                                \
		if (argc  < 4 || argc > 6)                                                       \
		{                                                                                \
			throw ReadingException(Verdict::FAIL,                                        \
				"Program must be run with the following arguments: \n"                   \
				"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"    \
			);                                                                           \
		}                                                                                \
		                                                                                 \
		                                                                                 \
		if(argc == 6){                                                                   \
			if(std::strcmp(argv[5], "-APPES") && std::strcmp(argv[5], "-appes")){        \
				throw ReadingException(Verdict::FAIL,                                    \
					"Program must be run with the following arguments: \n"               \
					"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"\
				);                                                                       \
			}                                                                            \
		}                                                                                \
		input.open(argv[1]);                                                             \
		output.open(argv[2]);                                                            \
		answer.open(argv[3]);                                                            \
		if(input.fail() || output.fail() || output.fail())                               \
			throw ReadingException(Verdict::FAIL,"Can't open files");                    \
		                                                                                 \
		check(inf, ouf, ans);                                                            \
		                                                                                 \
	}                                                                                    \
	catch (ReadingException& ex){                                                        \
		verdict = ex.verdict;                                                            \
		message = ex.message;                                                            \
	}                                                                                    \
	if(verdict == Verdict::OK && !ouf.seekEof()){                                        \
		verdict = Verdict::PE;                                                           \
		message = "Extra Information in the output file";                                \
	}                                                                                    \
	std::ofstream file;                                                                  \
	if (argc > 4){                                                                       \
		file.open(argv[4]);                                                              \
		if(file.fail()){                                                                 \
			verdict = Verdict::FAIL;                                                     \
			message = "Can't open output file to write";                                 \
		}                                                                                \
	}                                                                                    \
	                                                                                     \
	                                                                                     \
	std::ostream& out = argc > 4 ? file : std::cout;                                     \
	if(argc == 6){                                                                       \
		/*output << "<?xml version=\"1.0\" encoding=\"windows-1251\"?>"                  \
			"<result outcome = \"" << << "\">";                                          \
		writeXml(output, message);                                                       \
		output << "</result>\n";                                                       */\
		std::cout << "Appes are not supported yet";                                      \
		std::exit(1);                                                                    \
	}                                                                                    \
	out << shortMessage(verdict) << ' ' << message << std::endl;                         \
	return exitCode(verdict);                                                            \
}                                                                                        \
void check(IStream& inf, IStream& ouf, IStream& ans)
