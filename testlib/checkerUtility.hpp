#pragma once

#include "istream.hpp"
#include "readers/float.hpp"
#include "verdictFunctions.hpp"

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
				<< alreadyReadTokensNumber << " tokens");
	}

	if (extraInOufCount) {
		WA("Output contains longer sequence [length = " 
				<< alreadyReadTokensNumber + extraInOufCount << "], but answer contains "
				<< alreadyReadTokensNumber << " tokens");
	}
}

template<typename T, typename EqualComparator = std::equal_to<T>>
struct AreEqualChecker {
	explicit AreEqualChecker(const EqualComparator& equalComparator = EqualComparator()): equalComparator(equalComparator) {}

	void operator() (const T& ansToken, const T& oufToken) const {
		verifyEqual(ansToken, oufToken, Verdict::WA, equalComparator);
	}

private:
	EqualComparator equalComparator;
};

template<typename T, typename TokensChecker = AreEqualChecker<T>, typename TReader = DefaultReader<T>>
inline void checkToEof(IStream& ans, IStream& ouf, TokensChecker tokensChecker = AreEqualChecker<T>(), 
	                     TReader reader = DefaultReader<T>()) {
	size_t tokensNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);
		++tokensNumber;
		try {
			tokensChecker(ansToken, oufToken);
		} catch(VerdictException& verdict) {
			verdict.message = "Differs in " + std::to_string(tokensNumber) + englishEnding(tokensNumber) 
			           	       + " item: " + verdict.message;
			throw verdict;
		}
	}
	checkExtraTokensInEnd<T>(ans, ouf, tokensNumber, reader);
	OK(tokensNumber << " tokens");
}

template<typename T, typename TokensChecker = AreEqualChecker<T>, typename TReader = DefaultReader<T>>
inline void checkN(IStream& ans, IStream& ouf, size_t tokensNumber, TokensChecker tokensChecker = AreEqualChecker<T>(), 
	                 Reader<T> reader = DefaultReader<T>()) {
	for (size_t tokenNumber = 0; tokenNumber < tokensNumber; ++tokenNumber) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);

		try {
			tokensChecker(ansToken, oufToken);
		} catch(VerdictException& verdict) {
			verdict.message = "Differs in " + std::to_string(tokensNumber) + englishEnding(tokensNumber) 
			           	       + " item: " + verdict.message;
			throw verdict;
		}
	}
}

template<typename T>
struct AreClose {
	explicit AreClose(T epsilon): epsilon(epsilon) {}

	bool operator() (const T& lhs, const T& rhs) const {
		return areClose(lhs, rhs, epsilon);
	}

private:
	T epsilon;
};

