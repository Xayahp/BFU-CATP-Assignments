#ifndef ASSIGNMENT0_BASICSHAPES_H
#define ASSIGNMENT0_BASICSHAPES_H

#include "Eigen/Eigen"

#include <iostream>
#include <vector>
#include <utility>




enum DRAW_MODE {
    POINTS, LINES, WIREFRAME, TRIANGLES
};

class BasicShape2D {
public:
    BasicShape2D() {
        color = Eigen::Vector4f(77.f/256.f, 67.f/256.f, 152.f/256.f, 1.f);
    }
    void set_color(Eigen::Vector3f &RGB) {
        color = Eigen::Vector4f(RGB.x(), RGB.y(), RGB.z(), 1.f);
    };
    void set_color(Eigen::Vector4f &RGBA) {
        color = RGBA;
    }
    void set_color(int HEX) {
        color[0] = ((HEX >> 16) & 0xFF) / 255.0;
        color[1] = ((HEX >> 8) & 0xFF) / 255.0;
        color[2] = ((HEX) & 0xFF) / 255.0;
    }
    virtual std::vector<float> generate_data(DRAW_MODE mode) = 0;
    std::vector<Eigen::Vector2f> positions;
    Eigen::Vector4f color;
};


class Rectangle : public BasicShape2D {

public:
    Rectangle(Eigen::Vector2f center, float harf_width, float harf_height) : BasicShape2D(), center(std::move(center)), harf_width(harf_width), harf_height(harf_height) {
        if ( !( harf_width > 0 || harf_height > 0) )
            std::clog << "RECTANGLE::INVALID::ATTRIBUTES" << std::endl;
    }

    std::vector<float> generate_data(DRAW_MODE mode) override {
        Eigen::Vector2f top_left(center.x() - harf_width, center.y() + harf_height);
        Eigen::Vector2f top_right(center.x() + harf_width, center.y() + harf_height);
        Eigen::Vector2f bot_left(center.x() - harf_width, center.y() - harf_height);
        Eigen::Vector2f bot_right(center.x() + harf_width, center.y() - harf_height);
        switch (mode) {
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
                std::cerr << "RECTANGLE::EXCEPTION::NOT_SUPPORTED_MODE" << std::endl;
                break;
        }
        std::vector<float> res;
        for (auto &p : positions) {
            res.emplace_back(p.x());
            res.emplace_back(p.y());
        }
        return res;
    }
private:
    Eigen::Vector2f center;
    float harf_width;
    float harf_height;
};





#endif //ASSIGNMENT0_BASICSHAPES_H
