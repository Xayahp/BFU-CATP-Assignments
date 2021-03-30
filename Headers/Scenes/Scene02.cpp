#include "Scene02.h"

void Scene02::init() {

}

void Scene02::load() {

    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_2D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_2D.frag";

    std::shared_ptr<Shader> default_shader_2D = std::make_shared<Shader>(v_path, f_path);

    auto ground = std::make_unique<Brick>(800, 50);
//    ground->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    ground->shader = default_shader_2D;
    ground->set_draw_mode(POLYGON);
    ground->set_position(Eigen::Vector3f(400, 550, 0));
    ground->as_triangle();
    ground->is_fixed = true;

    auto brick = std::make_unique<Brick>(20, 50);
    brick->shader = default_shader_2D;
//    brick->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    brick->set_position(Eigen::Vector3f(400, 300, 0.f));

    auto pizza = std::make_unique<Pizza>(25);
    pizza->shader = default_shader_2D;
//    pizza->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    pizza->set_position(Eigen::Vector3f(600, 200, 0.f));
    pizza->v = Eigen::Vector3f(-100, 0, 0);

    auto wall = std::make_unique<Wall>(800);
    wall->shader = default_shader_2D;
    wall->set_position(Eigen::Vector3f(400, 575, 0.f));
    wall->is_fixed = true;

    auto line100 = std::make_unique<Wall>(800);
    line100->shader = default_shader_2D;
    line100->set_position(Eigen::Vector3f(400, 100, 0.f));
    line100->is_fixed = true;

    auto line200 = std::make_unique<Wall>(800);
    line200->shader = default_shader_2D;
    line200->set_position(Eigen::Vector3f(400, 200, 0.f));
    line200->is_fixed = true;

    auto line300 = std::make_unique<Wall>(800);
    line300->shader = default_shader_2D;
    line300->set_position(Eigen::Vector3f(400, 300, 0.f));
    line300->is_fixed = true;

    auto line400 = std::make_unique<Wall>(800);
    line400->shader = default_shader_2D;
    line400->set_position(Eigen::Vector3f(400, 400, 0.f));
    line400->is_fixed = true;

    auto line500 = std::make_unique<Wall>(800);
    line500->shader = default_shader_2D;
    line500->set_position(Eigen::Vector3f(400, 500, 0.f));
    line500->is_fixed = true;


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

void Scene02::update() {

}

void Scene02::render(float delta_time) {
    for (auto &obj : objects) {
        if (scene_state != STATE_PAUSE) {
//            EulerSolver::ForwardEuler(obj, objects, delta_time);
            EulerSolver::SemiBackwardEuler(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Scene02::terminate() {

}
