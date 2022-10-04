#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define HIGH 23
#define WIDTH 60

int canvas[HIGH][WIDTH];//��¼��ά������Ϸ�����Ӧ��Ԫ��
						//0����ո� -1����߽� 1�����ͷ* ����1�������* 

int moveDirection;//�ƶ����� 1�� 2�� 3�� 4��

int position_x, position_y;
int operationNumber;
int score;
int speed[10];

int newHead_x;
int newHead_y;

int food_y;
int food_x;

void GameOver();

void gotoxy(int x, int y)  //����ƶ���(x,y)��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void color(short x)	//�Զ��庯���ݲ����ı���ɫ 
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//ֻ��һ���������ı�������ɫ 
	else//Ĭ�ϵ���ɫ��ɫ
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void startup()  //���ݳ�ʼ��
{
	int i,j;
	operationNumber = 5;
	moveDirection = 4;

	/*��ʼ����ͷ����*/
	canvas[HIGH / 2][WIDTH / 2] = 1;
	for (i = 1; i <= 3; i++)
	{
		canvas[HIGH / 2][WIDTH / 2-i] = 1+i;
	}
	newHead_x = 0;
	newHead_y = 0;
	/*�߿�*/
	for (i = 0; i < HIGH; i++)//���ұ߽��ʼ��
	{
		canvas[i][0] = -1;
		canvas[i][WIDTH - 1] = -1;
	}
	for (j = 0; j < WIDTH; j++)//���±߽��ʼ��
	{
		canvas[0][j] = -1;
		canvas[HIGH - 1][j] = -1;
	}

	food_y = rand() % (HIGH-10)+1;
	food_x = rand() % (WIDTH-30)+1;
	canvas[food_y][food_x] = -2;
}

void moveSnakeByDirection()
{
	int i, j;
	int max = 0;
	int oldTail_y = 0;//�ɵ���β
	int oldTail_x = 0;
	int oldHead_y = 0;//�ɵ���ͷ
	int oldHead_x = 0;

	for (i = 1; i < HIGH - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			if (canvas[i][j] > 0)
			{
				//�����д���0��Ԫ�ؼ�һ
				canvas[i][j]++;

				if (max < canvas[i][j])//������β
				{
					max = canvas[i][j];
					oldTail_y = i;
					oldTail_x = j;
				}

				if (canvas[i][j] == 2)//��¼����ͷλ��
				{
					oldHead_y = i;
					oldHead_x = j;
				}
			}
		}
	}
	

	if (moveDirection == 1)
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y - 1;
	}
	if (moveDirection == 2)
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y + 1;
	}
	if (moveDirection == 3)
	{
		newHead_x = oldHead_x - 1;
		newHead_y = oldHead_y;
	}	
	if (moveDirection == 4)
	{
		newHead_x = oldHead_x + 1;
		newHead_y = oldHead_y;
	}
	
	//�ж�С����ͷ�Ƿ�����ʳ��
	if (canvas[newHead_y][newHead_x] == -2)
	{
		//�Ե�ʳ�� ��β����Ϊ0
		canvas[food_y][food_x] = 0;
		food_y = rand() % (HIGH - 10);
		food_x = rand() % (WIDTH - 30);
		canvas[food_y][food_x] = -2;
	}
	else
	{
		//û�гԵ�ʳ�ﳤ�Ȳ���
		canvas[oldTail_y][oldTail_x] = 0;//��β��Ϊ�ո�
	}


	//��Ϸʧ������
	if (canvas[newHead_y][newHead_x] == -1 || canvas[newHead_y][newHead_x]>0)
	{
		color(4);
		printf("\nGAME OVER!");
		system("pause");
		exit(0);
	}
	else
	{
		//�����������ͷλ�øı�
		canvas[newHead_y][newHead_x] = 1;
	}

}

void show()  //��ʾ����
{

	int i, j;//i��y�� j��x��
	gotoxy(0, 0); //�������� ����ƶ������Ͻ�

	for (i = 0; i < HIGH; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (canvas[i][j] == 0)
				printf(" ");
			else if (canvas[i][j] == -1)
			{
				color(6);
				printf("#");//����߿�
				color(16);
			}
			else if (canvas[i][j] == 1)//�����ͷ
			{
				color(10);
				printf("*");
				color(16);
			}
			else if (canvas[i][j] >= 1)//�������
			{
				color(10);
				printf("*");
				color(16);
			}
			else if (canvas[i][j] == -2)
			{
				color(11);
				printf("*");
				color(16);
			}
				
		}
		printf("\n");
	}
	
}


void updateWithoutInput() //�û������޹صĲ���
{
	int i, j, k;
	
	
	for (i = 0; i < operationNumber; i++)
	{
		speed[i]++;
	}
	if (speed[0] == 5)
	{
		moveSnakeByDirection();
		speed[0] = 0;
	}
	
}


void updateWithInput() //��������
{
	char input;
	if (_kbhit())//������ʱִ��
	{
		input = _getch();
		if (input == 'a')
		{
			moveDirection = 3;
		}
		if (input == 'd')
		{
			moveDirection = 4;
		}
		if (input == 'w')
		{
			moveDirection = 1;
		}
		if (input == 's')
		{
			moveDirection = 2;
		}

		if (input == 27)//ESC��ͣ
			system("pause");

	}
}

void CleanCursor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}//ȥ������̨���

int main()
{
	srand((unsigned)time(NULL));//���������
	CleanCursor();//ȥ������̨���
	startup();//���ݳ�ʼ��

	while (1)
	{
		srand((int)time(NULL));//���������
		show();//��ʾ����
		updateWithoutInput();//�û������޹صĲ���
		updateWithInput();//�йصĲ���
	}
	return 0;
}





/*
��ɫ����SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ǰ��ɫ | ����ɫ | ǰ����ǿ | ������ǿ);
	ǰ��ɫ������0-15 �� FOREGROUND_XXX ��ʾ	������XXX����BLUE��RED��GREEN��ʾ��
	ǰ����ǿ������8 �� FOREGROUND_INTENSITY ��ʾ
	����ɫ������16 32 64 �� BACKGROUND_XXX ������ɫ��ʾ
	������ǿ�� ����128 �� BACKGROUND_INTENSITY ��ʾ
��ҪӦ�ã��ı�ָ�����������뱳������ɫ
ǰ����ɫ��Ӧֵ��
����0=��ɫ                8=��ɫ����
  ��1=��ɫ                9=����ɫ        ʮ������        ����
����2=��ɫ                10=����ɫ       0xa        ����
����3=����ɫ              11=��ǳ��ɫ     0xb��
����4=��ɫ                12=����ɫ       0xc����
����5=��ɫ                13=����ɫ       0xd        ����
����6=��ɫ                14=����ɫ       0xe        ����
����7=��ɫ                15=����ɫ       0xf
����Ҳ���԰���Щֵ���óɳ�����
*/
