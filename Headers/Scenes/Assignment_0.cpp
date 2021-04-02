#include "Assignment_0.h"

void Assignment_0::init() {

}

void Assignment_0::load() {

    /* Step 1: load shaders */
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_2D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_2D.frag";
    std::string v_path_tex = SHADER_DIRECTORY + "/" + "default_shader_2D_texture.vert";
    std::string f_path_tex = SHADER_DIRECTORY + "/" + "default_shader_2D_texture.frag";
    std::shared_ptr<Shader> default_shader_2D = std::make_shared<Shader>(v_path, f_path);
    std::shared_ptr<Shader> default_shader_2D_texture = std::make_shared<Shader>(v_path_tex, f_path_tex);


    /* Step 2: define objects */
    auto brick = std::make_unique<Brick>(100, 50); // 1. new object
    brick->shader = default_shader_2D_texture; // 2. set shader
    brick->set_position(Eigen::Vector3f(400, 550, 0)); // 3. set position
    brick->rotate(0,0,-45);
//    brick->set_color(0xcab8d9);// 4. set color, optional
    brick->load_texture("tex1.jpg");
    brick->as_triangle(); // 5. convert 2D shape to triangular mesh, optional
    brick->set_draw_mode(FILL); // 6. set draw mode {POINT_2D, LINE, POINT, POLYGON, FILL}, optional
//    brick->is_fixed = true; // 7. fix position, optional



    /* Step 3: add objects into scene */
    objects.push_back(std::move(brick)); // use std::move() to make the point unique
}

void Assignment_0::update() {

}

void Assignment_0::render(float delta_time) {
    for (auto &obj : objects) {
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
}

void Assignment_0::terminate() {

}
