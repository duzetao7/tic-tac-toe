//������Ϸ���߼�
#include "game.h"

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

	int case_a = 0;//������ֵ����

	int case_b = 0;//�������ֵ����

	int z;
	scanf("%d", &z);
	switch (z)
	{
	case 1:
	{
		while (Iswin(board, row, col, &count))
		{
			if (Iswin(board, row, col, &count) != 0)
			{
				//�����
				playercheck(board, row, col, &count, &case_b);
				system("cls");
				printf("����ߣ�\n");
				printboard(board, row, col);
			}
			if (Iswin(board, row, col, &count) != 0)
			{
				//������
				computercheck(board, row, col, &count, &case_b);
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
				computercheck(board, row, col, &count, &case_b);
				system("cls");
				printf("�����ߣ�\n");
				printboard(board, row, col);
			}
			if (Iswin(board, row, col, &count) == 0)
			{
				//�����
				playercheck(board, row, col, &count, &case_b);
				system("cls");
				printf("����ߣ�\n");
				printboard(board, row, col);
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
		printf("���Ӯ��\n");
	else if (Iswin(board, row, col, &count) == 'O')
		printf("����Ӯ��\n");
	else if (count == 9)
		printf("ƽ��\n");
	system("pause");
}

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
			case 0:
			{
				printf("exit\n");
				break;
			}
			default:
			{
				printf("fault\n");
				break; 
			}
		}
		//��ʼ������
		/*Initboard(board, ROW, COL);*/

	} while (input >= 1);

	return 0;
}