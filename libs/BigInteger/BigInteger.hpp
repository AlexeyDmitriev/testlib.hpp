#pragma once

#include "testlib/core.hpp"
#include "testlib/generator.hpp"
#include "testlib/generators/int.hpp"
#include "testlib/istream.hpp"
#include "testlib/random.hpp"
#include "testlib/reader.hpp"
#include "testlib/readers/string.hpp"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

class BigInteger {
public:
	BigInteger() : sign(1), data(0) {}

	explicit BigInteger(intmax_t val) {
		sign = 1;
		if (val < 0) {
			sign = -1;
			val = -val;
		}
		while (val) {
			data.push_back(val % base);
			val /= base;
		}
	}

	explicit BigInteger(const std::string &s) {
		sign = 1;
		size_t pos = 0;
		while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		if(pos > 1)
			throw VerdictException(Verdict::FAIL, "Too many signs");
		for (size_t i = s.size(); i > pos;) {
			int x = 0;
			size_t startIndex = i > pos + baseDigits ? i - baseDigits : pos;//max, avoid underflow
			for (size_t j = startIndex; j < i; ++j)
				x = x * 10 + s[j] - '0';
			data.push_back(x);
			i = startIndex;
		}
		removeLeadingZeros();
	}

	BigInteger& operator = (const BigInteger& v) {
		sign = v.sign;
		data = v.data;
		return *this;
	}
	BigInteger& operator = (intmax_t v) {
		return *this = BigInteger(v);
	}

	BigInteger& operator += (const BigInteger &summand) {
		if (sign == summand.sign) {
			for (size_t i = 0, carry = 0; i < std::max(data.size(), summand.data.size()) || carry > 0; ++i) {
				if (i == data.size())
					data.push_back(0);
				data[i] += carry + (i < summand.data.size() ? summand.data[i] : 0);
				carry = data[i] >= base;
				if (carry)
					data[i] -= base;
			}
			return *this;
		}
		*this -= (-summand);
		return *this;
	}

	BigInteger& operator -= (const BigInteger &deduction) {
		if (sign == deduction.sign) {
			if (abs() >= deduction.abs()) {
				for (size_t i = 0, carry = 0; i < deduction.data.size() || carry; ++i) {
					data[i] -= carry + (i < deduction.data.size() ? deduction.data[i] : 0);
					carry = data[i] < 0;
					if (carry)
						data[i] += base;
				}
				removeLeadingZeros();
				return *this;
			}
			*this = -(deduction - *this);
			return *this;
		}
		*this += (-deduction);
		return *this;
	}

	BigInteger& operator *= (int multiplier) {
		if (multiplier < 0) {
			sign = -sign;
			multiplier = -multiplier;
		}
		for (size_t i = 0, carry = 0; i < data.size() || carry; ++i) {
			if (i == data.size())
				data.push_back(0);
			long long cur = data[i] * (long long) multiplier + carry;
			carry = (int) (cur / base);
			data[i] = (int) (cur % base);
		}
		removeLeadingZeros();
		return *this;
	}

	BigInteger operator * (int multiplier) const {
		BigInteger res = *this;
		res *= multiplier;
		return res;
	}


	BigInteger& operator /= (int divider) {
		if (divider == 0)
			throw VerdictException(Verdict::FAIL, "division by zero");
		if (divider < 0)
			sign = -sign, divider = -divider;
		for (size_t i = data.size(), rem = 0; i-- > 0; ) {
			long long cur = data[i] + rem * (long long) base;
			data[i] = (int) (cur / divider);
			rem = static_cast<int>(cur % divider);
		}
		removeLeadingZeros();
		return *this;
	}

	BigInteger operator / (int divider) const {
		BigInteger res = *this;
		res /= divider;
		return res;
	}

