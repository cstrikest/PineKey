// #define DEBUG

#include "util.h"

using namespace ImGui;

static void handle_hook_key_press(WPARAM, DWORD);
static void HelpMarker(const char *desc);
LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);
void SetGlobalHook();
void RemoveGlobalHook();
void LoadConfig();
void SaveConfig(bool);
void SetDefaultConfig(bool);

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char **)
{
    SetGlobalHook();

    LoadConfig();

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

    // 字体
    io.Fonts->AddFontDefault();
    ImFont *font_impact = io.Fonts->AddFontFromFileTTF("c:/windows/fonts/impact.ttf", 32.0f);

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
                    key_pressed_window_time[i] += 1;
                else if (key_pressed_window_time[i] != 0)
                    key_pressed_window_time[i] = 0;
            }

            // 计算总数
            count_sum = 0;
            for (int i = 0; i < 8; i++)
                count_sum += key_press_count[i];

            char buf[64];
            sprintf(buf, "Pinekey %s FPS: %.1f ###PineKey_main", VERSION, io.Framerate);

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
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", ImVec2(sbtn_size_x, sbtn_size_y));
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
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), ImVec2(btn_size_x, btn_size_y));
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), ImVec2(btn_size_x, btn_size_y));
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
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", ImVec2(sbtn_size_x, sbtn_size_y));
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
                    Dummy(ImVec2(1, key_dummy_size - sbtn_size_y));
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", ImVec2(sbtn_size_x, sbtn_size_y));
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
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), ImVec2(btn_size_x, btn_size_y));
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(key_count_num ? std::to_string(key_press_count[i]).c_str() : std::to_string(i).c_str(), ImVec2(btn_size_x, btn_size_y));
                    }
                    PopID();
                    EndGroup();
                    SameLine();
                }

                // 2P皿
                if (play_position)
                {
                    BeginGroup();
                    Dummy(ImVec2(1, key_dummy_size - sbtn_size_y));
                    if (is_key_pressed[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(key_count_num ? std::to_string(key_press_count[7]).c_str() : "S", ImVec2(sbtn_size_x, sbtn_size_y));
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

            NewLine();
            Dummy(ImVec2(GetContentRegionAvail().x * 0.3f, 0.0f));
            SameLine();
            PushFont(font_impact);
            Text("Total: %d", count_sum);
            PopFont();

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
                    _histogram_values[i] = (float)key_pressed_window_time[i];
                }

                PlotHistogram("##values", _histogram_values, 8, 0, NULL, 0.0f, io.Framerate / press_time_scale, ImVec2(200, histogram_height));

                EndTable();
            }

            // KPS
            if (show_kps_text || show_kps_plot)
            {
                SeparatorText("KPS");

                // 更新KPS
                if (++_frame_count >= kps_fresh_frame)
                {
                    kps = (float)_count / ((float)kps_fresh_frame / io.Framerate);
                    _frame_count = 0;
                    _count = 0;

                    for (int i = kps_plot_length; i > 0; i--)
                        kpsHistory[i] = kpsHistory[i - 1];
                    kpsHistory[0] = kps;
                }

                if (show_kps_plot)
                {
                    PlotLines("", kpsHistory, kps_plot_length, 0, NULL, 0.0f, 48.0f, ImVec2(GetContentRegionAvail().x, 80));
                }

                if (show_kps_text)
                {
                    Dummy(ImVec2(GetContentRegionAvail().x * 0.35f, 0.0f));
                    SameLine();
                    PushFont(font_impact);
                    Text("KPS: %.1f", kps);
                    PopFont();
                }
            }

            NewLine();
            Separator();
            Separator();
            Separator();
            Separator();
            Separator();
            NewLine();

            // 底部下拉菜单
            if (CollapsingHeader("Config"))
            {
                // 保存按钮
                if (Button("Save config", ImVec2(100, 20)))
                {
                    SaveConfig(0);
                }
                SameLine();

                // 清空计数按钮
                if (Button("clear total", ImVec2(100, 20)))
                {
                    for (int i = 0; i < 8; i++)
                        key_press_count[i] = 0;
                    SameLine();
                    HelpMarker("This will clear you all history key press count.");
                }
                SameLine();

                // 默认按钮
                if (Button("overlay default", ImVec2(140, 20)))
                {
                    SetDefaultConfig(0);
                }

                // 柱状图
                Checkbox("histogram", &enabled_histogram);
                SameLine();
                HelpMarker("Enable 2 histogram\n\t- each key's press count\n\t-each key's pressed time");
                SameLine();

                // 柱状图高度调整
                SetNextItemWidth(120);
                if (!enabled_histogram)
                    BeginDisabled();
                SliderInt("histogram height", &histogram_height, 32, 512);
                if (!enabled_histogram)
                    EndDisabled();

                // 按键按下窗口柱状图上限倍率
                SliderFloat("key press time scale", &press_time_scale, 0.1f, 16.0f);
                Text("");
                SameLine(GetContentRegionAvail().x - 100);
                Text("max in %.0f ms", 1000.0f / press_time_scale);

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
                    int _iidx_button_size[2] = {btn_size_x, btn_size_y};
                    int _iidx_scr_button_size[2] = {sbtn_size_x, sbtn_size_y};
                    SliderInt2("button size", _iidx_button_size, 10, 70);
                    SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);

                    if (key_style == 0)
                    {
                        BeginDisabled();
                        SliderInt("button dummy size", &key_dummy_size, 0, btn_size_y);
                        EndDisabled();
                    }
                    else
                    {
                        SliderInt("button dummy size", &key_dummy_size, 0, btn_size_y);
                    }
                    SameLine();
                    HelpMarker("Set the spaces between those keys.\nJust try.");

                    btn_size_x = _iidx_button_size[0];
                    btn_size_y = _iidx_button_size[1];
                    sbtn_size_x = _iidx_scr_button_size[0];
                    sbtn_size_y = _iidx_scr_button_size[1];
                    TreePop();
                }

                // 按键绑定
                if (TreeNode("Key config"))
                {
                    BeginTable("key config", 3);
                    for (int i = 0; i < 8; i++)
                    {
                        TableNextRow();
                        TableNextColumn();
                        if (vkCodeToKeyName.find(key_vkcode_config[i]) == vkCodeToKeyName.end())
                            Text("Unknown");
                        else
                            Text(vkCodeToKeyName[key_vkcode_config[i]]);
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

                    NewLine();
                    TreePop();
                }

                // KPS
                if (TreeNode("KPS config"))
                {
                    Checkbox("show kps", &show_kps_text);
                    SameLine();
                    Checkbox("show kps graph", &show_kps_plot);
                    SameLine();
                    HelpMarker("Enable a plot shows that your kps's changing.");
                    SetNextItemWidth(200);
                    SliderInt("kps refresh frame", &kps_fresh_frame, 15, 60);
                    SameLine();
                    HelpMarker("Lower value brings faster kps fresh rate but bad accuracy.\nHigher fps monitor could help.");
                    SetNextItemWidth(200);
                    SliderInt("kps plot length", &kps_plot_length, 2, 400);
                    SameLine();
                    HelpMarker("Set how many kps sample point show in plot.");
                    TreePop();
                }
            }

            if (CollapsingHeader("About"))
            {
                PushStyleColor(ImGuiCol_Separator, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                SeparatorText("ABOUT THIS TOOL:");
                PopStyleColor();
                Text("This prog is a music game tool that visualizes the input of keys,");
                Text("joysticks, and game controllers.");
                TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "DEVELOP VERSION! %s", VERSION);
                Text("Features:");
                BulletText("Real-time display of pressed keys.");
                BulletText("Count for each key count, total count, realtime and average KPS.");
                Text("\tDisplay of changes in average KPS.");
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
        {
            SaveConfig(0);
            break;
        }

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
            *(key_vkcode_config + key_to_bind) = vkcode;
            key_to_bind = -1;
        }
        // 没有带绑定按键flag时 处理键盘按下钩子事件
        else
        {
            for (int i = 0; i < 8; i++)
            {
                // 按下的是被绑定的按键 避免连击
                if (vkcode == key_vkcode_config[i] && !is_key_pressed[i])
                {
                    // 触发是否被按下的数组
                    is_key_pressed[i] = true;
                    // 增加计数
                    key_press_count[i] += 1;
                    _count++;
                }
            }
        }
    }
    else if (wParam == WM_KEYUP)
    {
        for (int i = 0; i < 8; i++)
        {
            if (vkcode == key_vkcode_config[i] && is_key_pressed[i])
            {
                is_key_pressed[i] = 0;
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

void LoadConfig()
{
    // 文件不存在
    if (ini_getl("overlay", "key_style", -199024, ini_file) == -199024)
        SaveConfig(1);
    else
    {
        // [data]
        for (int i = 0; i < 8; i++)
        {
            key_vkcode_config[i] = ini_getl("data", (std::string("key_vkcode_config_") + std::to_string(i)).c_str(), -1, ini_file);
            key_press_count[i] = ini_getl("data", (std::string("key_press_count_") + std::to_string(i)).c_str(), -1, ini_file);
        }

        // [Key overlay]
        key_style = ini_getl("overlay", "key_style", 1, ini_file);
        key_color_style = ini_getl("overlay", "key_color_style", 1, ini_file);
        play_position = ini_getl("overlay", "play_position", 1, ini_file);
        btn_size_x = ini_getl("overlay", "btn_size_x", 30, ini_file);
        btn_size_y = ini_getl("overlay", "btn_size_y", 60, ini_file);
        sbtn_size_x = ini_getl("overlay", "sbtn_size_x", 60, ini_file);
        sbtn_size_y = ini_getl("overlay", "sbtn_size_y", 70, ini_file);
        key_dummy_size = ini_getl("overlay", "key_dummy_size", 15, ini_file);
        key_count_num = ini_getl("overlay", "key_count_num", 1, ini_file);

        // [histogram]
        enabled_histogram = ini_getl("histogram", "enabled_histogram", 0, ini_file);
        histogram_height = ini_getl("histogram", "histogram_height", 130, ini_file);
        press_time_scale = ini_getl("histogram", "press_time_scale", 2.0f, ini_file);

        // [KPS]
        show_kps_text = ini_getl("KPS", "show_kps_text", 0, ini_file);
        show_kps_plot = ini_getl("KPS", "show_kps_plot", 0, ini_file);
        kps_fresh_frame = ini_getl("KPS", "kps_fresh_frame", 30, ini_file);
        kps_plot_length = ini_getl("KPS", "kps_plot_length", 80, ini_file);
    }
}

void SaveConfig(bool init_config)
{
    // 创建config, 全重置
    if (init_config)
        SetDefaultConfig(1);

    // [data]
    for (int i = 0; i < 8; i++)
    {
        ini_putl("data", (std::string("key_vkcode_config_") + std::to_string(i)).c_str(), key_vkcode_config[i], ini_file);
        ini_putl("data", (std::string("key_press_count_") + std::to_string(i)).c_str(), key_press_count[i], ini_file);
    }

    // [Key overlay]
    ini_putl("overlay", "key_style", key_style, ini_file);
    ini_putl("overlay", "key_color_style", key_color_style, ini_file);
    ini_putl("overlay", "play_position", play_position, ini_file);
    ini_putl("overlay", "btn_size_x", btn_size_x, ini_file);
    ini_putl("overlay", "btn_size_y", btn_size_y, ini_file);
    ini_putl("overlay", "sbtn_size_x", sbtn_size_x, ini_file);
    ini_putl("overlay", "sbtn_size_y", sbtn_size_y, ini_file);
    ini_putl("overlay", "key_dummy_size", key_dummy_size, ini_file);
    ini_putl("overlay", "key_count_num", key_count_num, ini_file);

    // [histogram]
    ini_putl("histogram", "enabled_histogram", enabled_histogram, ini_file);
    ini_putl("histogram", "histogram_height", histogram_height, ini_file);
    ini_putl("histogram", "press_time_scale", press_time_scale, ini_file);

    // [KPS]
    ini_putl("KPS", "show_kps_text", show_kps_text, ini_file);
    ini_putl("KPS", "show_kps_plot", show_kps_plot, ini_file);
    ini_putl("KPS", "kps_fresh_frame", kps_fresh_frame, ini_file);
    ini_putl("KPS", "kps_plot_length", kps_plot_length, ini_file);
}

void SetDefaultConfig(bool clear_all)
{
    // [data]
    if (clear_all)
    {
        // 清除键位
        for (int i = 0; i < 8; i++)
        {
            key_vkcode_config[i] = 0;
            key_press_count[i] = 0;
        }
    }

    // [Key overlay]
    key_style = 1;
    key_color_style = 1;
    play_position = 0;
    btn_size_x = 30;
    btn_size_y = 60;
    sbtn_size_x = 60;
    sbtn_size_y = 70;
    key_dummy_size = 15;
    key_count_num = true;

    // [histogram]
    enabled_histogram = false;
    histogram_height = 130;
    press_time_scale = 2.0f;
    show_kps_text = false;
    show_kps_plot = false;
    kps_fresh_frame = 30;
    kps_plot_length = 80;
}
