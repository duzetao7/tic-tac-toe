//������Ϸ���߼�
#include "game.h"

float p_score = 0.0;
float c_score = 0.0;
int round = 0;

int main()
{
	int input = 0;

	do
	{
		//��ӡ�˵�
		Menu();
		printf("��ѡ��>");
		scanf("%d", &input);//1���棬0���˳�
		switch (input)//������ҵ�ѡ�������Ĳ�ͬ��Ӧ��
		{
			case 1:
			{
				game(board, ROW, COL);
				break;//ִ���������switch
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
				printf("��Ϸ����\n");
				break;
			}
			default:
			{
				printf("ѡ�����������ѡ��\n");
				while ('\n' != getchar())
					;
			}
		}
		//��ʼ������
		/*Initboard(board, ROW, COL);*/

	} while (input >= 1);

	return 0;
}

void game(char board[][COL], int row, int col)
{
	system("cls");
	//��ʼ������
	initboard(board, row, col);
	////��ӡ����
	//printboard(board, row, col);
	//��ӡѡ��˵� 
	SelMenu();

	int count = 0;//���������ӵ�����

	int Case = 0;//���

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
				//�����
				system("cls");
				printf("��������壺\n");
				printboard(board, row, col);
				playercheck(board, row, col, &count, &Case);
				system("cls"); printboard(board, row, col);//��������һ���ж���
			}
			if (Iswin(board, row, col, &count) == 0)
			{
				//������
				computercheck(board, row, col, &count, &Case);
				system("cls");
				printf("�����ߣ�\n");
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
				//������
				computercheck(board, row, col, &count, &Case);
				system("cls");
				printf("�����ߣ�\n");
				printboard(board, row, col);
			}
			if (Iswin(board, row, col, &count) == 0)
			{
				//�����
				playercheck(board, row, col, &count, &Case);
			}
			//system("pause");
		}
		break;
	}
	default:
	{
		printf("ѡ�����������ѡ��\n");
		while ('\n' != getchar())
			;
	}
	}
	if (Iswin(board, row, col, &count) == 'X')
	{
		printf("���Ӯ��\n");
		p_score++;
		round++;
	}
	else if (Iswin(board, row, col, &count) == 'O')
	{
		printf("����Ӯ��\n");
		c_score++;
		round++;
	}
	else if (count == 9)
	{
		printf("ƽ��\n");
		round++;
	}
	system("pause");
}