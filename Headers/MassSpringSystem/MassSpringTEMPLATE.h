#ifndef ASSIGNMENT_FRAMEWORK_MASSSPRINGTEMPLATE_H
#define ASSIGNMENT_FRAMEWORK_MASSSPRINGTEMPLATE_H

#include "Objects2D.h"

#include "Eigen/Eigen"

#include <vector>

class Node : public Pizza {
public:
    explicit Node(const Eigen::Vector3f &pos, float radius = 3) : Pizza(radius) {
        this->name = "Node";
        set_position(pos);
        set_velocity(Eigen::Vector3f::Zero());
    }
};

class Spring : public Edge {
public:
    Spring(std::shared_ptr<Node> &_n1, std::shared_ptr<Node> &_n2, float _k, float _d = 0.5f) : Edge((_n1->x -
                                                                                                      _n2->x).norm()),
                                                                                                n1(_n1), n2(_n2), k(_k),
                                                                                                d(_d), r((_n1->x -
                                                                                                          _n2->x).norm()) {
        this->name = "Spring";
        update_spring();
    }

    void update_spring() {
        x = 0.5 * (n1->x + n2->x);
        width = (n1->x - n2->x).norm() - 0.5 * (n1->radius + n2->radius);
        Eigen::Vector3f unit_dir = (n2->x - n1->x).normalized();
        float dot_product_x = unit_dir.dot(Eigen::Vector3f(1, 0, 0));
        float dot_product_y = unit_dir.dot(Eigen::Vector3f(0, 1, 0));
        float sign = dot_product_y > 0.f ? +1.f : -1.f;
        rotate(0, 0, sign * 180.f / 3.1415926f * acosf(dot_product_x));
    }

    std::shared_ptr<Node> n1, n2;
    float r; // rest length
    float k; // Hooke's coef
    float d; // damp coef
};

class MassSpringTEMPLATE {
public:

    void init(std::shared_ptr<Shader> &node_shader, std::shared_ptr<Shader> &spring_shader) {
        int width = 10;
        int height = 10;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::shared_ptr<Node> n = std::make_shared<Node>(
                        Eigen::Vector3f(200, 100, 0) + Eigen::Vector3f(j * 30.f, i * 30.f, 0.f));
                n->shader = node_shader;
                if (i == 0 && j == 0 || i == 0 && j == width - 1) n->fix();
                nodes.push_back(std::move(n));
            }
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width - 1; ++j) {
                std::shared_ptr<Spring> s = std::make_shared<Spring>(nodes[i * width + j], nodes[i * width + j + 1],
                                                                     100);
                s->shader = spring_shader;
                springs.push_back(std::move(s));
            }
        }
        for (int i = 0; i < height - 1; ++i) {
            for (int j = 0; j < width; ++j) {
                std::shared_ptr<Spring> s = std::make_shared<Spring>(nodes[i * width + j], nodes[(i + 1) * width + j],
                                                                     100);
                s->shader = spring_shader;
                springs.push_back(std::move(s));
            }
        }
    }

    void draw(const Eigen::Matrix4f &view, Eigen::Matrix4f projection, Eigen::Matrix4f ortho, float delta_time) {
        for (auto &node : nodes) {
            node->set_vp(view, projection);
            node->set_ortho(ortho);
            node->draw();
        }
        for (auto &spring : springs) {
            spring->set_vp(view, projection);
            spring->set_ortho(ortho);
            spring->draw();
        }
    }

    std::vector<std::shared_ptr<Node> > nodes;
    std::vector<std::shared_ptr<Spring> > springs;
};

#endif //ASSIGNMENTFRAMEWORK_MASSSPRINGTEMPLATE_H
