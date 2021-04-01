#include "tetrisDM.h"

unsigned char dot_matrix_font[10][10] = {
   { 0x3e,0x7f,0x63,0x73,0x73,0x6f,0x67,0x63,0x7f,0x3e }, // 0
   { 0x0c,0x1c,0x1c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x1e }, // 1
   { 0x7e,0x7f,0x03,0x03,0x3f,0x7e,0x60,0x60,0x7f,0x7f }, // 2
   { 0xfe,0x7f,0x03,0x03,0x7f,0x7f,0x03,0x03,0x7f,0x7e }, // 3
   { 0x66,0x66,0x66,0x66,0x66,0x66,0x7f,0x7f,0x06,0x06 }, // 4
   { 0x7f,0x7f,0x60,0x60,0x7e,0x7f,0x03,0x03,0x7f,0x7e }, // 5
   { 0x60,0x60,0x60,0x60,0x7e,0x7f,0x63,0x63,0x7f,0x3e }, // 6
   { 0x7f,0x7f,0x63,0x63,0x03,0x03,0x03,0x03,0x03,0x03 }, // 7
   { 0x3e,0x7f,0x63,0x63,0x7f,0x7f,0x63,0x63,0x7f,0x3e }, // 8
   { 0x3e,0x7f,0x63,0x63,0x7f,0x3f,0x03,0x03,0x03,0x03 } // 9
};

unsigned char game_over[8][10] = {
	{ 0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7f, 0x63, 0x63, 0x7f, 0x7f },
	{ 0x1c, 0x3e, 0x63, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x63, 0x63 },
	{ 0x63, 0x63, 0x63, 0x77, 0x7f, 0x6b, 0x6b, 0x6b, 0x63, 0x63 },
	{ 0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7f },
	{ 0x7f, 0x7f, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x7f },
	{ 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x1c },
	{ 0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7f },
	{ 0x7f, 0x7f, 0x63, 0x7f, 0x7f, 0x70, 0x78, 0x6c, 0x66, 0x63 }
};

const char dot_tetris[4][4][3] = {
   { { 0x2,0x7,0x0 },{ 0x2,0x3,0x2 },{ 0x7,0x2,0x0 },{ 0x1,0x3,0x1 } },
   { { 0x4,0x7,0x0 },{ 0x3,0x2,0x2 },{ 0x7,0x1,0x0 },{ 0x1,0x1,0x3 } },
   { { 0x6,0x3,0x0 },{ 0x1,0x3,0x2 },{ 0x6,0x3,0x0 },{ 0x1,0x3,0x2 } },
   { { 0x7,0x0,0x0 },{ 0x1,0x1,0x1 },{ 0x7,0x0,0x0 },{ 0x1,0x1,0x1 } }
};

unsigned char dot_matrix_levelup[3][10] = {
   { 0x0,0x0,0x0,0x8,0x1c,0x8,0x8,0x8,0x8,0x8 }, // 0
   { 0x0,0x0,0x8,0x14,0x2a,0x14,0x8,0x8,0x8,0x8 }, // 1
   { 0x0,0x8,0x14,0x2a,0x49,0x2a,0x14,0x8,0x8,0x8 } // 2
};

char matrix_window[10] =
{ 0,0,0,0,0,0,0,0,0,0 };

unsigned char dot_matrix_full[10] =
{ 0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f };

unsigned char dot_matrix_blank[10] =
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

void user_signal1(int sig)
{
	quit = 1;
}

void Tetris_Init(Tetris* tetris)
{
	tetris->curBlock = 0;
	tetris->nextBlock = 0;
	tetris->rotation = 0;
	tetris->isFirstTime = true;
	tetris->isGameOver = false;

	tetris->level = 1;
	tetris->score = 0;
	tetris->scoreNumber = 0;

	tetris->curX = 2;
	tetris->curY = 0;
}

void Arg_Init()
{
	arg[0] = "0000";
	arg[1] = "0010";
	arg[2] = "0020";
	arg[6] = "0060";
	arg[10] = "0100";
	arg[3] = "0030";
	arg[7] = "0070";
	arg[4] = "0040";
	arg[8] = "0080";
	arg[5] = "0050";
	arg[9] = "0090";
}

