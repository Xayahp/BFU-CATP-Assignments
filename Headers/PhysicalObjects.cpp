#include <Eigen/Cholesky>
#include <Eigen/Core>
#include "PhysicalObjects.h"

BasicPhysicalObjects::~BasicPhysicalObjects() = default;

void BasicPhysicalObjects::set_position(const Eigen::Vector3f &pos) {
    this->x = pos;
    im(0, 3) = x.x();
    im(1, 3) = x.y();
    im(2, 3) = x.z();
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

void BasicPhysicalObjects::collision_detection() {}

BasicPhysicalObjects::BasicPhysicalObjects() : x(Eigen::Vector3f::Zero()), v(Eigen::Vector3f::Zero()),
                                               f(Eigen::Vector3f::Zero()), ff(0.f), m(1.f), is_fixed(false),
                                               im(Eigen::Matrix4f::Identity()) {}


Brick::Brick(float width, float height) : Rectangle(), width(width), height(height) {}

void Brick::update() {

    for (int i = 0; i < 15; ++i) {
        f = Eigen::Vector3f(0.f, -9.8f, 0.f);
        v += (f / m) * 0.0001;

        collision_detection();

        x += v * 0.01;

        f = Eigen::Vector3f::Zero();
    }

    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = width;
    scale(1, 1) = height;
    Brick::model = translation * scale * rotation;
    Brick::set_model(Brick::model);
}

void Brick::draw() {
    update();
    Rectangle::draw();
}

void Brick::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Rectangle::set_model(model);
    Rectangle::set_view(Eigen::Matrix4f::Identity());
    Rectangle::set_projection(Eigen::Matrix4f::Identity());
}

void Brick::collision_detection() {
    if (x.y() < -1.f + height)
        v = -0.95 * v;
}

Pizza::Pizza(float radius) : Circle(), radius(radius) {}

void Pizza::update() {

    for (int i = 0; i < 15; ++i) {
        f = Eigen::Vector3f(0.f, -9.8f, 0.f);
        v += (f / m) * 0.0001;

        collision_detection();

        x += v * 0.01;

        f = Eigen::Vector3f::Zero();
    }

    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = radius;
    scale(1, 1) = radius;
    Circle::model = translation * scale * rotation;
    Circle::set_model(Circle::model);
}

void Pizza::draw() {
    update();
    Circle::draw();
}

void Pizza::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Circle::set_model(model);
    Circle::set_view(Eigen::Matrix4f::Identity());
    Circle::set_projection(Eigen::Matrix4f::Identity());
}

void Pizza::collision_detection() {
    if (x.y() < -1.f + radius)
        v = -0.95 * v;
}

Ground::Ground(float width, float height) : Plane(), width(width), height(height) {
    is_fixed = true;
}

void Ground::update() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    translation(2, 3) = x.z();
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = height;
    scale(2, 2) = width;
    Plane::model = translation * scale * rotation;
    Plane::set_model(Plane::model);
}

void Ground::draw() {
    update();
    Plane::draw();
}

void Ground::set_vp(const Eigen::Matrix4f &view, const Eigen::Matrix4f projection) {
    Plane::set_model(model);
    Plane::set_view(view);
    Plane::set_projection(projection);
}

void Ground::collision_detection() {}

Ball::Ball(float radius) : Sphere(), radius(radius) {}

void Ball::update() {

    for (int i = 0; i < 15; ++i) {
        f = Eigen::Vector3f(0.f, -9.8f, 0.f);
        v += (f / m) * 0.0001;

        collision_detection();

        x += v * 0.01;

        f = Eigen::Vector3f::Zero();
    }

    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    translation(2, 3) = x.z();
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = radius;
    scale(1, 1) = radius;
    scale(2, 2) = radius;
    Sphere::model = translation * scale * rotation;
    Sphere::set_model(Sphere::model);
}

void Ball::draw() {
    update();
    Sphere::draw();
}

void Ball::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Sphere::set_model(model);
    Sphere::set_view(view);
    Sphere::set_projection(projection);
}

void Ball::collision_detection() {
    if (x.y() < (radius))
        v = -0.95 * v;
}