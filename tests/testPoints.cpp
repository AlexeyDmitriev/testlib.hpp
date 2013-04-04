#include <boost/test/unit_test.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include "testlib/generators/int.hpp"
#include "testlib/generators/float.hpp"
#include "testlib/generatorWrapper.hpp"

#include "libs/geometry/point.hpp"

#include "testRandomTools.hpp"

BOOST_FIXTURE_TEST_SUITE(PointsRandom, RandomTest)

using namespace geometry;
struct TestDotProduct{
	TestDotProduct(Random& rnd): rnd(rnd) {}
	template<typename T>
	void operator () (T) {
		auto gen = make_default_generator<decltype(T().x)>(-100, 100);
		for(int i = 0; i < 10; ++i) {
			T point = rnd.next<T>(gen);
			BOOST_CHECK_EQUAL(point.lengthSquared(), point.dotProduct(point));
			T x = rnd.next<T>(gen);
			BOOST_CHECK_EQUAL(x.dotProduct(point), point.dotProduct(x));
		}
	}
private:
	Random& rnd;
};
BOOST_AUTO_TEST_CASE(dotProduct){
	boost::mpl::for_each<boost::mpl::vector<Point2D<int>, Point3D<int>, Point2D<double>>>(TestDotProduct(rnd));

	Point2D<int> x(5, 7) , y(3, 2);
	BOOST_CHECK_EQUAL(x.dotProduct(y), 29);

}

BOOST_AUTO_TEST_CASE(crossProduct2D) {
	for(int i = -2; i < 3; ++i) {
		auto point = rnd.next<Point2D<int>>();
		BOOST_CHECK_EQUAL(point.crossProduct(point * i), 0);
	}

	Point2D<int> x(5, 7) , y(3, 2);
	BOOST_CHECK_EQUAL(x.crossProduct(y), -11);

}

BOOST_AUTO_TEST_CASE(crossProduct3D) {
	typedef Point3D<int> Point;
	for(int i = 0; i < 10; ++i) {
		Point x = rnd.next<Point>();
		Point y = rnd.next<Point>();
		Point z = x.crossProduct(y);
		BOOST_CHECK_EQUAL(x.dotProduct(z), 0);
		BOOST_CHECK_EQUAL(y.dotProduct(z), 0);
	}

	Point x(5, 7, 0) , y(3, 2, 0);
	BOOST_CHECK(x.crossProduct(y) == Point(0, 0, -11));
}

BOOST_AUTO_TEST_CASE(misc) {
	typedef Point2D<int> Point;
	BOOST_CHECK_EQUAL(Point(1, 1).length(), sqrt(2.0));
	BOOST_CHECK_EQUAL(Point(3, 3).angle(), 45 * acos(-1.0) / 180);
}

BOOST_AUTO_TEST_SUITE_END()
