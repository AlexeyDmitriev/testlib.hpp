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
	std::fstream file;                                                                   \
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
			if(std::strcmp(argv[5], "-APPES") && std::strcmp(argv[5], "-appes")){                  \
				throw ReadingException(Verdict::FAIL,                                    \
					"Program must be run with the following arguments: \n"               \
					"<input-file> <output-file> <answer-file> [<report-file> [<-appes>]]"\
				);                                                                       \
			}                                                                            \
		}                                                                                \
		std::ifstream input(argv[1]);                                                    \
		std::ifstream output(argv[2]);                                                   \
		std::ifstream answer(argv[3]);                                                   \
		if(input.fail() || output.fail() || output.fail())                               \
			throw ReadingException(Verdict::FAIL,"Can't open files");                    \
		FailIStream inf(input, IStream::Mode::NON_STRICT);                               \
		OutputIStream ouf(output, IStream::Mode::NON_STRICT);                            \
		FailIStream ans(answer, IStream::Mode::NON_STRICT);                              \
		check(inf, ouf, ans);                                                            \
		                                                                                 \
		if(!ouf.seekEof()){                                                              \
			throw ReadingException(Verdict::PE, "Extra Information in the output file"); \
		}                                                                                \
		if (argc > 4){                                                                   \
			file.open(argv[4]);                                                          \
			if(file.fail()){                                                             \
				throw ReadingException(Verdict::FAIL, "Can't open output file to write");\
			}                                                                            \
		}                                                                                \
	}                                                                                    \
	catch (ReadingException& ex){                                                        \
		verdict = ex.verdict;                                                            \
		message = ex.message;                                                            \
	}                                                                                    \
	                                                                                     \
	std::ostream& output = argc > 4 ? file : std::cout;                                  \
	if(argc == 6){                                                                       \
		/*output << "<?xml version=\"1.0\" encoding=\"windows-1251\"?>"                  \
			"<result outcome = \"" << << "\">";                                          \
		writeXml(output, message);                                                       \
		output << "</result>\n";                                                       */\
		std::cout << "Appes are not supported yet";                                      \
		std::exit(1);                                                                    \
	}                                                                                    \
	output << shortMessage(verdict) << ' ' << message << std::endl;                      \
	return exitCode(verdict);                                                            \
}                                                                                        \
void check(IStream& inf, IStream& ouf, IStream& ans)
