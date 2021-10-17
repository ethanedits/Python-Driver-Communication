#include <iostream>
#include "driver.h"
#include "pyDriver.h"

//Basic Example of using Driver to Read/Write Memory (C++)
/*int main()
{
	globals::process_id = driver::get_process_id("ac_client.exe");
	globals::module_base = driver::get_module_base_address("ac_client.exe");

	while (true)
	{
		int ammo = driver::read<int>(0x00E6A638);
		std::cout << ammo << std::endl;

		driver::write<int>(0x00E6A638, 69, sizeof(0x00E6A638));
	}

	return 0;
}*/