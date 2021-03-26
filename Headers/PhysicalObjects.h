#ifndef ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
#define ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H

#include <Eigen/Cholesky>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include "BasicShapes.h"

#include "Eigen/Eigen"

class BasicPhysicalObjects {
public:
    BasicPhysicalObjects();

    virtual ~BasicPhysicalObjects();

public:
    bool is_fixed;
public:
    Eigen::Vector3f x; // centroid position
    Eigen::Vector3f v; // velocity
    Eigen::Vector3f f; // force
    float ff; // friction

    float m; // mass

    Eigen::Matrix4f im;
public:
    void set_position(const Eigen::Vector3f &pos);

    void sub_step(float delta_t);

    virtual void collision_detection() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) = 0;
};

// ------------------------------ 2D Objects ------------------------------

class Brick : public Rectangle, public BasicPhysicalObjects {
public:
    Brick(float width, float height);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

private:
    void collision_detection() override;

    float width;
    float height;
};

class Pizza : public Circle, public BasicPhysicalObjects {
public:
    Pizza(float radius);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

public:
    void collision_detection() override;

    float radius;
};


// ------------------------------ 3D Objects ------------------------------
class Ground : public Plane, public BasicPhysicalObjects {
public:
    Ground(float width, float height);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

public:
    void collision_detection() override;

    float width;
    float height;
};

class Ball : public Sphere, public BasicPhysicalObjects {
public:
    Ball(float radius);

    void update() override;

    void draw() override;

    void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) override;

public:
    void collision_detection() override;

    float radius;
};

#endif //ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
