#pragma once

#include "istream.hpp"

// template<typename T>
// class FinishCondition {
// public:
// 	tokensRead(const T& ansToken, const T& oufToken);
// };
	
// EOF
// special symbol
// N

// CompareBetter

// check(ans, ouf, FinishCondition finishCondition, Comparator comparator, Reader) {
// 	while (!finishCondition(ans, ouf)) {
// 		ansToken = ans.read(reader)
// 		oufToken = ouf.read(reader)

// 		if (comparator(ansToken, oufToken))
// 		comparator returns message
// 	}
// }

template<typename T, typename TReader = DefaultReader<T>>
inline void checkExtraTokensInEnd(IStream& ans, IStream& ouf, size_t alreadyReadTokensNumber, 
	                                TReader reader = DefaultReader<T>()) {
	size_t extraInAnsCount = 0;
	while (!ans.seekEof()) {
		ans.read<T>(reader);
		++extraInAnsCount;
	}

	size_t extraInOufCount = 0;
	while (!ouf.seekEof()) {
		ouf.read<T>(reader);
		++extraInOufCount;
	}

	if (extraInAnsCount) {
		WA("Answer contains longer sequence [length = " 
				<< alreadyReadTokensNumber + extraInAnsCount << "], but output contains "
				<< alreadyReadTokensNumber << " elements");
	}

	if (extraInOufCount) {
		WA("Output contains longer sequence [length = " 
				<< alreadyReadTokensNumber + extraInOufCount << "], but answer contains "
				<< alreadyReadTokensNumber << " elements");
	}
}

template<typename T, typename Less = std::less<T>>
struct DefaultEqualComparator
{
	bool operator() (const T& ansToken, const T& oufToken, Less less = Less()) const {
		return !less(ansToken, oufToken) && !less(oufToken, ansToken);
	}
};

template<typename T, typename TEqualComparator = DefaultEqualComparator<T>>
struct AreEqualChecker {
	bool operator() (const T& ansToken, const T& oufToken, TEqualComparator equalComparator = DefaultEqualComparator<T>()) const {
		if (!equalComparator(ansToken, oufToken)) {
			WA(expectation(ansToken, oufToken));
			return false;
		}
		return true;
	}
};

template<typename T, typename TReader = DefaultReader<T>, typename TokensChecker>
inline void checkEOF(IStream& ans, IStream& ouf, TokensChecker tokensChecker, TReader reader = DefaultReader<T>()) {
	size_t tokensNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);
		++tokensNumber;
		tokensChecker(ansToken, oufToken);
	}
	checkExtraTokensInEnd<T>(ans, ouf, tokensNumber, reader);
	OK("Correct answer, " << tokensNumber << " numbers");
}

template<typename T, typename TReader = DefaultReader<T>, typename TokensChecker>
inline void checkN(IStream& ans, IStream& ouf, size_t tokensNumber, TokensChecker tokensChecker, Reader<T> reader = DefaultReader<T>()) {
	for (size_t tokenNumber = 0; tokenNumber < tokensNumber; ++tokenNumber) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);

		tokensChecker(ansToken, oufToken);
	}
}

// if (IsBetterComparator(ans, ouf)) {
// 	WA("Jury's answer is better, " << expectation(ansToken, oufToken) <<
// 		" in " << tokensNumber << " element");
// } else if (IsBetterComparator(ouf, ans)) {
// 	Fail("Competitor's answer is better, " << expectation(ansToken, oufToken) <<
// 		" in " << tokensNumber << " element");
// }
// if(!areClose(ansDouble, oufDouble, EPS)) {
// 	WA(expectation(ansDouble, oufDouble) << ", error = " << ansDouble - oufDouble 
// 		<< " in " << doublesNumber << " element");
// }

inline void multipleDoublesEpsCheck(IStream& ans, IStream& ouf, const double EPS) {
	size_t doublesNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()) {
		double ansDouble = ans.read<double>();
		double oufDouble = ouf.read<double>();
		++doublesNumber;

		if(!areClose(ansDouble, oufDouble, EPS)) {
			WA(expectation(ansDouble, oufDouble) << ", error = " << ansDouble - oufDouble 
				<< " in " << doublesNumber << " element");
		}
	}

	checkExtraTokensInEnd<double>(ans, ouf, doublesNumber);
	OK("Correct answer, " << doublesNumber << " numbers");
}
