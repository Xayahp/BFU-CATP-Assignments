#include "Renderer2D.h"

using namespace W2D;

Renderer2D::Renderer2D() {
    init_shader();
}

Renderer2D::~Renderer2D() {
    delete shader_points;
    delete shader_lines;
    delete shader_triangles;
}

void Renderer2D::draw(std::vector<std::unique_ptr<BasicShape2D> > &objects) {
    render(objects);
    if (!positions_points.empty())
        draw_points();
    if (!positions_lines.empty())
        draw_lines();
    if (!positions_triangles.empty())
        draw_triangles();
}

void Renderer2D::render(std::vector<std::unique_ptr<BasicShape2D> > &objects) {
    clear();
    for (auto &&shape : objects) {
        render(*shape);
    }
}

void Renderer2D::render(BasicShape2D &shape) {
    std::vector<float> pos = shape.get_positions();
    switch (shape.draw_mode) {
        case POINTS:
            positions_points.insert(positions_points.end(), pos.begin(), pos.end());
            for (int i = 0; i < int(pos.size() / 2); ++i) {
                points_colors.emplace_back(shape.color[0]);
                points_colors.emplace_back(shape.color[1]);
                points_colors.emplace_back(shape.color[2]);
                points_colors.emplace_back(shape.color[3]);
            }
            for (int i = 0; i < int(pos.size() / 2); ++i) {
                points_size.emplace_back(5.f);
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

void Renderer2D::init_shader() {
    std::string PROJECT_DIRECTORY = PROJECT_SOURCE_DIR;
    std::string vertex_points_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_points_shader.vert";
    std::string fragment_points_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_points_shader.frag";
    std::string vertex_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_lines_shader.vert";
    std::string fragment_lines_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_lines_shader.frag";
    std::string vertex_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_triangles_shader.vert";
    std::string fragment_triangles_shader_path = PROJECT_DIRECTORY + "/Shaders/2D/" + "default_triangles_shader.frag";
    this->shader_points = new Shader(vertex_points_shader_path, fragment_points_shader_path);
    this->shader_lines = new Shader(vertex_lines_shader_path, fragment_lines_shader_path);
    this->shader_triangles = new Shader(vertex_triangles_shader_path, fragment_triangles_shader_path);
    glGenVertexArrays(1, &vao_points);
    glGenBuffers(3, vbo_points);
    glGenVertexArrays(1, &vao_lines);
    glGenBuffers(2, vbo_lines);
    glGenVertexArrays(1, &vao_triangles);
    glGenBuffers(2, vbo_triangles);
}

void Renderer2D::init_points() {
    glBindVertexArray(vao_points);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_points[0]);
    glBufferData(GL_ARRAY_BUFFER, positions_points.size() * sizeof(float), &positions_points[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_points[1]);
    glBufferData(GL_ARRAY_BUFFER, points_colors.size() * sizeof(float), &points_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_points[2]);
    glBufferData(GL_ARRAY_BUFFER, points_size.size() * sizeof(float), &points_size[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer2D::init_lines() {
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

void Renderer2D::init_triangles() {
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

void Renderer2D::draw_points() {
    init_points();
    shader_points->use();
    glBindVertexArray(vao_points);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, int(positions_points.size() / 2));
    glDisable(GL_PROGRAM_POINT_SIZE);
    glBindVertexArray(0);
}

void Renderer2D::draw_lines() {
    init_lines();
    shader_lines->use();
    glBindVertexArray(vao_lines);
    glDrawArrays(GL_LINES, 0, int(positions_lines.size() / 2));
    glBindVertexArray(0);
}

void Renderer2D::draw_triangles() {
    init_triangles();
    shader_triangles->use();
    glBindVertexArray(vao_triangles);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, int(positions_triangles.size() / 2));
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    glBindVertexArray(0);
}

void Renderer2D::clear() {
    positions_points.clear();
    positions_lines.clear();
    positions_triangles.clear();
    points_colors.clear();
    lines_colors.clear();
    triangles_colors.clear();
    points_size.clear();
}
