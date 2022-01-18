//测试游戏的逻辑
#include "game.h"

float p_score = 0.0;
float c_score = 0.0;
int round = 0;

int main()
{
	int input = 0;

	do
	{
		//打印菜单
		Menu();
		printf("请选择：>");
		scanf("%d", &input);//1就玩，0就退出
		switch (input)//根据玩家的选择做出的不同的应对
		{
			case 1:
			{
				game(board, ROW, COL);
				break;//执行完就跳出switch
			}
			case 2:
			{
				keyboard();
				system("pause");
				break;
			}
			case 3:
			{
				printscore(p_score, c_score, round);
				system("pause");
				break;
			}
			case 0:
			{
				printf("游戏结束\n");
				break;
			}
			default:
			{
				printf("选择错误，请重新选择：\n");
				while ('\n' != getchar())
					;
			}
		}
		//初始化棋盘
		/*Initboard(board, ROW, COL);*/

	} while (input >= 1);

	return 0;
}

void game(char board[][COL], int row, int col)
{
	system("cls");
	//初始化棋盘
	initboard(board, row, col);
	////打印出来
	//printboard(board, row, col);
	//打印选择菜单 
	SelMenu();

	int count = 0;//棋盘上棋子的数量

	int Case = 0;//情况

	int z;
	scanf("%d", &z);
	switch (z)
	{
	case 1:
	{
		while (Iswin(board, row, col, &count) == 0)
		{
			if (Iswin(board, row, col, &count) == 0)
			{
				//玩家走
				system("cls");
				printf("玩家请下棋：\n");
				printboard(board, row, col);
				playercheck(board, row, col, &count, &Case);
				system("cls"); printboard(board, row, col);//玩家是最后一个行动的
			}
			if (Iswin(board, row, col, &count) == 0)
			{
				//电脑走
				computercheck(board, row, col, &count, &Case);
				system("cls");
				printf("电脑走：\n");
				printboard(board, row, col);
			}
		}
		break;
	}
	case 2:
	{
		while (Iswin(board, row, col, &count) == 0)
		{
			if (Iswin(board, row, col, &count) == 0)
			{
				//电脑走
				computercheck(board, row, col, &count, &Case);
				system("cls");
				printf("电脑走：\n");
				printboard(board, row, col);
			}
			if (Iswin(board, row, col, &count) == 0)
			{
				//玩家走
				playercheck(board, row, col, &count, &Case);
			}
			//system("pause");
		}
		break;
	}
	default:
	{
		printf("选择错误，请重新选择：\n");
		while ('\n' != getchar())
			;
	}
	}
	if (Iswin(board, row, col, &count) == 'X')
	{
		printf("玩家赢了\n");
		p_score++;
		round++;
	}
	else if (Iswin(board, row, col, &count) == 'O')
	{
		printf("电脑赢了\n");
		c_score++;
		round++;
	}
	else if (count == 9)
	{
		printf("平局\n");
		round++;
	}
	system("pause");
}