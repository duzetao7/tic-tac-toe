//关于游戏相关的函数声明，符号声明，头文件包含
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <windows.h>
#define ROW 3
#define COL 3


void gotoxy(short x, short y);//

void Menu();//菜单

void keyboard();//键位操作

char board[ROW][COL];//棋盘数组

void initboard(char board[][COL], int row, int col);//初始化棋盘

void printboard(char board[][COL], int row, int col);//打印棋盘

void game(char board[][COL], int row, int col);//游戏部分

void SelMenu();//选择菜单

void playercheck(char board[][COL], int row, int col, int* pcount, int* Case);//玩家下棋

void computercheck(char board[][COL], int row, int col, int* pcount, int* Case);//电脑下棋

char Iswin(char board[][COL], int row, int col, int* pcount);//判断游戏是否继续

void printscore(float p_score, float c_score, int round);//计分板
