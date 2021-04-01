#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
				int fd;

				fd = open("/dev/csemad_led", O_RDWR);

				char i = (unsigned char)atoi(argv[1]);

				if(atoi(argv[1]) > 255 || atoi(argv[1]) < 0)
				{
								printf("Please enter 0~255\n");
								return 0;
				}
				else
				{
								write(fd, &i, 1);
								read(fd, &i, 1);
								printf("Current LED Value : %d\n", i);
								close(fd);
				}
				return 0;
}
