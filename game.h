//������Ϸ��صĺ�������������������ͷ�ļ�����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <windows.h>
#define ROW 3
#define COL 3


void gotoxy(short x, short y);//

void Menu();//�˵�

void keyboard();//��λ����

char board[ROW][COL];//��������

void initboard(char board[][COL], int row, int col);//��ʼ������

void printboard(char board[][COL], int row, int col);//��ӡ����

void game(char board[][COL], int row, int col);//��Ϸ����

void SelMenu();//ѡ��˵�

void playercheck(char board[][COL], int row, int col, int* pcount, int* Case);//�������

void computercheck(char board[][COL], int row, int col, int* pcount, int* Case);//��������

char Iswin(char board[][COL], int row, int col, int* pcount);//�ж���Ϸ�Ƿ����

void printscore(float p_score, float c_score, int round);//�Ʒְ�
