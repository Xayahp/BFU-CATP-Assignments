#include "particle_emitter.h"

HinaPE::ParticleEmitter3::ParticleEmitter3() : Kasumi::ArrowObject() { _rebuild_(); }

void HinaPE::ParticleEmitter3::INSPECT()
{
	Kasumi::ArrowObject::INSPECT();

	ImGui::Text("Emitter Physics");
	ImGui::Separator();
	INSPECT_BOOL(_opt.enable, "Enable");
	INSPECT_VEC3(_opt.origin, "origin");
	INSPECT_VEC3(_opt.direction, "direction");
	INSPECT_REAL(_opt.speed, "speed");
	INSPECT_REAL(_opt.spread_angle, "spread angle");

	if (Object3D::_opt.dirty)
	{
		_opt.origin = Object3D::_opt.pose.position;
		_opt.direction = mQuaternion(Object3D::_opt.pose.euler) * mVector3::UnitZ();
		Object3D::_opt.dirty = false;
	}
}
