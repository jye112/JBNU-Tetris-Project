#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "dot_matrix_font.h"

#define NUM 10

int main(int argc, char **argv)
{
	int dev = open("/dev/csemad_DM", O_RDWR);
	int number = atoi(argv[1]);

	if(dev < 0)
	{
		printf("Cannot open csemad_DM!\n");
		return -1;
	}
	
	if(number >= 0 || number <= 9)
	{	
				write(dev, DM_font[number], sizeof(DM_font[number]));
				printf("Current DM Value : %d\n", number);
	}
	else if(number >= 10)
	{
				write(dev, DM_full, sizeof(DM_full));
	}
	else
	{
				write(dev, DM_blank, sizeof(DM_blank));
	}

	close(dev);
	
	return 0;
}
