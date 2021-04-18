#include "Collision.h"

void Collision::naive_aabb_collison2D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, COLLISION_AXIS &axis,
                                      float &optimal_f) {

    axis = NO_COLLIDED;
    optimal_f = 0.f;

    auto aabb1 = obj->get_aabb();
    std::shared_ptr<AABB> aabb2;

    for (auto &other_obj : world_objs) {
        if (other_obj == obj)
            continue;

        aabb2 = other_obj->get_aabb();

        if (aabb1->x_min < aabb2->x_max && aabb1->x_max > aabb2->x_min) {
            if (aabb1->y_min < aabb2->y_max && aabb1->y_max > aabb2->y_min) {

                float dist_x12 = aabb1->x_max - aabb2->x_min;
                float dist_x21 = aabb2->x_max - aabb1->x_min;
                float dist_y12 = aabb1->y_max - aabb2->y_min;
                float dist_y21 = aabb2->y_max - aabb1->y_min;

                float dist_x = std::min({dist_x12, dist_x21});
                float dist_y = std::min({dist_y12, dist_y21});

                axis = dist_x < dist_y ? AXIS_X : AXIS_Y;

                float temp_f;
                if (axis == AXIS_X) {
                    temp_f = dist_x / delta_x;
                }
                if (axis == AXIS_Y) {
                    temp_f = dist_y / delta_y;
                }
                optimal_f = temp_f;
            }
        }
    }
}

void Collision::naive_aabb_collison3D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, float delta_z, COLLISION_AXIS &axis, float &optimal_f) {

    axis = NO_COLLIDED;
    optimal_f = 0.f;

    auto aabb1 = obj->get_aabb();
    std::shared_ptr<AABB> aabb2;

    for (auto &other_obj : world_objs) {
        if (other_obj == obj)
            continue;

        aabb2 = other_obj->get_aabb();

        // Your Code Start Here
        // ------------------------------






        // ------------------------------
        // Your Code End Here
    }
}
