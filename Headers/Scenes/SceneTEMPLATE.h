#ifndef ASSIGNMENT_FRAMEWORK_SCENE_H
#define ASSIGNMENT_FRAMEWORK_SCENE_H

#include "Eigen/Eigen"

#include "Objects2D.h"
#include "Objects3D.h"

#include "EulerSolver.h"

#include <vector>

enum SCENE_STATE {
    STATE_ACTIVE,
    STATE_PAUSE
};

class SceneTEMPLATE {
public:
    SceneTEMPLATE(unsigned int width, unsigned int height, bool is_2D = false) : width(width), height(height) {
        ortho = Eigen::Matrix4f::Identity();
        if (is_2D) {
            ortho(0, 0) = 2.f / float(width);
            ortho(1, 1) = -2.f / float(height);
            ortho(2, 2) = -1;
            ortho(0, 3) = -1;
            ortho(1, 3) = 1;
        }
    }

    virtual ~SceneTEMPLATE() = default;

    virtual void init() = 0;

    virtual void load() = 0;

    virtual void update() = 0;

    virtual void render(float delta_time) = 0;

    virtual void terminate() = 0;

public:
    SCENE_STATE scene_state;

    unsigned int width;
    unsigned int height;

    std::vector<std::unique_ptr<BasicPhysicalObjects>> objects;
    std::vector<std::unique_ptr<BasicPhysicalObjects>> init_objects;

    Eigen::Matrix4f view, projection, ortho;
};

#endif //ASSIGNMENTFRAMEWORK_SCENE_H
