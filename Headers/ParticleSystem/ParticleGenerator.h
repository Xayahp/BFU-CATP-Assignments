#ifndef ASSIGNMENT_FRAMEWORK_PARTICLESYSTEM_H
#define ASSIGNMENT_FRAMEWORK_PARTICLESYSTEM_H

#include "Eigen/Eigen"

#include <utility>
#include <vector>

class Particle {
public:
    Particle(Eigen::Vector3f _initial_x, Eigen::Vector3f _initial_v = Eigen::Vector3f(0, 50, 0),
             float _mass = 1, float _lifetime = 10) : initial_x(std::move(_initial_x)),
                                                      initial_v(std::move(_initial_v)),
                                                      mass(_mass), lifetime(_lifetime) {}

    Eigen::Vector3f initial_x;
    Eigen::Vector3f initial_v;
    float mass;
    float lifetime;
};


class PointParticleGenerator {
public:
    PointParticleGenerator(Eigen::Vector3f _point_position = Eigen::Vector3f(400, 300, 0)) : point_position(
            std::move(_point_position)) {}

    Particle rand_one_time() {
        direction = Eigen::Vector3f(0, 0, 0);
        direction.x() += sign * (float) (rand() % (200));
        direction.y() -= (float) (rand() % (1000));
        sign = -sign;
        return Particle(point_position, direction);
    }

    Eigen::Vector3f point_position;
    Eigen::Vector3f direction;
    float radius;
    float sign = 1.f;
};


#endif //ASSIGNMENT_FRAMEWORK_PARTICLESYSTEM_H
