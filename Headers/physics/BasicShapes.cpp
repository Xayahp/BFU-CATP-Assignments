#include "BasicShapes.h"

// ------------------------------ Basic Shape 2D ------------------------------

BasicShape2D::BasicShape2D(Eigen::Vector2f center) : center(std::move(center)), draw_mode(TRIANGLES),
                                                     rotation_angle(0) {}

void BasicShape2D::set_color(Eigen::Vector3f &RGB) {
    color = Eigen::Vector4f(RGB.x(), RGB.y(), RGB.z(), 1.f);
}

void BasicShape2D::set_color(Eigen::Vector4f &RGBA) {
    color = RGBA;
}

void BasicShape2D::set_draw_mode(DRAW_MODE mode) {
    draw_mode = mode;
    generate_data();
}

void BasicShape2D::set_color(int HEX) {
    color[0] = ((HEX >> 16) & 0xFF) / 255.0;
    color[1] = ((HEX >> 8) & 0xFF) / 255.0;
    color[2] = ((HEX) & 0xFF) / 255.0;
}


// ------------------------------ Rectangle ------------------------------

Rectangle::Rectangle(Eigen::Vector2f center, float harf_width, float harf_height) : BasicShape2D(std::move(center)),
                                                                                    harf_width(harf_width),
                                                                                    harf_height(harf_height) {
    if (!(harf_width > 0 || harf_height > 0))
        std::clog << "RECTANGLE::INVALID::ATTRIBUTES" << std::endl;
}

void Rectangle::generate_data() {
    Eigen::Vector2f top_left(center.x() - harf_width, center.y() + harf_height);
    Eigen::Vector2f top_right(center.x() + harf_width, center.y() + harf_height);
    Eigen::Vector2f bot_left(center.x() - harf_width, center.y() - harf_height);
    Eigen::Vector2f bot_right(center.x() + harf_width, center.y() - harf_height);
    switch (draw_mode) {
        case POINTS:
            positions.
                    emplace_back(top_left);
            positions.
                    emplace_back(top_right);
            positions.
                    emplace_back(bot_left);
            positions.
                    emplace_back(bot_right);
            break;
        case LINES:
            positions.emplace_back(top_left);
            positions.
                    emplace_back(top_right);
            positions.
                    emplace_back(top_right);
            positions.
                    emplace_back(bot_right);
            positions.
                    emplace_back(bot_right);
            positions.
                    emplace_back(bot_left);
            positions.
                    emplace_back(bot_left);
            positions.
                    emplace_back(top_left);
            break;
        case TRIANGLES:
            positions.
                    emplace_back(top_left);
            positions.
                    emplace_back(top_right);
            positions.
                    emplace_back(bot_right);
            positions.
                    emplace_back(bot_right);
            positions.
                    emplace_back(bot_left);
            positions.
                    emplace_back(top_left);
            break;
        default:
            std::cerr << "RECTANGLE::EXCEPTION::NOT_SUPPORTED_MODE" <<
                      std::endl;
            break;
    }
}

std::vector<float> Rectangle::get_positions() {
    std::vector<float> res;
    for (auto &p : positions) {
        res.emplace_back(p.x());
        res.emplace_back(p.y());
    }
    return res;
}