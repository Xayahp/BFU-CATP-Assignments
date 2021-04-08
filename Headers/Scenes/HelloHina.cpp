#include "HelloHina.h"

void HelloHina::init() {

}

void HelloHina::load() {
    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string v_path = SHADER_DIRECTORY + "/" + "default_shader_2D.vert";
    std::string f_path = SHADER_DIRECTORY + "/" + "default_shader_2D.frag";

    std::shared_ptr<Shader> default_shader_2D = std::make_shared<Shader>(v_path, f_path);

    float basestart1 = 170.f;
    float basestart2 = 220.f;
    float baseline1 = 230.f;
    float baseline2 = 370.f;
    float char_width = 13.f;
    float char_height = 70.f;

    float H_l_width = char_width;
    float H_l_height = char_height;
    float H_m_width = char_height / 2.f;
    float H_m_height = char_width;
    float H_r_width = char_width;
    float H_r_height = char_height;

    float E_l_width = char_width;
    float E_l_height = char_height;
    float E_rt_width = char_height / 1.5f;
    float E_rt_height = char_width;
    float E_rm_width = char_height / 2.f;
    float E_rm_height = char_width;
    float E_rb_width = char_height / 1.5f;
    float E_rb_height = char_width;

    float L_l_width = char_width;
    float L_l_height = char_height;
    float L_b_width = char_height / 1.7f;
    float L_b_height = char_width;

    float O_o_radius = char_height / 2.f;
    float O_i_radius = char_height / 2.f - char_width;

    float I_width = char_width;
    float I_height = char_height;

    float ex_t_width = char_width;
    float ex_t_height = char_height / 1.4f;
    float ex_b_width = char_width;
    float ex_b_height = char_width;


    auto pizza = std::make_unique<Pizza>(10);
    pizza->shader = default_shader_2D;
    pizza->set_position(Eigen::Vector3f(100, 10, 0.f));
    pizza->v = Eigen::Vector3f(200, 0, 0);
    pizza->as_triangle();
    pizza->set_draw_mode(FILL);


    auto H_l = std::make_unique<Brick>(H_l_width, H_l_height);
    auto H_m = std::make_unique<Brick>(H_m_width, H_m_height);
    auto H_r = std::make_unique<Brick>(H_r_width, H_r_height);
    H_l->shader = default_shader_2D;
    H_m->shader = default_shader_2D;
    H_r->shader = default_shader_2D;
    H_l->set_position(Eigen::Vector3f(basestart1, baseline1, 0.f));
    H_m->set_position(Eigen::Vector3f(basestart1 + H_l_width / 2.f + H_m_width / 2.f, baseline1, 0.f));
    H_r->set_position(Eigen::Vector3f(basestart1 + H_l_width / 2.f + H_m_width + H_r_width / 2.f, baseline1, 0.f));
    H_l->is_fixed = true;
    H_m->is_fixed = true;
    H_r->is_fixed = true;
    H_l->as_triangle();
    H_m->as_triangle();
    H_r->as_triangle();
    H_l->set_draw_mode(FILL);
    H_m->set_draw_mode(FILL);
    H_r->set_draw_mode(FILL);
    H_l->set_color(0x00a1e9);
    H_m->set_color(0x00a1e9);
    H_r->set_color(0x00a1e9);

    auto E_l = std::make_unique<Brick>(E_l_width, E_l_height);
    auto E_rt = std::make_unique<Brick>(E_rt_width, E_rt_height);
    auto E_rm = std::make_unique<Brick>(E_rm_width, E_rm_height);
    auto E_rb = std::make_unique<Brick>(E_rb_width, E_rb_height);
    E_l->shader = default_shader_2D;
    E_rt->shader = default_shader_2D;
    E_rm->shader = default_shader_2D;
    E_rb->shader = default_shader_2D;
    E_l->set_position(Eigen::Vector3f(basestart1 + 100, baseline1, 0.f));
    E_rt->set_position(
            Eigen::Vector3f(basestart1 + 100 + E_l_width / 2.f + E_rt_width / 2.f,
                            baseline1 - E_l_height / 2.f + E_rt_height / 2.f,
                            0.f));
    E_rm->set_position(Eigen::Vector3f(basestart1 + 100 + E_l_width / 2.f + E_rm_width / 2.f, baseline1, 0.f));
    E_rb->set_position(
            Eigen::Vector3f(basestart1 + 100 + E_l_width / 2.f + E_rb_width / 2.f,
                            baseline1 + E_l_height / 2.f - E_rb_height / 2.f,
                            0.f));
    E_l->is_fixed = true;
    E_rt->is_fixed = true;
    E_rm->is_fixed = true;
    E_rb->is_fixed = true;
    E_l->as_triangle();
    E_rt->as_triangle();
    E_rm->as_triangle();
    E_rb->as_triangle();
    E_l->set_draw_mode(FILL);
    E_rt->set_draw_mode(FILL);
    E_rm->set_draw_mode(FILL);
    E_rb->set_draw_mode(FILL);
    E_l->set_color(0x001e43);
    E_rt->set_color(0x001e43);
    E_rm->set_color(0x001e43);
    E_rb->set_color(0x001e43);

    auto L_l = std::make_unique<Brick>(L_l_width, L_l_height);
    auto L_b = std::make_unique<Brick>(L_b_width, L_b_height);
    L_l->shader = default_shader_2D;
    L_b->shader = default_shader_2D;
    L_l->set_position(Eigen::Vector3f(basestart1 + 200, baseline1, 0.f));
    L_b->set_position(
            Eigen::Vector3f(basestart1 + 200 + L_l_width / 2.f + L_b_width / 2.f,
                            baseline1 + L_l_height / 2.f - L_b_height / 2.f,
                            0.f));
    L_l->is_fixed = true;
    L_b->is_fixed = true;
    L_l->as_triangle();
    L_b->as_triangle();
    L_l->set_draw_mode(FILL);
    L_b->set_draw_mode(FILL);
    L_l->set_color(0xea5550);
    L_b->set_color(0xea5550);

    auto L_l_2 = std::make_unique<Brick>(L_l_width, L_l_height);
    auto L_b_2 = std::make_unique<Brick>(L_b_width, L_b_height);
    L_l_2->shader = default_shader_2D;
    L_b_2->shader = default_shader_2D;
    L_l_2->set_position(Eigen::Vector3f(basestart1 + 300, baseline1, 0.f));
    L_b_2->set_position(
            Eigen::Vector3f(basestart1 + 300 + L_l_width / 2.f + L_b_width / 2.f,
                            baseline1 + L_l_height / 2.f - L_b_height / 2.f,
                            0.f));
    L_l_2->is_fixed = true;
    L_b_2->is_fixed = true;
    L_l_2->as_triangle();
    L_b_2->as_triangle();
    L_l_2->set_draw_mode(FILL);
    L_b_2->set_draw_mode(FILL);
    L_l_2->set_color(0xfdd35c);
    L_b_2->set_color(0xfdd35c);

    auto O_o = std::make_unique<Pizza>(O_o_radius);
    auto O_i = std::make_unique<Pizza>(O_i_radius);
    O_o->shader = default_shader_2D;
    O_i->shader = default_shader_2D;
    O_o->set_position(Eigen::Vector3f(basestart1 + 390 + O_o_radius, baseline1, 0.f));
    O_i->set_position(Eigen::Vector3f(basestart1 + 390 + O_o_radius, baseline1, 0.f));
    O_o->is_fixed = true;
    O_i->is_fixed = true;
    O_o->as_triangle();
    O_i->as_triangle();
    O_o->set_draw_mode(FILL);
    O_i->set_draw_mode(FILL);
    O_o->set_color(0x00a960);
    O_i->set_color(0xffffff);

    auto H_l_2 = std::make_unique<Brick>(H_l_width, H_l_height);
    auto H_m_2 = std::make_unique<Brick>(H_m_width, H_m_height);
    auto H_r_2 = std::make_unique<Brick>(H_r_width, H_r_height);
    H_l_2->shader = default_shader_2D;
    H_m_2->shader = default_shader_2D;
    H_r_2->shader = default_shader_2D;
    H_l_2->set_position(Eigen::Vector3f(basestart2, baseline2, 0.f));
    H_m_2->set_position(Eigen::Vector3f(basestart2 + H_l_width / 2.f + H_m_width / 2.f, baseline2, 0.f));
    H_r_2->set_position(Eigen::Vector3f(basestart2 + H_l_width / 2.f + H_m_width + H_r_width / 2.f, baseline2, 0.f));
    H_l_2->is_fixed = true;
    H_m_2->is_fixed = true;
    H_r_2->is_fixed = true;
    H_l_2->as_triangle();
    H_m_2->as_triangle();
    H_r_2->as_triangle();
    H_l_2->set_draw_mode(FILL);
    H_m_2->set_draw_mode(FILL);
    H_r_2->set_draw_mode(FILL);

    auto I = std::make_unique<Brick>(I_width, I_height);
    I->shader = default_shader_2D;
    I->set_position(Eigen::Vector3f(basestart2 + 100, baseline2, 0.f));
    I->is_fixed = true;
    I->as_triangle();
    I->set_draw_mode(FILL);

    auto N_l = std::make_unique<Brick>(char_width, char_height);
    auto N_m = std::make_unique<Brick>(char_width, char_height);
    auto N_r = std::make_unique<Brick>(char_width, char_height);
    N_l->shader = default_shader_2D;
    N_m->shader = default_shader_2D;
    N_r->shader = default_shader_2D;
    N_l->set_position(Eigen::Vector3f(basestart2 + 150, baseline2, 0.f));
    N_m->set_position(Eigen::Vector3f(basestart2 + 150 + 19, baseline2, 0.f));
    N_r->set_position(Eigen::Vector3f(basestart2 + 150 + 38, baseline2, 0.f));
    N_l->is_fixed = true;
    N_m->is_fixed = true;
    N_r->is_fixed = true;
    N_m->rotate(0, 0, -30);
    N_l->as_triangle();
    N_m->as_triangle();
    N_r->as_triangle();
    N_l->set_draw_mode(FILL);
    N_m->set_draw_mode(FILL);
    N_r->set_draw_mode(FILL);

    auto A_l = std::make_unique<Brick>(char_width, char_height);
    auto A_m = std::make_unique<Brick>(char_height / 3.f, char_width);
    auto A_r = std::make_unique<Brick>(char_width, char_height);
    A_l->shader = default_shader_2D;
    A_m->shader = default_shader_2D;
    A_r->shader = default_shader_2D;
    A_l->set_position(Eigen::Vector3f(basestart2 + 250, baseline2, 0.f));
    A_m->set_position(Eigen::Vector3f(basestart2 + 250 + 12, baseline2 + 10, 0.f));
    A_r->set_position(Eigen::Vector3f(basestart2 + 250 + 24, baseline2, 0.f));
    A_l->is_fixed = true;
    A_m->is_fixed = true;
    A_r->is_fixed = true;
    A_l->rotate(0, 0, 20);
    A_r->rotate(0, 0, -20);
    A_l->as_triangle();
    A_m->as_triangle();
    A_r->as_triangle();
    A_l->set_draw_mode(FILL);
    A_m->set_draw_mode(FILL);
    A_r->set_draw_mode(FILL);

    auto ex_t = std::make_unique<Brick>(char_width, char_height - 1.5 * char_width);
    auto ex_b = std::make_unique<Brick>(char_width, char_width);
    ex_t->shader = default_shader_2D;
    ex_b->shader = default_shader_2D;
    ex_t->set_position(Eigen::Vector3f(basestart2 + 350, baseline2 - char_height / 2.f + ex_t_height / 2.f, 0.f));
    ex_b->set_position(Eigen::Vector3f(basestart2 + 350, baseline2 + char_height / 2.f - ex_b_height / 2.f, 0.f));
    ex_t->is_fixed = true;
    ex_b->is_fixed = true;
    ex_t->as_triangle();
    ex_b->as_triangle();
    ex_t->set_draw_mode(FILL);
    ex_b->set_draw_mode(FILL);


    this->objects.push_back(std::move(pizza));

    this->objects.push_back(std::move(H_l));
    this->objects.push_back(std::move(H_m));
    this->objects.push_back(std::move(H_r));
    this->objects.push_back(std::move(E_l));
    this->objects.push_back(std::move(E_rt));
    this->objects.push_back(std::move(E_rm));
    this->objects.push_back(std::move(E_rb));
    this->objects.push_back(std::move(L_l));
    this->objects.push_back(std::move(L_b));
    this->objects.push_back(std::move(L_l_2));
    this->objects.push_back(std::move(L_b_2));
    this->objects.push_back(std::move(O_i));
    this->objects.push_back(std::move(O_o));
    this->objects.push_back(std::move(H_l_2));
    this->objects.push_back(std::move(H_m_2));
    this->objects.push_back(std::move(H_r_2));
    this->objects.push_back(std::move(I));
    this->objects.push_back(std::move(N_l));
    this->objects.push_back(std::move(N_m));
    this->objects.push_back(std::move(N_r));
    this->objects.push_back(std::move(A_l));
    this->objects.push_back(std::move(A_m));
    this->objects.push_back(std::move(A_r));
    this->objects.push_back(std::move(ex_t));
    this->objects.push_back(std::move(ex_b));


    auto wall_l = std::make_unique<Brick>(height, char_width);
    auto wall_t = std::make_unique<Brick>(width, char_width);
    auto wall_r = std::make_unique<Brick>(height, char_width);
    auto wall_b = std::make_unique<Brick>(width, char_width);
    wall_l->shader = default_shader_2D;
    wall_t->shader = default_shader_2D;
    wall_r->shader = default_shader_2D;
    wall_b->shader = default_shader_2D;
    wall_l->set_position(Eigen::Vector3f(100, (float) height / 2, 0));
    wall_t->set_position(Eigen::Vector3f((float) width / 2, 100, 0));
    wall_r->set_position(Eigen::Vector3f((float) width - 100, (float) height / 2, 0));
    wall_b->set_position(Eigen::Vector3f((float) width / 2, (float) height - 100, 0));
    wall_l->is_fixed = true;
    wall_t->is_fixed = true;
    wall_r->is_fixed = true;
    wall_b->is_fixed = true;
    wall_l->rotate(0, 0, 90);
    wall_r->rotate(0, 0, 90);

    this->objects.push_back(std::move(wall_l));
    this->objects.push_back(std::move(wall_t));
    this->objects.push_back(std::move(wall_r));
    this->objects.push_back(std::move(wall_b));


    fireworks = std::make_unique<Fireworks2D>(default_shader_2D);
}

void HelloHina::update() {

}

void HelloHina::render(float delta_time) {
    for (auto &obj : objects) {
        if (scene_state != STATE_PAUSE) {
//            EulerSolver::ForwardEuler(obj, objects, delta_time);
        }
        obj->set_vp(view, projection);
        obj->set_ortho(ortho);
        obj->draw();
    }
    for (auto &firework : fireworks->pizzas) {
        if (scene_state != STATE_PAUSE) {
//            EulerSolver::ForwardEuler(firework, objects, delta_time);
        }
        firework->set_vp(view, projection);
        firework->set_ortho(ortho);
        firework->draw();
    }
}

void HelloHina::terminate() {

}