	int operator % (int divider) const {
		if (divider < 0)
			divider = -divider;
		int m = 0;
		for (size_t i = data.size(); i-- > 0;)
			m = (data[i] + m * (long long) base) % divider;
		return m * sign;
	}

	BigInteger operator + (const BigInteger &summand) const {
		BigInteger res(*this);
		res += summand;
		return res;
	}
	BigInteger operator - (const BigInteger &deduction) const {
		BigInteger res(*this);
		res -= deduction;
		return res;
	}

	BigInteger operator - () const {
		BigInteger res = *this;
		if (data.size())
			res.sign = -sign;
		return res;
	}

	BigInteger abs() const {
		BigInteger res = *this;
		res.sign = 1;
		return res;
	}

	BigInteger& operator *= (const BigInteger &multiplier) {
		*this = (*this) * multiplier;
		return *this;
	}

	BigInteger operator * (const BigInteger &multiplier) const {
		BigInteger res;
		res.data.assign(data.size() + multiplier.data.size(), 0);
		for (size_t i = 0; i < data.size(); ++i)
			for (size_t j = 0, carry = 0; j < multiplier.data.size() || carry; ++j) {
				long long cur = res.data[i + j] + data[i] * 1LL * (j < multiplier.data.size() ? multiplier.data[j] : 0) + carry;
				res.data[i + j] = (int) (cur % base);
				carry = (size_t) (cur / base);
			}
		res.removeLeadingZeros();
		return res;
	}

	BigInteger operator / (const BigInteger &divider) const {
		return divmod(divider).first;
	}

	BigInteger operator % (const BigInteger &divider) const {
		return divmod(divider).second;
	}

	friend BigInteger gcd(BigInteger a, BigInteger b) {
		int powerOf2 = 0;
		while(!b.isZero() && !a.isZero()) {
			while(a.isEven() && b.isEven()) {
				a /= 2;
				b /= 2;
				++powerOf2;
			}
			while(a.isEven()) {
				a /= 2;
			}
			while(b.isEven()) {
				b /= 2;
			}
			a -= b;
		}
		return pow(BigInteger(2), powerOf2) * (a.isZero() ? b : a);
		return b.isZero() ? a : gcd(b, a % b);
	}

	friend BigInteger lcm(const BigInteger &a, const BigInteger &b) {
		return a / gcd(a, b) * b;
	}

	BigInteger& operator /= (const BigInteger &divider) {
		*this = *this / divider;
		return *this;
	}

    BigInteger& operator %= (const BigInteger &divider) {
		*this = *this % divider;
		return *this;
	}
	
	static BigInteger ZERO() {
		return BigInteger(0);
	}
	
	static BigInteger ONE() {
		return BigInteger(1);
	}

	static BigInteger TEN() {
		return BigInteger(10);
	}

	friend BigInteger pow(BigInteger base, uintmax_t exponent) {
		BigInteger res = ONE();
		while (exponent) {
			if (exponent & 1) {
				res *= base;
			}
			base *= base;
			exponent >>= 1;
		}
		return res;
	}

	bool operator < (const BigInteger &val) const {
		if (sign != val.sign)
			return sign < val.sign;
		if (data.size() != val.data.size())
			return data.size() * sign < val.data.size() * val.sign;
		for (size_t i = data.size() - 1; i-- > 0;)
			if (data[i] != val.data[i])
				return data[i] * sign < val.data[i] * sign;
		return false;
	}

	bool operator > (const BigInteger &val) const {
		return val < *this;
	}
	bool operator <= (const BigInteger &val) const {
		return !(val < *this);
	}
	bool operator >= (const BigInteger &val) const {
		return !(*this < val);
	}
	bool operator == (const BigInteger &val) const {
		return !(*this < val) && !(val < *this);
	}
	bool operator != (const BigInteger &val) const {
		return *this < val || val < *this;
	}

	bool isZero() const {
		return data.empty();
	}

