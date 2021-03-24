#include "BasicShapes3D.h"

using namespace W3D;

AABB::AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) : x_min(xMin), x_max(xMax),
                                                                                     y_min(yMin), y_max(yMax),
                                                                                     z_min(zMin), z_max(zMax) {}

// ------------------------------ Basic Shape 3D ------------------------------
BasicShape3D::BasicShape3D(Eigen::Vector3f center) : center(std::move(center)), rotation_angle(0), draw_mode(LINES),
                                                     fixed(false), mass(1.f), velocity(Eigen::Vector3f(0.f, 0.f, 0.f)),
                                                     force(Eigen::Vector3f(0.f, 0.f, 0.f)) {}

BasicShape3D::~BasicShape3D() {
    positions.clear();
}

void BasicShape3D::iterate(float time_step) {
    Eigen::Vector3f acceleration = force / mass;
    velocity += acceleration * time_step;
    center += velocity * time_step;
    force = Eigen::Vector3f::Zero();
}

BasicShape3D &BasicShape3D::set_color(Eigen::Vector3f &RGB) {
    color = Eigen::Vector4f(RGB.x(), RGB.y(), RGB.z(), 1.f);
    return *this;
}

BasicShape3D &BasicShape3D::set_color(Eigen::Vector4f &RGBA) {
    color = RGBA;
    return *this;
}

BasicShape3D &BasicShape3D::set_color(int HEX) {
    color[0] = ((HEX >> 16) & 0xFF) / 255.0;
    color[1] = ((HEX >> 8) & 0xFF) / 255.0;
    color[2] = ((HEX) & 0xFF) / 255.0;
    return *this;
}

BasicShape3D &BasicShape3D::set_draw_mode(DRAW_MODE mode) {
    draw_mode = mode;
    return *this;
}

BasicShape3D &BasicShape3D::fix() {
    fixed = true;
    return *this;
}

// ------------------------------ Cuboid ------------------------------
void Cuboid::generate_data() {
    Eigen::Vector3f tfl(center.x() - harf_length_x, center.y() + harf_length_y, center.z() + harf_length_z);
    Eigen::Vector3f tfr(center.x() + harf_length_x, center.y() + harf_length_y, center.z() + harf_length_z);
    Eigen::Vector3f bfl(center.x() - harf_length_x, center.y() + harf_length_y, center.z() - harf_length_z);
    Eigen::Vector3f bfr(center.x() + harf_length_x, center.y() + harf_length_y, center.z() - harf_length_z);
    Eigen::Vector3f tbl(center.x() - harf_length_x, center.y() - harf_length_y, center.z() + harf_length_z);
    Eigen::Vector3f tbr(center.x() + harf_length_x, center.y() - harf_length_y, center.z() + harf_length_z);
    Eigen::Vector3f bbl(center.x() - harf_length_x, center.y() - harf_length_y, center.z() - harf_length_z);
    Eigen::Vector3f bbr(center.x() + harf_length_x, center.y() - harf_length_y, center.z() - harf_length_z);
    switch (draw_mode) {
        case POINTS:
            positions.emplace_back(tfl);
            positions.emplace_back(tfr);
            positions.emplace_back(bfl);
            positions.emplace_back(bfr);
            positions.emplace_back(tbl);
            positions.emplace_back(tbr);
            positions.emplace_back(bbl);
            positions.emplace_back(bbr);
            break;
        case LINES:
            positions.emplace_back(tfl);
            positions.emplace_back(tfr);
            positions.emplace_back(tbl);
            positions.emplace_back(tbr);
            positions.emplace_back(bfl);
            positions.emplace_back(bfr);
            positions.emplace_back(bbl);
            positions.emplace_back(bbr);
            positions.emplace_back(tfl);
            positions.emplace_back(tbl);
            positions.emplace_back(tfr);
            positions.emplace_back(tbr);
            positions.emplace_back(bfl);
            positions.emplace_back(bbl);
            positions.emplace_back(bfr);
            positions.emplace_back(bbr);
            positions.emplace_back(tfl);
            positions.emplace_back(bfl);
            positions.emplace_back(tfr);
            positions.emplace_back(bfr);
            positions.emplace_back(tbl);
            positions.emplace_back(bbl);
            positions.emplace_back(tbr);
            positions.emplace_back(bbr);
            break;
        case TRIANGLES:
            positions.emplace_back(tfl);
            positions.emplace_back(tfr);
            positions.emplace_back(tbr);
            positions.emplace_back(tfl);
            positions.emplace_back(tbl);
            positions.emplace_back(tbr);
            positions.emplace_back(tfl);
            positions.emplace_back(tbl);
            positions.emplace_back(bfl);
            positions.emplace_back(tbl);
            positions.emplace_back(bfl);
            positions.emplace_back(bbl);
            positions.emplace_back(tfl);
            positions.emplace_back(tfr);
            positions.emplace_back(bfr);
            positions.emplace_back(tfl);
            positions.emplace_back(bfl);
            positions.emplace_back(bfr);

            positions.emplace_back(bbr);
            positions.emplace_back(tbr);
            positions.emplace_back(tbl);
            positions.emplace_back(bbr);
            positions.emplace_back(bbl);
            positions.emplace_back(tbl);
            positions.emplace_back(bbr);
            positions.emplace_back(bfr);
            positions.emplace_back(bfl);
            positions.emplace_back(bbr);
            positions.emplace_back(bbl);
            positions.emplace_back(bfl);
            positions.emplace_back(bbr);
            positions.emplace_back(tbr);
            positions.emplace_back(bfr);
            positions.emplace_back(tfr);
            positions.emplace_back(bfr);
            positions.emplace_back(tbr);
            break;
        default:
            std::cerr << "CUBOID::EXCEPTION::NOT_SUPPORTED_MODE" <<
                      std::endl;
            break;
    }
}

std::vector<float> Cuboid::get_positions() {
    positions.clear();
    generate_data();
    std::vector<float> res;
    for (auto &p : positions) {
        res.emplace_back(p.x());
        res.emplace_back(p.y());
        res.emplace_back(p.z());
    }
    return res;
}

AABB Cuboid::getAABB() {
    return AABB(0, 0, 0, 0, 0, 0);
}

void Cuboid::iterate(float time_step) {
    BasicShape3D::iterate(time_step);
}

void Cuboid::do_collision(const std::vector<std::unique_ptr<BasicShape3D>> &world_data) {

}

Cuboid::Cuboid(const Eigen::Vector3f &center, float harfLengthX, float harfLengthY, float harfLengthZ) : BasicShape3D(
        center), harf_length_x(harfLengthX), harf_length_y(harfLengthY), harf_length_z(harfLengthZ) {}
