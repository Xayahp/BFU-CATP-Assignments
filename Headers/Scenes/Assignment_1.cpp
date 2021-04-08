#include "Assignment_1.h"

void Assignment_1::init() {}

void Assignment_1::load() {

    /* Step 1: load shaders */
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_2D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_2D.frag";
    std::string v_path_tex = SHADER_DIRECTORY + "/" + "default_shader_2D_texture.vert";
    std::string f_path_tex = SHADER_DIRECTORY + "/" + "default_shader_2D_texture.frag";
    std::shared_ptr<Shader> default_shader_2D = std::make_shared<Shader>(v_path, f_path);
    std::shared_ptr<Shader> default_shader_2D_texture = std::make_shared<Shader>(v_path_tex, f_path_tex);


    /* Step 2: define objects */
    auto brick_accurate = std::make_unique<Brick>(30, 70);
    brick_accurate->shader = default_shader_2D;
    brick_accurate->set_position(200, 100, 0);

    auto brick_forward_euler = std::make_unique<Brick>(30, 70);
    brick_forward_euler->shader = default_shader_2D;
    brick_forward_euler->set_position(400, 100, 0);

    auto brick_semi_euler = std::make_unique<Brick>(30, 70);
    brick_semi_euler->shader = default_shader_2D;
    brick_semi_euler->set_position(600, 100, 0);

    auto base_line = std::make_unique<Wall>(600);
    base_line->shader = default_shader_2D;
    base_line->set_position(400, brick_accurate->x.y() + brick_accurate->height / 2.f, 0);
    base_line->set_color(0xea5550);

    auto brick_ground = std::make_unique<Wall>(800);
    brick_ground->shader = default_shader_2D;
    brick_ground->set_position(400, 550, 0);
    brick_ground->fix();

    auto brick_left = std::make_unique<Wall>(800);
    brick_left->shader = default_shader_2D;
    brick_left->set_position(50, 300, 0);
    brick_left->rotate(0, 0, 90);
    brick_left->fix();

    auto brick_top = std::make_unique<Wall>(800);
    brick_top->shader = default_shader_2D;
    brick_top->set_position(400, 50, 0);
    brick_top->fix();

    auto brick_right = std::make_unique<Wall>(800);
    brick_right->shader = default_shader_2D;
    brick_right->set_position(750, 300, 0);
    brick_right->rotate(0, 0, -90);
    brick_right->fix();

    /* Step 3: add objects into scene */
    // use std::move() to make the point unique
    objects.push_back(std::move(brick_accurate)); // objects[0]
    objects.push_back(std::move(brick_forward_euler)); // objects[1]
    objects.push_back(std::move(brick_semi_euler)); // objects[2]
//    objects.push_back(std::move(base_line)); // objects[3]
    objects.push_back(std::move(brick_ground)); // objects[4]
    objects.push_back(std::move(brick_left)); // objects[5]
    objects.push_back(std::move(brick_top)); // objects[6]
    objects.push_back(std::move(brick_right)); // objects[7]
}

void Assignment_1::update() {}

void Assignment_1::render(float delta_time) {
    this->total_time_elapsed += delta_time;
    for (auto &obj : objects) {
        if (this->scene_state != STATE_PAUSE) {
            EulerSolver::ForwardEuler2D(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Assignment_1::terminate() {

}
