#include "driver.h"
#include "memory.h"
#include "hook.h"

extern "C" NTSTATUS EntryPoint(PDRIVER_OBJECT  driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(driver_object);
	UNREFERENCED_PARAMETER(registry_path);

	if (hook::call_kernel_function(&hook::hook_handler)) {
		DbgPrintEx(0, 0, "PyComm Driver | Function hooked!\n");
			
		return STATUS_SUCCESS;
	}
	else {
		DbgPrintEx(0, 0, "PyComm Driver | Function hook failed!\n");

		return STATUS_FAILED_DRIVER_ENTRY;
	}
}