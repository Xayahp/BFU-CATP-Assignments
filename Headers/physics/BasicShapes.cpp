#include "BasicShapes.h"


// ------------------------------ Basic Shape 2D ------------------------------

BasicShape2D::BasicShape2D(Eigen::Vector2f center) : center(std::move(center)), rotation_angle(0), draw_mode(LINES),
                                                     fixed(false), mass(1.f), velocity(Eigen::Vector2f(0.f, 0.f)),
                                                     force(Eigen::Vector2f(0.f, 0.f)) {}

BasicShape2D::~BasicShape2D() {
    positions.clear();
}

BasicShape2D &BasicShape2D::set_color(Eigen::Vector3f &RGB) {
    color = Eigen::Vector4f(RGB.x(), RGB.y(), RGB.z(), 1.f);
    return *this;
}

BasicShape2D &BasicShape2D::set_color(Eigen::Vector4f &RGBA) {
    color = RGBA;
    return *this;
}

BasicShape2D &BasicShape2D::set_draw_mode(DRAW_MODE mode) {
    draw_mode = mode;
    return *this;
}

BasicShape2D &BasicShape2D::set_color(int HEX) {
    color[0] = ((HEX >> 16) & 0xFF) / 255.0;
    color[1] = ((HEX >> 8) & 0xFF) / 255.0;
    color[2] = ((HEX) & 0xFF) / 255.0;
    return *this;
}

BasicShape2D &BasicShape2D::fix() {
    fixed = true;
    return *this;
}

void BasicShape2D::iterate(float time_step) {
    Eigen::Vector2f acceleration = force / mass;
    velocity += acceleration * time_step;
    center += velocity * time_step;
    force = Eigen::Vector2f::Zero();
}


// ------------------------------ Line ------------------------------

Line::Line(Eigen::Vector2f start, Eigen::Vector2f end) : BasicShape2D((start + end) / 2.f),
                                                         start(std::move(start)), end(std::move(end)) {
    draw_mode = LINES;
}

void Line::generate_data() {
    switch (draw_mode) {
        case POINTS:
            for (int i = 0; i < 50; ++i) {
                positions.emplace_back((1 - i / 49.f) * start + (i / 49.f) * end);
            }
            break;
        case LINES:
            positions.emplace_back(start);
            positions.emplace_back(end);
            break;
        case TRIANGLES:
        default:
            std::cerr << "LINE::EXCEPTION::NOT_SUPPORTED_MODE" << std::endl;
            break;
    }
}

std::vector<float> Line::get_positions() {
    positions.clear();
    generate_data();
    std::vector<float> res;
    for (auto &p : positions) {
        res.emplace_back(p.x());
        res.emplace_back(p.y());
    }
    return res;
}

void Line::do_collision(const std::vector<std::unique_ptr<BasicShape2D>> &world_data) {
    AABB thisAABB = getAABB();
    for (auto &obj : world_data) {
        AABB thatAABB = obj->getAABB();
        // TODO
    }
}

AABB Line::getAABB() {
    return AABB(std::min(start.x(), end.x()), std::max(start.x(), end.x()), std::min(start.y(), end.y()), std::max(start.y(), end.y()));
}


// ------------------------------ Rectangle ------------------------------

Rectangle::Rectangle(Eigen::Vector2f center, float harf_width, float harf_height) : BasicShape2D(std::move(center)),
                                                                                    harf_width(harf_width),
                                                                                    harf_height(harf_height) {
    if (!(harf_width > 0 || harf_height > 0))
        std::clog << "RECTANGLE::INVALID::ATTRIBUTES" << std::endl;
    draw_mode = TRIANGLES;
}

void Rectangle::generate_data() {
    Eigen::Vector2f top_left(center.x() - harf_width, center.y() + harf_height);
    Eigen::Vector2f top_right(center.x() + harf_width, center.y() + harf_height);
    Eigen::Vector2f bot_left(center.x() - harf_width, center.y() - harf_height);
    Eigen::Vector2f bot_right(center.x() + harf_width, center.y() - harf_height);
    switch (draw_mode) {
        case POINTS:
            positions.emplace_back(top_left);
            positions.emplace_back(top_right);
            positions.emplace_back(bot_left);
            positions.emplace_back(bot_right);
            break;
        case LINES:
            positions.emplace_back(top_left);
            positions.emplace_back(top_right);
            positions.emplace_back(top_right);
            positions.emplace_back(bot_right);
            positions.emplace_back(bot_right);
            positions.emplace_back(bot_left);
            positions.emplace_back(bot_left);
            positions.emplace_back(top_left);
            break;
        case TRIANGLES:
            positions.emplace_back(top_left);
            positions.emplace_back(top_right);
            positions.emplace_back(bot_right);
            positions.emplace_back(bot_right);
            positions.emplace_back(bot_left);
            positions.emplace_back(top_left);
            break;
        default:
            std::cerr << "RECTANGLE::EXCEPTION::NOT_SUPPORTED_MODE" <<
                      std::endl;
            break;
    }
}

std::vector<float> Rectangle::get_positions() {
    positions.clear();
    generate_data();
    std::vector<float> res;
    for (auto &p : positions) {
        res.emplace_back(p.x());
        res.emplace_back(p.y());
    }
    return res;
}

AABB Rectangle::getAABB() {
    auto a = sin(20);
    return AABB(center.x()-harf_width, center.x()+harf_width, center.y()-harf_height, center.y()+harf_height);
}

void Rectangle::do_collision(const std::vector<std::unique_ptr<BasicShape2D>> &world_data) {

}
