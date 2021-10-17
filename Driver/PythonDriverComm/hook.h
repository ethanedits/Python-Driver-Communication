#pragma once
#include "memory.h"
#pragma warning (disable: 4130)

namespace hook {
	NTSTATUS hook_handler(PVOID called_param)
	{
		COPY_MEMORY* m = (COPY_MEMORY*)called_param;
		if (m->get_pid) {
			m->pid = memory::get_process_id(m->process_name);
		}
		if (m->base) {
			PEPROCESS process = NULL;
			if (NT_SUCCESS(PsLookupProcessByProcessId(m->pid, &process))) {
				if (m->pid == memory::get_process_id("csgo.exe")) { //For x86 Processes

					KAPC_STATE apc;
					KeStackAttachProcess(process, &apc);

					LONG b = memory::get_module_base_x86(process, L"client.dll");
					KeUnstackDetachProcess(&apc);
					if (b) { m->buffer = reinterpret_cast<PVOID>(b); }
				}
				else {
					m->buffer = (PVOID)memory::get_module_base_x64(process);
				}
			}
		}
		else if (m->peb) {
			PEPROCESS process = NULL;

			if (m->pid == memory::get_process_id("csgo.exe")) { //x86 
				m->buffer = PsGetProcessWow64Process(process);
			}
			else if (NT_SUCCESS(PsLookupProcessByProcessId(m->pid, &process))) { //x64
				m->buffer = (PVOID)PsGetProcessPeb(process);
			}
		}
		else if (m->read) {
			memory::read_kernel_memory(m->pid, (PVOID)m->address, m->buffer, m->size);
		}
		else if (m->write) {
			memory::write_kernel_memory(m->pid, m->buffer, (PVOID)m->address, m->size);
		}

		return STATUS_SUCCESS;
	}

	bool call_kernel_function(void* kernel_function_address) {
		if (!kernel_function_address)
			return false;

		PVOID* hookFunction = reinterpret_cast<PVOID*>(memory::get_system_module_export("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys", "NtOpenCompositionSurfaceSectionInfo"));

		if (!hookFunction) {
			return false;
		}

		BYTE original_func[] = { 0x4C, 0x8B, 0xDC, 0x49, 0x89, 0x5B, 0x18, 0x4D, 0x89, 0x4B, 0x20, 0x49, 0x89, 0x4B, 0x08 }; //Shellcode for the original function in dxgkrnl.sys

		BYTE shell_code_start[]
		{
			0x48, 0xB8 // 0x48 is mov, 0xBB is rax; then our function address
		};

		BYTE shell_code_end[]
		{
			0xFF, 0xE0, // jmp rax
			0xCC
		};

		RtlSecureZeroMemory(&original_func, sizeof(original_func));
		memcpy((PVOID)((ULONG_PTR)original_func), &shell_code_start, sizeof(shell_code_start));
		uintptr_t test_address = reinterpret_cast<uintptr_t>(kernel_function_address);
		memcpy((PVOID)((ULONG_PTR)original_func + sizeof(shell_code_start)), &test_address, sizeof(void*));
		memcpy((PVOID)((ULONG_PTR)original_func + sizeof(shell_code_start) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));
		memory::write_to_read_only_memory(hookFunction, &original_func, sizeof(original_func));

		return true;
	}
}