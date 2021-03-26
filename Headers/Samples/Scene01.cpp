#include "Scene01.h"


Scene01::~Scene01() {
    for (std::unique_ptr<BasicPhysicalObjects> &obj : objects)
        obj.reset(nullptr);
}

void Scene01::init() {}

void Scene01::load() {


    auto plane = std::make_unique<Plane>();
    plane->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto sphere = std::make_unique<Sphere>();
    sphere->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto cube = std::make_unique<Cube>();
    cube->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto cylinder = std::make_unique<Cylinder>();
    cylinder->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto cone = std::make_unique<Cone>();
    cone->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto corner_ball = std::make_unique<Corner_ball>();
    corner_ball->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    auto torus = std::make_unique<Torus>();
    torus->load_shader("default_shader_3D.vert", "default_shader_3D.frag");

    sphere->set_draw_mode(POLYGON);

    auto ground = std::make_unique<Ground>(30.f, 30.f);
    ground->load_shader("Ground_default.vert", "Ground_default.frag");
    ground->set_position(Eigen::Vector3f(0.f, -.1f, 0.f));
    ground->set_draw_mode(FILL);
    ground->load_texture("tex1.jpg");


    auto ball = std::make_unique<Ball>(0.2);
    ball->load_shader("default_shader_3D.vert", "default_shader_3D.frag");
    ball->set_position(Eigen::Vector3f(0.f, 10.f, 0.f));
    ball->set_draw_mode(POLYGON);

    auto brick = std::make_unique<Brick>(0.2, 0.2);
    brick->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    brick->set_position(Eigen::Vector3f(-0.5f, 1.f, 0.f));


    auto pizza = std::make_unique<Pizza>(0.2);
    pizza->load_shader("default_shader_2D.vert", "default_shader_2D.frag");
    pizza->set_position(Eigen::Vector3f(0.5f, 1.f, 0.f));

//    this->objects.push_back(std::move(ground));
//    this->objects.push_back(std::move(ball));
    this->objects.push_back(std::move(brick));
    this->objects.push_back(std::move(pizza));
}

void Scene01::update() {}

void Scene01::render() {

    for (auto &obj : objects) {
        obj->set_vp(view, projection);
        obj->draw();
    }
}

void Scene01::terminate() {}
