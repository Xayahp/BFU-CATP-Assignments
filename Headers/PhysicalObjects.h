#ifndef ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
#define ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H

#include "BasicShapes.h"

#include "Eigen/Eigen"

class BasicPhysicalObjects {
public:
    BasicPhysicalObjects();

public:
    bool is_fixed;
public:
    Eigen::Vector3f x; // centroid position
    Eigen::Vector3f v; // velocity
    Eigen::Vector3f f; // force
    float ff; // friction

    float m; // mass
public:
    void set_position(const Eigen::Vector3f &pos);

    void sub_step(float delta_t);

    virtual void collision_detection();

//    void update_position();
    Eigen::Matrix4f generate_translation_mat();
//    Eigen::Matrix4f generate_rotation_mat();
};

class Ground : public Plane, public BasicPhysicalObjects {
public:
    Ground(float width, float height);

    [[nodiscard]] Eigen::Matrix4f generate_scale_mat() const;

public:
    float width;
    float height;
};

class Ball : public Sphere, public BasicPhysicalObjects {
public:
    Ball(float radius);

    [[nodiscard]] Eigen::Matrix4f generate_scale_mat() const;

    void collision_detection() override;

public:
    float radius{};
};

#endif //ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
