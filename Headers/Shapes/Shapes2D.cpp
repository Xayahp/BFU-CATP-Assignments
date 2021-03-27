#include "Shapes2D.h"


Line::Line() : BasicShape("line", SHAPE_2D) {}

Rectangle::Rectangle() : BasicShape("rectangle", SHAPE_2D) {}

void Rectangle::as_triangle() {
    std::vector<unsigned int> indices;
    indices = {0, 1, 2, 0, 3, 2};
    meshes[0].indices = indices;
    set_draw_mode(POLYGON);
    meshes[0].update_mesh();
}

Circle::Circle() : BasicShape("circle", SHAPE_2D) {
    naive_circle(segments);
}

void Circle::naive_circle(int seg) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float incremental = 2.0f * 3.1415926f / float(seg);

    for (int i = 0; i < seg; ++i) {
        Vertex vertex;
        unsigned int index;
        vertex.position = Eigen::Vector3f(cos(float(i) * incremental), sin(float(i) * incremental), 0.0);
        index = unsigned(i);
        vertices.emplace_back(vertex);
        indices.emplace_back(index);
        indices.emplace_back((index + 1) % seg);
    }

    this->meshes[0].vertices = vertices;
    this->meshes[0].indices = indices;
    this->meshes[0].update_mesh();
}

void Circle::as_triangle() {
    Vertex center;
    center.position = Eigen::Vector3f(0.f, 0.f, 0.f);
    size_t size = meshes[0].vertices.size();
    meshes[0].vertices.push_back(center);
    std::vector<unsigned int> indices;
    for (int i = 0; i < segments; ++i) {
        indices.push_back(unsigned(i));
        indices.push_back(unsigned((i + 1) % segments));
        indices.push_back(unsigned(size)); // center
    }
    meshes[0].indices = indices;
    set_draw_mode(POLYGON);
    meshes[0].update_mesh();
}