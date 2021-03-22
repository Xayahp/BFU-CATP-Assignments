/**
 * @authored by Xayah, BFU
 */
#ifndef ASSIGNMENT2_SCENE_H
#define ASSIGNMENT2_SCENE_H

#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "Eigen/Eigen"

#include "camera.h"
#include <vector>

struct Points {
    std::vector<Eigen::Vector2f> positions;
    std::vector<Eigen::Vector4f> colors;
    std::vector<float> sizes;
};

struct Lines {
    std::vector<Eigen::Vector2f> positions;
};

struct Triangles {
    std::vector<Eigen::Vector2f> positions;
};

class scene {
public:
    scene();

    ~scene() = default;

    void initialize();

    void flush();

    void add_point(const Eigen::Vector2f &position, float size, const Eigen::Vector3f &color);
    void add_point(const Eigen::Vector2f &position, float size, const Eigen::Vector4f &color);
    void draw_points();

private:
    void init_points();
//    void init_lines();
//    void init_triangles();
    Points points;
//    std::vector<Line> lines;
//    std::vector<Triangle> triangles;

private:
    unsigned int programID_points;
    unsigned int vaoID_points;
    unsigned int vboID_points[3];
    int previous_points_num;

    unsigned int programID_lines;
    unsigned int vaoID_lines;
    unsigned int vboID_lines;

    unsigned int programID_triangles;
    unsigned int vaoID_triangles;
    unsigned int vboID_triangles;

    unsigned int projection_uniform;

    const int MAX_POINTS_LIMIT = 512;
};

#endif //ASSIGNMENT2_SCENE_H
