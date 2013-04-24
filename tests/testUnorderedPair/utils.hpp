#pragma once

typedef UnorderedPair<int> pi;

template<typename T>
std::ostream& operator << (std::ostream& stream, UnorderedPair<T> const & p){
	return stream << '{' << p.first << ',' << p.second << '}' << std::endl;
}
