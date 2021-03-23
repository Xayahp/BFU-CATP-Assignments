// PREREQUISITE
#include "glad/glad.h" // [ Please ensure glad is included ahead of GLFW ]
#include "GLFW/glfw3.h"
// USER HEADERS
#include "Scene.h"
#include "config.h"
// SYSTEM HEADERS
#include <iostream>


int main(int argc, char** argv) {
#include "initializer.h"

    Rectangle rect1(Eigen::Vector2f(0.f,0.f), 0.1f, 0.1f);


    Rectangle rect2(Eigen::Vector2f(0.5f,0.f), 0.1f, 0.1f);

    Rectangle rect3(Eigen::Vector2f(-0.5f,0.f), 0.1f, 0.1f);

    Scene scene;

    scene.eat(rect1, LINES);
    scene.eat(rect2, TRIANGLES);
    scene.eat(rect3, LINES);



/* ------------------------------ RENDERING LOOP START ------------------------------ */
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT + GL_DEPTH_BUFFER_BIT);

//        draw(shader, VAO);


//        if(!printed && !mouse_input_points.empty()) {
//            printed = true;
//            std::cout << glm::to_string(mouse_input_points.back()) << std::endl;
//            glm::vec2 new_point = mouse_input_points.back();
//            mouse_input_points.emplace_back(glm::vec3((new_point.x-(WIDTH/2.f))/(WIDTH/2.f), -(new_point.y - (HEIGHT/2.f))/(HEIGHT/2.f), 0.f));
//        }

        scene.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
/* ------------------------------ RENDERING LOOP END ------------------------------ */










    glfwTerminate();
    return 0;
}