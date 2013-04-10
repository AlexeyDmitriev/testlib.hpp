#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/Tree.hpp"
#include "testlib/readers/pair.hpp"
#include "testlib/readers/vector.hpp"
#include "testReadTools.hpp"
#include <boost/test/unit_test.hpp>

typedef std::vector<std::pair<size_t, size_t> > vpii;
using namespace treee;
BOOST_FIXTURE_TEST_SUITE(TreeTest, NonStrictRead)
	BOOST_AUTO_TEST_CASE(BaseTree) {
		setStr("3 0 1 0 2 1 3");
		vpii a = stream.read<vpii>(DefaultReader<std::pair<size_t, size_t> >());
		std::cerr << "1\n";
		Tree tree(a);
		std::cerr << "2\n";
		
		std::vector<int> b;
		std::cerr << tree.size() << "\n";
		for (auto x: tree.children(0))
			b.push_back(x);
		std::cerr << "3\n";
		
		std::vector<int> expected = {1, 2};
		for (auto x: b) std::cerr << x << std::endl;
		BOOST_CHECK(b == expected);
	}
 
BOOST_AUTO_TEST_SUITE_END()