void Create_Block(Tetris* tetris)
{
	srand((unsigned)time(NULL));

	if (tetris->isFirstTime == true)
	{
		tetris->curBlock = rand() % 4;
		tetris->nextBlock = rand() % 4;
		tetris->isFirstTime = false;

		tetris->curX = 2;
		tetris->curY = 0;
		tetris->rotation = 0;

		return;
	}
	else
	{
		tetris->curBlock = tetris->nextBlock;
		tetris->nextBlock = rand() % 4;

		tetris->curX = 2;
		tetris->curY = 0;
		tetris->rotation = 0;

		return;
	}
}

void Usleep_Level_Time(Tetris* tetris)
{
	if (tetris->level == 1)
		usleep(1000000);
	else if (tetris->level == 2)
		usleep(800000);
	else if (tetris->level == 3)
		usleep(600000);
	else if (tetris->level == 4)
		usleep(400000);
	else if (tetris->level == 5)
		usleep(200000);

}

input_key input_user(Driver* driver)
{
	buff_size = sizeof(push_buff);

	read(driver->SWITCH, push_buff, buff_size);

	if (push_buff[1] == 1) return ROTATE;
	else if (push_buff[3] == 1)return LEFT;
	else if (push_buff[4] == 1)return DOWN;
	else if (push_buff[5] == 1)return RIGHT;
	else return NO;
}

void Draw_Block(Tetris* tetris, Driver* driver)
{
	char temp_window[10] = { 0 };
	int i = 0;
	int j = 0;

	for (i = 0; i < 10; i++)
		temp_window[i] = matrix_window[i];

	for (i = tetris->curY; i < tetris->curY + 3; i++)
		temp_window[i] = matrix_window[i] | dot_tetris[tetris->curBlock][tetris->rotation][j++] << tetris->curX;

	write(driver->DM, temp_window, sizeof(temp_window));
	printf(" curY : %d\n", tetris->curY);
}

void Move_Block(input_key key, Tetris* tetris, Driver* driver)
{
	char number;

	switch (key)
	{
	case LEFT:
		if (Detect_Left_Block(tetris) == false)
			tetris->curX++;
		break;

	case RIGHT:
		if (Detect_Right_Block(tetris) == false)
			tetris->curX--;
		break;

	case DOWN:
		if (Detect_Floor_Block(tetris) || Detect_Block_Block(tetris))
		{
			Pile_Block(tetris, driver);

			if (Detect_Top_Block())
			{
				tetris->isGameOver = true;
				Init_Block(tetris,driver);
				number = 0;
				write(driver->LED, &number, sizeof(number));

				Draw_Game_Over(tetris, driver);
				printf("Tetris is Game over. good bye!\n");
				exit(0);
			}
			Create_Block(tetris);
			Turn_On_LED(tetris, driver);
		}
		else
			tetris->curY++;
		break;

	case ROTATE:
		tetris->rotation = (tetris->rotation + 1) % 4;
		break;

	default:
		break;
	}
}

void Draw_Game_Over(Tetris* tetris, Driver* driver)
{
	int i;
	tetris->scoreNumber = 0;

	for (i = 0; i < 8; i++)
	{
		write(driver->DM, game_over[i], sizeof(game_over[i]));
		usleep(500000);
	}
	for (i = 0; i < 30; i++)
	{
		write(driver->DM, dot_matrix_full, sizeof(dot_matrix_full));
		usleep(50000);
		write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
		usleep(50000);
	}
}

bool Detect_Top_Block()
{
	if (matrix_window[0] & 0x7f)
		return true;
	else
		return false;
}

bool Detect_Left_Block(Tetris* tetris)
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (0x40 & (dot_tetris[tetris->curBlock][tetris->rotation][i] << tetris->curX))
			return true;
	}

	return false;
}

bool Detect_Right_Block(Tetris* tetris)
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (0x1 & (dot_tetris[tetris->curBlock][tetris->rotation][i] << tetris->curX))
			return true;
	}

	return false;
}

