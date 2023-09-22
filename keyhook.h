#pragma once

#include <windows.h>
#include <WinUser.h>
#include <iostream>

LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);
void SetGlobalHook();
void RemoveGlobalHook();
