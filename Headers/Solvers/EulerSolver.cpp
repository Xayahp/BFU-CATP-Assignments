#include "EulerSolver.h"

void EulerSolver::ForwardEuler2D(std::unique_ptr<BasicPhysicalObjects> &obj,
                                 std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time)
{
    if (!obj->is_fixed)
    {

        float time_step_remaining = delta_time;
        float epsilon = 1e-3;

        Eigen::Vector3f v_pre, x_pre, v_new, x_new;
        Eigen::Vector3f a;

        while (time_step_remaining > epsilon)
        {
            // calc acceleration
            obj->f += Eigen::Vector3f(0.f, 900.f, 0.f); // gravity
            obj->f -= 0.01 * obj->v; // air friction
            a = (obj->f / obj->m);

            // store the previous statew
            v_pre = obj->v;
            x_pre = obj->x;

            // attempt to update state
            v_new = v_pre + a * time_step_remaining;
            x_new = x_pre + v_new * time_step_remaining;
            obj->v = v_new;
            obj->x = x_new;

            // initialize collision parameters
            COLLISION_AXIS axis;
            float optimal_f;
            float delta_x = abs(x_new.x() - x_pre.x());
            float delta_y = abs(x_new.y() - x_pre.y());

            Collision::naive_aabb_collison2D(obj, world_objs, delta_x, delta_y, axis, optimal_f);

            if (axis != NO_COLLIDED)
            {
                x_new = x_pre + v_new * (1.f - optimal_f) * time_step_remaining;
                if (axis == AXIS_X)
                {
                    v_new.x() = -v_new.x();
                    v_new.x() *= 0.99;
                }
                if (axis == AXIS_Y)
                {
                    v_new.y() = -v_new.y();
                    v_new.y() *= 0.99;
                }
                obj->v = v_new;
                obj->x = x_new;
            }
            obj->f = Eigen::Vector3f::Zero();
            time_step_remaining *= optimal_f;

            if (1.f - optimal_f < epsilon) time_step_remaining = 0;
        }
    }
}

void EulerSolver::ForwardEuler3D(std::unique_ptr<BasicPhysicalObjects> &obj,
                                 std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time)
{
    if (!obj->is_fixed)
    {

        float time_step_remaining = delta_time;
        float epsilon = 1e-3;

        Eigen::Vector3f v_pre, x_pre, v_new, x_new;
        Eigen::Vector3f a;

        while (time_step_remaining > epsilon)
        {
            // calc acceleration
            obj->f += Eigen::Vector3f(0.f, -.98f, 0.f); // gravity
            obj->f -= 0.01 * obj->v; // air friction
            a = (obj->f / obj->m);

            // store the previous statew
            v_pre = obj->v;
            x_pre = obj->x;

            // attempt to update state
            v_new = v_pre + a * time_step_remaining;
            x_new = x_pre + v_new * time_step_remaining;
            obj->v = v_new;
            obj->x = x_new;

            // initialize collision parameters
            COLLISION_AXIS axis;
            float optimal_f;
            float delta_x = abs(x_new.x() - x_pre.x());
            float delta_y = abs(x_new.y() - x_pre.y());
            float delta_z = abs(x_new.z() - x_pre.z());

            Collision::naive_aabb_collison3D(obj, world_objs, delta_x, delta_y, delta_z, axis, optimal_f);

            if (axis != NO_COLLIDED)
            {
                x_new = x_pre + v_new * (1.f - optimal_f) * time_step_remaining;
                if (axis == AXIS_X)
                {
                    v_new.x() = -v_new.x();
                    v_new.x() *= 0.99;
                }
                if (axis == AXIS_Y)
                {
                    v_new.y() = -v_new.y();
                    v_new.y() *= 0.99;
                }
                if (axis == AXIS_Z)
                {
                    v_new.z() = -v_new.z();
                    v_new.z() *= 0.99;
                }
                obj->v = v_new;
                obj->x = x_new;
            }
            obj->f = Eigen::Vector3f::Zero();
            time_step_remaining *= optimal_f;

            if (1.f - optimal_f < epsilon) time_step_remaining = 0;
        }
    }
}

void EulerSolver::ImplicitEuler2D(std::unique_ptr<BasicPhysicalObjects> &obj,
                                  std::vector<std::unique_ptr<BasicPhysicalObjects>> &world_objs, float delta_time)
{

}


void EulerSolver::ForwardEulerMassSpring(std::unique_ptr<MassSpringTEMPLATE> &mass_spring_system, float delta_time)
{
    for (auto &spring : mass_spring_system->springs)
    {
        auto n1 = spring->n1;
        auto n2 = spring->n2;
        float r = spring->r;
        float k = spring->k;

        float current_length = (n2->x - n1->x).norm();
        Eigen::Vector3f dir_n1_to_n2 = (n2->x - n1->x).normalized();
        Eigen::Vector3f f_spring = -k * (current_length - r) * dir_n1_to_n2;

        n1->f += -f_spring;
        n2->f += f_spring;
    }
    for (auto &node : mass_spring_system->nodes)
    {
        if (!node->is_fixed)
        {
            Eigen::Vector3f v_pre, x_pre, v_new, x_new;
            Eigen::Vector3f a;

            node->f += Eigen::Vector3f(0, 9.8f, 0);

            a = node->f / node->m;
            v_pre = node->v;
            x_pre = node->x;
            v_new = v_pre + a * delta_time;
            x_new = x_pre + v_new * delta_time;
            node->v = v_new;
            node->x = x_new;
        }
        node->f = Eigen::Vector3f::Zero();
    }
    for (auto &spring : mass_spring_system->springs)
    {
        spring->update_spring();
    }
}