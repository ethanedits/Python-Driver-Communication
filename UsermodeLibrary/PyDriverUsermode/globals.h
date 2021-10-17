#pragma once
#include <Windows.h>

namespace globals {
	HANDLE	 process_id = NULL;
	uintptr_t module_base = NULL;
	uintptr_t peb = NULL;
	HWND      hwnd = NULL;
}