bool Detect_Floor_Block(Tetris* tetris)
{
	if (tetris->curY == 7)
	{
		if ((dot_tetris[tetris->curBlock][tetris->rotation][2] << tetris->curX) & 0x7f)
		{
			printf("curY : %d, curBlock : %d, rotation : %d \n", tetris->curY, tetris->curBlock, tetris->rotation);
			return true;
		}
	}
	if (tetris->curY == 8)
	{
		if ((dot_tetris[tetris->curBlock][tetris->rotation][1] << tetris->curX) & 0x7f)
		{
			printf("curY : %d, curBlock : %d, rotation : %d \n", tetris->curY, tetris->curBlock, tetris->rotation);
			return true;
		}
	}
	if (tetris->curY == 9)
	{
		if ((dot_tetris[tetris->curBlock][tetris->rotation][0] << tetris->curX) & 0x7f)
		{
			printf("curY : %d, curBlock : %d, rotation : %d \n", tetris->curY, tetris->curBlock, tetris->rotation);
			return true;
		}
	}

	return false;
}

bool Detect_Block_Block(Tetris* tetris)
{
	int k = 0;

	for (k = 0; k < 3; k++)
	{
		if (matrix_window[k + tetris->curY + 1] & (dot_tetris[tetris->curBlock][tetris->rotation][k] << tetris->curX))
		{
			printf("Detect Block curY : %d\n", tetris->curY);
			
			return true;
		}
	}

	return false;
}

void Pile_Block(Tetris* tetris, Driver* driver)
{
	int i;

	for (i = 0; i < 3; i++)
		matrix_window[i + tetris->curY] |= (dot_tetris[tetris->curBlock][tetris->rotation][i] << tetris->curX);

	Draw_Block(tetris, driver);
	printf("Pile_Block curY : %d\n", tetris->curY);

	if (Detect_Delete(tetris))
		Delete_Line_Block(tetris, driver);
}

bool Detect_Delete(Tetris* tetris)
{
	int i;

	for (i = 0; i < 10; i++)
	{
		if (matrix_window[i] == 0x7f)
			return true;
	}

	return false;
}

void Delete_Line_Block(Tetris* tetris, Driver* driver)
{
	int i, k;
	int j = 9;

	tetris->scoreNumber += 1;

	for (k = 0; k < 4; k++)
		data[k] = arg[tetris->scoreNumber][k] - 0x30;

	write(driver->FPGA, &data, 4);

	while (j != 0)
	{

		if (matrix_window[j] == 0x7f)
		{
			for (i = 0; i < 4; i++)
			{
				matrix_window[j] = 0x0;
				usleep(80000);
				write(driver->DM, matrix_window, sizeof(matrix_window));
				matrix_window[j] = 0x7f;
				usleep(80000);
				write(driver->DM, matrix_window, sizeof(matrix_window));
			}

			for (i = 0; i < 6; i++)
			{
				matrix_window[j] = matrix_window[j] ^ (0x1 << i);
				write(driver->DM, matrix_window, sizeof(matrix_window));

				usleep(80000);
			}

			for (i = j; i >= 0; i--)
			{
				matrix_window[i] = matrix_window[i - 1];
			}

			tetris->score++;
		}

		if (Level_Check(tetris,driver))
		{
			Init_Block(tetris,driver);
			Create_Block(tetris);
			Turn_On_LED(tetris, driver);
		}

		j--;
	}
}

void Init_Block(Tetris* tetris, Driver* driver)
{
	int i;

	for (i = 0; i < 10; i++)
		matrix_window[i] = 0;

	tetris->isFirstTime = true;

	write(driver->DM, matrix_window, sizeof(matrix_window));
}

