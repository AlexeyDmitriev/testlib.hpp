#include <vector>
#include <boost/test/unit_test.hpp>
#include "tests/testTools.hpp"
#include "testlib/readers/float.hpp"
#include "testlib/readers/int.hpp"
#include "testlib/readers/pair.hpp"
#include "testlib/readerWrapper.hpp"
#include "testlib/readers/vector.hpp"
#include "testlib/readers/string.hpp"
using std::vector;
using std::string;
using std::pair;
BOOST_FIXTURE_TEST_SUITE(wrapperTest, StrictRead)

class PSD_Reader : Reader<pair<string, double>>{
public:
	pair<string, double> read(IStream& stream) const{
		string s = stream.read<string>(2);
		stream.readChar(' ');
		double num = stream.read<double>(-1.0, 2.0);
		return std::make_pair(s, num);
	}
};

BOOST_AUTO_TEST_CASE(wrapper){
	
	setStr("2\n2 -11");
	vector<int> a(2, 2);
	a[1] = -11;
	vector<int> x = stream.read<vector<int>>(make_default_reader<int>(-15, 12));
	BOOST_CHECK(a == x);
	
	setStr("2\n2\n2.0 -11 3\n1.0 -11 2");
	vector<vector<double>> res(2, vector<double>());
	res[0].assign(2, 2.0); res[0][1] = -11.0;
	res[1].assign(3, 1.0); res[1][1] = -11.0; res[1][2] = 2.0;
	vector<vector<double>> y = stream.read< vector<vector<double>> >(make_default_reader<vector<double>>(make_default_reader<double>(-15.0, 12.0)));
	BOOST_CHECK(y == res);

	typedef pair<pair<string, double>, string> T;
	setStr("v 1.0 a");
	T pair(std::make_pair("v", 1.0), "a");
	PSD_Reader r;
	T z = stream.read<T>(r, make_default_reader<string>(1));
	BOOST_CHECK(z == pair);
}

BOOST_AUTO_TEST_SUITE_END()
