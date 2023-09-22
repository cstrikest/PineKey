#define DEBUG

#include <map>
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#define GL_SILENCE_DEPRECATION

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

using namespace ImGui;

static void handle_hook_key_press(WPARAM, DWORD);
static void HelpMarker(const char *desc);
LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);
void SetGlobalHook();
void RemoveGlobalHook();

std::map<int, const char *> vkCodeToKeyName = {
    {0x08, "BACKSPACE"},
    {0x09, "TAB"},
    {0x0D, "ENTER"},
    {0x10, "SHIFT"},
    {0x0C, "CLEAR"},
    {0x0D, "ENTER"},
    {0x10, "SHIFT"},
    {0x11, "CTRL"},
    {0x12, "ALT"},
    {0x13, "PAUSE"},
    {0x14, "CAPS LOCK"},
    {0x15, "IME kana"},
    {0x16, "IME Hangul"},
    {0x17, "IME Junja"},
    {0x18, "IME Final"},
    {0x19, "IME Kanji"},
    {0x1A, "IME Off"},
    {0x1B, "ESC"},
    {0x1C, "IME Convert"},
    {0x1D, "IME Nonconvert"},
    {0x1E, "IME Accept"},
    {0x1F, "IME Mode Change"},
    {0x20, "SPACE"},
    {0x21, "PAGE UP"},
    {0x22, "PAGE DOWN"},
    {0x23, "END"},
    {0x24, "HOME"},
    {0x25, "LEFT"},
    {0x26, "UP"},
    {0x27, "RIGHT"},
    {0x28, "DOWN"},
    {0x29, "SELECT"},
    {0x2A, "PRINT"},
    {0x2B, "EXECUTE"},
    {0x2C, "PRINT SCREEN"},
    {0x2D, "INSERT"},
    {0x2E, "DELETE"},
    {0x2F, "HELP"},
    {0x30, "KEY_0"},
    {0x31, "KEY_1"},
    {0x32, "KEY_2"},
    {0x33, "KEY_3"},
    {0x34, "KEY_4"},
    {0x35, "KEY_5"},
    {0x36, "KEY_6"},
    {0x37, "KEY_7"},
    {0x38, "KEY_8"},
    {0x39, "KEY_9"},
    {0x41, "A"},
    {0x42, "B"},
    {0x43, "C"},
    {0x44, "D"},
    {0x45, "E"},
    {0x46, "F"},
    {0x47, "G"},
    {0x48, "H"},
    {0x49, "I"},
    {0x4A, "J"},
    {0x4B, "K"},
    {0x4C, "L"},
    {0x4D, "M"},
    {0x4E, "N"},
    {0x4F, "O"},
    {0x50, "P"},
    {0x51, "Q"},
    {0x52, "R"},
    {0x53, "S"},
    {0x54, "T"},
    {0x55, "U"},
    {0x56, "V"},
    {0x57, "W"},
    {0x58, "X"},
    {0x59, "Y"},
    {0x5A, "Z"},
    {0x5B, "LWIN"},
    {0x5C, "RWIN"},
    {0x5D, "APPS"},
    {0x60, "NUMPAD0"},
    {0x61, "NUMPAD1"},
    {0x62, "NUMPAD2"},
    {0x63, "NUMPAD3"},
    {0x64, "NUMPAD4"},
    {0x65, "NUMPAD5"},
    {0x66, "NUMPAD6"},
    {0x67, "NUMPAD7"},
    {0x68, "NUMPAD8"},
    {0x69, "NUMPAD9"},
    {0x6A, "MULTIPLY"},
    {0x6B, "ADD"},
    {0x6C, "SEPARATOR"},
    {0x6D, "SUBTRACT"},
    {0x6E, "DECIMAL"},
    {0x6F, "DIVIDE"},
    {0x70, "F1"},
    {0x71, "F2"},
    {0x72, "F3"},
    {0x73, "F4"},
    {0x74, "F5"},
    {0x75, "F6"},
    {0x76, "F7"},
    {0x77, "F8"},
    {0x78, "F9"},
    {0x79, "F10"},
    {0x7A, "F11"},
    {0x7B, "F12"},
    {0x7C, "F13"},
    {0x7D, "F14"},
    {0x7E, "F15"},
    {0x7F, "F16"},
    {0x80, "F17"},
    {0x81, "F18"},
    {0x82, "F19"},
    {0x83, "F20"},
    {0x84, "F21"},
    {0x85, "F22"},
    {0x86, "F23"},
    {0x87, "F24"},
    {0x90, "NUM LOCK"},
    {0x91, "SCROLL LOCK"},
    {0x92, "NUMPAD_EQUAL"},
    {0x93, "NUMPAD_MULTIPLY"},
    {0x94, "NUMPAD_ADD"},
    {0x95, "NUMPAD_SEPARATOR"},
    {0x96, "NUMPAD_SUBTRACT"},
    {0x97, "NUMPAD_DECIMAL"},
    {0x98, "NUMPAD_DIVIDE"},
    {0xA0, "LSHIFT"},
    {0xA1, "RSHIFT"},
    {0xA2, "LCONTROL"},
    {0xA3, "RCONTROL"},
    {0xA4, "LMENU"},
    {0xA5, "RMENU"},
    {0xBA, "OEM_1"},
    {0xBB, "OEM_PLUS"},
    {0xBC, "OEM_COMMA"},
    {0xBD, "OEM_MINUS"},
    {0xBE, "OEM_PERIOD"},
    {0xBF, "OEM_2"},
    {0xC0, "OEM_3"},
    {0xDB, "OEM_4"},
    {0xDC, "OEM_5"},
    {0xDD, "OEM_6"},
    {0xDE, "OEM_7"},
    {0xDF, "OEM_8"},
    {0xE2, "OEM_102"}};