bool Level_Check(Tetris* tetris, Driver* driver)
{
	int i,k;

	if (tetris->level == 1)
	{
		if (tetris->score == 1)
		{
			tetris->level = 2;
			tetris->score = 0;
			tetris->scoreNumber = 0;

			for (k = 0; k < 4; k++)
				data[k] = arg[tetris->scoreNumber][k] - 0x30;

			write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
			Draw_Clear_Block(tetris, driver);
			usleep(500000);
			write(driver->DM, dot_matrix_font[2], sizeof(dot_matrix_font[2]));
			usleep(500000);
			write(driver->FPGA, &data, 4);
			
			return true;
		}
	}
	else if (tetris->level == 2)
	{
		if (tetris->score == 3)
		{
			tetris->level = 3;
			tetris->score = 0;
			tetris->scoreNumber = 0;

			for (k = 0; k < 4; k++)
				data[k] = arg[tetris->scoreNumber][k] - 0x30;

			write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
			Draw_Clear_Block(tetris, driver);
			usleep(500000);
			write(driver->DM, dot_matrix_font[3], sizeof(dot_matrix_font[3]));
			usleep(500000);
			write(driver->FPGA, &data, 4);

			return true;
		}
	}
	else if (tetris->level == 3)
	{
		if (tetris->score == 5)
		{
			tetris->level = 4;
			tetris->score = 0;
			tetris->scoreNumber = 0;

			for (k = 0; k < 4; k++)
				data[k] = arg[tetris->scoreNumber][k] - 0x30;

			write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
			Draw_Clear_Block(tetris, driver);
			usleep(500000);
			write(driver->DM, dot_matrix_font[3], sizeof(dot_matrix_font[3]));
			usleep(500000);
			write(driver->FPGA, &data, 4);

			return true;
		}
	}
	else if (tetris->level == 4)
	{
		if (tetris->score == 7)
		{
			tetris->level = 5;
			tetris->score = 0;
			tetris->scoreNumber = 0;

			for (k = 0; k < 4; k++)
				data[k] = arg[tetris->scoreNumber][k] - 0x30;

			write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
			Draw_Clear_Block(tetris, driver);
			usleep(500000);
			write(driver->DM, dot_matrix_font[3], sizeof(dot_matrix_font[3]));
			usleep(500000);
			write(driver->FPGA, &data, 4);

			return true;
		}
	}
	else if (tetris->level == 5)
	{
		if (tetris->score == 10)
		{
			for (i = 0; i < 10; i++)
			{
				tetris->scoreNumber = 0;
				write(driver->DM, dot_matrix_blank, sizeof(dot_matrix_blank));
				write(driver->DM, dot_matrix_full, sizeof(dot_matrix_full));
			}

			return true;
		}
	}

	return false;
}

void Draw_Clear_Block(Tetris* tetris, Driver* driver)
{
	unsigned char levelup_matrix[10] = { 0 };
	int i;

	for (i = 9; i > 4; i--)
	{
		levelup_matrix[i] = (0x1 << 3);
		write(driver->DM, levelup_matrix, sizeof(levelup_matrix));
		usleep(100000);
	}

	for (i = 0; i < 3; i++)
	{
		write(driver->DM, dot_matrix_levelup[i], sizeof(dot_matrix_levelup[i]));
		usleep(500000);
	}

	for (i = 0; i < 10; i++)
	{
		write(driver->DM, dot_matrix_levelup[0], sizeof(dot_matrix_levelup[0]));
		usleep(70000);
		write(driver->DM, dot_matrix_levelup[1], sizeof(dot_matrix_levelup[1]));
		usleep(70000);
		write(driver->DM, dot_matrix_levelup[2], sizeof(dot_matrix_levelup[2]));
		usleep(70000);
		write(driver->DM, dot_matrix_levelup[1], sizeof(dot_matrix_levelup[1]));
		usleep(70000);
	}
}

void Turn_On_LED(Tetris* tetris, Driver* driver)
{
	char number = 0;
	write(driver->LED, &number, sizeof(number));
	
	switch (tetris->nextBlock)
	{
	case 0:
		number = 32 + 4 + 2 + 1;
		write(driver->LED, &number, sizeof(number));
		break;
	case 1:
		number = 64 + 4 + 2 + 1;
		write(driver->LED, &number, sizeof(number));
		break;
	case 2:
		number = 64 + 32 + 2 + 1;
		write(driver->LED, &number, sizeof(number));
		break;
	case 3:
		number = 4 + 2 + 1;
		write(driver->LED, &number, sizeof(number));
		break;
	}
}