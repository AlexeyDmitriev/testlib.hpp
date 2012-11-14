#pragma once
#include <string>

typedef HexReader<int>::Case Case;

inline int rnd()
{
	static int RND_X = 0;
	RND_X = RND_X * 26 + 17;
	return RND_X;
}

inline std::string getNextString(const std::string& s)
{
	std::string res = s;
	if (res[0] == '-')
		res[res.size() - 1]--;
	else
		res[res.size() - 1]++;
	return res;
}

inline std::string getPrevString(const std::string& s)
{
	if (s == "0")
		return "-1";
	std::string res = s;
	if (s[0] == '-')
		res[res.size() - 1]++;
	else
		res[res.size() - 1]--;
	return res;
}

inline std::string getPrevHexString(const std::string& s);

inline std::string getNextHexString(const std::string& s)
{
	if (s == "-1")
		return "0";
	if (s[0] == '-'){
		return '-' + getPrevHexString(s.substr(1));
	}
	std::string res = s;
	for (int i = res.length() - 1; i >= 0; --i){
		if (res[i] != 'f'){
			if (res[i] == '9'){	
				res[i] = 'a';
			}
			else{
				res[i]++;
			}
			return res;
		}
		res[i] = 0;
	}
	res = '1' + res;
	return res;
}

inline std::string getPrevHexString(const std::string& s)
{
	if (s == "0")
		return "-1";
	if (s[0] == '-'){
		return '-' + getNextHexString(s.substr(1));
	}
	std::string res = s;
	for (int i = res.length() - 1; i >= 0; --i){
		if (res[i] != '0')
		{
			if (res[i] == 'a'){	
				res[i] = '9';
			}
			else{
				res[i]--;
			}
			return res;
		}
		res[i] = 'f';
	}
	
	return res;
}

template <typename T>
void testCornersThrow(Read& in) {
	in.setStr(getPrevString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
	in.setStr(getNextString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_THROW(in.stream.read<T>(), ReadingException);
}

template <typename T>
void testCorners(Read& in) {
	in.setStr(toString(std::numeric_limits<T>::min()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
	in.setStr(toString(std::numeric_limits<T>::max()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());

	in.setStr(getPrevString(toString(std::numeric_limits<T>::max())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
	in.setStr(getNextString(toString(std::numeric_limits<T>::min())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>());
}

template <typename T>
std::string toHex(T val) {
	if (val == 0)
		return "0";
	std::string res;
	T c = val;
	while (c) {
		if (abs(c % 16) >= 10)
			res += char('a' + abs(c % 16) - 10);
		else
			res += char('0' + abs(c % 16));
		c /= 16;
	}
	std::reverse(res.begin(), res.end());
	if (val < 0)
		res = "-" + res;
	return res;
}

template <typename T>
void testHexPairs(Read& in, T l1, T r1, T l2, T r2) {	
	for (T i = l1; i <= r1; i++)
		for (T j = l2; j <= r2; j++)
		{
			in.setStr(toHex<T>(i) + " " + toHex<T>(j));
			BOOST_CHECK_EQUAL(in.stream.read<T>(HexReader<T>()), i);
			BOOST_CHECK_NO_THROW(in.stream.readSpace());
			BOOST_CHECK_EQUAL(in.stream.read<T>(HexReader<T>()), j);
		}
}

template <typename T>
void testHexCornersThrow(Read& in) {	
	in.setStr(getPrevHexString(toHex(std::numeric_limits<T>::min())));
	BOOST_CHECK_THROW(in.stream.read<T>(HexReader<T>()), ReadingException);
	in.setStr(getNextHexString(toHex(std::numeric_limits<T>::max())));
	BOOST_CHECK_THROW(in.stream.read<T>(HexReader<T>()), ReadingException);
}

template <typename T>
void testHexCorners(Read& in) {		
	in.setStr(toHex(std::numeric_limits<T>::min()));
	BOOST_CHECK_NO_THROW(HexReader<T>().read(in.stream));
	in.setStr(toHex(std::numeric_limits<T>::max()));
	BOOST_CHECK_NO_THROW(in.stream.read<T>(HexReader<T>()));

	in.setStr(getPrevHexString(toHex(std::numeric_limits<T>::max())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>(HexReader<T>()));
	in.setStr(getNextHexString(toHex(std::numeric_limits<T>::min())));
	BOOST_CHECK_NO_THROW(in.stream.read<T>(HexReader<T>()));
}
