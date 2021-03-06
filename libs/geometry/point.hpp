#pragma once

#include "testlib/reader.hpp"
#include "testlib/generator.hpp"
#include "testlib/random.hpp"
#include "testlib/istream.hpp"
#include "testlib/separator.hpp"
#include "testlib/readers/pair.hpp"
#include "testlib/utility.hpp"
#include <type_traits>
#include <cmath>

namespace geometry {
template<typename T>
struct Point2D {
	T x;
	T y;
	Point2D(): x(), y() {}
	Point2D(T x, T y): x(x), y(y) {}

	Point2D& operator += (const Point2D& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point2D& operator -= (const Point2D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Point2D operator - () const {
		return Point2D(-x, -y);
	}

	Point2D& operator *= (T c) {
		x *= c;
		y *= c;
		return *this;
	}

	Point2D& operator /= (T c) {
		x /= c;
		y /= c;
		return *this;
	}

	T lengthSquared() const {
		return x * x + y * y;
	}

	auto length() -> decltype(sqrt(x)) const {
		return sqrt(lengthSquared());
		//TODO: compile in VS. add sqrt(int)
	}

	T dotProduct(const Point2D& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	T crossProduct(const Point2D& rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	auto angle() -> decltype(atan2(y, x)) const {
		return atan2(y, x);
	}
};

template<typename T>
Point2D<T> operator + (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	Point2D<T> copy = lhs;
	return copy += rhs;
}

template<typename T>
Point2D<T> operator - (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	Point2D<T> copy = lhs;
	return copy += rhs;
}

template<typename T>
bool operator < (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	std::less<T> less;
	std::equal_to<T> equal;
	return less(lhs.x, rhs.x) || equal(lhs.x, rhs.x) && less(lhs.y, rhs.y);
}

template<typename T>
bool operator > (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator <= (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	return !(lhs > rhs);
}

template <typename T>
bool operator >= (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	return !(lhs < rhs);
}

template<typename T>
bool operator == (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	std::equal_to<T> equal;
	return equal(lhs.x, rhs.x) && equal(lhs.y, rhs.y);
}

template<typename T>
bool operator != (const Point2D<T>& lhs, const Point2D<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
Point2D<T> operator * (const Point2D<T>& lhs, const T& rhs){
	Point2D<T> copy = lhs;
	return copy *= rhs;
}

template<typename T>
Point2D<T> operator * (const T& lhs, const Point2D<T>& rhs){
	Point2D<T> copy = rhs;
	return copy *= lhs;
}

template<typename T>
Point2D<T> operator / (const Point2D<T>& lhs, const T& rhs){
	Point2D<T> copy = lhs;
	return copy /= rhs;
}

template<typename T>
struct Point3D {
	T x;
	T y;
	T z;
	Point3D(): x(), y() {}
	Point3D(T x, T y, T z): x(x), y(y), z(z) {}

	Point3D& operator += (const Point3D& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Point3D& operator -= (const Point3D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Point3D operator - () const {
		return Point3D(-x, -y, -z);
	}

	Point3D& operator *= (T c) {
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	Point3D& operator /= (T c) {
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	T lengthSquared() const {
		return x * x + y * y + z * z;
	}

	auto length() -> decltype(sqrt(std::declval<T>())) const {
		return sqrt(lengthSquared());
	}

	T dotProduct(const Point3D& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Point3D crossProduct(const Point3D& rhs) const {
		return Point3D(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}
};

template<typename T>
Point3D<T> operator + (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	Point3D<T> copy = lhs;
	return copy += rhs;
}

template<typename T>
Point3D<T> operator - (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	Point3D<T> copy = lhs;
	return copy += rhs;
}

template<typename T>
bool operator < (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	std::less<T> less;
	std::equal_to<T> equal;
	return less(lhs.x, rhs.x) || 
	      equal(lhs.x, rhs.x) &&  less(lhs.y, rhs.y) ||
	      equal(lhs.x, rhs.x) && equal(lhs.y, rhs.y) && less(lhs.z, rhs.z);
}

template<typename T>
bool operator > (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	return rhs < lhs;
}

template <typename T>
bool operator <= (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	return !(lhs > rhs);
}

template <typename T>
bool operator >= (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	return !(lhs < rhs);
}


template<typename T>
bool operator == (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	std::equal_to<T> equal;
	return equal(lhs.x, rhs.x) &&
	       equal(lhs.y, rhs.y) &&
	       equal(lhs.z, rhs.z);
}

template<typename T>
bool operator != (const Point3D<T>& lhs, const Point3D<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
Point3D<T> operator * (const Point3D<T>& lhs, const T& rhs){
	Point3D<T> copy = lhs;
	return copy *= rhs;
}

template<typename T>
Point3D<T> operator * (const T& lhs, const Point3D<T>& rhs){
	Point3D<T> copy = rhs;
	return copy *= lhs;
}

template<typename T>
Point3D<T> operator / (const Point3D<T>& lhs, const T& rhs){
	Point3D<T> copy = lhs;
	return copy /= rhs;
}

} // namespace geometry

template<typename T>
class DefaultGenerator<typename geometry::Point2D<T>> : public Generator<typename geometry::Point2D<T>> {
	typedef typename geometry::Point2D<T> Point;
public:
	Point generate(Random& rnd) const {
		return generate(rnd, DefaultGenerator<T>());
	}

	template <typename Gen>
	Point generate(Random& rnd, Gen gen) const {
		return generate(rnd, gen, gen);
	}

	template <typename GenX, typename GenY>
	Point generate(Random& rnd, GenX genX, GenY genY) const {
		T x = rnd.next<T>(genX);
		T y = rnd.next<T>(genY);
		return Point(std::move(x), std::move(y));
	}
};

template<typename T>
class DefaultGenerator<typename geometry::Point3D<T>> : public Generator<typename geometry::Point3D<T>> {
	typedef typename geometry::Point3D<T> Point;
public:
	Point generate(Random& rnd) const {
		return generate(rnd, DefaultGenerator<T>());
	}

	template <typename Gen>
	Point generate(Random& rnd, Gen gen) const {
		return generate(rnd, gen, gen, gen);
	}

	template <typename GenX, typename GenY, typename GenZ>
	Point generate(Random& rnd, GenX genX, GenY genY, GenZ genZ) const {
		T x = rnd.next<T>(genX);
		T y = rnd.next<T>(genY);
		T z = rnd.next<T>(genZ);
		return Point(std::move(x), std::move(y), std::move(z));
	}
};

template<typename T>
class DefaultReader<typename geometry::Point2D<T>>: public Reader<typename geometry::Point2D<T>> {
	typedef typename geometry::Point2D<T> Point;
public:
	template <typename... Args>
	Point read(Args&&... args) const {
		std::pair<T, T> pair = DefaultReader<std::pair<T,T>>().read(std::forward<Args>(args)...);
		return Point(pair.first, pair.second);
	}
};

template<typename T>
class DefaultReader<typename geometry::Point3D<T>>: public Reader<typename geometry::Point3D<T>> {
	typedef typename geometry::Point3D<T> Point;
public:
	Point read(IStream& stream) const {
		return read(stream, defaultSeparator(stream));
	}
	Point read(IStream& stream, const Separator& separator) const {
		return read(stream, DefaultReader<T>(), separator);
	}

	template <typename U>
	if_reader<U, T, Point> read(IStream& stream, U reader) const {
		return read(stream, defaultSeparator(stream));
	}

	template <typename U>
	if_reader<U, T, Point> read(IStream& stream, U reader, const Separator& separator) const {
		return read(stream, reader, reader, reader, separator);
	}

	template <typename X, typename Y, typename Z>
	Point read(IStream& stream, X readerX, Y readerY, Z readerZ) const {
		return read(stream, readerX, readerY, readerZ, defaultSeparator(stream));
	}

	template <typename X, typename Y, typename Z>
	Point read(IStream& stream, X readerX, Y readerY, Z readerZ, const Separator& separator) const {
		static_assert(std::is_base_of<Reader<T>, X>::value, "reader must be Reader<T>");
		static_assert(std::is_base_of<Reader<T>, Y>::value, "reader must be Reader<T>");
		static_assert(std::is_base_of<Reader<T>, Z>::value, "reader must be Reader<T>");
		T x = stream.read<T>(readerX);
		separator.read(stream);
		T y = stream.read<T>(readerY);
		separator.read(stream);
		T z = stream.read<T>(readerZ);
		return Point(std::move(x), std::move(y), std::move(z));
	}
private:
	Separator defaultSeparator(IStream& stream) const {
		return stream.getMode() == IStream::Mode::STRICT ? " " : "";
	}
};

