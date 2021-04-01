#ifndef __TETRIS_DM_H__
#define __TETRIS_DM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include "tetrisDriver.h"
#define MAX_BUTTON 9

typedef struct _tetrisInfo
{
	int level;
	int score;
	int scoreNumber;
	int rotation;
	int curX, curY;
	int curBlock;
	int nextBlock;
	bool isFirstTime;
	bool isGameOver;
}Tetris;

typedef enum { NO, LEFT, RIGHT, DOWN, ROTATE } input_key;

//global variable
unsigned char quit;
int buff_size;
char* arg[54];
unsigned char data[4];
unsigned char push_buff[MAX_BUTTON];

//tetris function definition
void user_signal1(int sig);
void Tetris_Init(Tetris* tetris);
void Arg_Init();
void Create_Block(Tetris* tetris);
void Usleep_Level_Time(Tetris* tetris);
input_key input_user(Driver* driver);
void Turn_On_LED(Tetris* tetris, Driver* driver);
void Draw_Block(Tetris* tetris, Driver* driver);
void Move_Block(input_key key, Tetris* tetris, Driver* driver);
void Draw_Game_Over(Tetris* tetris, Driver* driver);

bool Detect_Top_Block();
bool Detect_Left_Block(Tetris* tetris);
bool Detect_Right_Block(Tetris* tetris);
bool Detect_Floor_Block(Tetris* tetris);
bool Detect_Block_Block(Tetris* tetris);
bool Detect_Delete(Tetris* tetris);
bool Level_Check(Tetris* tetris, Driver* driver);

void Pile_Block(Tetris* tetris, Driver* driver);
void Delete_Line_Block(Tetris* tetris, Driver* driver);
void Init_Block(Tetris* tetris, Driver* driver);
void Draw_Clear_Block(Tetris* tetris, Driver* driver);

#endif