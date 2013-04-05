#pragma once

#include "istream.hpp"

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

enum class ErrorCode {
	OK, WA, FAIL
};

struct CheckResult {
	CheckResult(ErrorCode errorCode, const std::string& message): errorCode(errorCode), message(message) {}

	ErrorCode errorCode;
	std::string message;
};

template<typename T, typename TEqualComparator = DefaultEqualComparator<T>>
struct AreEqualChecker {
	CheckResult operator() (const T& ansToken, const T& oufToken, 
			TEqualComparator equalComparator = TEqualComparator()) const {

		if (!equalComparator(ansToken, oufToken)) {
			return CheckResult(ErrorCode::WA, expectation(ansToken, oufToken));
		}
		return CheckResult(ErrorCode::OK, "");
	}
};

template<typename T, typename TReader = DefaultReader<T>, typename TokensChecker = AreEqualChecker<T>>
inline void checkEOF(IStream& ans, IStream& ouf, TokensChecker tokensChecker = AreEqualChecker<T>(), 
	                   TReader reader = DefaultReader<T>()) {
	size_t tokensNumber = 0;
	while (!ans.seekEof() && !ouf.seekEof()) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);
		++tokensNumber;
		CheckResult checkResult = tokensChecker(ansToken, oufToken);
		if (checkResult.errorCode == ErrorCode::WA) {
			WA(checkResult.message);
		}
		if (checkResult.errorCode == ErrorCode::FAIL) {
			FAIL(checkResult.message);
		}
	}
	checkExtraTokensInEnd<T>(ans, ouf, tokensNumber, reader);
	OK("Correct answer, " << tokensNumber << " numbers");
}

template<typename T, typename TReader = DefaultReader<T>, typename TokensChecker>
inline void checkN(IStream& ans, IStream& ouf, size_t tokensNumber, TokensChecker tokensChecker, Reader<T> reader = DefaultReader<T>()) {
	for (size_t tokenNumber = 0; tokenNumber < tokensNumber; ++tokenNumber) {
		T ansToken = ans.read<T>(reader);
		T oufToken = ouf.read<T>(reader);

		CheckResult checkResult = tokensChecker(ansToken, oufToken);
		if (checkResult.errorCode == ErrorCode::WA) {
			WA(checkResult.message);
		}
		if (checkResult.errorCode == ErrorCode::FAIL) {
			FAIL(checkResult.message);
		}
	}
}

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
