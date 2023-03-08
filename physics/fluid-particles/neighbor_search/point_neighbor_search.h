#ifndef HINAPE_POINT_NEIGHBOR_SEARCH_H
#define HINAPE_POINT_NEIGHBOR_SEARCH_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "common.h"

namespace HinaPE
{
class PointNeighborSearch3
{
public:
	using ForEachNearbyPointFunc = std::function<void(size_t, const mVector3 &)>;

	virtual void for_each_nearby_point(const mVector3 &origin, real radius, const ForEachNearbyPointFunc &callback) = 0;
	virtual auto has_nearby_point(const mVector3 &origin, real radius) const -> bool = 0;
	virtual void build(const std::vector<mVector3> &points) = 0;
};


class PointSimpleListSearch3 final : public PointNeighborSearch3
{
public:
	void for_each_nearby_point(const mVector3 &origin, real radius, const ForEachNearbyPointFunc &callback) final;
	auto has_nearby_point(const mVector3 &origin, real radius) const -> bool final;
	void build(const std::vector<mVector3> &points) final;

private:
	std::vector<mVector3> _points;
};


class PointHashGridSearch3 final : public PointNeighborSearch3
{
public:
	void for_each_nearby_point(const mVector3 &origin, real radius, const ForEachNearbyPointFunc &callback) final;
	auto has_nearby_point(const mVector3 &origin, real radius) const -> bool final;
	void build(const std::vector<mVector3> &points) final;

private:
	real _grid_spacing = 1.0;
	mSize3 _resolution = {1, 1, 1};
	std::vector<mVector3> _points;
	std::vector<std::vector<size_t>> _buckets;
};

using PointNeighborSearch3Ptr = std::shared_ptr<PointNeighborSearch3>;
using PointSimpleListSearch3Ptr = std::shared_ptr<PointSimpleListSearch3>;
using PointHashGridSearch3Ptr = std::shared_ptr<PointHashGridSearch3>;
} //namespace HinaPE

#endif //HINAPE_POINT_NEIGHBOR_SEARCH_H