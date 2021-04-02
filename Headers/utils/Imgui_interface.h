#ifndef ASSIGNMENT_FRAMEWORK_IMGUI_INTERFACE_H
#define ASSIGNMENT_FRAMEWORK_IMGUI_INTERFACE_H

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS 1

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace IMGUI_INTERFACE {

    static void IMGUI_CREATE(GLFWwindow *&window, const char *glslVersion = NULL) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        bool success;
        success = ImGui_ImplGlfw_InitForOpenGL(window, false);
        if (!success) {
            printf("ImGui_ImplGlfw_InitForOpenGL failed\n");
            assert(false);
        }

        success = ImGui_ImplOpenGL3_Init(glslVersion);
        if (!success) {
            printf("ImGui_ImplOpenGL3_Init failed\n");
            assert(false);
        }

        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui::StyleColorsDark();
    }

    static void hello_imgui() {

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Frames per second");

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    static void IMGUI_SHUTDOWN() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}


#endif //ASSIGNMENT0_IMGUI_INTERFACE_H
