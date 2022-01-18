//��Ϸ��غ�����ʵ��
#include "game.h"

void gotoxy(short x, short y) 
{
	COORD coord = { x, y };
	//COORD��Windows API�ж����һ�ֽṹ�����ͣ���ʾ����̨��Ļ�ϵ����ꡣ
	//��������Ƕ�����COORD���͵ı���coord�������β�x��y���г�ʼ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	//GetStdHandle(STD_OUTPUT_HANDLE); ��ȡ����̨������
	//Ȼ����SetConsoleCursorPosition���ÿ���̨(cmd)���λ��
}
void Menu()
{
	system("cls");
	printf("********************\n");
	printf("*****��������Ϸ*****\n");
	printf("*****1.��ʼ��Ϸ*****\n");
	printf("*****2.��λ����*****\n");
	printf("*****0.�˳���Ϸ*****\n");
	printf("********************\n");
}
void keyboard()
{
	system("cls");
	printf("W        ��\n");
	printf("S        ��\n");
	printf("A        ��\n");
	printf("D        ��\n");
	printf("Enter  ����\n");

}

void initboard(char board[][COL], int row, int col)
{
	//���ո�
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

		//��ӡ1,2��
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
		//��ӡ��3��
		for (int j = 0; j < col && i < row; j++)
		{
			printf("       ");
			if (j < col - 1)
			{
				printf("|");
			}

		}
		printf("\n");
		if (i < row - 1)//���һ�е�  ---  ���ô�ӡ
		{
			//��ӡ��4��
			
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
	printf("��ѡ����Ϸģʽ��\n");
	printf("1.�������\n");
	printf("2.��������\n");
	printf("��ѡ��\n");
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
	//�ж��Ƿ�Ϊ�գ��ж��Ƿ�Խ��
	*pcount += 1;//Ϊʲô++���У�
}

void computercheck(char board[][COL], int row, int col, int* pcount, int* Case)
{
	int i, j;

	//for (i = 0; i < row; i++)//����
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

	if (*pcount == 0)     //��һ��
	{
		//����
		board[0][0] = 'O';
	}
	else if (*pcount == 1)//�ڶ���
	{
		//����
		if (board[1][1] != 'X')//board[1][1] == '\0'???       //��������
			board[1][1] = 'O';
		else
			board[0][0] = 'O';//���б�ռ����ռ��
	}
	else if (*pcount == 2)//������
	{
		//����
		if (board[1][1] == 'X')
		{
			board[2][2] = 'O';
			*Case = 1;//��Һ�������
		}
		else if (board[0][1] == 'X')
		{
			board[2][0] = 'O';
			*Case = 2;//��Һ��ֽ�����
		}
		else if (board[1][0] == 'X')
		{
			board[0][2] = 'O';
			*Case = 3;//��Һ��ֽ�����
		}
		else if (board[0][2] == 'X')
		{
			board[2][0] = 'O';
			*Case = 4;//��Һ����ڽ���
		}
		else if (board[2][0] == 'X')
		{
			board[0][2] = 'O';
			*Case = 5;//��Һ����ڽ���
		}
		else if (board[1][2] == 'X')
		{
			board[2][0] = 'O';
			*Case = 6;//��Һ���Զ����
		}
		else if (board[2][1] == 'X')
		{
			board[0][2] = 'O';
			*Case = 7;//��Һ���Զ����
		}
		else
		{
			board[2][0] = 'O';
			*Case = 8;//��Һ���Զ��
		}
	}
	else if (*pcount == 3)//���Ĳ�
	{
		//����
		if (board[0][0] == board[0][1] && board[0][0] == 'X')//������Ͻ� �ϱ�
		{
			board[0][2] = 'O';
			*Case = 11;
		}
		else if (board[0][1] == board[0][2] && board[0][1] == 'X')//������Ͻ� �ϱ�
		{
			board[0][0] = 'O';
			*Case = 12;
		}
		else if (board[2][0] == board[2][1] && board[2][0] == 'X')//������Ͻ� �±�
		{
			board[2][2] = 'O';
			*Case = 13;
		}
		else if (board[2][2] == board[2][1] && board[2][2] == 'X')//������½� �±�
		{
			board[2][0] = 'O';
			*Case = 14;
		}
		else if (board[0][0] == board[1][0] && board[0][0] == 'X')//������Ͻ� ���
		{
			board[2][0] = 'O';
			*Case = 15;
		}
		else if (board[0][2] == board[1][2] && board[0][2] == 'X')//������Ͻ� �ұ�
		{
			board[2][2] = 'O';
			*Case = 16;
		}
		else if (board[2][0] == board[1][0] && board[2][0] == 'X')//������Ͻ� ���
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
	else if (*pcount == 4)//���岽
	{
		//����
		switch (*Case)
		{
		case 1:
			if (board[0][1] == 'X')     //��ƽ
			{
				board[2][1] = 'O';
				*Case = 11;
			}
			else if (board[1][0] == 'X')//��ƽ
			{
				board[1][2] = 'O';
				*Case = 12;
			}
			else if (board[0][2] == 'X')//����ʤ
			{
				board[2][0] = 'O';
				*Case = 13;
			}
			else if (board[2][0] == 'X')//����ʤ
			{
				board[0][2] = 'O';
				*Case = 14;
			}
			else if (board[1][2] == 'X')//��ƽ
			{
				board[1][0] = 'O';
				*Case = 15;
			}
			else if (board[2][1] == 'X')//��ƽ
			{
				board[0][1] = 'O';
				*Case = 16;
			}
			break;
		//���µ��Ա�ʤ
		case 2:
			if (board[1][0] != 'X')//������Ҳ���
				board[1][0] = 'O';
			else
				board[1][1] = 'O';//[2][2]
			break;
		case 3:
			if (board[0][1] != 'X')//������Ҳ���
				board[0][1] = 'O';
			else
				board[1][1] = 'O';//[2][2]
			break;
		case 4:
			if (board[1][0] != 'X')//������Ҳ���
				board[1][0] = 'O';
			else
				board[2][2] = 'O';
			break;
		case 5:
			if (board[0][1] != 'X')//������Ҳ���
				board[0][1] = 'O';
			else
				board[2][2] = 'O';
			break;
		case 6:
			if (board[1][0] != 'X')//������Ҳ���
				board[1][0] = 'O';
			else
				board[1][1] = 'O';//[2][0],[2][2]
			break;
		case 7:
			if (board[0][1] != 'X')//������Ҳ���
				board[0][1] = 'O';
			else
				board[1][1] = 'O';//[2][0],[2][2]
			break;
		case 8:
			if (board[1][0] != 'X')//������Ҳ���
				board[1][0] = 'O';
			else
				board[0][2] = 'O';
			break;
		}
	}
	else if (*pcount == 5)//������
	{
		//����
		switch (*Case)
		{
			case 11:
			{

			}
		}
	}
	else if (*pcount == 6)//���߲�
	{
		//����
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
	else if (*pcount == 7)//�ڰ˲�
	{
		//����
	}
	else if (*pcount == 8)//�ھŲ�
	{
		//����
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

