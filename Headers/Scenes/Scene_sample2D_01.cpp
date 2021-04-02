#include "Scene_sample2D_01.h"

void Scene_sample2D_01::init() {

}

void Scene_sample2D_01::load() {

    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_2D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_2D.frag";
    std::shared_ptr<Shader> default_shader_2D = std::make_shared<Shader>(v_path, f_path);

    auto ground = std::make_unique<Brick>(800, 50);
    ground->shader = default_shader_2D;
    ground->set_draw_mode(POLYGON);
    ground->set_position(Eigen::Vector3f(400, 550, 0));
    ground->as_triangle();
    ground->is_fixed = true;

    auto brick = std::make_unique<Brick>(20, 50);
    brick->shader = default_shader_2D;
    brick->set_position(Eigen::Vector3f(400, 300, 0.f));

    auto pizza = std::make_unique<Pizza>(25);
    pizza->shader = default_shader_2D;
    pizza->set_position(Eigen::Vector3f(600, 300, 0.f));
    pizza->v = Eigen::Vector3f(-100, 0, 0);

    auto wall = std::make_unique<Wall>(800);
    wall->shader = default_shader_2D;
    wall->set_position(Eigen::Vector3f(400, 575, 0.f));
    wall->is_fixed = true;


    this->objects.push_back(std::move(ground));
    this->objects.push_back(std::move(brick));
    this->objects.push_back(std::move(pizza));
//    this->objects.push_back(std::move(wall));


//    Fireworks2D fireworks;
//
//    for (auto &p : fireworks.pizzas) {
//        p->shader = default_shader_2D;
//        p->as_triangle();
//        p->set_draw_mode(FILL);
//        this->objects.push_back(std::move(p));
//    }
}

void Scene_sample2D_01::update() {

}

void Scene_sample2D_01::render(float delta_time) {
    for (auto &obj : objects) {
        if (scene_state != STATE_PAUSE) {
            EulerSolver::ForwardEuler(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Scene_sample2D_01::terminate() {

}
