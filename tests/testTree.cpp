#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include "libs/tree/tree.hpp"
#include "testlib/readers/pair.hpp"
#include "testlib/readers/vector.hpp"
#include "testReadTools.hpp"
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
	
	BOOST_AUTO_TEST_CASE(MakeParentIdLessTree) {
		setStr("3 0 1 0 2 1 3");
		vpii a = stream.read<vpii>(DefaultReader<std::pair<size_t, size_t> >());
		Tree tree(a);
		tree = tree.rehang(2);
		tree = makeParentsIdLess(tree);		
		std::vector<size_t> b;
		for (auto x: tree.children(0))
			b.push_back(x);
		std::vector<size_t> expected = {1};
		BOOST_CHECK(b == expected);
		
		b.clear();
		for (auto x : tree.children(1))
			b.push_back(x);
		sort(b.begin(), b.end());	
		expected = {2};
		BOOST_CHECK(b == expected);		
	}
	BOOST_AUTO_TEST_CASE(RehangTree) {
		setStr("5 0 1 0 2 1 3 1 4 4 5");
		vpii a = stream.read<vpii>(DefaultReader<std::pair<size_t, size_t> >());
		Tree tree(a);
		
		tree = tree.rehang(1);
		std::vector<size_t> b;
		for (auto x: tree.children(1))
			b.push_back(x);
		sort(b.begin(), b.end());
		std::vector<size_t> expected = {0, 3, 4};
		BOOST_CHECK(b == expected);
		
		b.clear();
		for (auto x : tree.children(0))
			b.push_back(x);
		expected = {2};
		BOOST_CHECK(b == expected);
	}
	
	BOOST_AUTO_TEST_CASE(GeneratorTree) {
		for (size_t i = 1, q = 0; q < 10; i *= 123, q++){
			Random rnd(i);
			for (size_t n = 1; n <= 100; ++n){
				Tree tree = rnd.next<Tree>(n);
				BOOST_CHECK(tree.size() == n);
				BOOST_CHECK(isTree(tree) == true);	
			}
			
			for (size_t n = 1; n <= 100; ++n){
				Tree tree = rnd.next<Tree>(BambooGenerator(), n);
				BOOST_CHECK(tree.size() == n);
				BOOST_CHECK(isTree(tree) == true);	
			}
			
			for (size_t n = 1; n <= 100; ++n){
				Tree tree = rnd.next<Tree>(FluffyBambooGenerator(), n);
				BOOST_CHECK(tree.size() == n);
				BOOST_CHECK(isTree(tree) == true);	
			}
		
		}
	}

	BOOST_AUTO_TEST_CASE(GeneratorBalancedKTree) {
		for (size_t i = 1, q = 0; q < 10; i *= 267, q++){
			Random rnd(i);
			for (size_t n = 1; n <= 100; n++){
				for (size_t k = 1; k <= std::min(n, size_t(6)); k++){
					Tree tree = rnd.next<Tree>(BalancedKTreeGenerator(), n, k);
					BOOST_CHECK(tree.size() == n);
					BOOST_CHECK(isBalancedKTree(tree, k) == true);
				}
			}
		}
	}

	BOOST_AUTO_TEST_CASE(GeneratorBinaryTree) {
		for (size_t i = 1, q = 0; q < 10; i *= 267, q++){
			Random rnd(i);
			for (size_t n = 1; n <= 100; ++n){
				if (n % 2 == 0){
					BOOST_CHECK_THROW(rnd.next<Tree>(BinaryTreeGenerator(), n), VerdictException);
				}
				else{
					Tree tree = rnd.next<Tree>(BinaryTreeGenerator(), n);
					BOOST_CHECK(tree.size() == n);
					BOOST_CHECK(isBinaryTree(tree) == true);
				}
			}
		}
	}
BOOST_AUTO_TEST_SUITE_END()
