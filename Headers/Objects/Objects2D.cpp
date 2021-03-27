#include "Objects2D.h"

// ---------------------------------------- constructors ----------------------------------------
Wall::Wall(float width) : Line(), width(width) {}

Brick::Brick(float width, float height) : Rectangle(), width(width), height(height) {}

Pizza::Pizza(float radius) : Circle(), radius(radius) {}


// ---------------------------------------- updates ----------------------------------------
void Wall::update() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = width / 2.f;
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Line::model = translation * rotation * scale;
    Line::set_model(Line::model);
}

void Brick::update() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = width / 2.f;
    scale(1, 1) = height / 2.f;
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Brick::model = translation * rotation * scale;
    Brick::set_model(Brick::model);
}

void Pizza::update() {
    Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
    translation(0, 3) = x.x();
    translation(1, 3) = x.y();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    scale(0, 0) = radius;
    scale(1, 1) = radius;
    Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
    Circle::model = translation * rotation * scale;
    Circle::set_model(Circle::model);
}


// ---------------------------------------- draws ----------------------------------------
void Wall::draw() {
    update();
    Line::draw();
}

void Brick::draw() {
    update();
    Rectangle::draw();
}

void Pizza::draw() {
    update();
    Circle::draw();
}


// ---------------------------------------- sets ----------------------------------------
void Wall::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Line::set_model(model);
    Line::set_view(Eigen::Matrix4f::Identity());
    Line::set_projection(Eigen::Matrix4f::Identity());
}

void Brick::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Rectangle::set_model(model);
    Rectangle::set_view(Eigen::Matrix4f::Identity());
    Rectangle::set_projection(Eigen::Matrix4f::Identity());
}

void Pizza::set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) {
    Circle::set_model(model);
    Circle::set_view(Eigen::Matrix4f::Identity());
    Circle::set_projection(Eigen::Matrix4f::Identity());
}

void Wall::set_ortho(const Eigen::Matrix4f &ortho) {
    Wall::ortho = ortho;
}

void Brick::set_ortho(const Eigen::Matrix4f &ortho) {
    Brick::ortho = ortho;
}

void Pizza::set_ortho(const Eigen::Matrix4f &ortho) {
    Circle::ortho = ortho;
}
