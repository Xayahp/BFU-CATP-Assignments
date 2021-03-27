#include "Objects3D.h"


Ground::Ground(float width, float height) : Plane(), width(width), height(height) { is_fixed = true; }

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

Ball::Ball(float radius) : Sphere(), radius(radius) {}

void Ball::update() {

    for (int i = 0; i < 15; ++i) {
        f = Eigen::Vector3f(0.f, -9.8f, 0.f);
        v += (f / m) * 0.0001;

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