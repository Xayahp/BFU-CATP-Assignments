/**
 * @author Xayah, BFU
 * @date 3.24, 2021
 */
#ifndef ASSIGNMENT_FRAMEWORK_BASICSHAPES3D_H
#define ASSIGNMENT_FRAMEWORK_BASICSHAPES3D_H

#include "Eigen/Eigen"

#include <iostream>
#include <utility>
#include <vector>
#include <utility>

namespace W3D {

    enum DRAW_MODE {
        POINTS, LINES, TRIANGLES
    };

    struct AABB {

        AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

        float x_min;
        float x_max;
        float y_min;
        float y_max;
        float z_min;
        float z_max;
    };

// ------------------------------ Basic Shape 3D ------------------------------
    class BasicShape3D {
    public:// constructor(s)
        explicit BasicShape3D(Eigen::Vector3f center);

        virtual ~BasicShape3D();

    public:// virtual methods
        virtual void generate_data() = 0;

        virtual std::vector<float> get_positions() = 0;

        virtual AABB getAABB() = 0;

        virtual void iterate(float time_step);

        virtual void do_collision(const std::vector<std::unique_ptr<BasicShape3D> > &world_data) = 0;

    public:// sets
        BasicShape3D &set_color(Eigen::Vector3f &RGB);

        BasicShape3D &set_color(Eigen::Vector4f &RGBA);

        BasicShape3D &set_color(int HEX);

        BasicShape3D &set_draw_mode(DRAW_MODE mode);

        BasicShape3D &fix();

    public:// interface fields
        std::vector<Eigen::Vector3f> positions;
        Eigen::Vector4f color;
        DRAW_MODE draw_mode;
        float rotation_angle;
        bool fixed;
    public:
        // kinematics
        Eigen::Vector3f center;
        Eigen::Vector3f velocity;
        Eigen::Vector3f force;
        float mass;
    };


// ------------------------------ Basic Shape 3D ------------------------------
    class Cuboid : public BasicShape3D {
    public:
        Cuboid(const Eigen::Vector3f &center, float harfLengthX, float harfLengthY, float harfLengthZ);

        void generate_data() override;

        std::vector<float> get_positions() override;

        AABB getAABB() override;

        void iterate(float time_step) override;

        void do_collision(const std::vector<std::unique_ptr<BasicShape3D>> &world_data) override;

    private:
        float harf_length_x;
        float harf_length_y;
        float harf_length_z;
    };
}

#endif //ASSIGNMENTFRAMEWORK_BASICSHAPES3D_H
