#include "Scene.h"

Scene::Scene() {
    init_shader();
}

Scene::~Scene() {
    delete shader_points;
    delete shader_lines;
    delete shader_triangles;
}

void Scene::eat(BasicShape2D &shape, DRAW_MODE mode) {
    shape.set_draw_mode(mode);
    std::vector<float> pos = shape.get_positions();
    switch (mode) {
        case POINTS:
            positions_points.insert(positions_points.end(), pos.begin(), pos.end());
            for (int i = 0; i < int(pos.size() / 2); ++i) {
                points_colors.emplace_back(shape.color[0]);
                points_colors.emplace_back(shape.color[1]);
                points_colors.emplace_back(shape.color[2]);
                points_colors.emplace_back(shape.color[3]);
            }
            break;
        case LINES:
            positions_lines.insert(positions_lines.end(), pos.begin(), pos.end());
            for (int i = 0; i < int(pos.size() / 2); ++i) {
                lines_colors.emplace_back(shape.color[0]);
                lines_colors.emplace_back(shape.color[1]);
                lines_colors.emplace_back(shape.color[2]);
                lines_colors.emplace_back(shape.color[3]);
            }
            break;
        case TRIANGLES:
            positions_triangles.insert(positions_triangles.end(), pos.begin(), pos.end());
            for (int i = 0; i < int(pos.size() / 2); ++i) {
                triangles_colors.emplace_back(shape.color[0]);
                triangles_colors.emplace_back(shape.color[1]);
                triangles_colors.emplace_back(shape.color[2]);
                triangles_colors.emplace_back(shape.color[3]);
            }
            break;
        default:
            std::cerr << "DRAWER::EXCEPTION::I_CAN_NOT_EAT_THIS" << std::endl;
            break;
    }
}

void Scene::draw() {
    if (!positions_points.empty())
        draw_points();
    if (!positions_lines.empty())
        draw_lines();
    if (!positions_triangles.empty())
        draw_triangles();
}

void Scene::init_shader() {
    std::string PROJECT_DIRECTORY = PROJECT_SOURCE_DIR;
    std::string vertex_points_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_points_shader.vert";
    std::string fragment_points_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_points_shader.frag";
    std::string vertex_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_lines_shader.vert";
    std::string fragment_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_lines_shader.frag";
    std::string vertex_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_triangles_shader.vert";
    std::string fragment_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/" + "default_triangles_shader.frag";
    this->shader_points = new Shader(vertex_points_shader_path, fragment_points_shader_path);
    this->shader_lines = new Shader(vertex_lines_shader_path, fragment_lines_shader_path);
    this->shader_triangles = new Shader(vertex_triangles_shader_path, fragment_triangles_shader_path);
}

void Scene::init_lines() {
    glGenVertexArrays(1, &vao_lines);
    glGenBuffers(2, vbo_lines);

    glBindVertexArray(vao_lines);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_lines[0]);
    glBufferData(GL_ARRAY_BUFFER, positions_lines.size() * sizeof(float), &positions_lines[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_lines[1]);
    glBufferData(GL_ARRAY_BUFFER, lines_colors.size() * sizeof(float), &lines_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Scene::init_triangles() {
    glGenVertexArrays(1, &vao_triangles);
    glGenBuffers(2, vbo_triangles);

    glBindVertexArray(vao_triangles);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangles[0]);
    glBufferData(GL_ARRAY_BUFFER, positions_triangles.size() * sizeof(float), &positions_triangles[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangles[1]);
    glBufferData(GL_ARRAY_BUFFER, triangles_colors.size() * sizeof(float), &triangles_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Scene::draw_points() {

}

void Scene::draw_lines() {
    init_lines();
    shader_lines->use();
    glBindVertexArray(vao_lines);
    glDrawArrays(GL_LINES, 0, int(positions_lines.size() / 2));
    glBindVertexArray(0);
}

void Scene::draw_triangles() {
    init_triangles();
    shader_triangles->use();
    glBindVertexArray(vao_triangles);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, int(positions_triangles.size() / 2));
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    glBindVertexArray(0);
}
