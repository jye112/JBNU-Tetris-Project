#ifndef __TETRIS_COMPLETE_H__
#define __TETRIS_COMPLETE_H__

#include "tetrisDM.h"
#include <pthread.h>

Tetris tetris;
Driver driver;
pthread_t myThread;

void* Use_Switch_Thread()
{
	input_key key = 0;
	
	while (!usleep(100000))
	{
		key = input_user(&driver);
		if (key != 0)
		{
			if (tetris.isGameOver == false)
			{
				Move_Block(key, &tetris, &driver);
				Draw_Block(&tetris, &driver);
			}
		}
	}

	return NULL;
}

void Start_Tetris(void)
{
	Open_All_Dirver(&driver);
	Tetris_Init(&tetris);
	Arg_Init();

	printf("TETRIS GAME START!!!\n");
	printf("Press <CTRL+C> to quit. \n");

	(void)signal(SIGINT, user_signal1);
	Create_Block(&tetris);
	Turn_On_LED(&tetris, &driver);

	//use Thread!
	if (pthread_create(&myThread, NULL, Use_Switch_Thread, NULL) < 0)
	{
		perror("thread create error!\n");
		exit(0);
	}

	while (!quit)
	{
		if (tetris.isGameOver == false)
		{
			Draw_Block(&tetris, &driver);
			Move_Block(DOWN, &tetris, &driver);

			//AddFunction
			Usleep_Level_Time(&tetris);
		}
	}

	Close_All_Driver(&driver);
	return;
}

#endif