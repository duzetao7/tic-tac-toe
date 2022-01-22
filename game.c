//游戏相关函数的实现
#include "game.h"

void gotoxy(short x, short y) 
{
	COORD coord = { x, y };
	//COORD是Windows API中定义的一种结构体类型，表示控制台屏幕上的坐标。
	//上面语句是定义了COORD类型的变量coord，并以形参x和y进行初始化。
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	//GetStdHandle(STD_OUTPUT_HANDLE); 获取控制台输出句柄
	//然后用SetConsoleCursorPosition设置控制台(cmd)光标位置
}
void Menu()
{
	system("cls");
	printf("                    \n");
	printf("     三子棋游戏     \n");
	printf("     1.开始游戏     \n");
	printf("     2.键位操作     \n");
	printf("     3.得分情况     \n");
	printf("     0.退出游戏     \n");
	printf("                    \n");
}
void keyboard()
{
	system("cls");
	printf("W        上\n");
	printf("S        下\n");
	printf("A        左\n");
	printf("D        右\n");
	printf("Enter  下棋\n");

}

void initboard(char board[][COL], int row, int col)
{
	//填充空格
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}

}

void printboard(char board[][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{

		//打印1,2行
		for (int j = 0; j < col && i < row; j++)
		{
			printf("       ");
			if (j < col - 1)
			{
				printf("|");
			}

		}
		printf("\n");
		for (int j = 0; j < col; j++)
		{
			printf("   %c   ", board[i][j]);
			if (j < col - 1)
			{
				printf("|");
			}

		}
		printf("\n");
		//打印第3行
		for (int j = 0; j < col && i < row; j++)
		{
			printf("       ");
			if (j < col - 1)
			{
				printf("|");
			}

		}
		printf("\n");
		if (i < row - 1)//最后一行的  ---  不用打印
		{
			//打印第4行
			
			for (int k = 0; k < col; k++)
			{
				printf("-------");
				if (k < col - 1)
				{
					printf("|");
				}
			}
			printf("\n");
		}
	}
}

void SelMenu()
{
	printf("请选择游戏模式：\n");
	printf("1.玩家先手\n");
	printf("2.电脑先手\n");
	printf("请选择：\n");
}

void playercheck(char board[][COL], int row, int col, int* pcount)
{
	int x = 3, y = 2;
	gotoxy(x, y);
	while (1)
	{
		char temp = getch();
		if (temp == 'w' && y > 2)
		{
			y -= 4;
			gotoxy(x, y);
			continue;
		}
		else if (temp == 's' && y < 10)
		{
			y += 4;
			gotoxy(x, y);
			continue;
		}
		else if (temp == 'a' && x > 3)
		{
			x -= 8;
			gotoxy(x, y);
			continue;
		}
		else if (temp == 'd' && x < 19)
		{
			x += 8;
			gotoxy(x, y);
			continue;
		}
		else if ((temp == '\r') && (board[y / 4][x / 8] == ' '))
		{
			board[y / 4][x / 8] = 'X';
			break;
		}

	}
	*pcount += 1;//为什么++不行？
}

void computercheck(char board[][COL], int row, int col, int* pcount, int* Case)
{
	int i, j;

	//for (i = 0; i < row; i++)//堵行
	//{
	//	for (j = 0; j < col - 1; j++)
	//	{
	//		if (board[i][j] == board[i][j + 1])
	//			if (j = 0)
	//				board[i][j + 2] = 'O';
	//			else
	//				board[i][j - 1] = 'O';
	//	}
	//}

	if (*pcount == 0)     //第一步
	{
		//先手
		board[0][0] = 'O';
	}
	else if (*pcount == 1)//第二步
	{
		//后手
		if (board[1][1] != 'X')//board[1][1] == '\0'???       //后手抢中
			board[1][1] = 'O';
		else
			board[0][0] = 'O';//若中被占，则占角
	}
	else if (*pcount == 2)//第三步
	{
		//先手
		if (board[1][1] == 'X')
		{
			board[2][2] = 'O';
			*Case = 1;//玩家后手中心
		}
		else if (board[0][1] == 'X')
		{
			board[2][0] = 'O';
			*Case = 2;//玩家后手近边上
		}
		else if (board[1][0] == 'X')
		{
			board[0][2] = 'O';
			*Case = 3;//玩家后手近边下
		}
		else if (board[0][2] == 'X')
		{
			board[2][0] = 'O';
			*Case = 4;//玩家后手邻角上
		}
		else if (board[2][0] == 'X')
		{
			board[0][2] = 'O';
			*Case = 5;//玩家后手邻角下
		}
		else if (board[1][2] == 'X')
		{
			board[2][0] = 'O';
			*Case = 6;//玩家后手远边上
		}
		else if (board[2][1] == 'X')
		{
			board[0][2] = 'O';
			*Case = 7;//玩家后手远边下
		}
		else
		{
			board[2][0] = 'O';
			*Case = 8;//玩家后手远角
		}
	}
	else if (*pcount == 3)//第四步
	{
		//后手
		if (board[0][0] == board[0][1] && board[0][0] == 'X')//玩家左上角 上边
		{
			board[0][2] = 'O';
			*Case = 11;
		}
		else if (board[0][1] == board[0][2] && board[0][1] == 'X')//玩家右上角 上边
		{
			board[0][0] = 'O';
			*Case = 12;
		}
		else if (board[2][0] == board[2][1] && board[2][0] == 'X')//玩家左上角 下边
		{
			board[2][2] = 'O';
			*Case = 13;
		}
		else if (board[2][2] == board[2][1] && board[2][2] == 'X')//玩家右下角 下边
		{
			board[2][0] = 'O';
			*Case = 14;
		}
		else if (board[0][0] == board[1][0] && board[0][0] == 'X')//玩家左上角 左边
		{
			board[2][0] = 'O';
			*Case = 15;
		}
		else if (board[0][2] == board[1][2] && board[0][2] == 'X')//玩家右上角 右边
		{
			board[2][2] = 'O';
			*Case = 16;
		}
		else if (board[2][0] == board[1][0] && board[2][0] == 'X')//玩家右下角 左边
		{
			board[0][0] = 'O';
			*Case = 17;
		}
		else if (board[1][2] == board[2][2] && board[2][2] == 'X')//玩家右下角 右边
		{
			board[0][2] = 'O';
			*Case = 18;
		}
		else if (board[0][0] == board[0][2] && board[0][2] == 'X')//玩家左上角 右上角
		{
			board[0][1] = 'O';
			*Case = 21;
		}
		else if (board[0][0] == board[2][0] && board[0][0] == 'X')//玩家左上角 左下角
		{
			board[1][0] = 'O';
			*Case = 22;
		}
		else if (board[0][2] == board[2][2] && board[2][2] == 'X')//玩家右上角 右下角
		{
			board[1][2] = 'O';
			*Case = 23;
		}
		else if (board[2][0] == board[2][2] && board[2][2] == 'X')//玩家左下角 右下角
		{
			board[2][1] = 'O';
			*Case = 24;
		}
		else if (board[0][0] == board[1][2] && board[1][2] == 'X')//玩家左上角 右边
		{
			board[2][1] = 'O';
			*Case = 31;//占远边
		}
		else if (board[0][0] == board[2][1] && board[2][1] == 'X')//玩家左上角 下边
		{
			board[1][0] = 'O';
			*Case = 32;
		}
		else if (board[0][2] == board[1][0] && board[0][2] == 'X')//玩家右上角 左边
		{
			board[2][1] = 'O';
			*Case = 33;
		}
		else if (board[0][2] == board[2][1] && board[0][2] == 'X')//玩家右上角 下边
		{
			board[1][0] = 'O';
			*Case = 34;
		}
		else if (board[0][1] == board[2][0] && board[0][1] == 'X')//玩家左下角 上边
		{
			board[1][2] = 'O';
			*Case = 35;
		}
		else if (board[1][2] == board[2][0] && board[1][2] == 'X')//玩家左下角 右边
		{
			board[0][1] = 'O';
			*Case = 36;
		}
		else if (board[0][1] == board[2][2] && board[0][1] == 'X')//玩家右下角 上边
		{
			board[1][0] = 'O';
			*Case = 37;
		}
		else if (board[1][0] == board[2][2] && board[1][0] == 'X')//玩家右下角 左边
		{
			board[0][1] = 'O';
			*Case = 38;
		}
		//case 4X 电脑可负
		else if (board[0][0] == board[2][2] && board[0][0] == 'X')//玩家左上角 右下角
		{
			board[1][0] = 'O';
			*Case = 41;
		}
		else if (board[0][2] == board[2][0] && board[2][0] == 'X')//玩家右上角 左下角
		{
			board[1][0] = 'O';
			*Case = 42;
		}
		//玩家双边
		else if (board[0][1] == board[1][0] && board[1][0] == 'X')//玩家上边 左边
		{
			board[0][0] = 'O';
			*Case = 61;
		}
		else if (board[0][1] == board[1][2] && board[1][2] == 'X')
		{
			board[0][2] = 'O';
			*Case = 62;
		}
		else if (board[0][1] == board[2][1] && board[0][1] == 'X')//电脑胜
		{
			board[0][0] = 'O';
			*Case = 63;
		}
		else if (board[1][0] == board[1][2] && board[1][0] == 'X')//电脑胜
		{
			board[0][0] = 'O';
			*Case = 64;
		}
		else if (board[1][2] == board[2][1] && board[1][2] == 'X')
		{
			board[2][2] = 'O';
			*Case = 65;
		}
		//玩家占中
		else if (board[0][1] == board[1][1] && board[0][1] == 'X')//玩家上边 中
		{
			board[2][1] = 'O';
			*Case = 52;
		}
		else if (board[0][2] == board[1][1] && board[1][1] == 'X')//玩家右上角 中
		{
			board[2][0] = 'O';
			*Case = 53;
		}
		else if (board[1][0] == board[1][1] && board[1][1] == 'X')//玩家左边 中
		{
			board[1][2] = 'O';
			*Case = 54;
		}
		else if (board[1][2] == board[1][1] && board[1][1] == 'X')//玩家右边 中
		{
			board[1][0] = 'O';
			*Case = 55;
		}
		else if (board[2][0] == board[1][1] && board[1][1] == 'X')//玩家左下角 中
		{
			board[0][2] = 'O';
			*Case = 56;
		}
		else if (board[2][1] == board[1][1] && board[1][1] == 'X')//玩家下边 中
		{
			board[0][1] = 'O';
			*Case = 57;
		}
		else if (board[1][0] == board[1][1] && board[1][1] == 'X')//玩家右下角 中
		{
			board[0][2] = 'O';//变
			*Case = 58;
		}
	}
	else if (*pcount == 4)//第五步
	{
		//先手
		switch (*Case)
		{
		case 1:
			if (board[0][1] == 'X')     //必平
			{
				board[2][1] = 'O';
				*Case = 11;
			}
			else if (board[1][0] == 'X')//必平
			{
				board[1][2] = 'O';
				*Case = 12;
			}
			else if (board[0][2] == 'X')//电脑胜
			{
				board[2][0] = 'O';
				*Case = 13;
			}
			else if (board[2][0] == 'X')//电脑胜
			{
				board[0][2] = 'O';
				*Case = 14;
			}
			else if (board[1][2] == 'X')//必平
			{
				board[1][0] = 'O';
				*Case = 15;
			}
			else if (board[2][1] == 'X')//必平
			{
				board[0][1] = 'O';
				*Case = 16;
			}
			break;
		//以下电脑必胜
		case 2:
			if (board[1][0] != 'X')//避免玩家不堵
				board[1][0] = 'O';
			else
				board[1][1] = 'O';//[2][2]
			break;
		case 3:
			if (board[0][1] != 'X')//避免玩家不堵
				board[0][1] = 'O';
			else
				board[1][1] = 'O';//[2][2]
			break;
		case 4:
			if (board[1][0] != 'X')//避免玩家不堵
				board[1][0] = 'O';
			else
				board[2][2] = 'O';
			break;
		case 5:
			if (board[0][1] != 'X')//避免玩家不堵
				board[0][1] = 'O';
			else
				board[2][2] = 'O';
			break;
		case 6:
			if (board[1][0] != 'X')//避免玩家不堵
				board[1][0] = 'O';
			else
				board[1][1] = 'O';//[2][0],[2][2]
			break;
		case 7:
			if (board[0][1] != 'X')//避免玩家不堵
				board[0][1] = 'O';
			else
				board[1][1] = 'O';//[2][0],[2][2]
			break;
		case 8:
			if (board[1][0] != 'X')//避免玩家不堵
				board[1][0] = 'O';
			else
				board[0][2] = 'O';
			break;
		}
	}
	else if (*pcount == 5)//第六步
	{
		//后手
		switch (*Case)
		{
			case 11:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 12:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 13:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 14:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 15:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 16:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 17:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 18:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 21:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 22:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 23:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 24:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 31:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 32:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 33:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[0][0] = 'O';
				break;
			}
			case 34:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 35:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[0][0] = 'O';
				break;
			}
			case 36:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 37:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 38:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 41:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 42:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 61:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 62:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[0][0] = 'O';
				break;
			}
			case 63:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 64://=61
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 65:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 52:
			{
				if (board[0][2] == 'X')
				{
					board[2][0] = 'O';
					*Case = 521;
				}
				else if (board[1][0] == 'X')
				{
					board[1][2] = 'O';
					*Case = 522;
				}
				else if (board[1][2] == 'X')
				{
					board[1][0] = 'O';
					*Case = 523;
				}
				else if (board[2][0] == 'X')
				{
					board[0][2] = 'O';
					*Case = 524;
				}
				else if (board[2][2] == 'X')
				{
					board[2][0] = 'O';
					*Case = 525;
				}
				break;
			}
			case 53:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 54:
			{
				if (board[0][1] == 'X')
				{
					board[2][1] = 'O';
					*Case = 541;
				}
				else if (board[0][2] == 'X')
				{
					board[2][0] = 'O';
					*Case = 542;
				}
				else if (board[2][0] == 'X')
				{
					board[0][2] = 'O';
					*Case = 543;
				}
				else if (board[2][1] == 'X')
				{
					board[0][1] = 'O';
					*Case = 544;
				}
				else if (board[2][2] == 'X')
				{
					board[2][0] = 'O';
					*Case = 545;
				}
				break;
			}
			case 55:
			{
				if (board[2][0] != 'X')
					board[2][0] = 'O';
				else board[0][2] = 'O';
				break;
			}
			case 56:
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else board[2][1] = 'O';
				break;
			}
			case 57:
			{
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else board[2][0] = 'O';
				break;
			}
			case 58:
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else board[2][1] = 'O';
				break;
			}
		}
	}
	else if (*pcount == 6)//第七步
	{
		//先手
		switch (*Case)
		{
			case 11:
				if (board[2][0] != 'X')
					board[2][0] = 'O';
				else
					board[0][2] = 'O';
				break;
			case 12:
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			case 13:
				if (board[1][0] != 'X')
					board[1][0] = 'O';
				else
					board[2][1] = 'O';
				break;
			case 14:
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else
					board[1][2] = 'O';
				break;
			case 15:
				if (board[2][0] != 'X')
					board[2][0] = 'O';
				else
					board[0][2] = 'O';
				break;
			case 16:
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			case 2://=6
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			case 3://=7
				if (board[2][0] != 'X')
					board[2][0] = 'O';
				else
					board[2][2] = 'O';
				break;
			case 4:
				if (board[1][1] != 'X')
					board[1][1] = 'O';
				else
					board[2][1] = 'O';
				break;
			case 5:
				if (board[1][1] != 'X')
					board[1][1] = 'O';
				else
					board[1][2] = 'O';
				break;
			case 6:
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			case 7:
				if (board[2][0] != 'X')
					board[2][0] = 'O';
				else
					board[2][2] = 'O';
				break;
			case 8:
				if (board[1][1] != 'X')
					board[1][1] = 'O';
				else
					board[0][1] = 'O';
				break;
		}
	}
	else if (*pcount == 7)//第八步
	{
		//后手
		switch (*Case)
		{
			case 11:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 12:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 13:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 14:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[0][0] = 'O';
				break;
			}
			case 15:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 16:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 17:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 18:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[0][0] = 'O';
				break;
			}
			case 21:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 22:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 23:
			{
				if (board[2][1] != 'X')//避免玩家不堵
					board[2][1] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 24:
			{
				if (board[1][2] != 'X')//避免玩家不堵
					board[1][2] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 31:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 32:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 33:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 34:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 35:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 36:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 37:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 38:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 41:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 42:
			{
				if (board[0][0] != 'X')//避免玩家不堵
					board[0][0] = 'O';
				else
					board[0][1] = 'O';
				break;
			}
			case 61:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 62:
			{
				if (board[2][2] != 'X')//避免玩家不堵
					board[2][2] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 63:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 64:
			{
				if (board[0][1] != 'X')//避免玩家不堵
					board[0][1] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 65:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[1][0] = 'O';
				break;
			}
			case 521:
			{
				if (board[1][0] != 'X')//两头蛇
					board[1][0] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 522:
			{
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 523:
			{
				if (board[2][0] != 'X')//避免玩家不堵
					board[2][0] = 'O';
				else
					board[0][2] = 'O';
				break;
			}
			case 524:
			{
				if (board[1][0] != 'X')
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 525:
			{
				if (board[1][0] != 'X')//避免玩家不堵
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 53:
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 541://=522
			{
				if (board[0][2] != 'X')
					board[0][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 542://=53
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 543:
			{
				if (board[0][1] != 'X')//两头蛇
					board[0][1] = 'O';
				else
					board[2][2] = 'O';
				break;
			}
			case 544:
			{
				if (board[0][2] != 'X')//避免玩家不堵
					board[0][2] = 'O';
				else
					board[2][0] = 'O';
				break;
			}
			case 545:
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 55:
			{
				if (board[0][1] != 'X')
					board[0][1] = 'O';
				else
					board[2][1] = 'O';
				break;
			}
			case 56://=57=58
			{
				if (board[1][0] != 'X')
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 57:
			{
				if (board[1][0] != 'X')
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
			case 58:
			{
				if (board[1][0] != 'X')
					board[1][0] = 'O';
				else
					board[1][2] = 'O';
				break;
			}
		}
	}
	else if (*pcount == 8)//第九步
	{
		//先手
		switch (*Case)
		{
		case 11:
			if (board[1][2] != 'X')
				board[1][2] = 'O';
			else
				board[1][0] = 'O';
			break;
		case 12:
			if (board[2][1] != 'X')
				board[2][1] = 'O';
			else
				board[0][1] = 'O';
			break;
		case 15:
			if (board[0][1] != 'X')
				board[0][1] = 'O';
			else
				board[2][1] = 'O';
			break;
		case 16:
			if (board[1][0] != 'X')
				board[1][0] = 'O';
			else
				board[1][2] = 'O';
			break;
		}
	}
	*pcount += 1;
}

char Iswin(char board[][COL], int row, int col, int* pcount)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
		{
			return board[i][0];
			break;
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
		{
			return board[0][i];
			break;
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return board[0][0];
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
		return board[0][2];
	else if (*pcount == 9)
		return 1;
	else if (*pcount < 9)
		return 0;
}

void printscore(float p_score, float c_score, int round)
{
	system("cls");
	printf("玩家胜 %.0f 局，胜率  %.2f%%\n", p_score, (p_score * 100) / round);
	printf("电脑胜 %.0f 局，胜率  %.2f%%\n", c_score, (c_score * 100) / round);
	printf("平     %.0f 局\n", round - p_score - c_score);
	if (p_score < c_score)
		printf("你要加油了哦ヾ(≧▽≦*)o\n");
	else if (p_score == c_score)
		printf("电脑和你不相上下呀(●ˇ∀ˇ●)\n");
}

