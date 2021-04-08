#include "Collision.h"

void Collision::naive_aabb_collison2D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, COLLISION_AXIS &axis, float &optimal_f) {

    axis = NO_COLLIDED;
    optimal_f = 0.f;

    float dist = 10000.f;

    DIRECT_POINT_2D direction;
    if (obj->v.x() <= 0 && obj->v.y() <= 0) direction = TOP_LEFT;
    if (obj->v.x() <= 0 && obj->v.y() >= 0) direction = BOTTOM_LEFT;
    if (obj->v.x() >= 0 && obj->v.y() <= 0) direction = TOP_RIGHT;
    if (obj->v.x() >= 0 && obj->v.y() >= 0) direction = BOTTOM_RIGHT;

    auto aabb1 = obj->get_aabb();
    std::shared_ptr<AABB> aabb2;

    for (auto &other_obj : world_objs) {
        if (other_obj == obj)
            continue;

        aabb2 = other_obj->get_aabb();

        float x_min_1 = aabb1->x_min;
        float x_max_1 = aabb1->x_max;
        float x_min_2 = aabb2->x_min;
        float x_max_2 = aabb2->x_max;
        float y_min_1 = aabb1->y_min;
        float y_max_1 = aabb1->y_max;
        float y_min_2 = aabb2->y_min;
        float y_max_2 = aabb2->y_max;

        if (x_min_1 < x_max_2 && x_max_1 > x_min_2) {
            if (y_min_1 < y_max_2 && y_max_1 > y_min_2) {


                float dist_x12 = x_max_1 - x_min_2;
                float dist_x21 = x_max_2 - x_min_1;
                float dist_y12 = y_max_1 - y_min_2;
                float dist_y21 = y_max_2 - y_min_1;

                switch (direction) {
                    case TOP_LEFT:
                        if (dist_x21 < dist_y21) {
                            float temp_f = dist_x21 / delta_x;
                            if (temp_f > optimal_f) {
                                axis = AXIS_X;
                                dist = dist_x21;
                                optimal_f = temp_f;
                            }
                        } else {
                            float temp_f = dist_y21 / delta_y;
                            if (temp_f > optimal_f) {
                                axis = AXIS_Y;
                                dist = dist_y21;
                                optimal_f = temp_f;
                            }
                        }
                        break;
                    case BOTTOM_LEFT:
                        if (dist_x21 < dist_y12) {
                            float temp_f = dist_x21 / delta_x;
                            if (temp_f > optimal_f) {
                                axis = AXIS_X;
                                dist = dist_x21;
                                optimal_f = temp_f;
                            }
                        } else {
                            float temp_f = dist_y12 / delta_y;
                            if (temp_f > optimal_f) {
                                axis = AXIS_Y;
                                dist = dist_y12;
                                optimal_f = temp_f;
                            }
                        }
                        break;
                    case TOP_RIGHT:
                        if (dist_x12 < dist_y21) {
                            float temp_f = dist_x12 / delta_x;
                            if (temp_f > optimal_f) {
                                axis = AXIS_X;
                                dist = dist_x12;
                                optimal_f = temp_f;
                            }
                        } else {
                            float temp_f = dist_y21 / delta_y;
                            if (temp_f > optimal_f) {
                                axis = AXIS_Y;
                                dist = dist_y21;
                                optimal_f = temp_f;
                            }
                        }
                        break;
                    case BOTTOM_RIGHT:
                        if (dist_x12 < dist_y12) {
                            float temp_f = dist_x12 / delta_x;
                            if (temp_f > optimal_f) {
                                axis = AXIS_X;
                                dist = dist_x12;
                                optimal_f = temp_f;
                            }
                        } else {
                            float temp_f = dist_y12 / delta_y;
                            if (temp_f > optimal_f) {
                                axis = AXIS_Y;
                                dist = dist_y12;
                                optimal_f = temp_f;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Collision::naive_aabb_collison3D(const std::unique_ptr<BasicPhysicalObjects> &obj,
                                      const std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs,
                                      float delta_x, float delta_y, float delta_z, COLLISION_AXIS &axis,
                                      float &optimal_f) {

    axis = NO_COLLIDED;
    optimal_f = 0.f;

    float dist = 10000.f;

    DIRECT_POINT_3D direction;
    if (obj->v.x() <= 0 && obj->v.y() <= 0 && obj->v.z() <= 0) direction = BOTTOM_LEFT_BEHIND;
    if (obj->v.x() <= 0 && obj->v.y() <= 0 && obj->v.z() >= 0) direction = BOTTOM_LEFT_FRONT;
    if (obj->v.x() <= 0 && obj->v.y() >= 0 && obj->v.z() <= 0) direction = TOP_LEFT_BEHIND;
    if (obj->v.x() <= 0 && obj->v.y() >= 0 && obj->v.z() >= 0) direction = TOP_LEFT_FRONT;
    if (obj->v.x() >= 0 && obj->v.y() <= 0 && obj->v.z() <= 0) direction = BOTTOM_RIGHT_BEHIND;
    if (obj->v.x() >= 0 && obj->v.y() <= 0 && obj->v.z() >= 0) direction = BOTTOM_RIGHT_FRONT;
    if (obj->v.x() >= 0 && obj->v.y() >= 0 && obj->v.z() <= 0) direction = TOP_RIGHT_BEHIND;
    if (obj->v.x() >= 0 && obj->v.y() >= 0 && obj->v.z() >= 0) direction = TOP_RIGHT_FRONT;

    auto aabb1 = obj->get_aabb();
    std::shared_ptr<AABB> aabb2;

    for (auto &other_obj : world_objs) {
        if (other_obj == obj)
            continue;

        aabb2 = other_obj->get_aabb();

        float x_min_1 = aabb1->x_min;
        float x_max_1 = aabb1->x_max;
        float x_min_2 = aabb2->x_min;
        float x_max_2 = aabb2->x_max;
        float y_min_1 = aabb1->y_min;
        float y_max_1 = aabb1->y_max;
        float y_min_2 = aabb2->y_min;
        float y_max_2 = aabb2->y_max;
        float z_min_1 = aabb1->z_min;
        float z_max_1 = aabb1->z_max;
        float z_min_2 = aabb2->z_min;
        float z_max_2 = aabb2->z_max;

        if (x_min_1 < x_max_2 && x_max_1 > x_min_2) {
            if (y_min_1 < y_max_2 && y_max_1 > y_min_2) {
                if (z_min_1 < z_max_2 && z_max_1 > z_min_2) {


                    float dist_x12 = x_max_1 - x_min_2;
                    float dist_x21 = x_max_2 - x_min_1;
                    float dist_y12 = y_max_1 - y_min_2;
                    float dist_y21 = y_max_2 - y_min_1;
                    float dist_z12 = z_max_1 - z_min_2;
                    float dist_z21 = z_max_2 - z_min_1;

                    switch (direction) {
                        case TOP_LEFT_BEHIND:
                            if (dist_x21 < dist_y21 && dist_x21 < dist_z21) {
                                float temp_f = dist_x21 / delta_x;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_X;
                                    dist = dist_x21;
                                    optimal_f = temp_f;
                                }
                            } else if () {
                                float temp_f = dist_y21 / delta_y;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_Y;
                                    dist = dist_y21;
                                    optimal_f = temp_f;
                                }
                            }
                            break;
                        case BOTTOM_LEFT:
                            if (dist_x21 < dist_y12) {
                                float temp_f = dist_x21 / delta_x;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_X;
                                    dist = dist_x21;
                                    optimal_f = temp_f;
                                }
                            } else {
                                float temp_f = dist_y12 / delta_y;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_Y;
                                    dist = dist_y12;
                                    optimal_f = temp_f;
                                }
                            }
                            break;
                        case TOP_RIGHT:
                            if (dist_x12 < dist_y21) {
                                float temp_f = dist_x12 / delta_x;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_X;
                                    dist = dist_x12;
                                    optimal_f = temp_f;
                                }
                            } else {
                                float temp_f = dist_y21 / delta_y;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_Y;
                                    dist = dist_y21;
                                    optimal_f = temp_f;
                                }
                            }
                            break;
                        case BOTTOM_RIGHT:
                            if (dist_x12 < dist_y12) {
                                float temp_f = dist_x12 / delta_x;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_X;
                                    dist = dist_x12;
                                    optimal_f = temp_f;
                                }
                            } else {
                                float temp_f = dist_y12 / delta_y;
                                if (temp_f > optimal_f) {
                                    axis = AXIS_Y;
                                    dist = dist_y12;
                                    optimal_f = temp_f;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}