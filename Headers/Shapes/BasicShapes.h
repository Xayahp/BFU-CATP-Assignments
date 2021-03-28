#ifndef ASSIGNMENT_FRAMEWORK_BASICSHAPE_H
#define ASSIGNMENT_FRAMEWORK_BASICSHAPE_H

#include "Shader.h"
#include "Model.h"

#include "Eigen/Eigen"

#include <string>

enum SHAPE_TYPE {
    SHAPE_2D,
    SHAPE_3D
};

enum AABB_TYPE {
    AABB_2D,
    AABB_3D
};

class AABB;

class BasicShape : public Model {
protected: // -------------------- CONSTRUCTOR(S) --------------------
    explicit BasicShape(const std::string &name, SHAPE_TYPE type = SHAPE_3D);


public: // -------------------- DRAW INTERFACE --------------------
    virtual void draw();

    void load_shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name,
                     const std::string &geometry_shader_name = "");

    void load_texture(const std::string &texturePath, TEXTURE_TYPE = TEXTURE_DIFFUSE);

    void set_color(const Eigen::Vector4f &_color);

    void set_projection(const Eigen::Matrix4f &_projection);

    void set_view(const Eigen::Matrix4f &_view);

    void set_model(const Eigen::Matrix4f &_model);

    bool DRAW_AABB = false;


public:
    SHAPE_TYPE type;
    const std::string name;
    std::shared_ptr<Shader> shader;
    Eigen::Vector4f color;
    Eigen::Matrix4f model, view, projection;
    Eigen::Matrix4f ortho;

private: // -------------------- AABB INTERFACE --------------------
    void init_aabb(AABB_TYPE aabb_type);

    void load_aabb_shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name,
                          const std::string &geometry_shader_name = "");

    void draw_AABB();

    void update_AABB();

    std::unique_ptr<Shader> shader_aabb;
    std::unique_ptr<AABB> aabb;
};


// ------------------------------ AABB CLASS ------------------------------
class AABB {
public:
    AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, AABB_TYPE type = AABB_3D);

    void update(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

    std::unique_ptr<Mesh> aabb_mesh;
    float x_min, x_max, y_min, y_max, z_min, z_max;
    AABB_TYPE type;
};


#endif //ASSIGNMENT_FRAMEWORK_BASICSHAPE_H