#ifndef HINAPE_BBOX_H
#define HINAPE_BBOX_H

#include "vector.h"

#include <limits>

namespace HinaPE::Base
{
template<typename T>
class BoundingBox3
{
public:
	auto width() const -> T;
	auto height() const -> T;
	auto depth() const -> T;
	auto length(size_t axis) -> T;
	auto overlaps(const BoundingBox3 &other) const -> bool;

public:
	constexpr BoundingBox3();
	constexpr BoundingBox3(const Vector3<T> &point1, const Vector3<T> &point2);
	constexpr BoundingBox3(const BoundingBox3 &bbox);
	constexpr BoundingBox3(BoundingBox3 &&bbox) noexcept;

public:
	Vector3<T> lower_corner, upper_corner;
};

template<typename T>
constexpr BoundingBox3<T>::BoundingBox3() : lower_corner(0), upper_corner(0) {}
template<typename T>
constexpr BoundingBox3<T>::BoundingBox3(const Vector3<T> &point1, const Vector3<T> &point2)
{
	lower_corner.x() = std::min(point1.x(), point2.x());
	lower_corner.y() = std::min(point1.y(), point2.y());
	lower_corner.z() = std::min(point1.z(), point2.z());
	upper_corner.x() = std::max(point1.x(), point2.x());
	upper_corner.y() = std::max(point1.y(), point2.y());
	upper_corner.z() = std::max(point1.z(), point2.z());
}
template<typename T>
constexpr BoundingBox3<T>::BoundingBox3(const BoundingBox3 &bbox) = default;
template<typename T>
constexpr BoundingBox3<T>::BoundingBox3(BoundingBox3 &&bbox) noexcept = default;

template<typename T>
auto BoundingBox3<T>::width() const -> T { return upper_corner.x() - lower_corner.x(); }
template<typename T>
auto BoundingBox3<T>::height() const -> T { return upper_corner.y() - lower_corner.y(); }
template<typename T>
auto BoundingBox3<T>::depth() const -> T { return upper_corner.z() - lower_corner.z(); }
template<typename T>
auto BoundingBox3<T>::length(size_t axis) -> T
{
	assert(axis < 3);
	return upper_corner[axis] - lower_corner[axis];
}
template<typename T>
auto BoundingBox3<T>::overlaps(const BoundingBox3 &other) const -> bool
{
	if (upper_corner.x() < other.lower_corner.x() || lower_corner.x() > other.upper_corner.x())
		return false;

	if (upper_corner.y() < other.lower_corner.y() || lower_corner.y() > other.upper_corner.y())
		return false;

	if (upper_corner.z() < other.lower_corner.z() || lower_corner.z() > other.upper_corner.z())
		return false;

	return true;
}
}

#endif //HINAPE_BBOX_H