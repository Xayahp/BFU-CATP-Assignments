#include "Objects3D.h"

// ---------------------------------------- constructors ----------------------------------------
Ground::Ground(float width, float height) : Plane(), width(width), height(height) { is_fixed = true; }

Ball::Ball(float radius) : Sphere(), radius(radius) {}


// ---------------------------------------- updates ----------------------------------------
void Ground::update() {
    Plane::model = get_model();
    Plane::set_model(Plane::model);
}

void Ball::update() {
    Sphere::model = get_model();
    Sphere::set_model(Sphere::model);
}


// ---------------------------------------- draws ----------------------------------------
void Ground::draw() {
    update();
    Plane::draw();
}

void Ball::draw() {
    update();
    Sphere::draw();
}


// ---------------------------------------- sets ----------------------------------------
void Ground::set_vp(const Eigen::Matrix4f &view, const Eigen::Matrix4f projection) {
    Plane::set_model(model);
    Plane::set_view(view);
    Plane::set_projection(projection);
}

void Ball::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Sphere::set_model(model);
    Sphere::set_view(view);
    Sphere::set_projection(projection);
}


// ---------------------------------------- gets ----------------------------------------
Eigen::Matrix4f Ground::get_model() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    translation(2, 3) = x.z();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = height;
    scale(2, 2) = width;
    return translation * rotation * scale;
}

Eigen::Matrix4f Ball::get_model() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    translation(2, 3) = x.z();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = radius;
    scale(1, 1) = radius;
    scale(2, 2) = radius;
    return translation * rotation * scale;
}

std::shared_ptr<AABB> &Ground::get_aabb() {
    update();
    Ground::update_AABB();
    return Ground::aabb;
}

std::shared_ptr<AABB> &Ball::get_aabb() {
    update();
    Ball::update_AABB();
    return Ball::aabb;
}