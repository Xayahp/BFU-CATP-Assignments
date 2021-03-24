/**
 * @author Xayah, BFU
 * @date 3.24, 2021
 */
#ifndef ASSIGNMENT_FRAMEWORK_BASICSHAPES2D_H
#define ASSIGNMENT_FRAMEWORK_BASICSHAPES2D_H

#include "Eigen/Eigen"

#include <iostream>
#include <utility>
#include <vector>
#include <utility>

namespace W2D {


    enum DRAW_MODE {
        POINTS, LINES, TRIANGLES
    };

    struct AABB {
        AABB(float xMin, float xMax, float yMin, float yMax);

        float x_min;
        float x_max;
        float y_min;
        float y_max;
    };

// ------------------------------ Basic Shape 2D ------------------------------
    class BasicShape2D {
    public:// constructor(s)
        explicit BasicShape2D(Eigen::Vector2f center);

        virtual ~BasicShape2D();

    public:// virtual methods
        virtual void generate_data() = 0;

        virtual std::vector<float> get_positions() = 0;

        virtual AABB getAABB() = 0;

        virtual void iterate(float time_step);

        virtual void do_collision(const std::vector<std::unique_ptr<BasicShape2D> > &world_data) = 0;

    public:// sets
        BasicShape2D &set_color(Eigen::Vector3f &RGB);

        BasicShape2D &set_color(Eigen::Vector4f &RGBA);

        BasicShape2D &set_color(int HEX);

        BasicShape2D &set_draw_mode(DRAW_MODE mode);

        BasicShape2D &fix();

    public:// interface fields
        std::vector<Eigen::Vector2f> positions;
        Eigen::Vector4f color;
        DRAW_MODE draw_mode;
        float rotation_angle;
        bool fixed;
    public:
        // kinematics
        Eigen::Vector2f center;
        Eigen::Vector2f velocity;
        Eigen::Vector2f force;
        float mass;
    };


// ------------------------------ Line ------------------------------
    class Line : public BasicShape2D {

    public:// constructor(s)
        Line(Eigen::Vector2f start, Eigen::Vector2f end);

        void generate_data() override;

        std::vector<float> get_positions() override;

        AABB getAABB() override;

        void do_collision(const std::vector<std::unique_ptr<BasicShape2D>> &world_data) override;

    private:
        Eigen::Vector2f start;
        Eigen::Vector2f end;
    };


// ------------------------------ Rectangle ------------------------------
    class Rectangle : public BasicShape2D {

    public:// constructor(s)
        Rectangle(Eigen::Vector2f center, float harf_width, float harf_height);

    public:// override(s)
        void generate_data() override;

        std::vector<float> get_positions() override;

        AABB getAABB() override;

        void do_collision(const std::vector<std::unique_ptr<BasicShape2D>> &world_data) override;

    private:// private fields
        float harf_width;
        float harf_height;
    };
}

#endif //ASSIGNMENT0_BASICSHAPES_H
