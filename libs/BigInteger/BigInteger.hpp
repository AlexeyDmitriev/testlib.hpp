#pragma once

#include "testlib/istream.hpp"
#include "testlib/random.hpp"
#include "testlib/reader.hpp"
#include "testlib/readers/string.hpp"
#include <algorithm>
#include <string>
#include <vector>

//TODO *,/,0,design,toLong
namespace biginteger {
using std::vector;

class BigInteger {
public:
	BigInteger() : sign(1), data(0) {}

	explicit BigInteger(long long v) {
		sign = 1;
		if (v < 0) {
			sign = -1;
			v = -v;
		}
		while (v) {
			data.push_back(v % base);
			v /= base;
		}
	}

	explicit BigInteger(const std::string &s) {
		sign = 1;
		data.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		for (int i = s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = std::max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			data.push_back(x);
		}
		removeLeadingZeros();
	}

	BigInteger& operator = (const BigInteger& v) {
		sign = v.sign;
		data = v.data;
		return *this;
	}
	BigInteger& operator = (long long v) {
		return *this = BigInteger(v);
	}

	BigInteger& operator += (const BigInteger &summand) {
		if (sign == summand.sign) {
			for (size_t i = 0, carry = 0; i < std::max(data.size(), summand.data.size()) || carry; ++i) {
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


	BigInteger& operator /= (int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = (int) data.size() - 1, rem = 0; i >= 0; --i) {
			long long cur = data[i] + rem * (long long) base;
			data[i] = (int) (cur / v);
			rem = (int) (cur % v);
		}
		removeLeadingZeros();
		return *this;
	}

	BigInteger operator / (int v) const {
		BigInteger res = *this;
		res /= v;
		return res;
	}

	int operator % (int v) const {
		if (v < 0)
			v = -v;
		int m = 0;
		for (int i = data.size() - 1; i >= 0; --i)
			m = (data[i] + m * (long long) base) % v;
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

	friend std::pair<BigInteger, BigInteger> divmod(const BigInteger &a1, const BigInteger &b1) {
		int norm = base / (b1.data.back() + 1);
		BigInteger a = a1.abs() * norm;
		BigInteger b = b1.abs() * norm;
		BigInteger q, r;
		q.data.resize(a.data.size());

		for (int i = a.data.size() - 1; i >= 0; i--) {
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

		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.removeLeadingZeros();
		r.removeLeadingZeros();
		return std::make_pair(q, r / norm);
	}

	BigInteger operator / (const BigInteger &v) const {
		return divmod(*this, v).first;
	}

	BigInteger operator % (const BigInteger &v) const {
		return divmod(*this, v).second;
	}

	friend BigInteger gcd(const BigInteger &a, const BigInteger &b) {
		return b.isZero() ? a : gcd(b, a % b);
	}

	friend BigInteger lcm(const BigInteger &a, const BigInteger &b) {
		return a / gcd(a, b) * b;
	}

	BigInteger& operator /= (const BigInteger &v) {
		*this = *this / v;
		return *this;
	}

    BigInteger& operator %= (const BigInteger &v) {
		*this = *this % v;
		return *this;
	}

	bool operator < (const BigInteger &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (data.size() != v.data.size())
			return data.size() * sign < v.data.size() * v.sign;
		for (int i = data.size() - 1; i >= 0; i--)
			if (data[i] != v.data[i])
				return data[i] * sign < v.data[i] * sign;
		return false;
	}

	bool operator > (const BigInteger &v) const {
		return v < *this;
	}
	bool operator <= (const BigInteger &v) const {
		return !(v < *this);
	}
	bool operator >= (const BigInteger &v) const {
		return !(*this < v);
	}
	bool operator == (const BigInteger &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator != (const BigInteger &v) const {
		return *this < v || v < *this;
	}

	bool isZero() const {
		return data.empty() || (data.size() == 1 && !data[0]);
	}



	long long toLong() const {
		long long res = 0;
		for (int i = data.size() - 1; i >= 0; i--)
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

		for (int i = data.size() - 2; i >= 0; i--) {
			std::string s = std::to_string(data[i]);
			while (s.length() < 9)
				s = "0" + s;
			res += s;
		}
		return res;
	}
private:
	static const int base = 1000000000;
	static const int base_digits = 9;
	int sign;
	vector<int> data;

	void removeLeadingZeros() {
		while (!data.empty() && !data.back())
			data.pop_back();
		if (data.empty())
			sign = 1;
	}
};

}//namespace biginteger

template<>
class DefaultReader<biginteger::BigInteger> : public Reader<biginteger::BigInteger> {
public:
	biginteger::BigInteger read(IStream& stream) const {
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
		return biginteger::BigInteger(input);
	}
};

