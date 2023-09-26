//#define DEBUG

#include "util.h"

using namespace ImGui;

static void handle_hook_key_press(WPARAM, DWORD);
static void HelpMarker(const char *desc);
LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);
void SetGlobalHook();
void RemoveGlobalHook();

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char **)
{
    SetGlobalHook();

    try
    {
        ini_getl("Key overlay", "val", -1, ini_file);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);

    // 创建图形上下文
    GLFWwindow *window = glfwCreateWindow(1, 1, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 垂直同步

    // ImGui上下文
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO &io = GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // 小字体test
    {
        // Get the default font's config
        ImFontConfig config;
        config.OversampleH = 3;
        config.OversampleV = 1;

        // Add a smaller version of the default font (scale down to 0.8 times)
        io.Fonts->AddFontDefault();
        ImFont *my_small_font = io.Fonts->AddFontDefault(&config);
        my_small_font->Scale = 0.8f;

        // Build the font atlas
        unsigned char *pixels;
        int width, height;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    }

    // 风格
    StyleColorsDark();

    // 平台、渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 抓取事件处理
        glfwPollEvents();

        // 新帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();

#ifdef DEBUG
        ShowDemoWindow(nullptr);
#endif

        // 窗口属性
        const ImGuiViewport *main_viewport = GetMainViewport();
        SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 300, main_viewport->WorkPos.y + 100), ImGuiCond_FirstUseEver);
        SetNextWindowSize(ImVec2(500, -1), ImGuiCond_FirstUseEver);
        // SetNextWindowSizeConstraints(ImVec2(450, -1), ImVec2(450, FLT_MAX));

        // style
        ImGuiStyle &style = GetStyle();
        style.WindowPadding = ImVec2(14, 2);
        style.FrameBorderSize = 3;
        style.FrameRounding = 4;
        style.GrabRounding = 1;
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextPadding = ImVec2(2, 18);

        // 窗口flag
        ImGuiWindowFlags main_window_flags = 0;
        // main_window_flags |= ImGuiWindowFlags_NoResize; // 不能调整大小
        main_window_flags |= ImGuiWindowFlags_NoCollapse; // 不能折叠窗口
        main_window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

        // 主窗口
        {
            // 计算按键按下窗口时间
            for (int i = 0; i < 8; i++)
            {
                if (is_key_pressed[i])
                    key_pressed_time[i] += 1;
                else if (key_pressed_time[i] != 0)
                    key_pressed_time[i] = 0;
            }

            // 计算kps
            if (++_frame_count >= kps_fresh_frame)
            {
                kps = _count / (kps_fresh_frame / io.Framerate);
                _frame_count = 0;
                _count = 0;
            }

            char buf[64];
            sprintf(buf, "Pinekey %s FPS: %.1f ###PineKey_main", version, io.Framerate);

            Begin(buf, &main_window_close_flag, main_window_flags);

            // 按键图形
            SeparatorText("Key overlay");
            Dummy(ImVec2(5, 0));
            SameLine();
            BeginGroup();
            switch (key_style)
            {
            case 0: // line style
                // 1P皿
                if (!play_position)
                {
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", iidx_button_size);
                    PopStyleColor(3);
                    SameLine();
                }
                for (int i = 0; i < 7; i++)
                {
                    bool is_upper_button = i % 2;
                    PushID(i);
                    if (key_color_style)
                    {
                        // 默认红蓝
                        if (is_key_pressed[i] == 1)
                            PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                        else
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button ? 0.0f : 0.7f, is_upper_button ? 0.0f : 0.7f, 0.7f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), iidx_button_size);
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), iidx_button_size);
                    }
                    PopID();
                    SameLine();
                }

                // 2P皿
                if (play_position)
                {
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", iidx_button_size);
                    PopStyleColor(3);
                }
                else
                {
                    NewLine();
                }

                break;

            case 1: // IIDX controller style

                // 1P 皿
                if (!play_position)
                {
                    BeginGroup();
                    Dummy(ImVec2(1, key_dummy_size - iidx_scr_button_size.y));
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", iidx_scr_button_size);
                    PopStyleColor(3);
                    EndGroup();
                    SameLine();
                }

                for (int i = 0; i < 7; i++)
                {
                    bool is_upper_button = i % 2;
                    BeginGroup();
                    PushID(i);
                    if (!is_upper_button)
                        Dummy(ImVec2(1, key_dummy_size));
                    if (key_color_style)
                    { // 默认红蓝
                        if (is_key_pressed[i] == 1)
                            PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                        else
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button ? 0.0f : 0.7f, is_upper_button ? 0.0f : 0.7f, 0.7f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), iidx_button_size);
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), iidx_button_size);
                    }
                    PopID();
                    EndGroup();
                    SameLine();
                }

                // 2P皿
                if (play_position)
                {
                    BeginGroup();
                    Dummy(ImVec2(1, key_dummy_size - iidx_scr_button_size.y));
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", iidx_scr_button_size);
                    PopStyleColor(3);
                    EndGroup();
                }
                else
                {
                    NewLine();
                }
                break;
            case 2: // flat style
                break;
            }
            EndGroup();
            SameLine();
            Dummy(ImVec2(8, 0));
            NewLine();

            // 柱状图
            if (enabled_histogram)
            {
                SeparatorText("Key count histogram");

                BeginTable("histogram", 2);
                TableNextRow();
                TableNextColumn();
                Text("key count graph");
                TableNextColumn();
                Text("key press window graph");
                TableNextRow();
                TableNextColumn();
                int max = 0;
                for (int i = 0; i < 8; i++)
                {
                    _histogram_values[i] = (float)key_press_count[i];
                    if (key_press_count[i] > max)
                        max = key_press_count[i];
                }
                PlotHistogram("##values", _histogram_values, 8, 0, NULL, 0.0f, (float)max, ImVec2(200, histogram_height));
                TableNextColumn();
                for (int i = 0; i < 8; i++)
                {
                    _histogram_values[i] = (float)key_pressed_time[i];
                }

                PlotHistogram("##values", _histogram_values, 8, 0, NULL, 0.0f, io.Framerate / press_time_scale, ImVec2(200, histogram_height));

                EndTable();
            }

            // KPS
            if (show_kps_test || show_kps_plot)
            {
                SeparatorText("KPS");
                if (show_kps_test)
                    TextWrapped(std::to_string(kps).c_str());
                if (show_kps_plot)
                {
                    kpsHistory[currentIdx] = (float)kps;
                    currentIdx = (currentIdx + 1) % 200;
                    float displayData[200];
                    for (int i = 0; i < 200; i++)
                    {
                        int idx = (currentIdx + i) % 200;
                        displayData[i] = kpsHistory[idx];
                    }
                    ImGui::PlotLines(std::to_string(kps).c_str(), displayData, 200, 0, NULL, 0.0f, 50.0f, ImVec2(400, 60));
                }
            }
            // 底部下拉菜单
            if (CollapsingHeader("Config"))
            {
                // 保存按钮
                if (Button("Save config", ImVec2(100, 20)))
                {
                    // TODO: Save config
                }
                SameLine();

                // 默认按钮
                if (Button("set default", ImVec2(100, 20)))
                {
                    enabled_histogram = false;
                    play_position = 0;
                    key_style = 1;
                    key_color_style = 1;
                    iidx_button_size.x = 30;
                    iidx_button_size.y = 60;
                    iidx_scr_button_size.x = 60;
                    iidx_scr_button_size.y = 70;
                    key_dummy_size = 15;
                    key_count_num = true; // TODO:
                    histogram_height = 130;
                    press_time_scale = 2.0f;
                    show_kps_test = false;
                    show_kps_plot = false;
                    kps_plot_history_time = 10; // 存几秒的Kps
                    kps_fresh_frame = 30;
                }

                // 柱状图
                Checkbox("histogram", &enabled_histogram);
                SameLine();

                // 柱状图高度调整
                SetNextItemWidth(120);
                if (!enabled_histogram)
                    BeginDisabled();
                SliderInt("histogram height", &histogram_height, 128, 512);
                if (!enabled_histogram)
                    EndDisabled();

                // 按键按下窗口柱状图上限倍率
                SliderFloat("key press window graph max scale", &press_time_scale, 0.2f, 10.0f);
                Text("\t\tmax in %.0f ms", 1000.0f / press_time_scale);

                // 按键样式
                if (TreeNode("Button style"))
                {
                    RadioButton("line style", &key_style, 0);
                    SameLine();
                    RadioButton("IIDX style", &key_style, 1);
                    SameLine();
                    BeginDisabled();
                    RadioButton("flat style", &key_style, 2);
                    EndDisabled();
                    SameLine();
                    HelpMarker("Not supported yet.");

                    RadioButton("1P", &play_position, 0);
                    SameLine();
                    RadioButton("2P", &play_position, 1);

                    Checkbox("color button", &key_color_style);
                    SameLine();
                    Checkbox("show count number on keys", &key_count_num);
                    TreePop();
                }

                // 按键大小
                if (TreeNode("Button size & padding"))
                {
                    int _iidx_button_size[2] = {(int)iidx_button_size.x, (int)iidx_button_size.y};
                    int _iidx_scr_button_size[2] = {(int)iidx_scr_button_size.x, (int)iidx_scr_button_size.y};
                    SliderInt2("button size", _iidx_button_size, 10, 70);
                    if (key_style == 0)
                    {
                        BeginDisabled();
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &key_dummy_size, 0, (int)iidx_button_size.y);
                        EndDisabled();
                    }
                    else
                    {
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &key_dummy_size, 0, (int)iidx_button_size.y);
                    }

                    iidx_button_size.x = (float)_iidx_button_size[0];
                    iidx_button_size.y = (float)_iidx_button_size[1];
                    iidx_scr_button_size.x = (float)_iidx_scr_button_size[0];
                    iidx_scr_button_size.y = (float)_iidx_scr_button_size[1];
                    TreePop();
                }

                // 按键绑定
                if (TreeNode("button input config"))
                {
                    BeginTable("key config", 3);
                    for (int i = 0; i < 8; i++)
                    {
                        TableNextRow();
                        TableNextColumn();
                        if (vkCodeToKeyName.find(key_config[i]) == vkCodeToKeyName.end())
                            Text("Unknown");
                        else
                            Text(vkCodeToKeyName[key_config[i]]);
                        Dummy(ImVec2(30, 1));
                        TableNextColumn();
                        if (Button((i == 7) ? ("scr") : (std::to_string(i + 1).c_str()), ImVec2(70, 20)))
                            key_to_bind = i;
                        if (key_to_bind == i)
                        {
                            TableNextColumn();
                            Text("PRESS A BUTTON TO BIND.");
                        }
                    }
                    EndTable();
                    TreePop();
                }

                // KPS
                if (TreeNode("KPS config"))
                {
                    Checkbox("show kps", &show_kps_test);
                    SameLine();
                    Checkbox("show kps graph", &show_kps_plot);
                    SetNextItemWidth(200);
                    SliderInt("kps refresh frame", &kps_fresh_frame, 15, 60);
                    SetNextItemWidth(200);
                    SliderInt("kps plot history time (seconds)", &kps_plot_history_time, 2, 300);
                    TreePop();
                }
            }

            if (CollapsingHeader("About"))
            {
                PushStyleColor(ImGuiCol_Separator, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                SeparatorText("ABOUT THIS TOOL:");
                PopStyleColor();
                Text("This prog is a music game tool that visualizes the input of keys, joysticks, and game controllers.");
                TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "DEVELOP VERSION! v0.0a");
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

            NewLine();
            End();
        }

        // 关闭窗口
        if (!main_window_close_flag)
            break;

        // 渲染
        Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            UpdatePlatformWindows();
            RenderPlatformWindowsDefault();
        }
        glfwSwapBuffers(window);
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    RemoveGlobalHook();
    return 0;
}

