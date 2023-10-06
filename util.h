#pragma once
#pragma comment(lib, "xinput.lib")

#define VERSION "v1.0.2"

#include <map>
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <iostream>
#include "minini_13/minIni.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <MMSystem.h>
#include <xinput.h>
#include <cstring>

#define GL_SILENCE_DEPRECATION

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

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

// config
// [data]
static int key_vkcode_config[9] = {83, 68, 70, 32, 74, 75, 76, 77, 78};
static int key_press_count[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

// [Key overlay]
static bool key_window_mode = 0;
static bool key_show_total = 1;
static int key_style = 1;        // 显示按键布局 0一条线 1iidx默认布局 2平铺
static bool key_color_style = 1; // 显示按键颜色 0单色 1默认红蓝
static int play_position = 0;    // iidx游玩位置 0 1p 1 2p
static int btn_size_x = 30;
static int btn_size_y = 60;
static int sbtn_size_x = 60;
static int sbtn_size_y = 70;
static int key_dummy_size = 15; // iidx默认布局横向填充空白大小
static bool key_count_num = true;

// [histogram]
static bool enabled_histogram = false;
static int histogram_height = 130;
static int press_time_scale = 200;

// [KPS]
static bool show_kps_text = false;
static bool show_kps_plot = false;
static int kps_fresh_frame = 30;
static int kps_plot_length = 80;

// 全局变量
const char *ini_file = "./config.ini";
static float f = 0.0f;
static int counter = 0; // fps计算
bool main_window_close_flag = true;
bool key_window_close_flag = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
static float _histogram_values[8] = {};
static bool is_key_pressed[9] = {0, 0, 0, 0, 0, 0, 0, 0,0};
static int key_pressed_window_time[9] = {0, 0, 0, 0, 0, 0, 0, 0,0};
static HHOOK hHook = NULL;
static int key_to_bind = -1; // 待绑定按键编号 -1为无
static int _frame_count = 0;
static int _count = 0;
static float kps = 0;
static int currentIdx = 0;
static int count_sum = 0;

float kpsHistory[500] = {0};
