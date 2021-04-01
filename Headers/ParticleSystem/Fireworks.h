#ifndef ASSIGNMENT_FRAMEWORK_FIREWORKS_H
#define ASSIGNMENT_FRAMEWORK_FIREWORKS_H

#include "ParticleGenerator.h"

#include "Objects2D.h"
#include "Objects3D.h"


class Fireworks2D : public PointParticleGenerator {
public:
    Fireworks2D(std::shared_ptr<Shader> shader) : PointParticleGenerator(Eigen::Vector3f(400, 300, 0)) {
        for (int i = 0; i < 100; ++i) {
            Particle p = rand_one_time();
            std::unique_ptr<Pizza> new_p = std::make_unique<Pizza>(5);
            new_p->shader = shader;

            new_p->x = p.initial_x;
            new_p->v = p.initial_v;
            new_p->m = p.mass;
            Eigen::Vector4f color((float) (rand() % (256)), (float) (rand() % (256)), (float) (rand() % (256)), 1.f - (float) (rand() % (256)) / 512.f);
            new_p->set_color(color);

            new_p->as_triangle();

            new_p->as_triangle();
            new_p->set_draw_mode(FILL);

            pizzas.push_back(std::move(new_p));
        }
    }

public:
    std::vector<std::unique_ptr<BasicPhysicalObjects>> pizzas;
};

#endif //ASSIGNMENT_FRAMEWORK_FIREWORKS_H
