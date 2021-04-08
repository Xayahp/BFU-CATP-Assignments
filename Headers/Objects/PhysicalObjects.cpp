#include "PhysicalObjects.h"

BasicPhysicalObjects::BasicPhysicalObjects() : x(Eigen::Vector3f::Zero()), v(Eigen::Vector3f::Zero()),
                                               f(Eigen::Vector3f::Zero()), ff(0.f), m(1.f), is_fixed(false),
                                               rotation(Eigen::Matrix4f::Identity()) {}


void BasicPhysicalObjects::set_position(const Eigen::Vector3f &pos) {
    this->x = pos;
    if (!x_inited) {
        this->x0 = pos;
        x_inited = true;
    }
}

void BasicPhysicalObjects::set_position(float _x, float _y, float _z) {
    this->x[0] = _x;
    this->x[1] = _y;
    this->x[2] = _z;
    if (!x_inited) {
        this->x0[0] = _x;
        this->x0[1] = _y;
        this->x0[2] = _z;
        x_inited = true;
    }
}

void BasicPhysicalObjects::set_velocity(const Eigen::Vector3f &vel) {
    this->v = vel;
    if (!v_inited) {
        this->v0 = vel;
        v_inited = true;
    }
}

void BasicPhysicalObjects::set_velocity(float _x, float _y, float _z) {
    this->v[0] = _x;
    this->v[1] = _y;
    this->v[2] = _z;
    if (!v_inited) {
        this->v0[0] = _x;
        this->v0[1] = _y;
        this->v0[2] = _z;
        v_inited = true;
    }
}

void BasicPhysicalObjects::set_mass(float _m) {
    this->m = _m;
    if (!m_inited) {
        this->m0 = _m;
    }
}

void BasicPhysicalObjects::rotate(float theta_x_axis, float theta_y_axis, float theta_z_axis) {
    float rad_x_axis = (float) 3.1415926 * theta_x_axis / 180.f;
    float rad_y_axis = (float) 3.1415926 * theta_y_axis / 180.f;
    float rad_z_axis = (float) 3.1415926 * theta_z_axis / 180.f;
    Eigen::Matrix4f rotation_x, rotation_y, rotation_z;
    rotation_x << 1, 0, 0, 0
            , 0, cos(rad_x_axis), -sin(rad_x_axis), 0
            , 0, sin(rad_x_axis), cos(rad_x_axis), 0
            , 0, 0, 0, 1;
    rotation_y << cos(rad_y_axis), 0, sin(rad_y_axis), 0
            , 0, 1, 0, 0
            , -sin(rad_y_axis), 0, cos(rad_y_axis), 0
            , 0, 0, 0, 1;
    rotation_z << cos(rad_z_axis), -sin(rad_z_axis), 0, 0
            , sin(rad_z_axis), cos(rad_z_axis), 0, 0
            , 0, 0, 1, 0
            , 0, 0, 0, 1;
    this->rotation = rotation_x * rotation_y * rotation_z;
    if (!r_inited) {
        this->rotation0 = rotation_x * rotation_y * rotation_z;
    }
}

void BasicPhysicalObjects::fix() {
    this->is_fixed = true;
}