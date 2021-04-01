#ifndef __TETRIS_DRIVER_H__
#define __TETRIS_DRIVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct _driverInfo
{
	int SWITCH;
	int LED;
	int DM;
	int FPGA;
}Driver;

//driver function definition
void Driver_Init(Driver* driver);
bool Open_LED_Driver(Driver* driver);
bool Open_DM_Driver(Driver* driver);
bool Open_SWITCH_Driver(Driver* driver);
bool Open_FPGA_Driver(Driver* driver);
void Open_All_Dirver(Driver* driver);
void Close_All_Driver(Driver* driver);

#endif