#include "testlib.hpp"
#include <set>
#include <vector>

using namespace std;
const double EPS = 1e-8;

struct Point{
	double x, y;
	Point() {}
	Point(double x, double y): x(x), y(y) {}
	bool operator < (const Point& point) const{
		return make_pair(x, y) < make_pair(point.x, point.y);
	}
	Point operator - (const Point& point) const{
		return Point(x - point.x, y - point.y);
	}
};
typedef vector<Point> Triangle;

class ReaderPoint : Reader<Point>{
public:
	ReaderPoint(double maxAbsX, double maxAbsY): minX(-maxAbsX), maxX(maxAbsX), minY(-maxAbsY), maxY(maxAbsY) {}
	ReaderPoint(double minX, double maxX, double minY, double maxY): minX(minX), maxX(maxX), minY(minY) , maxY(maxY) {}
	Point read(IStream& stream){
		double x = stream.read<double>(minX, maxX);
		if (stream.getMode() == IStream::Mode::STRICT)
			stream.readChar(' ');
		double y = stream.read<double>(minY, maxY);
		return Point(x, y);
	}
private:
	double minX, maxX, minY, maxY;
};

double outerProduct(const Point& a, const Point& b){
	return a.x * b.y - a.y * b.x;
}

double triangleArea(const Triangle& triangle){
	return fabs( outerProduct(triangle[2] - triangle[0], triangle[1] - triangle[0]) )/ 2.0;
}

set<Point> inputPoints;
ReaderPoint readerPoint(1e6, 1e6);
	
double readAns(IStream& is, Verdict verdict) {
	double s = is.read<double>();
	Triangle res = is.read<Triangle>(3, readerPoint); 
	for (const auto& point: res){
		if (inputPoints.find(point) == inputPoints.end()){
			QUIT(verdict, "Point " << point.x << " " << point.y << " isn't exist in input file");
		}
	}
	verify(fabs(triangleArea(res) - s) < EPS, verdict, "Triangle's square doesn't match answer");
	return s;
}

TESTLIB_CHECK(){
	int n = inf.read<int>();
	for (int i = 0; i < n; i++){
		inputPoints.insert(inf.read<Point>(readerPoint));
	}
	
	double pa = readAns(ouf, Verdict::WA);
	double ja = readAns(ans, Verdict::FAIL);
	
	if (fabs(ja - pa) < EPS)
		OK(pa);
	if (pa > ja + EPS)
		FAIL("Participant answer is better");
	WA("Jury answer is better");
}