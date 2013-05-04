#include "testlib/core.hpp"
#include "testlib/generator.hpp"
#include "testlib/reader.hpp"
#include "testlib/random.hpp"
#include "testlib/istream.hpp"

#include <vector>
#include <ostream>
#include <array>
#include <cstdint>
#include <algorithm>
class Permutation {
	typedef size_t ValueType;
	typedef std::vector<ValueType>::const_iterator iterator;
public:
	explicit Permutation(const std::vector<ValueType>& permutation): permutation(permutation) {
		size_t n = permutation.size();
		std::vector<char> used(n);
		for(ValueType to: permutation){
			if(to < 0 || to >= n) {
				throw VerdictException(Verdict::FAIL, "Permutation Number: in permutation is out of range");
			}
			used[to] = true;
		}

		for(size_t i = 0; i < n; ++i) {
			if(!used[i]){
				throw VerdictException(Verdict::FAIL, "Duplicate numbers in permutation");
			}
		}
	}

	template <typename Iterator>
	void applyTo(Iterator from, Iterator to) const {
		std::ptrdiff_t n = to - from;
		std::vector<typename std::iterator_traits<Iterator>::value_type> result(n);
		if(std::distance(from, to) != n)
			throw VerdictException(Verdict::FAIL, "Size of permutation not equal to size of range");
		for(size_t i = 0, s = static_cast<size_t>(n); i < s; ++i) {
			result[permutation[i]] = std::move(from[i]);
		}
		std::move(result.begin(), result.end(), from);
	}

	template <typename T>
	void applyTo(T& range) const {
		return applyTo(std::begin(range), std::end(range));
	}

	Permutation inverse() const {
		size_t n = size();
		Permutation result(n);
		for(size_t i = 0; i < n; ++i){
			result.permutation[permutation[i]] = i;
		}
		return result;
	}

	static Permutation identity(size_t n) {
		Permutation id(n);
		for(size_t i = 0; i < n; ++i){
			id.permutation[i] = i;
		}
		return id;
	}

	size_t operator[] (size_t index) const {
		return permutation[index];
	}

	iterator begin() const {
		return permutation.begin();
	}

	iterator end() const {
		return permutation.end();
	}

	size_t size() const {
		return permutation.size();
	}

	Permutation operator * (const Permutation& rhs) const {
		size_t n = size();
		if(n != rhs.size())
			throw VerdictException(Verdict::FAIL, "Can't multiply permutations of different sizes");
		Permutation result(n);
		for(size_t i = 0; i < n; ++i)
			result.permutation[i] = permutation[rhs.permutation[i]];
		return result;
	}

	bool operator == (const Permutation& rhs) const {
		if(size() != rhs.size()) {
			throw VerdictException(Verdict::FAIL, "Comparation of permutation of different length");
		}
		return permutation == rhs.permutation;
	}

	bool operator != (const Permutation& rhs) const {
		return !(*this == rhs);
	}

	bool operator < (const Permutation& rhs) const {
		if(size() != rhs.size()) {
			throw VerdictException(Verdict::FAIL, "Comparation of permutation of different length");
		}
		return permutation < rhs.permutation;
	}

	bool operator > (const Permutation& rhs) const {
		return rhs < *this;
	}

	bool operator <= (const Permutation& rhs) const {
		return !(*this > rhs);
	}

	bool operator >= (const Permutation& rhs) const {
		return !(*this < rhs);
	}

	friend std::ostream& operator << (std::ostream& stream, const Permutation& permutation) {
		return stream << rangeToString(permutation.begin(), permutation.end());
	}
private:

	Permutation(size_t n): permutation(n) {
	}

	std::vector<ValueType> permutation;

};

Permutation pow(Permutation p, intmax_t n) {
	bool needInverse = n < 0;
	Permutation result = Permutation::identity(n);
	while(n != 0) {
		if(n % 2) {
			result = result * p;
		}
		p = p * p;
		n /= 2;
	}
	if(needInverse)
		result = result.inverse();
	return result;
}

template <>
class DefaultGenerator<Permutation> : public Generator<Permutation> {
public:
	Permutation generate(Random& rnd, size_t n) {
		std::vector<size_t> result(n);
		for(size_t i = 0; i < n; ++i) {
			result[i] = i;
		}
		rnd.shuffle(result.begin(), result.end());
		return Permutation(result);
	}
};

template <>
class DefaultReader<Permutation> : public Reader<Permutation> {
public:
	template <typename... Args>
	Permutation read(IStream& stream, Args&&... args) {
		auto vector = stream.read<size_t>(std::forward<Args>(args)...);
		try {
			return Permutation(vector);
		}
		catch(VerdictException& e){
			stream.quit(Verdict::PE, e.message);
		}
	}
};
