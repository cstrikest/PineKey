#define DEBUG

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <iostream>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

using namespace ImGui;

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); 
    glfwWindowHint(GLFW_DECORATED, GL_FALSE); 
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE); 

    // 创建图形上下文
    GLFWwindow* window = glfwCreateWindow(1, 1, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // ImGui上下文
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // 风格
    StyleColorsDark();

    // 平台、渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 加载字体
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // 全局变量
    bool show_main_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
    static int key_count[9] = {0,0,0,0,0,0,0,0,0}; // 1~7号键按键 皿A 皿B 计数

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // 新帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();

        // 全局变量
        static float f = 0.0f;
        static int counter = 0;
        //ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoSavedSettings;
        /*
        {
            if(!Begin("PineKey", &show_main_window, ImGuiWindowFlags_NoSavedSettings)){
                End();
                break;                          // Create a window called "Hello, world!" and append into it.
            }
            Text("This is some useful text.");               // Display some text (you can use a format strings too)
            Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            Checkbox("Another Window", &show_another_window);

            SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            SameLine();
            Text("counter = %d", counter);

            Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            End();    
        }
        */

        // 没有ini则以此位置大小新建窗口
#ifdef DEBUG
        ShowDemoWindow(nullptr);
#endif
        const ImGuiViewport* main_viewport = GetMainViewport();
        SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 300, main_viewport->WorkPos.y + 100), ImGuiCond_FirstUseEver);
        SetNextWindowSize(ImVec2(750, 600), ImGuiCond_FirstUseEver);

        ImGuiStyle& style = GetStyle();
        ImGuiWindowFlags main_window_flags = 0 | ImGuiWindowFlags_NoResize; // 不能调整大小
        main_window_flags |= ImGuiWindowFlags_NoCollapse; // 不能折叠窗口

        // 主窗口
        {
            Begin("PineKey", &show_main_window, main_window_flags);
            static bool pressed = false;
            for (int i = 0; i < 7; i++)
            {
                if (i > 0)
                    ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4((i % 2)?0.0f:1.0f, (i % 2)?0.0f:1.0f, 1.0f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                if (pressed){
                    ImGui::Button((std::to_string(i) + std::string("111111")).c_str());
                    pressed = false;
                }
                else{
                    ImGui::Button((std::to_string(i)).c_str());
                }
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }

if (Button("test"))
{
    
}

            if (CollapsingHeader("Config"))
            {
                
            }
            if (CollapsingHeader("Help"))
            {
                PushStyleColor(ImGuiCol_Separator, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                SeparatorText("ABOUT THIS TOOL:");
                PopStyleColor();
                Text("This tool is a music game auxiliary tool that visualizes the input of keys, joysticks, and game controllers.");
                Text("Features:");
                BulletText("Real-time display of pressed keys.");
                BulletText("Count for each key count, total count, realtime and average KPS. Display of changes in average KPS.");
                BulletText("Statistics on the proportion of times each key is pressed.");
                BulletText("Calculate the average hold time for each key press.");
                Separator();
                TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Pineapple ~2023~");
            }
            
            End();
        }

        //如果窗口被关闭
        if (!show_main_window)
            break;  


        // 渲染
        {
            Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
                UpdatePlatformWindows();
                RenderPlatformWindowsDefault();
            }
            glfwSwapBuffers(window);  
        }
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}