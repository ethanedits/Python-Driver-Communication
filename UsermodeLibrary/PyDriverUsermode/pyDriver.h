#pragma once
#include "driver.h"

extern "C" {

	//Test Function
	__declspec(dllexport)void TestFunction()
	{
		std::cout << "Test Function Called!" << std::endl;
	}

	//Driver-Python Communication
	__declspec(dllexport)void ProcessID(const char* procName)
	{
		globals::process_id = driver::get_process_id(procName);
		std::cout << "ProcName: " << procName << std::endl;
		std::cout << "PiD: " << globals::process_id << std::endl;
	}

	__declspec(dllexport) uintptr_t ModuleBaseAddress(const char* modName)
	{
		globals::module_base = driver::get_module_base_address(modName);
		std::cout << "Modbase: " << globals::module_base << std::endl;
		return globals::module_base;
	}

	__declspec(dllexport) int ReadInt(int address)
	{
		int buffer = driver::read<int>(address);
		return buffer;
	}

	__declspec(dllexport) void WriteInt(int address, int buffer)
	{
		driver::write<int>(address, buffer, sizeof(address));
	}

	__declspec(dllexport) float ReadFloat(int address)
	{
		float buffer = driver::read<float>(address);
		return buffer;
	}

	__declspec(dllexport) void WriteFloat(float address, float buffer)
	{
		driver::write<float>(address, buffer, sizeof(address));
	}
}