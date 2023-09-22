#include "keyhook.h"

HHOOK hHook = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // 在此处处理按键事件
        // 例如，你可以检查wParam是否为你关心的按键，并相应地更新计数器
        KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN) {
            // 键被按下
        }
        if (wParam == WM_KEYUP){
            // 键被释放
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void SetGlobalHook() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
}

void RemoveGlobalHook() {
    if (hHook) {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
    }
}
