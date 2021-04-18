#ifndef ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
#define ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H

#include "BasicShapes.h"

#include "Eigen/Eigen"

class BasicPhysicalObjects {
public:
    BasicPhysicalObjects();

    virtual ~BasicPhysicalObjects() = default;

public:
    Eigen::Vector3f x; // centroid position
    Eigen::Vector3f v; // velocity
    Eigen::Vector3f f; // force
    float m; // mass
    float ff; // friction args
    Eigen::Matrix4f rotation; // rotation mat

public: // for reset
    Eigen::Vector3f x0; // original centroid position
    Eigen::Vector3f v0; // original velocity
    Eigen::Matrix4f rotation0; // original force
    float m0; // original mass
    bool x_inited = false;
    bool v_inited = false;
    bool r_inited = false;
    bool m_inited = false;

public:
    bool is_fixed;

public:
    virtual void update() = 0;

    virtual void draw() = 0;

    void rotate(float x_axis, float y_axis, float z_axis);

    void set_position(const Eigen::Vector3f &pos);

    void set_position(float _x, float _y, float _z);

    void set_velocity(const Eigen::Vector3f &vel);

    void set_velocity(float _x, float _y, float _z);

    void set_mass(float _m);

    void fix();

    virtual void set_vp(const Eigen::Matrix4f &view, Eigen::Matrix4f projection) = 0;

    virtual void set_ortho(const Eigen::Matrix4f &ortho) {}

    virtual Eigen::Matrix4f get_model() = 0;

    virtual std::shared_ptr<AABB> &get_aabb() = 0;
};


#endif //ASSIGNMENTFRAMEWORK_PHYSICALOBJECTS_H
