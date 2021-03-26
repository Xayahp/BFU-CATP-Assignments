#ifndef ASSIGNMENT_FRAMEWORK_BASICSHAPES_H
#define ASSIGNMENT_FRAMEWORK_BASICSHAPES_H

#include "Shader.h"
#include "Model.h"

#include "Eigen/Eigen"
#include "glm/glm.hpp"

#include <string>


class AABB {
public:
    AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

    void update(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

    std::unique_ptr<Mesh> aabb_mesh;
    float x_min, x_max, y_min, y_max, z_min, z_max;
};


class BasicShape : public Model {
protected:
    explicit BasicShape(const std::string &name);

public: // DRAW INTERFACE
    void draw();

    void load_shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");

    void set_projection(Eigen::Matrix4f &_projection);

    void set_view(Eigen::Matrix4f &_view);

    void set_model(Eigen::Matrix4f &_model);

public:
    static std::string fetch_obj_model_by_name(const std::string &obj_filename);

    const std::string name;

    std::unique_ptr<Shader> shader;
    Eigen::Matrix4f model;

private: // AABB INTERFACE
    void draw_AABB();

    void update_AABB();

    std::unique_ptr<Shader> shader_aabb;
    std::unique_ptr<AABB> aabb;
};


class Plane : public BasicShape {
public:
    Plane();
};


class Cube : public BasicShape {
public:
    Cube();
};


class Sphere : public BasicShape {
public:
    Sphere();
};


class Cylinder : public BasicShape {
public:
    Cylinder();
};


class Cone : public BasicShape {
public:
    Cone();
};


class Corner_ball : public BasicShape {
public:
    Corner_ball();
};


class Torus : public BasicShape {
public:
    Torus();
};


#endif //ASSIGNMENTFRAMEWORK_BASICSHAPES_H