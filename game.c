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
	printf("********************\n");
	printf("*****三子棋游戏*****\n");
	printf("*****1.开始游戏*****\n");
	printf("*****2.键位操作*****\n");
	printf("*****0.退出游戏*****\n");
	printf("********************\n");
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
		else if (temp == '\r')
		{
			board[y / 4][x / 8] = 'X';
			break;
		}

	}
	//判断是否为空，判断是否越界
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
			board[0][0] = 'O';//若中被占，则占边
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
		else if (board[2][0] == board[1][0] && board[2][0] == 'X')//玩家左上角 左边
		{
			board[0][0] = 'O';
			*Case = 17;
		}
		else if (board[1][2] == board[2][2] && board[2][2] == 'X')
		{
			board[0][2] = 'O';
			*Case = 18;
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
				if (board[1][2] != 'X')
					board[1][2] = 'O';
				else
					board[0][2] = 'O';
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
	}
	else if (*pcount == 8)//第九步
	{
		//先手
		switch (*Case)
		{
		case 11:
			if (board[0][2] != 'X')
				board[0][2] = 'O';
			else if (board[2][1] != 'X')
				board[2][1] = 'O';
			else
				board[2][2] = 'O';
			break;
		case 12:
			if (board[2][2] != 'X')
				board[2][2] = 'O';
			else
				board[0][2] = 'O';
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

