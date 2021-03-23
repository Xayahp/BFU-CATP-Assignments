/**
 * @author Xayah, BFU
 * @date 3.23, 2021
 */
#ifndef ASSIGNMENT0_SCENE_H
#define ASSIGNMENT0_SCENE_H

#include "BasicShapes.h"
#include "Shader.h"

#include <vector>
#include <string>

class Scene {

public:
    Scene();

    ~Scene();

    void eat(BasicShape2D &shape, DRAW_MODE mode);

    void draw();

private:
    void init_shader();

    void draw_points();

    void draw_lines();

    void draw_triangles();

    void init_lines();

    void init_triangles();

private:
    std::vector<float> positions_points;
    std::vector<float> points_colors;
    unsigned int vao_points;
    unsigned int vbo_points;

    std::vector<float> positions_lines;
    std::vector<float> lines_colors;
    unsigned int vao_lines;
    unsigned int vbo_lines[2];

    std::vector<float> positions_triangles;
    std::vector<float> triangles_colors;
    unsigned int vao_triangles;
    unsigned int vbo_triangles[2];

    Shader *shader_points;
    Shader *shader_lines;
    Shader *shader_triangles;

    int MAX_POINTS_LIMIT = 512;
};


#endif //ASSIGNMENT0_SCENE_H