	intmax_t toInteger() const {
		intmax_t res = 0;
		for (size_t i = data.size(); i-- > 0;)
			res = res * base + data[i];
		return res * sign;
	}
	
	std::string toString() const {
		std:: string res;
		if (data.empty())
			return "0";
		if (sign == -1)
			res = "-";

		res += std::to_string(data.back());

		for (size_t i = data.size() - 1; i-- > 0; ) {
			std::string s = std::to_string(data[i]);
			std::string addString;
			for (size_t j = 0; j < baseDigits - s.length(); ++j)
				addString += "0";
			res += addString + s;
		}
		return res;
	}
private:
	static const int base = 1000000000;
	static const size_t baseDigits = 9;
	int sign;
	std::vector<int> data;

	void removeLeadingZeros() {
		while (!data.empty() && !data.back())
			data.pop_back();
		if (data.empty())
			sign = 1;
	}

	bool isEven() const {
		return data.empty() || ((data[0] & 1) == 0);
	}

	std::pair<BigInteger, BigInteger> divmod(const BigInteger &b1) const {
 		if (b1.isZero())
			throw VerdictException(Verdict::FAIL, "division by zero");
		
		int norm = base / (b1.data.back() + 1);
		BigInteger a = (*this).abs() * norm;
		BigInteger b = b1.abs() * norm;
		BigInteger q, r;
		q.data.resize(a.data.size());

		for (size_t i = a.data.size(); i-- > 0;) {
			r *= base;
			r += BigInteger(a.data[i]);
			int s1 = r.data.size() <= b.data.size() ? 0 : r.data[b.data.size()];
			int s2 = r.data.size() <= b.data.size() - 1 ? 0 : r.data[b.data.size() - 1];
			int d = ((long long) base * s1 + s2) / b.data.back();
			r -= b * d;
			while (r < BigInteger(0))
				r += b, --d;
			q.data[i] = d;
		}

		q.sign = sign * b1.sign;
		r.sign = sign;
		q.removeLeadingZeros();
		r.removeLeadingZeros();
		return std::make_pair(q, r / norm);
	}

};

template<>
class DefaultReader<BigInteger> : public Reader<BigInteger> {
public:
	BigInteger read(IStream& stream) const {
		std::string input = stream.read<std::string>();
		if (input.length() == 0)
			stream.quit(Verdict::PE, expectation("BigInteger", input));		
		size_t firstDigitPos = 0;
		if (input[0] == '-') {
			++firstDigitPos;
			if (input.length() == 1 || input[1] == '0')	
				stream.quit(Verdict::PE, expectation("BigInteger", input));		
		}
		if (input.length() > 1) {
			if (input[0] == '0')
				stream.quit(Verdict::PE, expectation("BigInteger", input));
		}
		for (size_t i = firstDigitPos; i < input.length(); ++i){
			if (!isdigit(input[i]))
				stream.quit(Verdict::PE, expectation("BigInteger", input));	
		}	
		return BigInteger(input);
	}
};

template<>
class DefaultGenerator<BigInteger>: public Generator<BigInteger>{
private:
	BigInteger generateTo (Random& rnd, BigInteger to) const {
		size_t qDigits = to.toString().length();
		std::string str = "1";
		for (size_t i = 0; i < qDigits; ++i)
			str += "0";
		BigInteger limit(str);
		BigInteger disallowed = limit - limit % to;
		BigInteger number;
		do {
			std::string str;
			for (size_t i = 0; i < qDigits; ++i)
				str += std::to_string(rnd.next<int>(0, 9));
			number = BigInteger(str);
		}
		while (number >= disallowed);
		return number % to;
	}
	
public:
	BigInteger generate(Random& rnd, BigInteger l, BigInteger r) const {
		if(l > r)
			throw VerdictException(Verdict::FAIL, "DefaultGenerator<BigInteger>::generate(): l > r");
		return generateTo(rnd, r - l + BigInteger::ONE()) + l;
	}
};

