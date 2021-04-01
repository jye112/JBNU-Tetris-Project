#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>

#define MAX_BUTTON 9
unsigned char quit = 0;

void user_signal1(int sig) { quit = 1; }

int main(void)
{
				int i;
				int dev;
				int buff_size = 100;

				unsigned char push_sw_buff[MAX_BUTTON];

				if(0 > (dev = open("/dev/csemad_push_switch", O_RDWR)))
				{
								printf("failed to open\n");
								return -1;
				}

				(void)signal(SIGINT, user_signal1);
				printf("Press <ctrl+c> to quit. \n");

				while(!quit)
				{
								usleep(400000);
								read(dev, push_sw_buff, buff_size);
								printf("[Current_Clicked]\n");

								for(i=0; i<MAX_BUTTON; i++)
								{
												printf("Push_Switch_Clicked[%d] : %d\n", i+1, push_sw_buff[i]);
								}
				}

				close(dev);
				return 0;
}
