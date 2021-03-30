#include "EulerSolver.h"

void EulerSolver::ForwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
                               std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time) {
    if (!obj->is_fixed) {
        for (int i = 0; i < 15; ++i) {
            obj->f += Eigen::Vector3f(0.f, 980.f, 0.f);
            obj->v += (obj->f / obj->m) * delta_time / 15.f;

            // collision detection here
            if (obj->x.y() > 550.f)
                obj->v = -0.96 * obj->v;

            obj->x += obj->v * delta_time / 15.f;
            obj->f = Eigen::Vector3f::Zero();
        }
    }
}

void EulerSolver::SemiBackwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
                                    std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time) {
    if (!obj->is_fixed) {
//        obj->rotate(0, 0, (float) rand());
        int n = 23;
        for (int i = 0; i < n; ++i) {
            obj->f += Eigen::Vector3f(0.f, 980.f, 0.f);
            obj->f -= 0.01 * obj->v;
            Eigen::Vector3f a = (obj->f / obj->m);
            auto v_pre = obj->v;
            auto v_after = obj->v + a * delta_time / (float) n;
            obj->v = 0.5 * (v_pre + v_after);

            // collision detection here
            if (obj->x.x() < 0.f) {
                obj->x.x() = 0.001f;
                obj->v.x() = -0.75 * obj->v.x();
            }
            if (obj->x.x() > 799.f) {
                obj->x.x() = 798.999f;
                obj->v.x() = -0.75 * obj->v.x();
            }
            if (obj->x.y() > 550.f) {
                obj->x.y() = 549.999f;
                obj->v.y() = -0.75 * obj->v.y();
            }
            if (obj->x.y() > 549.901f && obj->x.y() < 550.090f) {
                obj->v.x() = 0.9999 * obj->v.x();
            }

            Collision::naive_aabb_collison(obj, world_objs);

            obj->x += obj->v * delta_time / (float) n;

            obj->f = Eigen::Vector3f::Zero();
        }
    }
}

void EulerSolver::BackwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
                                std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time) {

}