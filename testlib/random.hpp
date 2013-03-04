#pragma once

#include <ctime>
#include <cstdint>
#include <cstddef>
#include <climits>
#include <stdexcept>
#include <type_traits>
#include "generator.hpp"

class Random {
public:
	static const size_t MAX_BITS = sizeof(uintmax_t) * CHAR_BIT;
	Random(uint64_t seed){
		this->seed = (seed ^ 0x5DEECE66DL) & ((one() << 48) - 1);
	}

	bool nextBit() {
		return _nextBits(1);
	}

	uintmax_t nextBits(size_t bitCount) {
		if(bitCount > MAX_BITS){
			throw std::out_of_range("Can't fit this number of bits in uintmax_t");
		}
		uintmax_t v = _nextBits(bitCount & 31);
		bitCount >>= 5;
		while(bitCount--){
			v <<= 32;
			v ^= _nextBits(32);
		}
		return v;
	}

	template<typename T, typename... Args>
	typename std::enable_if<!std::is_base_of<Generator<T>, typename firstType<Args...>::type>::value,T>::type next(Args&&... args){
		return DefaultGenerator<T>().generate(*this, std::forward<Args>(args)...);
	}
	
	template<typename T, typename U, typename... Args>
	typename std::enable_if<std::is_base_of<Generator<T>, U>::value,T>::type next(U generator, Args&&... args){
		return generator.generate(*this, std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	void fill(T& variable, Args&&... args) {
		variable = next<T>(std::forward<Args>(args)...);
	}
	
	template <typename RAI>
	void shuffle(RAI first, RAI last) {
		using std::swap;
		ptrdiff_t len = last - first;
		while(first != last){
			--len;
			swap(*first, first[next<ptrdiff_t>(0, len)]);
			++first;
		}
	}
private:
	uint64_t seed;
	
	uint32_t _nextBits(size_t bitCount){
		seed = (seed * 0x5DEECE66DL + 0xBL) & ((one() << 48) - 1);
		return uint32_t(seed >> (48 - bitCount));
	}

	uintmax_t one(){
		return 1;
	}

};
