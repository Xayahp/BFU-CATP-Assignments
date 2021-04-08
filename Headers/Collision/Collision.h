#ifndef ASSIGNMENT_FRAMEWORK_COLLISION_H
#define ASSIGNMENT_FRAMEWORK_COLLISION_H

#include "PhysicalObjects.h"

enum DIRECT_POINT_2D {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

enum DIRECT_POINT_3D {
    TOP_LEFT_FRONT,
    TOP_RIGHT_FRONT,
    BOTTOM_LEFT_FRONT,
    BOTTOM_RIGHT_FRONT,
    TOP_LEFT_BEHIND,
    TOP_RIGHT_BEHIND,
    BOTTOM_LEFT_BEHIND,
    BOTTOM_RIGHT_BEHIND
};

enum COLLISION_AXIS {
    NO_COLLIDED,
    AXIS_X,
    AXIS_Y,
    AXIS_Z
};

class Collision {
public:

    static void naive_aabb_collison2D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, COLLISION_AXIS &axis, float &optimal_f);

    static void naive_aabb_collison3D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, float delta_z, COLLISION_AXIS &axis, float &optimal_f);
};

#endif //ASSIGNMENT_FRAMEWORK_COLLISION_H
