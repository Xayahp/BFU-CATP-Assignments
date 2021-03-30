#include "Collision.h"

void Collision::naive_aabb_collison(std::unique_ptr<BasicPhysicalObjects> &obj,
                                    std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs) {
    auto aabb1 = obj->get_aabb();
    std::shared_ptr<AABB> aabb2;
    for (auto &other_obj : world_objs) {
        if (other_obj == obj) continue;
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

                float dist_x12 = x_max_1 - x_min_2 + 0.00001;
                float dist_x21 = x_max_2 - x_min_1 + 0.00001;
                float dist_y12 = y_max_1 - y_min_2 + 0.00001;
                float dist_y21 = y_max_2 - y_min_1 + 0.00001;

                auto min = std::min({dist_x12, dist_x21, dist_y12, dist_y21});

                if (min == dist_x12) {
                    obj->v.x() = -0.99 * obj->v.x();
                    other_obj->v.x() = -0.99 * other_obj->v.x();
                    if (!obj->is_fixed && !other_obj->is_fixed) {
                        obj->x.x() -= 0.5 * dist_x12;
                        other_obj->x.x() += 0.5 * dist_x12;
                    } else if (!obj->is_fixed) {
                        obj->x.x() -= dist_x12;
                    } else if (!other_obj->is_fixed) {
                        other_obj->x.x() += dist_x12;
                    }
                }
                if (min == dist_x21) {
                    obj->v.x() = -0.99 * obj->v.x();
                    other_obj->v.x() = -0.99 * other_obj->v.x();
                    if (!obj->is_fixed && !other_obj->is_fixed) {
                        obj->x.x() += 0.5 * dist_x21;
                        other_obj->x.x() -= 0.5 * dist_x21;
                    } else if (!obj->is_fixed) {
                        obj->x.x() += dist_x21;
                    } else if (!other_obj->is_fixed) {
                        other_obj->x.x() -= dist_x21;
                    }
                }
                if (min == dist_y12) {
                    obj->v.y() = -0.99 * obj->v.y();
                    other_obj->v.y() = -0.99 * other_obj->v.y();
                    if (!obj->is_fixed && !other_obj->is_fixed) {
                        obj->x.y() -= 0.5 * dist_y12;
                        other_obj->x.y() += 0.5 * dist_y12;
                    } else if (!obj->is_fixed) {
                        obj->x.y() -= dist_y12;
                    } else if (!other_obj->is_fixed) {
                        other_obj->x.y() += dist_y12;
                    }
                }
                if (min == dist_y21) {
                    obj->v.y() = -0.99 * obj->v.y();
                    other_obj->v.y() = -0.99 * other_obj->v.y();
                    if (!obj->is_fixed && !other_obj->is_fixed) {
                        obj->x.y() += 0.5 * dist_x21;
                        other_obj->x.y() -= 0.5 * dist_x21;
                    } else if (!obj->is_fixed) {
                        obj->x.y() += dist_x21;
                    } else if (!other_obj->is_fixed) {
                        other_obj->x.y() -= dist_x21;
                    }
                }
            }
        }
    }
}
