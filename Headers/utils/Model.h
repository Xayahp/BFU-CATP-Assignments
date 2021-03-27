#ifndef ASSIGNMENT_FRAMEWORK_MODEL_H
#define ASSIGNMENT_FRAMEWORK_MODEL_H

#include "glad/glad.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb/stb_image.h"

#include "Eigen/Eigen"

#include "Shader.h"

#include <iostream>
#include <string>
#include <vector>


enum DRAW_MODE {
    // 2D
    POINT_2D,
    LINE,
    // 3D
    POINT,
    POLYGON,
    FILL
};

enum TEXTURE_TYPE {
    TEXTURE_DIFFUSE,
    TEXTURE_SPECULAR,
    TEXTURE_NORMAL,
    TEXTURE_HEIGHT
};

struct Vertex {
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    Eigen::Vector2f tex_coord;
    Eigen::Vector3f tangent;
    Eigen::Vector3f bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    unsigned int VAO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures = {});

    void draw(Shader &shader) const;

    void set_draw_mode(DRAW_MODE mode);

    void update_mesh();

    DRAW_MODE draw_mode = POLYGON;

private:
    void setup_mesh();

    unsigned int VBO, EBO;
};

class Model {
public:
    Model() = default;

    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    bool gamma = false;

    void load_model(std::string const &path, bool is_3D = true, bool _gamma = false);

    void draw(Shader &shader);

    static unsigned int load_texture(const char *path, const std::string &directory, bool gamma = false);

    void set_draw_mode(DRAW_MODE mode);

private:

    void process_node(aiNode *node, const aiScene *scene);

    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
};


#endif //ASSIGNMENTFRAMEWORK_MODEL_H
