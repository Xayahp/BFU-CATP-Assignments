#include "BasicShapes.h"

BasicShape::BasicShape(const std::string &name, SHAPE_TYPE type) : name(name), type(type) {
    /* load buildin model by name, and load corresponding default aabb shader */
    if (type == SHAPE_3D) {
        load_model(std::string(PROJECT_DATA_DIR) + "/3D/" + name + ".obj");
        set_draw_mode(POLYGON);
        load_aabb_shader("AABB_default.vert", "AABB_default.frag");
        init_aabb(AABB_3D);
    } else {
        load_model(std::string(PROJECT_DATA_DIR) + "/2D/" + name + ".txt", false);
        set_draw_mode(LINE);
        load_aabb_shader("default_shader_2D.vert", "default_shader_2D.frag");
        init_aabb(AABB_2D);
    }
    /* initialize fields */
    this->ortho = Eigen::Matrix4f::Identity();
    this->model = Eigen::Matrix4f::Identity();
    this->view = Eigen::Matrix4f::Identity();
    this->projection = Eigen::Matrix4f::Identity();
    set_color(0x5a4498); // set default color
}

void BasicShape::load_shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name,
                             const std::string &geometry_shader_name) {
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + vertex_shader_name;
    std::string f_path = SHADER_DIRECTORY + "/" + fragment_shader_name;
    std::string g_path;
    if (!geometry_shader_name.empty())
        g_path = SHADER_DIRECTORY + "/" + geometry_shader_name;
    else
        g_path = "";
    this->shader = std::make_unique<Shader>(v_path, f_path, g_path);
    set_model(Eigen::Matrix4f::Identity());
    set_view(Eigen::Matrix4f::Identity());
    set_projection(Eigen::Matrix4f::Identity());
}

void BasicShape::load_texture(const std::string &texture_name, TEXTURE_TYPE texture_type) {
    std::string TEXTURE_DIRECTORY = PROJECT_TEXTURE_DIR;
    Texture tex;
    tex.id = Model::load_texture(texture_name.c_str(), TEXTURE_DIRECTORY);
    switch (texture_type) {
        case TEXTURE_DIFFUSE:
            tex.type = "texture_diffuse";
            break;
        case TEXTURE_SPECULAR:
            tex.type = "texture_specular";
            break;
        case TEXTURE_NORMAL:
            tex.type = "texture_normal";
            break;
        case TEXTURE_HEIGHT:
            tex.type = "texture_height";
            break;
    }
    tex.path = TEXTURE_DIRECTORY + texture_name;
    this->textures_loaded.push_back(tex);
    this->meshes[0].textures.push_back(tex);
}

void BasicShape::set_color(const Eigen::Vector3f &RGB) {
    this->color = Eigen::Vector4f(RGB.x() / 255.f, RGB.y() / 255.f, RGB.z() / 255.f, 1.f);
}

void BasicShape::set_color(const Eigen::Vector4f &RGBA) {
    this->color = Eigen::Vector4f(RGBA.x() / 255.f, RGBA.y() / 255.f, RGBA.z() / 255.f, RGBA.z());
}

void BasicShape::set_color(const int HEX, float opacity) {
    this->color[0] = static_cast<float>(((HEX >> 16) & 0xFF)) / 255.f;
    this->color[1] = static_cast<float>(((HEX >> 8) & 0xFF)) / 255.f;
    this->color[2] = static_cast<float>(((HEX) & 0xFF)) / 255.f;
    this->color[3] = opacity;
}

void BasicShape::set_projection(const Eigen::Matrix4f &_projection) {
    this->projection = _projection;
}

void BasicShape::set_view(const Eigen::Matrix4f &_view) {
    this->view = _view;
}

void BasicShape::set_model(const Eigen::Matrix4f &_model) {
    this->model = _model;
}

void BasicShape::draw() {
    this->shader->use();
    this->shader->setMat4("projection", projection);
    this->shader->setMat4("view", view);
    this->shader->setMat4("model", ortho * model);
    this->shader->setVec4("color", color);
    Model::draw(*this->shader);
    update_AABB();
//    DRAW_AABB = true;
    if (DRAW_AABB) {
        this->shader_aabb->use();
        this->shader_aabb->setMat4("projection", projection);
        this->shader_aabb->setMat4("view", view);
        this->shader_aabb->setMat4("model", ortho * Eigen::Matrix4f::Identity());
        draw_AABB();
    }
}

void BasicShape::init_aabb(AABB_TYPE aabb_type) {
    float x_min = 1.f, x_max = -1.f, y_min = 1.f, y_max = -1.f, z_min = 1.f, z_max = -1.f;
    aabb = std::make_shared<AABB>(x_min, x_max, y_min, y_max, z_min, z_max, aabb_type);
}

void BasicShape::load_aabb_shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name,
                                  const std::string &geometry_shader_name) {
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + vertex_shader_name;
    std::string f_path = SHADER_DIRECTORY + "/" + fragment_shader_name;
    std::string g_path;
    if (!geometry_shader_name.empty())
        g_path = SHADER_DIRECTORY + "/" + geometry_shader_name;
    else
        g_path = "";
    this->shader_aabb = std::make_unique<Shader>(v_path, f_path, g_path);
}

