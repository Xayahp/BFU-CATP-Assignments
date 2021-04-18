#ifndef ASSIGNMENTFRAMEWORK_CLOTH_H
#define ASSIGNMENTFRAMEWORK_CLOTH_H

#include <utility>

#include "Eigen/Eigen"
#include "Objects2D.h"
#include "Objects3D.h"
#include "Shader.h"

namespace CLOTH_SIMULATION
{
    enum DRAWMODE
    {
        DRAW_NODES, DRAW_LINES, DRAW_FACES
    };


// ------------------------------ [ NODE ] class fields start ------------------------------
    class Node : public Ball
    {
    public:
        // object [node] as one *point* in the *cloth face*
        Eigen::Vector3f normal;
        Eigen::Vector2f tex_coord;

    public:
        Node(const Eigen::Vector3f &_position, float _default_radius = 0.05) : Ball(_default_radius)
        { BasicPhysicalObjects::set_position(_position); }

    public:
        void integrate(float time_step)
        {
            if (!is_fixed)
            {
                Eigen::Vector3f a = f / m;
                v += a * time_step;
                x += v * time_step;
            }
            f = Eigen::Vector3f::Zero();
        }
    };
// ------------------------------ [ NODE ] class fields end ------------------------------



// ------------------------------ [ SPRING ] class fields start ------------------------------
    class Spring : public Edge
    {
    public:
        std::shared_ptr<Node> n1, n2;
        float r; // rest length
        float k; // Hooke's coef
        float d; // damp coef

    public:
        Spring(std::shared_ptr<Node> &_n1, std::shared_ptr<Node> &_n2, float _k, float _d = 0.5f) : Edge((_n1->x - _n2->x).norm()), n1(_n1), n2(_n2), k(_k), d(_d),
                                                                                                    r((_n1->x - _n2->x).norm())
        {
            name = "Spring";
            update_spring();
        }

    public:
        void apply_internal_force(float time_step) const
        {
            float current_length = (n2->x - n1->x).norm();
            Eigen::Vector3f dir_n1_to_n2 = (n2->x - n1->x).normalized();
            Eigen::Vector3f f_spring = -k * (current_length - r) * dir_n1_to_n2;
            n1->f += -f_spring;
            n2->f += f_spring;
        }

        void update_spring()
        {
            x = 0.5 * (n1->x + n2->x);
            width = (n1->x - n2->x).norm() - 0.5 * (n1->radius + n2->radius);
            Eigen::Vector3f unit_dir = (n2->x - n1->x).normalized();
            float dot_product_x = unit_dir.dot(Eigen::Vector3f(1, 0, 0));
            float dot_product_y = unit_dir.dot(Eigen::Vector3f(0, 1, 0));
            float sign = dot_product_y > 0.f ? +1.f : -1.f;
            rotate(0, 0, sign * 180.f / 3.1415926f * acosf(dot_product_x));
        }
    };

// ------------------------------ [ SPRING ] class fields end ------------------------------



// ------------------------------ [ CLOTH ] class fields start ------------------------------
    class Cloth
    {
    public:
        DRAWMODE mode = DRAW_LINES;
        std::vector<std::unique_ptr<Node> > nodes;
        std::vector<std::unique_ptr<Spring> > springs;
        std::vector<std::unique_ptr<Node> > faces;

    public:
        Cloth(Eigen::Vector3f _position, unsigned int _width, unsigned int _height) : cloth_position(std::move(_position)), width(_width), height(_height)
        { init(); }

        void update(float time_step)
        {}

        void draw(const Eigen::Matrix4f &view, Eigen::Matrix4f projection, float delta_time)
        {
            update(delta_time);
//            for (auto &node : nodes)
//            {
//                node->set_vp(view, projection);
//                node->draw();
//            }
        }

        void set_shader(std::shared_ptr<Shader> _shader)
        {
            for (auto &node : nodes)
            {
                node->shader = _shader;
            }
        }

    private:
        Eigen::Vector3f cloth_position;
        unsigned int width, height;
        unsigned int nodes_by_row, nodes_ber_col;
        const unsigned int nodes_density = 4;
        std::vector<Eigen::Vector2d> pins;
        const int iteration_freq = 25;
        const float structural_coef = 1000.f;
        const float shear_coef = 50.f;
        const float bending_coef = 400.f;

    private:
        void init()
        {
            nodes_by_row = width * nodes_density;
            nodes_ber_col = height * nodes_density;
            pins.emplace_back(Eigen::Vector2d(0, 0));
            pins.emplace_back(Eigen::Vector2d(nodes_by_row - 1, 0));

            // add nodes
            for (int i = 0; i < nodes_by_row; i++)
            {
                for (int j = 0; j < nodes_ber_col; j++)
                {
                    auto node = std::make_unique<Node>(Eigen::Vector3f((float) ((float) j / (float) nodes_density), (float) ((float) i / (float) nodes_density), 0.f));
                    node->tex_coord[0] = (float) j / (float) (nodes_by_row - 1);
                    node->tex_coord[1] = (float) i / (float) (1 - nodes_ber_col);
                    nodes.push_back(std::move(node));
                }
            }
        }

        void compute_normal()
        {}

        void add_force(const Eigen::Vector3f &_force)
        {}

        void integrate(float time_step)
        {}

        Eigen::Vector3f get_world_position(std::unique_ptr<Node> n)
        { return cloth_position + n->x; }

        void set_world_position(std::unique_ptr<Node> n, const Eigen::Vector3f &pos) const
        {
            n->x = pos - cloth_position;
        }

        void collision_response()
        {}
    };
// ------------------------------ [ CLOTH ] class fields end ------------------------------
}
#endif //ASSIGNMENT_FRAMEWORK_CLOTH_H
