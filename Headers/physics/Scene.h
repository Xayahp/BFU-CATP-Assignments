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

    Scene() {
        init();
    }

    ~Scene() {
        delete shader_points;
        delete shader_lines;
        delete shader_triangles;
    }

    void eat(BasicShape2D &shape, DRAW_MODE mode) {
        std::vector<float> pos = shape.generate_data(mode);
        switch (mode) {
            case POINTS:
                positions_points.insert(positions_points.end(), pos.begin(), pos.end());
                break;
            case LINES:
                positions_lines.insert(positions_lines.end(), pos.begin(), pos.end());
                break;
            case TRIANGLES:
                positions_triangles.insert(positions_triangles.end(), pos.begin(), pos.end());
                break;
            default:
                std::cerr << "DRAWER::EXCEPTION::I_CAN_NOT_EAT_THIS" << std::endl;
                break;
        }
    }

    void draw() {
        if (!positions_points.empty())
            draw_points();
        if (!positions_lines.empty())
            draw_lines();
        if (!positions_triangles.empty())
            draw_triangles();
    }
private:
    void init() {
        std::string PROJECT_DIRECTORY = PROJECT_SOURCE_DIR;
        std::string vertex_points_shader_path = PROJECT_DIRECTORY + "/Shaders/default_points_shader.vert";
        std::string fragment_points_shader_path = PROJECT_DIRECTORY + "/Shaders/default_points_shader.frag";
        std::string vertex_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/default_lines_shader.vert";
        std::string fragment_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/default_lines_shader.frag";
        std::string vertex_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/default_triangles_shader.vert";
        std::string fragment_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/default_triangles_shader.frag";
        this->shader_points = new Shader(vertex_points_shader_path, fragment_points_shader_path);
        this->shader_lines = new Shader(vertex_lines_shader_path, fragment_lines_shader_path);
        this->shader_triangles = new Shader(vertex_triangles_shader_path, fragment_triangles_shader_path);
    }
    void draw_points() {

    }
    void draw_lines() {
        init_lines();
        shader_lines->use();
        glBindVertexArray(vao_lines);
        glDrawArrays(GL_LINES, 0, int(positions_lines.size() / 2));
        glBindVertexArray(0);
    }
    void draw_triangles() {
        init_triangles();
        shader_triangles->use();
        glBindVertexArray(vao_triangles);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, int(positions_triangles.size() / 2));
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        glBindVertexArray(0);
    }
    void init_lines() {
        glGenVertexArrays(1, &vao_lines);
        glGenBuffers(1, &vbo_lines);
        glBindVertexArray(vao_lines);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_lines);
        glBufferData(GL_ARRAY_BUFFER, positions_lines.size() * sizeof(float), &positions_lines[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    void init_triangles() {
        glGenVertexArrays(1, &vao_triangles);
        glGenBuffers(1, &vbo_triangles);
        glBindVertexArray(vao_triangles);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_triangles);
        glBufferData(GL_ARRAY_BUFFER, positions_triangles.size() * sizeof(float), &positions_triangles[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    std::vector<float> positions_points;
    unsigned int vao_points;
    unsigned int vbo_points;

    std::vector<float> positions_lines;
    unsigned int vao_lines;
    unsigned int vbo_lines;

    std::vector<float> positions_triangles;
    unsigned int vao_triangles;
    unsigned int vbo_triangles;

    Shader* shader_points;
    Shader* shader_lines;
    Shader* shader_triangles;

    int MAX_POINTS_LIMIT = 512;
};


#endif //ASSIGNMENT0_SCENE_H