void BasicShape::update_AABB() {
    float x_min = std::numeric_limits<float>::infinity(), x_max = -std::numeric_limits<float>::infinity(), y_min = std::numeric_limits<float>::infinity(), y_max = -std::numeric_limits<float>::infinity(), z_min = std::numeric_limits<float>::infinity(), z_max = -std::numeric_limits<float>::infinity();
    for (auto &mesh : meshes) {
        for (auto &vertex: mesh.vertices) {
            Eigen::Vector4f real_position =
                    model * Eigen::Vector4f(vertex.position.x(), vertex.position.y(), vertex.position.z(), 1.f);
            real_position /= real_position.w();
            if (real_position.x() <= x_min)
                x_min = real_position.x();
            if (real_position.x() >= x_max)
                x_max = real_position.x();
            if (real_position.y() <= y_min)
                y_min = real_position.y();
            if (real_position.y() >= y_max)
                y_max = real_position.y();
            if (real_position.z() <= z_min)
                z_min = real_position.z();
            if (real_position.z() >= z_max)
                z_max = real_position.z();
        }
    }
    aabb->update(x_min, x_max, y_min, y_max, z_min, z_max);
}

void BasicShape::draw_AABB() {
    aabb->aabb_mesh->draw(*shader_aabb);
}

// ------------------------------ AABB ------------------------------
AABB::AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, AABB_TYPE type) : x_min(xMin),
                                                                                                     x_max(xMax),
                                                                                                     y_min(yMin),
                                                                                                     y_max(yMax),
                                                                                                     z_min(zMin),
                                                                                                     z_max(zMax),
                                                                                                     type(type) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    vertices.resize(8);
    indices.resize(36);
    vertices[0].position = Eigen::Vector3f(x_min, y_min, z_min);
    vertices[1].position = Eigen::Vector3f(x_min, y_min, z_max);
    vertices[2].position = Eigen::Vector3f(x_min, y_max, z_min);
    vertices[3].position = Eigen::Vector3f(x_min, y_max, z_max);
    vertices[4].position = Eigen::Vector3f(x_max, y_min, z_min);
    vertices[5].position = Eigen::Vector3f(x_max, y_min, z_max);
    vertices[6].position = Eigen::Vector3f(x_max, y_max, z_min);
    vertices[7].position = Eigen::Vector3f(x_max, y_max, z_max);
    switch (type) {
        case AABB_2D:
//            indices = {1, 2, 4, 3, 2, 4, 7, 8, 6, 5, 8, 6, 3, 4, 8, 7, 4, 8, 1, 2, 6, 5, 2, 6};
            indices = {1, 3, 3, 7, 7, 5, 5, 1};
            for (auto &i : indices) --i;
            aabb_mesh = std::make_unique<Mesh>(vertices, indices, textures);
            aabb_mesh->draw_mode = LINE;
            break;
        case AABB_3D:
            //    indices = {1, 2, 5, 6, 2, 5, 3, 4, 7, 8, 4, 7, 4, 8, 6, 4, 2, 6, 3, 7, 5, 3, 1, 5, 8, 7, 6, 5, 7, 6,
            //               3, 4, 2, 3, 1, 2};
            indices = {1, 2, 3, 1, 2, 4, 3, 4, 1, 3, 4, 2, 5, 6, 7, 5, 6, 8, 7, 8, 5, 7, 8, 6, 3, 4, 7, 3, 4, 8, 7, 8,
                       3, 7, 8,
                       4, 5, 6, 1, 5, 6, 2, 1, 2, 5, 1, 2, 6, 2, 4, 6, 2, 4, 8, 8, 6, 2, 8, 6, 4, 3, 7, 1, 3, 7, 5, 1,
                       5, 3, 1,
                       5, 7};
            for (auto &i : indices) --i;
            aabb_mesh = std::make_unique<Mesh>(vertices, indices, textures);
            aabb_mesh->draw_mode = POLYGON;
            break;
        default:
            break;
    }
}

void AABB::update(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
    x_min = xMin;
    x_max = xMax;
    y_min = yMin;
    y_max = yMax;
    z_min = zMin;
    z_max = zMax;
    std::vector<Vertex> vertices;
    vertices.resize(8);
    vertices[0].position = Eigen::Vector3f(x_min, y_min, z_min);
    vertices[1].position = Eigen::Vector3f(x_min, y_min, z_max);
    vertices[2].position = Eigen::Vector3f(x_min, y_max, z_min);
    vertices[3].position = Eigen::Vector3f(x_min, y_max, z_max);
    vertices[4].position = Eigen::Vector3f(x_max, y_min, z_min);
    vertices[5].position = Eigen::Vector3f(x_max, y_min, z_max);
    vertices[6].position = Eigen::Vector3f(x_max, y_max, z_min);
    vertices[7].position = Eigen::Vector3f(x_max, y_max, z_max);
    aabb_mesh->vertices = std::move(vertices);
    aabb_mesh->update_mesh();
}