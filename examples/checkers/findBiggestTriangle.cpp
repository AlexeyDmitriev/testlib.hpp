#include "testlib.hpp"
#include <set>
#include <vector>

using namespace std;
const double EPS = 1e-8;
const double MAXX = 1e6, MAXY = 1e6;

struct Point{
	double x, y;
	Point() {}
	Point(double x, double y): x(x), y(y) {}
	bool operator < (const Point& point) const{
		return make_pair(x, y) < make_pair(point.x, point.y);
	}
	
};

class ReaderPoint : Reader<Point>{
public:
	ReaderPoint(double maxAbsX, double maxAbsY): minX(-maxAbsX), maxX(maxAbsX), minY(-maxAbsY), maxY(maxAbsY) {}
	ReaderPoint(double minX, double maxX, double minY, double maxY): minX(minX), maxX(maxX), minY(minY) , maxY(maxY) {}
	Point read(IStream& stream){
		double x = stream.read<double>(minX, maxX);
		double y = stream.read<double>(minY, maxY);
		return Point(x, y);
	}
private:
	double minX, maxX, minY, maxY;
};

double findSquare(vector<Point> polygon){
	double res = 0;
	polygon.push_back(polygon[0]);
	for (size_t i = 0; i < polygon.size() - 1; i++){
		res += (polygon[i].x - polygon[i + 1].x) * (polygon[i].y + polygon[i + 1].y);
	}
	return fabs(res) / 2.0;
}

set<Point> inputPoints;
ReaderPoint readerPoint(1e6, 1e6);
	
double readAns(IStream &is, Verdict verdict) {
	double s = is.read<double>();
	vector<Point> res;
	for (int i = 0; i < 3; i++){
		Point tmp = is.read<Point>(readerPoint);
		res.push_back(tmp);
		if (inputPoints.find(tmp) == inputPoints.end()){
			QUIT(verdict, "Point " << tmp.x << " " << tmp.y << " isn't exist in input file");
		}
	}
	verify(fabs(findSquare(res) - s) < EPS, verdict, "Triangle's square doesn't match answer");
	return s;
}

TESTLIB_CHECK(){
	int n = inf.read<int>();
	for (int i = 0; i < n; i++) {
		inputPoints.insert(inf.read<Point>(readerPoint));
	}
	
	double pa = readAns(ouf, Verdict::WA);
	double ja = readAns(ans, Verdict::FAIL);
	
	if (fabs(ja - pa) < EPS)
		OK(pa);
	if (pa > ja + EPS)
		FAIL("Participant found better answer than jury");
	WA("Jury found better answer than participant");
}