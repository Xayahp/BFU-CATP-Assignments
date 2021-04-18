#include "Assignment_2.h"

void Assignment_2::init() {

}

void Assignment_2::load() {
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_3D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_3D.frag";

    std::shared_ptr<Shader> default_shader_3D = std::make_shared<Shader>(v_path, f_path);

    auto ball = std::make_unique<Ball>(0.5);
    ball->shader = default_shader_3D;
    ball->set_position(0, 6.5, 0);
    ball->DRAW_AABB = true; // set this to enable AABB display

    auto box = std::make_unique<Box>(1,1,1);
    box->shader = default_shader_3D;
    box->set_position(0, 9.5, 0);
    box->DRAW_AABB = true;

    auto ground = std::make_unique<Box>(20, 0.2, 20);
    ground->shader = default_shader_3D;
    ground->set_position(Eigen::Vector3f(0, -0.1, 0));
    ground->fix();

    auto ceil = std::make_unique<Box>(20, 0.2, 20);
    ceil->shader = default_shader_3D;
    ceil->set_position(Eigen::Vector3f(0, 10.1, 0));
    ceil->fix();

    objects.push_back(std::move(ball));
    objects.push_back(std::move(box));
    objects.push_back(std::move(ground));
    objects.push_back(std::move(ceil));
}

void Assignment_2::update() {

}

void Assignment_2::render(float delta_time) {
    for (auto &obj : objects) {
        if (scene_state != STATE_PAUSE) {
            EulerSolver::ForwardEuler3D(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Assignment_2::terminate() {

}