// 全局键盘钩子回调函数
static void handle_hook_key_press(WPARAM wParam, DWORD vkcode)
{
    if (wParam == WM_KEYDOWN)
    {
        // 待绑定flag不处于—1：此时bind_button_id的值是按键索引
        if (key_to_bind != -1)
        {
            // 用这个索引改掉按键绑定信息key_config的键值为触发当前函数的vkcode值
            *(key_config + key_to_bind) = vkcode;
            key_to_bind = -1;
        }
        // 没有带绑定按键flag时 处理键盘按下钩子事件
        else
        {
            for (int i = 0; i < 8; i++)
            {
                // 按下的是被绑定的按键 避免连击
                if (vkcode == *(key_config + i) && !*(is_key_pressed + i))
                {
                    // 触发是否被按下的数组
                    *(is_key_pressed + i) = true;
                    // 增加计数
                    *(key_press_count + i) += 1;
                    all_count++;
                    _count++;
                }
            }
        }
    }
    else if (wParam == WM_KEYUP)
    {
        for (int i = 0; i < 8; i++)
        {
            if (vkcode == *(key_config + i) && *(is_key_pressed + i))
            {
                *(is_key_pressed + i) = 0;
            }
        }
    }
}

// 快速生成帮助悬停区
static void HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

// 全局键盘钩子
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)lParam;
        handle_hook_key_press(wParam, kb->vkCode);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void SetGlobalHook()
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
}

void RemoveGlobalHook()
{
    if (hHook)
    {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
    }
}