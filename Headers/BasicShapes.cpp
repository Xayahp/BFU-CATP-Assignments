#include "BasicShapes.h"

AABB::AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) : x_min(xMin), x_max(xMax),
                                                                                     y_min(yMin), y_max(yMax),
                                                                                     z_min(zMin), z_max(zMax) {

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
//    indices = {1, 2, 5, 6, 2, 5, 3, 4, 7, 8, 4, 7, 4, 8, 6, 4, 2, 6, 3, 7, 5, 3, 1, 5, 8, 7, 6, 5, 7, 6,
//               3, 4, 2, 3, 1, 2};
    indices = {1, 2, 3, 1, 2, 4, 3, 4, 1, 3, 4, 2, 5, 6, 7, 5, 6, 8, 7, 8, 5, 7, 8, 6, 3, 4, 7, 3, 4, 8, 7, 8, 3, 7, 8,
               4, 5, 6, 1, 5, 6, 2, 1, 2, 5, 1, 2, 6, 2, 4, 6, 2, 4, 8, 8, 6, 2, 8, 6, 4, 3, 7, 1, 3, 7, 5, 1, 5, 3, 1,
               5, 7};
    for (auto &i : indices) --i;
    aabb_mesh = std::make_unique<Mesh>(vertices, indices, textures);
    aabb_mesh->draw_mode = POLYGON;
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

BasicShape::BasicShape(const std::string &name) : name(name) {
    load_model(fetch_obj_model_by_name(name));
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string vertex_triangles_shader_path = SHADER_DIRECTORY + "/" + "AABB.vert";
    std::string fragment_triangles_shader_path = SHADER_DIRECTORY + "/" + "AABB.frag";
    shader_aabb = std::make_unique<Shader>(vertex_triangles_shader_path, fragment_triangles_shader_path);

    float x_min = 0.f, x_max = 0.f, y_min = 0.f, y_max = 0.f, z_min = 0.f, z_max = 0.f;
    aabb = std::make_unique<AABB>(x_min, x_max, y_min, y_max, z_min, z_max);
}

std::string BasicShape::fetch_obj_model_by_name(const std::string &obj_filename) {
    std::string data_directory = PROJECT_DATA_DIR;
    return std::string(data_directory + "/3D/" + obj_filename + ".obj");;
}

void BasicShape::load_shader(const std::string &vertexPath, const std::string &fragmentPath,
                             const std::string &geometryPath) {
    this->shader = std::make_unique<Shader>(vertexPath, fragmentPath, geometryPath);
}

void BasicShape::set_MVP(Eigen::Matrix4f &_model, Eigen::Matrix4f &_view, Eigen::Matrix4f &_projection) {
    this->model = _model;
    this->shader->use();
    this->shader->setMat4("projection", _projection);
    this->shader->setMat4("view", _view);
    this->shader->setMat4("model", _model);
    this->shader_aabb->use();
    this->shader_aabb->setMat4("projection", _projection);
    this->shader_aabb->setMat4("view", _view);
    this->shader_aabb->setMat4("model", Eigen::Matrix4f::Identity());
}

void BasicShape::draw() {
    this->shader->use();
    Model::draw(*this->shader);
    this->shader_aabb->use();
    draw_AABB();
}

void BasicShape::update_AABB() {
    float x_min = 0.f, x_max = 0.f, y_min = 0.f, y_max = 0.f, z_min = 0.f, z_max = 0.f;
    for (auto &mesh : meshes) {
        for (auto &vertex: mesh.vertices) {
            Eigen::Vector4f real_position =
                    model * Eigen::Vector4f(vertex.position.x(), vertex.position.y(), vertex.position.z(), 1.f);
            real_position /= real_position.w();
            if (real_position.x() < x_min)
                x_min = real_position.x();
            if (real_position.x() > x_max)
                x_max = real_position.x();
            if (real_position.y() < y_min)
                y_min = real_position.y();
            if (real_position.y() > y_max)
                y_max = real_position.y();
            if (real_position.z() < z_min)
                z_min = real_position.z();
            if (real_position.z() > z_max)
                z_max = real_position.z();
        }
    }
    aabb->update(x_min, x_max, y_min, y_max, z_min, z_max);
}

void BasicShape::draw_AABB() {
    update_AABB();
    aabb->aabb_mesh->draw(*shader_aabb);
}

Plane::Plane() : BasicShape("plane") {}

Cube::Cube() : BasicShape("cube") {}

Sphere::Sphere() : BasicShape("sphere") {}

Cylinder::Cylinder() : BasicShape("cylinder") {}

Cone::Cone() : BasicShape("cone") {}

Corner_ball::Corner_ball() : BasicShape("corner_ball") {}

Torus::Torus() : BasicShape("torus") {}
