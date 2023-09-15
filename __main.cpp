    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <iostream>
    #include <imgui_impl_sdl2.h>
    #include <imgui_impl_opengl3.h>
    #include <gl/gl.h>

    void SetGlobalHook();
    void RemoveGlobalHook();

    static int t_button_count = 0;

    int main(int argc, char* argv[]) {  
        SDL_SetMainReady();
        SetGlobalHook();

        // 初始化SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)  {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        SDL_Window* window = SDL_CreateWindow("Controller Input Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_KEYBOARD_GRABBED);

        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        
        // 初始化imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        // 初始化imgui的SDL2和OpenGL3渲染器
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init();

        std::cout<<"program start."<<std::endl;

        bool quit = false;
        bool pressed = false;

        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_WINDOWEVENT:
                        if(e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window))
                            quit = true;
                    case SDL_KEYDOWN:
                        if (e.key.keysym.scancode == SDL_SCANCODE_T && e.key.repeat == 0) {
                            t_button_count++;
                            pressed = true;
                        }
                        break;
                    case SDL_KEYUP:
                        if (e.key.keysym.scancode == SDL_SCANCODE_T)
                            pressed = false;
                        break;
                    default:
                        // 将事件传递给imgui
                        ImGui_ImplSDL2_ProcessEvent(&e);
                        break;
                }

            }

            // 开始imgui帧
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();  

            // imgui主循环
            ImGui::Begin("Controller Input Display");

            // 示例：显示键盘按键T的状态
            if (pressed) 
                ImGui::TextColored(ImVec4(1,0,0,1), "T Button: Pressed");
            else 
                ImGui::Text("T Button: Not Pressed");

            // 在UI中显示计数
            ImGui::Text("T Button Count: %d", t_button_count);

            // ... 为其他按键重复此过程
            ImGui::End();
            
            // 清除背景
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // 渲染imgui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(window);
        }

        // 清理imgui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        // 清理SDL代码 ..
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();

        RemoveGlobalHook();

        return 0;
    }
