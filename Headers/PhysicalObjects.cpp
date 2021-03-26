#include "PhysicalObjects.h"

void BasicPhysicalObjects::set_position(const Eigen::Vector3f &pos) {

    this->x = pos;
}

//void BasicPhysicalObjects::update_position() {}

Eigen::Matrix4f BasicPhysicalObjects::generate_translation_mat() {
    Eigen::Matrix4f res = Eigen::Matrix4f::Identity();
    res(0, 3) = x.x();
    res(1, 3) = x.y();
    res(2, 3) = x.z();
    return res;
}

void BasicPhysicalObjects::sub_step(float delta_t) {

    if (!is_fixed) {
        Eigen::Vector3f F_total = Eigen::Vector3f::Zero();

        F_total = Eigen::Vector3f(0.f, -0.098f, 0.f);

        Eigen::Vector3f a = F_total / m;

        v += a * delta_t;


        collision_detection();


        x += v * delta_t;
    }
}

void BasicPhysicalObjects::collision_detection() { /* no implementation here */ }

BasicPhysicalObjects::BasicPhysicalObjects() : x(Eigen::Vector3f::Zero()), v(Eigen::Vector3f::Zero()),
                                               f(Eigen::Vector3f::Zero()), ff(0.f), m(1.f) {}

Ground::Ground(float width, float height) : Plane(), width(width), height(height) {
    is_fixed = true;
}

Eigen::Matrix4f Ground::generate_scale_mat() const {
    Eigen::Matrix4f res = Eigen::Matrix4f::Identity();
    res(0, 0) = height;
    res(2, 2) = width;
    return res;
}

Ball::Ball(float radius) : Sphere(), radius(radius) {}

void Ball::collision_detection() {
    if (x.y() < -3.f+radius)
        v = -0.99 * v;
}

Eigen::Matrix4f Ball::generate_scale_mat() const {
    Eigen::Matrix4f res = Eigen::Matrix4f::Identity();
    res(0, 0) = radius;
    res(1, 1) = radius;
    res(2, 2) = radius;
    return Eigen::Matrix4f();
}
