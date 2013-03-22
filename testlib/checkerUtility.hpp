#pragma once

#include "istream.hpp"

template<typename T>
void checkExtraTokensInEnd(IStream& ans, IStream& ouf,
													size_t alreadyReadTokensNumber,
													Reader<T> = DefaultReader<T>())
{
	size_t extraInAnsCount = 0;
	while (!ans.seekEof()){
		ans.read<T>();
		++extraInAnsCount;
	}

	size_t extraInOufCount = 0;
	while (!ouf.seekEof()){
		ouf.read<T>();
		++extraInOufCount;
	}

	if (extraInAnsCount){
		WA("Answer contains longer sequence [length = " 
				<< alreadyReadTokensNumber + extraInAnsCount << "], but output contains "
				<< alreadyReadTokensNumber << " elements");
	}

	if (extraInOufCount){
		WA("Output contains longer sequence [length = " 
				<< alreadyReadTokensNumber + extraInOufCount << "], but answer contains "
				<< alreadyReadTokensNumber << " elements");
	}
}
