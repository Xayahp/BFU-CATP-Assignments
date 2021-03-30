#include "PhysicalObjects.h"

BasicPhysicalObjects::BasicPhysicalObjects() : x(Eigen::Vector3f::Zero()), v(Eigen::Vector3f::Zero()),
                                               f(Eigen::Vector3f::Zero()), ff(0.f), m(1.f), is_fixed(false),
                                               rotation(Eigen::Matrix4f::Identity()) {}


void BasicPhysicalObjects::set_position(const Eigen::Vector3f &pos) {
    this->x = pos;
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
}
