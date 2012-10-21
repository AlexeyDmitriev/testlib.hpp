#pragma once

#include "reader.hpp"
#include "istream.hpp"
#include <limits>
#include <string>
#include <type_traits>
#include <cmath>

template <typename T>
class FloatReader : public Reader<T> {
public:
	T read(IStream& stream) const {
		std::string input = stream.readToken();
		std::string usedValue = input;
		if (input.size() >= MAX_LENGTH)
			stream.quit(Verdict::PE, expectation("Float", input));
		if(input[0] == '-') {
			usedValue = usedValue.substr(1);
		}
		if(usedValue.empty())
			stream.quit(Verdict::PE, expectation("Float", input));

		if(usedValue[0] == '0' && usedValue.size() > 1 && usedValue[1] != '.')
			stream.quit(Verdict::PE, expectation("Float", input));
		if(usedValue[0] == '.')
			stream.quit(Verdict::PE, expectation("Float", input));
		if(usedValue.back() == '.')
			stream.quit(Verdict::PE, expectation("Float", input));

		bool wasPoint = false;
		for (char digit: usedValue) {
			if(digit == '.') {
				if (wasPoint)
					stream.quit(Verdict::PE, expectation("Float", input));
				wasPoint = true;
			}
			else {
				if(digit < '0' || digit > '9')
					stream.quit(Verdict::PE, expectation("Float", input));
			}
		}

		std::stringstream ss(input);
		T result;
		
		ss >> result;
		
		return result;
	}
	T read(IStream& stream, T min, T max) const {
		T result = read(stream);
		if(result < min || result > max)
			stream.quit(Verdict::WA, "Float violates the range [" + toString(min) + "," + toString(max) + "]");
		return result; 
	}
	T read(IStream& stream, T min, T max, const std::string& name) const {
		T result = read(stream);
		if(result < min || result > max)
			stream.quit(Verdict::WA, "Float " + toPrint(name) + " violates the range [" + toString(min) + "," + toString(max) + "]");
		return result;
	}
private:
	static constexpr T EPS = 1e-10;
	static constexpr size_t MAX_LENGTH = 50;
};

template<typename T>
class DefaultReader<T, typename std::is_floating_point<T>::type> : public FloatReader<T> {};

