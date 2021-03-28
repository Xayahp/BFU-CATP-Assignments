#include "EluerSolver.h"

void EluerSolver::ForwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
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

void EluerSolver::SemiBackwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
                                    std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time) {
    if (!obj->is_fixed) {
        for (int i = 0; i < 15; ++i) {
            obj->f += Eigen::Vector3f(0.f, 980.f, 0.f);
            auto v_pre = obj->v;
            auto v_after = obj->v + (obj->f / obj->m) * delta_time / 15.f;
            obj->v = 0.5 * (v_pre + v_after);

            // collision detection here
            if (obj->x.y() > 550.f) {
                obj->x.y() = 549.999f;
                obj->v.y() = -0.45 * obj->v.y();
//                std::cout << "[" << obj->v.x() << ", " << obj->v.y() << ", " << obj->v.z() << "]" << std::endl;
            }
            if (obj->x.y() > 549.901f && obj->x.y() < 550.090f) {
                obj->v.x() = 0.99 * obj->v.x();
            }

            obj->x += obj->v * delta_time / 15.f;

            obj->f = Eigen::Vector3f::Zero();
        }
    }
}

void EluerSolver::BackwardEuler(std::unique_ptr<BasicPhysicalObjects> &obj,
                                std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time) {

}