// 全局变量
static float f = 0.0f;
static int counter = 0; // fps计算
bool show_main_window = true;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
static int iidx_button_count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static float _histogram_values[8] = {};
static bool iidx_key_pressed_situation[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static HHOOK hHook = NULL;
static int bind_button_id = -1; // 待绑定按键编号 -1为无
static bool key_down_flag[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // 避免连击

// TODO: 需要加载的配置
static bool enabled_count_histogram = true;
static bool enabled_frame_window_histogram = true;
static bool enabled_all_kps = true;
static bool enabled_spec_kps = true;
static int iidx_button_layout_style = 1;         // 显示按键布局 0一条线 1iidx默认布局 2平铺
static bool iidx_button_default_color_style = 1; // 显示按键颜色 0单色 1默认红蓝
static int iidx_play_position = 0;               // iidx游玩位置 0 1p 1 2p
static ImVec2 iidx_button_size(45, 60);          // iidx按键长宽
static ImVec2 iidx_scr_button_size(60, 70);      // iidx皿按键长宽
static int iidx_button_dummy_size = 15;          // iidx默认布局横向填充空白大小
static bool iidx_button_show_num = true;
static int key_count[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // 1~7号键按键 皿 计数
static int key_config[8] = {83, 68, 70, 32, 74, 75, 76, 77};

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char **)
{
    SetGlobalHook();

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
    glfwSwapInterval(1); // Enable vsync

    // ImGui上下文
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO &io = GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Get the default font's config
    ImFontConfig config;
    config.OversampleH = 3;
    config.OversampleV = 1;

    // Add a smaller version of the default font (scale down to 0.8 times)
    io.Fonts->AddFontDefault();
    ImFont* my_small_font = io.Fonts->AddFontDefault(&config);
    my_small_font->Scale = 0.8f;

    // Build the font atlas
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    // 风格
    StyleColorsDark();

    // 平台、渲染器后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 加载字体
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);

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

#ifdef DEBUG
        ShowDemoWindow(nullptr);
#endif

        // window prop.
        const ImGuiViewport *main_viewport = GetMainViewport();
        SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 300, main_viewport->WorkPos.y + 100), ImGuiCond_FirstUseEver);
        // SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);
        SetNextWindowSizeConstraints(ImVec2(550, -1), ImVec2(550, FLT_MAX));

        // style
        ImGuiStyle &style = GetStyle();
        style.WindowPadding = ImVec2(14, 2);
        style.FrameBorderSize = 3;
        style.FrameRounding = 4;
        style.GrabRounding = 1;
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextAlign = ImVec2(0.5, 0.5);
        style.SeparatorTextPadding = ImVec2(2, 18);

        // flag
        ImGuiWindowFlags main_window_flags = 0;
        // main_window_flags |= ImGuiWindowFlags_NoResize; // 不能调整大小
        main_window_flags |= ImGuiWindowFlags_NoCollapse; // 不能折叠窗口
        main_window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

        // 主窗口
        {
            Begin("PineKey", &show_main_window, main_window_flags);

            SeparatorText("Key overlay");
            Dummy(ImVec2(5, 0));
            SameLine();
            BeginGroup();
            switch (iidx_button_layout_style)
            {
            case 0: // line style
                // 1P皿
                if (!iidx_play_position)
                {
                    if (iidx_key_pressed_situation[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushFont(my_small_font);
                    Button(std::to_string(iidx_button_count[7]).c_str(), iidx_button_size); 
                    PopFont();
                    PopStyleColor(3);
                    SameLine();
                }
                for (int i = 0; i < 7; i++)
                {
                    bool is_upper_button = i % 2;
                    PushID(i);
                    if (iidx_button_default_color_style)
                    { // 默认红蓝
                        if (iidx_key_pressed_situation[i] == 1)
                            PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                        else
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button ? 0.0f : 0.7f, is_upper_button ? 0.0f : 0.7f, 0.7f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        Button(std::to_string(iidx_button_count[i]).c_str(), iidx_button_size);
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(std::to_string(iidx_button_count[i]).c_str(), iidx_button_size);
                    }
                    PopID();
                    SameLine();
                }

                // 2P皿
                if (iidx_play_position)
                {
                    if (iidx_key_pressed_situation[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(std::to_string(iidx_button_count[7]).c_str(), iidx_button_size);
                    PopStyleColor(3);
                }
                else
                {
                    NewLine();
                }

                break;

            case 1: // IIDX controller style

                // 1P 皿
                if (!iidx_play_position)
                {
                    BeginGroup();
                    Dummy(ImVec2(1, iidx_button_dummy_size - iidx_scr_button_size.y));
                    if (iidx_key_pressed_situation[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(std::to_string(iidx_button_count[7]).c_str(), iidx_scr_button_size);
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
                        Dummy(ImVec2(1, iidx_button_dummy_size));
                    if (iidx_button_default_color_style)
                    { // 默认红蓝
                        if (iidx_key_pressed_situation[i] == 1)
                            PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                        else
                            PushStyleColor(ImGuiCol_Button, ImVec4(is_upper_button ? 0.0f : 0.7f, is_upper_button ? 0.0f : 0.7f, 0.7f, 0.3f));
                        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 0.8f));
                        Button(std::to_string(iidx_button_count[i]).c_str(), iidx_button_size);
                        PopStyleColor(3);
                    }
                    else
                    { // 单色
                        Button(std::to_string(iidx_button_count[i]).c_str(), iidx_button_size);
                    }
                    PopID();
                    EndGroup();
                    SameLine();
                }

                // 2P皿
                if (iidx_play_position)
                {
                    BeginGroup();
                    Dummy(ImVec2(1, iidx_button_dummy_size - iidx_scr_button_size.y));
                    if (iidx_key_pressed_situation[7] == 1)
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.0f, 0.9f));
                    else
                        PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.0f, 0.0f, 0.3f));
                    PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.0f, 0.8f));
                    Button(std::to_string(iidx_button_count[7]).c_str(), iidx_scr_button_size);
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

            // 按键次数柱状图
            SeparatorText("Key count histogram");
            if (enabled_count_histogram)
            {
                int max = 0;
                for (int i = 0; i < 8; i++)
                {
                    _histogram_values[i] = (float)iidx_button_count[i];
                    if (iidx_button_count[i] > max)
                        max = iidx_button_count[i];
                }
                PlotHistogram("##values", _histogram_values, 8, 0, NULL, 0.0f, (float)max, ImVec2(300, 200));
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            // 底部下拉菜单
            if (CollapsingHeader("Config"))
            {
                // 保存按钮
                if (Button("Save config"))
                {
                    // TODO: Save config
                }

                if (TreeNode("Button style"))
                {
                    RadioButton("line style", &iidx_button_layout_style, 0);
                    SameLine();
                    RadioButton("IIDX controller style", &iidx_button_layout_style, 1);
                    SameLine();
                    BeginDisabled();
                    RadioButton("flat style", &iidx_button_layout_style, 2);
                    EndDisabled();
                    SameLine();
                    HelpMarker("Not supported yet.");

                    RadioButton("1P", &iidx_play_position, 0);
                    SameLine();
                    RadioButton("2P", &iidx_play_position, 1);

                    Checkbox("default button color", &iidx_button_default_color_style);
                    SameLine();
                    // Dummy(ImVec2(150,20));
                    Checkbox("show number on keys", &iidx_button_show_num);
                    SameLine();
                    PushItemWidth(-130);
                    if (Button("set default", ImVec2(100, 20)))
                    {
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

                if (TreeNode("Button size & padding"))
                {
                    int _iidx_button_size[2] = {(int)iidx_button_size.x, (int)iidx_button_size.y};
                    int _iidx_scr_button_size[2] = {(int)iidx_scr_button_size.x, (int)iidx_scr_button_size.y};
                    SliderInt2("button size", _iidx_button_size, 10, 50);
                    if (iidx_button_layout_style == 0)
                    {
                        BeginDisabled();
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &iidx_button_dummy_size, 0, (int)iidx_button_size.y);
                        EndDisabled();
                    }
                    else
                    {
                        SliderInt2("scr button size", _iidx_scr_button_size, 10, 100);
                        SliderInt("button dummy size", &iidx_button_dummy_size, 0, (int)iidx_button_size.y);
                    }

                    iidx_button_size.x = (float)_iidx_button_size[0];
                    iidx_button_size.y = (float)_iidx_button_size[1];
                    iidx_scr_button_size.x = (float)_iidx_scr_button_size[0];
                    iidx_scr_button_size.y = (float)_iidx_scr_button_size[1];
                    TreePop();
                }

                if (TreeNode("histogram view"))
                {
                    Checkbox("key count", &enabled_count_histogram);
                    Checkbox("key press frame window", &enabled_frame_window_histogram);
                    TreePop();
                }

                if (TreeNode("button input config"))
                {
                    BeginTable("key config", 3);
                    for (int i = 0; i < 8; i++)
                    {
                        TableNextRow();
                        TableNextColumn();
                        if(vkCodeToKeyName.find(key_config[i]) == vkCodeToKeyName.end())
                        {
                            Text("Unknown");
                        }
                        else
                        {
                            Text(vkCodeToKeyName[key_config[i]]);
                        }
                        Dummy(ImVec2(30, 1));
                        TableNextColumn();
                        if (Button((i == 7) ? ("scr") : (std::to_string(i + 1).c_str()), ImVec2(70, 20)))
                        {
                            bind_button_id = i;
                        }
                        if (bind_button_id == i)
                        {
                            TableNextColumn();
                            Text("PRESS A BUTTON TO BIND.");
                        }
                    }
                    EndTable();
                    TreePop();
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

            NewLine();

            End();
        }

        // 关闭窗口
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
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
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
    RemoveGlobalHook();
    return 0;
}

// 全局键盘钩子回调函数
static void handle_hook_key_press(WPARAM wParam, DWORD vkcode)
{
    if (wParam == WM_KEYDOWN)
    {
        // 待绑定flag不处于—1：此时bind_button_id的值是按键索引
        if (bind_button_id != -1)
        {
            // 用这个索引改掉按键绑定信息key_config的键值为触发当前函数的vkcode值
            *(key_config + bind_button_id) = vkcode;
            bind_button_id = -1;
        }
        // 没有带绑定按键flag时 处理键盘按下钩子事件
        else
        {
            for (int i = 0; i < 8; i++)
            {
                // 按下的是被绑定的按键
                if (vkcode == *(key_config + i) && !*(key_down_flag +i ))
                {
                    // 触发是否被按下的数组
                    *(iidx_key_pressed_situation + i) = true;
                    // 增加计数
                    *(iidx_button_count + i) += 1;
                    // 记录按下flag 避免连击
                    *(key_down_flag +i ) = true;
                }
            }
        }
    }
    else if (wParam == WM_KEYUP)
    {
        for (int i = 0; i < 8; i++)
        {
            if (vkcode == *(key_config + i) && *(key_down_flag +i ))
            {
                *(iidx_key_pressed_situation + i) = 0;
                *(key_down_flag +i ) = false;
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
