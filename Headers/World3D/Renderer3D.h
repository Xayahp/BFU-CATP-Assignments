/**
 * @author Xayah, BFU
 * @date 3.24, 2021
 */
#ifndef ASSIGNMENT_FRAMEWORK_RENDERER3D_H
#define ASSIGNMENT_FRAMEWORK_RENDERER3D_H

#include "BasicShapes3D.h"
#include "Shader.h"


#include <vector>
#include <string>

namespace W3D {


    class Renderer3D {

    public:
        Renderer3D();

        ~Renderer3D();

        void draw(std::vector<std::unique_ptr<BasicShape3D> > &objects);

    private:

        void render(std::vector<std::unique_ptr<BasicShape3D> > &objects);

        void render(BasicShape3D &shape);

        void init_shader();

        void init_points();

        void init_lines();

        void init_triangles();

        void draw_points();

        void draw_lines();

        void draw_triangles();

        void clear();

    private:
        std::vector<float> positions_points;
        std::vector<float> points_colors;
        std::vector<float> points_size;
        unsigned int vao_points;
        unsigned int vbo_points[3];

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
}



#endif //ASSIGNMENTFRAMEWORK_RENDERER3D_H
