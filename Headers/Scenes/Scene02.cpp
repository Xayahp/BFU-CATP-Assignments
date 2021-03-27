#include "Scene02.h"

void Scene02::init() {

}

void Scene02::load() {

    auto ground = std::make_unique<Brick>(800, 50);
    ground->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    ground->set_draw_mode(POLYGON);
    ground->set_position(Eigen::Vector3f(400, 595, 0));
    ground->as_triangle();
    ground->is_fixed = true;

    auto brick = std::make_unique<Brick>(20, 50);
    brick->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    brick->set_position(Eigen::Vector3f(400, 300, 0.f));

    auto pizza = std::make_unique<Pizza>(25);
    pizza->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    pizza->set_position(Eigen::Vector3f(600, 200, 0.f));
    pizza->v = Eigen::Vector3f(-100, 0, 0);

    auto wall = std::make_unique<Wall>(800);
    wall->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    wall->set_position(Eigen::Vector3f(400, 575, 0.f));
    wall->is_fixed = true;


//    this->objects.push_back(std::move(ground));
    this->objects.push_back(std::move(brick));
    this->objects.push_back(std::move(pizza));
    this->objects.push_back(std::move(wall));
}

void Scene02::update() {

}

void Scene02::render(float delta_time) {
    for (auto &obj : objects) {
        if (scene_state != STATE_PAUSE) {
//            EluerSolver::ForwardEuler(obj, objects, delta_time);
            EluerSolver::SemiBackwardEuler(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Scene02::terminate() {

}
