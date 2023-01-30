#ifndef HINAPE_GRID_H
#define HINAPE_GRID_H

#include "base/base.h"
#include "field.h"
#include <vector>

namespace Hina
{
class Grid3
{
public:
	void resize(const Base::Size3 &resolution, const Base::mVector3 &grid_spacing, const Base::mVector3 &origin);

public:
	struct Opt
	{
		Base::Size3 resolution;
		Base::mVector3 origin;
		Base::mVector3 grid_spacing = Base::mVector3(1, 1, 1);
		Base::mBBox3 bounding_box;
	} _opt;
};

class ScalarGrid3 : public Grid3, public ScalarField3
{
public:
	void resize(const Base::Size3 &resolution, const Base::mVector3 &grid_spacing, const Base::mVector3 &origin, Base::real initial_value);
	virtual inline auto size() const -> Base::Size3 = 0;

private:
	std::vector<Base::real> _data;
};
using ScalarGrid3Ptr = std::shared_ptr<ScalarGrid3>;
class CellCenteredScalarGrid3 final : public ScalarGrid3
{
public:
	inline auto size() const -> Base::Size3 final { return _opt.resolution; }
};
class VertexCenteredScalarGrid3 final : public ScalarGrid3
{
public:
	inline auto size() const -> Base::Size3 final { return _opt.resolution + Base::Size3(1, 1, 1); }
};

class VectorGrid3 : public Grid3, public VectorField3
{
public:
	void resize(const Base::Size3 &resolution, const Base::mVector3 &grid_spacing, const Base::mVector3 &origin, Base::mVector3 initial_value);
};
using VectorGrid3Ptr = std::shared_ptr<VectorGrid3>;
class CollocatedVectorGrid3 : public VectorGrid3
{
private:
	Base::Array3<Base::mVector3> _data;
};
class CellCenteredVectorGrid3 final : public CollocatedVectorGrid3 {};
class VertexCenteredVectorGrid3 final : public CollocatedVectorGrid3 {};
class FaceCenteredVectorGrid3 final : public VectorGrid3 {};
}

#endif //HINAPE_GRID_H
