#include "cloth_data.h"
HinaPE::ClothEngine::ClothData::ClothData() : ClothData(0) {}
HinaPE::ClothEngine::ClothData::ClothData(size_t number_of_particles)
{
    _position_idx = add_vector_data();
    _velocity_idx = add_vector_data();
    _force_idx = add_vector_data();

    resize(number_of_particles);
}
auto HinaPE::ClothEngine::ClothData::positions() const -> HinaPE::ConstArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_position_idx); }
auto HinaPE::ClothEngine::ClothData::position() -> HinaPE::ArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_position_idx); }
auto HinaPE::ClothEngine::ClothData::velocities() const -> HinaPE::ConstArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_velocity_idx); }
auto HinaPE::ClothEngine::ClothData::velocity() -> HinaPE::ArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_velocity_idx); }
auto HinaPE::ClothEngine::ClothData::forces() const -> HinaPE::ConstArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_force_idx); }
auto HinaPE::ClothEngine::ClothData::force() -> HinaPE::ArrayAccessor1<HinaPE::Vector3D> { return vector_data_at(_force_idx); }
auto HinaPE::ClothEngine::ClothData::number_of_particles() const -> size_t { return _number_of_particles; }
void HinaPE::ClothEngine::ClothData::resize(size_t new_number_of_particles)
{
    _number_of_particles = new_number_of_particles;
    for (auto &scalar_data: _scalar_data_list)
        scalar_data.resize(new_number_of_particles, 0.0);
    for (auto &vector_data: _vector_data_list)
        vector_data.resize(new_number_of_particles, Vector3D());
}
auto HinaPE::ClothEngine::ClothData::add_vector_data(const HinaPE::Vector3D &initial_value) -> size_t
{
    size_t attr_idx = _vector_data_list.size();
    _vector_data_list.emplace_back(number_of_particles(), initial_value);
    return attr_idx;
}
auto HinaPE::ClothEngine::ClothData::add_scalar_data(double initial_value) -> size_t
{
    size_t attr_idx = _scalar_data_list.size();
    _scalar_data_list.emplace_back(number_of_particles(), initial_value);
    return attr_idx;
}
auto HinaPE::ClothEngine::ClothData::vector_data_at(size_t idx) -> HinaPE::ArrayAccessor1<HinaPE::Vector3D> { return _vector_data_list[idx].accessor(); }
auto HinaPE::ClothEngine::ClothData::vector_data_at(size_t idx) const -> HinaPE::ConstArrayAccessor1<HinaPE::Vector3D> { return _vector_data_list[idx].constAccessor(); }
auto HinaPE::ClothEngine::ClothData::scalar_data_at(size_t idx) -> HinaPE::ArrayAccessor1<double> { return _scalar_data_list[idx].accessor(); }
auto HinaPE::ClothEngine::ClothData::scalar_data_at(size_t idx) const -> HinaPE::ConstArrayAccessor1<double> { return _scalar_data_list[idx].constAccessor(); }
