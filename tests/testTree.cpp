#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "testlib/tree.hpp"
#include "testlib/readers/pair.hpp"
#include "testlib/readers/vector.hpp"
#include "testReadTools.hpp"
#include <boost/test/unit_test.hpp>
#include "testTree/utils.hpp"

typedef std::vector<std::pair<size_t, size_t> > vpii;
using namespace tree;
BOOST_FIXTURE_TEST_SUITE(TreeTest, NonStrictRead)
	BOOST_AUTO_TEST_CASE(BaseTree) {
		setStr("3 0 1 0 2 1 3");
		vpii a = stream.read<vpii>(DefaultReader<std::pair<size_t, size_t> >());
		Tree tree(a);
		std::vector<int> b;
		for (auto x: tree.children(0))
			b.push_back(x);
		std::vector<int> expected = {1, 2};
		BOOST_CHECK(b == expected);
		
		tree = tree.rehang(1);
		b.clear();
		for (auto x: tree.children(0))
			b.push_back(x);
		expected = {2};
		BOOST_CHECK(b == expected);
		
	}
	
	BOOST_AUTO_TEST_CASE(GeneratorTree) {
		Random rnd(1);
		for (size_t n = 1; n <= 100; ++n){
			Tree tree = rnd.next<Tree>(n);
			//printTree(tree);
			BOOST_CHECK(isTree(tree) == true);	
		}
	}
BOOST_AUTO_TEST_SUITE_END()
