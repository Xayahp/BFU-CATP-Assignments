#include "Objects3D.h"

// ---------------------------------------- constructors ----------------------------------------
Box::Box(float width, float height, float depth) : Cube(), width(width), height(height), depth(depth) {}

Ball::Ball(float radius) : Sphere(), radius(radius) {}


// ---------------------------------------- updates ----------------------------------------
void Box::update() {
    Cube::model = get_model();
    Cube::set_model(Cube::model);
}

void Ball::update() {
    Sphere::model = get_model();
    Sphere::set_model(Sphere::model);
}


// ---------------------------------------- draws ----------------------------------------
void Box::draw() {
    update();
    Cube::draw();
}

void Ball::draw() {
    update();
    Sphere::draw();
}


// ---------------------------------------- sets ----------------------------------------
void Box::set_vp(const Eigen::Matrix4f &view, const Eigen::Matrix4f projection) {
    Cube::set_model(model);
    Cube::set_view(view);
    Cube::set_projection(projection);
}

void Ball::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Sphere::set_model(model);
    Sphere::set_view(view);
    Sphere::set_projection(projection);
}


// ---------------------------------------- gets ----------------------------------------
Eigen::Matrix4f Box::get_model() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    translation(2, 3) = x.z();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = width / 2.f;
    scale(1, 1) = height / 2.f;
    scale(2, 2) = depth / 2.f;
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

std::shared_ptr<AABB> &Box::get_aabb() {
    update();
    Box::update_AABB();
    return Box::aabb;
}

std::shared_ptr<AABB> &Ball::get_aabb() {
    update();
    Ball::update_AABB();
    return Ball::aabb;
}