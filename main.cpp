#include "main.h"

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
    static float f = 0.0f;
    static int counter = 0; // fps计算
    
    bool show_main_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
    static int iidx_button_count[8] = {5035,4926,4427,4414,4743,4526,4196,588};
    static float _histogram_values[8] = {};
    static bool iidx_key_pressed_situation[8] = {0,0,0,0,0,0,0,0};

    // TODO: 需要加载的配置
    static bool enabled_count_histogram = true;
    static bool enabled_frame_window_histogram = true;
    static bool enabled_all_kps = true;
    static bool enabled_spec_kps = true;
    static int iidx_button_layout_style = 1; // 显示按键布局 0一条线 1iidx默认布局 2平铺
    static bool iidx_button_default_color_style = 1; // 显示按键颜色 0单色 1默认红蓝 
    static int iidx_play_position = 0; // iidx游玩位置 0 1p 1 2p
    static ImVec2 iidx_button_size(30, 60); // iidx按键长宽
    static ImVec2 iidx_scr_button_size(60, 70); // iidx皿按键长宽
    static int iidx_button_dummy_size = 15; // iidx默认布局横向填充空白大小
    static bool iidx_button_show_num = true;
    static int key_count[8] = {0,0,0,0,0,0,0,0}; // 1~7号键按键 皿A 皿B 计数
    static int key_config[8] = {0x55,0,0,0,0,0,0,0};
    

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

        // window prop.
        const ImGuiViewport* main_viewport = GetMainViewport();
        SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 300, main_viewport->WorkPos.y + 100), ImGuiCond_FirstUseEver);
        //SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);
        SetNextWindowSizeConstraints(ImVec2(500, -1), ImVec2(500, FLT_MAX));

        // style
        ImGuiStyle& style = GetStyle();
        style.WindowPadding = ImVec2(14, 2);
        style.FrameBorderSize = 3;
        style.FrameRounding = 4;
        style.GrabRounding = 1;
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextPadding = ImVec2(2, 18);

        // flag
        ImGuiWindowFlags main_window_flags = 0;
        //main_window_flags |= ImGuiWindowFlags_NoResize; // 不能调整大小
        main_window_flags |= ImGuiWindowFlags_NoCollapse; // 不能折叠窗口
        main_window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

        // 主窗口 
        {
            Begin("PineKey", &show_main_window, main_window_flags);
            
            SeparatorText("Key overlay");
            Dummy(ImVec2(20, 0));
            SameLine();
            BeginGroup();
            switch (iidx_button_layout_style){
                case 0: //line style
                    // 1P皿
                    if (!iidx_play_position){
                        PushStyleColor(ImGuiCol_Button, ImVec4(1.0f,0.0f, 0.0f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        Button("S", iidx_button_size); // 字体
                        PopStyleColor(3);
                        SameLine();
                    }
                    for (int i = 0; i < 7; i++){
                        bool is_upper_button = i % 2;
                        PushID(i);
                        if (iidx_button_default_color_style){ // 默认红蓝
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button?0.0f:1.0f, is_upper_button?0.0f:1.0f, 1.0f, 0.3f));
                            PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                            PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                            Button((std::to_string(i + 1)).c_str(), iidx_button_size);
                            PopStyleColor(3);
                        }
                        else{ // 单色
                            Button((std::to_string(i + 1)).c_str(), iidx_button_size);
                        }
                        PopID();
                        SameLine();
                    }

                    // 2P皿
                    if (iidx_play_position){
                        PushStyleColor(ImGuiCol_Button, ImVec4(1.0f,0.0f, 0.0f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        Button("S", iidx_button_size);
                        PopStyleColor(3);
                    }
                    else{
                        NewLine();
                    }
                    
                break;

                case 1: //IIDX controller style

                    // 1P 皿
                    if (!iidx_play_position){
                        BeginGroup();
                        Dummy(ImVec2(1, iidx_button_dummy_size - iidx_scr_button_size.y));
                        PushStyleColor(ImGuiCol_Button, ImVec4(1.0f,0.0f, 0.0f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        Button("S", iidx_scr_button_size);
                        PopStyleColor(3);
                        EndGroup();
                        SameLine();
                    }

                    for (int i = 0; i < 7; i++){
                        bool is_upper_button = i % 2;
                        BeginGroup();
                        PushID(i);
                        if (!is_upper_button) Dummy(ImVec2(1, iidx_button_dummy_size));
                        if (iidx_button_default_color_style){ // 默认红蓝
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button?0.0f:1.0f, is_upper_button?0.0f:1.0f, 1.0f, 0.3f));
                            PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                            PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.1f, 0.1f, 0.8f));
                            Button((std::to_string(i + 1)).c_str(), iidx_button_size);
                            PopStyleColor(3);
                        }
                        else{ // 单色
                            Button((std::to_string(i + 1)).c_str(), iidx_button_size);
                        }
                        PopID();
                        EndGroup();
                        SameLine();
                    }

                    // 2P皿
                    if (iidx_play_position){
                        BeginGroup();
                        Dummy(ImVec2(1, iidx_button_dummy_size - iidx_scr_button_size.y));
                        PushStyleColor(ImGuiCol_Button, ImVec4(1.0f,0.0f, 0.0f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f,0.0f, 0.0f, 0.8f));
                        Button("S", iidx_scr_button_size);
                        PopStyleColor(3);
                        EndGroup();
                    }
                    else{
                        NewLine();
                    }
                break;
                case 2: //flat style
                break;
            }
            
            EndGroup();

            // 按键次数柱状图
            SeparatorText("Key count histogram");
            if (enabled_count_histogram){
                int max = 0;
                for (int i = 0; i<8;i++){
                    _histogram_values[i] = (float)iidx_button_count[i];
                    if (iidx_button_count[i]>max) max = iidx_button_count[i];
                }
                PlotHistogram("##values", _histogram_values, 8, 0, NULL, 0.0f, (float)max, ImVec2(300, 200));
            }
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            
            // 底部下拉菜单
            if (CollapsingHeader("Config"))
            {
                if (TreeNode("Button style")){
                    RadioButton("line style", &iidx_button_layout_style, 0); SameLine();
                    RadioButton("IIDX controller style", &iidx_button_layout_style, 1); SameLine();
                    BeginDisabled();
                    RadioButton("flat style", &iidx_button_layout_style, 2);EndDisabled();
                    SameLine();
                    HelpMarker("Not supported yet.");

                    RadioButton("1P", &iidx_play_position, 0);
                    SameLine();
                    RadioButton("2P", &iidx_play_position, 1);

                    Checkbox("default button color", &iidx_button_default_color_style);
                    SameLine();
                    //Dummy(ImVec2(150,20));
                    Checkbox("show number on keys", &iidx_button_show_num);
                    SameLine();
                    PushItemWidth(-130);
                    if (Button("set default", ImVec2(100, 20))){
                        iidx_play_position = 0;
                        iidx_button_layout_style = 1;
                        iidx_button_default_color_style = 1;
                        iidx_button_size.x = 30;
                        iidx_button_size.y = 60;
                        iidx_scr_button_size.x = 60;
                        iidx_scr_button_size.y = 70;
                        iidx_button_dummy_size = 15;
                    }
                    TreePop();
                }

                if (TreeNode("Button size & padding")){
                    int _iidx_button_size[2] = {(int)iidx_button_size.x, (int)iidx_button_size.y};
                    int _iidx_scr_button_size[2] = {(int)iidx_scr_button_size.x, (int)iidx_scr_button_size.y};
                    SliderInt2("button size", _iidx_button_size, 10, 45);
                    if (iidx_button_layout_style == 0) {
                        BeginDisabled();
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &iidx_button_dummy_size, 0, (int)iidx_button_size.y);
                        EndDisabled();
                    }
                    else{
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &iidx_button_dummy_size, 0, (int)iidx_button_size.y);
                    }
                    
                    iidx_button_size.x = (float)_iidx_button_size[0];
                    iidx_button_size.y = (float)_iidx_button_size[1];
                    iidx_scr_button_size.x = (float)_iidx_scr_button_size[0];  
                    iidx_scr_button_size.y = (float)_iidx_scr_button_size[1];
                    TreePop();
                }

                if (TreeNode("histogram view")){
                    Checkbox("key count", &enabled_count_histogram);
                    Checkbox("key press frame window", &enabled_frame_window_histogram);
                }

                if (TreeNode("button input config")){
                    
                }
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
                SameLine();
                HelpMarker("QQ:384065633.\nAdd me or @ me in any group chat :)");
            }
            
            End();
        }

        //关闭窗口
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

// 全局键盘钩子回调函数
static int handle_hook_key_press(bool& _press_down, WPARAM wParam, DWORD vkcode, int* _key_config, bool* _iidx_key_press_situation)
{
    if (wParam == WM_KEYDOWN){
        for(int i = 0; i<7;i++){
            if (vkcode == *(_key_config+i)){
                _press_down = true;
                return i;
            }
        }
    }

    else if (wParam == WM_KEYUP){
        for(int i = 0; i<7;i++){
            if (vkcode == *(_key_config+i)){
                _press_down = false;
                return i;
            }
        }
    }

    return -1;
}

// 快速生成帮助悬停区
static void HelpMarker(const char* desc){
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}