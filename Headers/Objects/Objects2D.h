#ifndef ASSIGNMENT_FRAMEWORK_OBJECTS2D_H
#define ASSIGNMENT_FRAMEWORK_OBJECTS2D_H

#include "Shapes2D.h"

#include "PhysicalObjects.h"

class Edge : public Line, public BasicPhysicalObjects {
public:
    Edge(float width);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

    void set_ortho(const Eigen::Matrix4f &ortho) override;

    Eigen::Matrix4f get_model() override;

    std::shared_ptr<AABB> &get_aabb() override;

public:
    float width;
    Eigen::Vector3f start;
    Eigen::Vector3f end;
};

class Brick : public Rectangle, public BasicPhysicalObjects {
public:
    Brick(float width, float height);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

    void set_ortho(const Eigen::Matrix4f &ortho) override;

    Eigen::Matrix4f get_model() override;

    std::shared_ptr<AABB> &get_aabb() override;

public:
    float width;
    float height;
};

class Pizza : public Circle, public BasicPhysicalObjects {
public:
    Pizza(float radius);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

    void set_ortho(const Eigen::Matrix4f &ortho) override;

    Eigen::Matrix4f get_model() override;

    std::shared_ptr<AABB> &get_aabb() override;

public:
    float radius;
};

#endif //ASSIGNMENT_FRAMEWORK_OBJECTS2D_H
