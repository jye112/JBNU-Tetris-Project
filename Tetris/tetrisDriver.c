#include "tetrisDriver.h"

void Driver_Init(Driver* driver)
{
	driver->DM = 0;
	driver->FPGA = 0;
	driver->LED = 0;
	driver->SWITCH = 0;
}

bool Open_LED_Driver(Driver* driver)
{
	driver->LED = open("/dev/csemad_led", O_RDWR);

	if (driver->LED < 0)
	{
		printf("failed to open LED Driver\n");
		return false;
	}
	else
		return true;
}

bool Open_DM_Driver(Driver* driver)
{
	driver->DM = open("/dev/csemad_DM", O_WRONLY);

	if (driver->DM < 0)
	{
		printf("failed to open DM Driver\n");
		return false;
	}
	else
		return true;
}

bool Open_SWITCH_Driver(Driver* driver)
{
	driver->SWITCH = open("/dev/csemad_push_switch", O_RDONLY);

	if (driver->SWITCH < 0)
	{
		printf("failed to open Push_Swtich Driver\n");
		return false;
	}
	else
		return true;
}

bool Open_FPGA_Driver(Driver* driver)
{
	driver->FPGA = open("/dev/csemad_fpga_fnd", O_RDWR);

	if (driver->FPGA < 0)
	{
		printf("failed to open FPGA Driver\n");
		return false;
	}
	else
		return true;
}

void Open_All_Dirver(Driver* driver)
{
	if (Open_DM_Driver(driver) && Open_FPGA_Driver(driver) && Open_LED_Driver(driver) && Open_SWITCH_Driver(driver))
		printf("All Driver Open Success!!\n");
	else
	{
		printf("Some Driver Open Error!\n");
		exit(-1);
	}
}

void Close_All_Driver(Driver* driver)
{
	close(driver->LED);
	close(driver->FPGA);
	close(driver->SWITCH);
	close(driver->DM);

	printf("Close Success!, Good Bye\n");
}