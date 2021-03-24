// PREREQUISITE
#include "glad/glad.h" // [ Please ensure glad is included ahead of GLFW ]
#include "GLFW/glfw3.h"
// USER HEADERS
#include "Scene.h"
#include "World.h"
#include "config.h"
// SYSTEM HEADERS
#include <iostream>
#include <memory>

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS 1
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

static void CreateUI(GLFWwindow* window, const char* glslVersion = NULL)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    bool success;
    success = ImGui_ImplGlfw_InitForOpenGL(window, false);
    if (!success)
    {
        printf("ImGui_ImplGlfw_InitForOpenGL failed\n");
        assert(false);
    }

    success = ImGui_ImplOpenGL3_Init(glslVersion);
    if (!success)
    {
        printf("ImGui_ImplOpenGL3_Init failed\n");
        assert(false);
    }
/*
    // Search for font file
    const char* fontPath1 = "data/droid_sans.ttf";
    const char* fontPath2 = "../data/droid_sans.ttf";
    const char* fontPath = nullptr;
    FILE* file1 = fopen(fontPath1, "rb");
    FILE* file2 = fopen(fontPath2, "rb");
    if (file1)
    {
        fontPath = fontPath1;
        fclose(file1);
    }

    if (file2)
    {
        fontPath = fontPath2;
        fclose(file2);
    }

    if (fontPath)
    {
        ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 13.0f);
    }*/
}

int main(int argc, char **argv) {
#include "initializer.h"

    CreateUI(window, "#version 330");

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Scene scene;
    World2D world(Eigen::Vector2f(0, -0.000098f));

    auto rect = std::make_unique<Rectangle>(Eigen::Vector2f(-0.5f, 0.f), 0.1f, 0.1f);
    rect->set_color(0x4d4398).set_draw_mode(LINES);
    auto floor = std::make_unique<Rectangle>(Eigen::Vector2f(0.f, -.9f), 1.f, .01f);
    floor->set_color(0x4d4398).set_draw_mode(TRIANGLES).fix();
    auto l1 = std::make_unique<Line>(Eigen::Vector2f(-.8f, 0.f), Eigen::Vector2f(.8f, 0.f));
    l1->set_color(0x4d4398).set_draw_mode(POINTS);

    world.objects.push_back(std::move(rect));
    world.objects.push_back(std::move(floor));
    world.objects.push_back(std::move(l1));



/* ------------------------------ RENDERING LOOP START ------------------------------ */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(window);

        if (!mouse_input_points.empty()) {
            for (Eigen::Vector2f &p : mouse_input_points) {
                auto temp = std::make_unique<Rectangle>(p, 0.1f, 0.1f);
                temp->set_color(0x4d4398).set_draw_mode(LINES);
                world.objects.push_back(std::move(temp));
            }
            mouse_input_points.clear();
        }

//        world.solve();
//        scene.render(world);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();




        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT + GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//        scene.draw();

        glfwSwapBuffers(window);
    }
/* ------------------------------ RENDERING LOOP END ------------------------------ */






    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}