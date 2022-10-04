#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#define HIGH 23
#define WIDTH 60
#define ENEMYNUMBER 5 //�л���Ŀ

int canvas[HIGH+1][WIDTH+1];//��¼��ά������Ϸ�����Ӧ��Ԫ��
						//0����ո� 1����ɻ� 2����ӵ� 3�ǵл� 

int position_x, position_y;
int bullet_x, bullet_y;
int enemy_x[ENEMYNUMBER], enemy_y[ENEMYNUMBER];
int BulletWidth;//�ӵ����
int BulletNumber;//�ӵ���Ŀ
int EnemySpeed;
int operationNumber;

int score;
int speed[10];

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
	int k;
	
	position_x = WIDTH / 2;
	position_y = HIGH - 5;
	
	for (k = 0; k < ENEMYNUMBER; k++)//�����̨�л�
	{
		enemy_x[k] = rand() % WIDTH;
		enemy_y[k] = rand() % 4;
		canvas[enemy_y[k]][enemy_x[k]] = 3;
	}
	
	EnemySpeed = 50;

	BulletWidth = 0;
	BulletNumber = 10;

	canvas[position_y][position_x] = 1;
	
	score = 0;

	operationNumber = 3;
}

void show()  //��ʾ����
{

	int i, j;//i��y�� j��x��
	gotoxy(0, 0); //�������� ����ƶ������Ͻ�

	for (i = 0; i < HIGH; i++)
	{
		//printf("|");
		for (j = 0; j <WIDTH; j++)
		{
			if (canvas[i][j] == 1)
			{
				color(13);
				printf("*");//����ɻ�
				color(16);
			}
				
			else if (canvas[i][j] == 0)
				printf(" ");
			else if (canvas[i][j] == 2)//����ӵ�
			{
				color(14);
				printf("|");
				color(16);
			}
			else if (canvas[i][j] == 3)//����л�
				printf("@");
		}
		printf("\n");
	}
	color(4); printf("�÷� = %-2d\n", score);
	color(6); printf("�ӵ���Ŀ = %-2d \n", BulletNumber);
	color(15); printf("\nWASD�ƶ� �ո���");
	printf("\n����Խ���ӵ�Խǿ���о�Ҳ����죡\n");
	printf("�о������±߽�۷֣�����С��0�������л�ʱ��Ϸ����\n");
	color(16);
}


void updateWithoutInput() //�û������޹صĲ���
{
	int i, j, k;
	//srand((unsigned)time(NULL));//���������

	for (i = 0; i < operationNumber; i++)
	{
		speed[i]++;
	}

	//�ӵ�����
	if (speed[0] == 2)
	{
		for (i = 0; i < HIGH; i++)//���������ӵ�
		{
			for (j = 0; j < WIDTH; j++)
			{
				if (canvas[i][j] == 2) //ʹ���ӵ��Զ������ƶ� ������ӵ�
				{
					for (k = 0;k < ENEMYNUMBER; k++)
					{
						if ((i == enemy_y[k] && j == enemy_x[k])||( i == enemy_y[k]+1 && j == enemy_x[k]))//���ел���ʱ��
						{
							srand((int)time(NULL));//���������
							canvas[enemy_y[k]][enemy_x[k]] = 0;
							enemy_x[k] = rand() % (WIDTH-1);
							enemy_y[k] = rand() % 1;
							score++;

							if (score % 5 == 0)//�ӵ���� �л���� Ҫд�ڻ��ел���˲��
							{
								BulletWidth += 1;
								EnemySpeed = EnemySpeed - 5;
							}
						}

					}

					canvas[i][j] = 0;//�ӵ���ʧ 

					if (i > 0)//�ӵ������ƶ�
					{
						canvas[i - 1][j] = 2;
					}
					else
					{
						canvas[i][j] = 0;
					}
				}
			}
		}
		speed[0] = 0;
	}


	//�л�����
	if(speed[1] == EnemySpeed)
	{
		for (k = 0; k < ENEMYNUMBER; k++)
		{
			if (enemy_y[k] < HIGH)//�л��Զ�����
			{
				canvas[enemy_y[k]][enemy_x[k]] = 0;
				enemy_y[k]++;
				canvas[enemy_y[k]][enemy_x[k]] = 3;
			}
			else if(enemy_y[k] >= HIGH)
			{
				score-=1;
				canvas[enemy_y[k]][enemy_x[k]] = 0;
				enemy_x[k] = rand() % WIDTH;
				enemy_y[k] = rand() % 2;
			}
		}
		speed[1] = 0;//���ٺ�������
		
	}
	
	//�����ӵ�
	if (speed[2] == 100)
	{
		BulletNumber++;
		speed[2] = 0;
	}

	GameOver();
}

void GameOver()
{
	int k;
	if (score < 0)
	{
		printf("GameOver!");
		system("pause");
	}
	if(score>50)
	{
		printf("You Win!");
		system("pause");
	}
	for (k = 0; k < ENEMYNUMBER; k++)
	{
		if (position_x == enemy_x[k] && position_y == enemy_y[k])
		{
			printf("GameOver!");
			system("pause");
		}
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
				canvas[position_y][position_x] = 0;//��ԭλ�ñ�Ϊ�ո�
				if(position_x>0)
					position_x--;
				canvas[position_y][position_x] = 1;
			}
			if (input == 'd')
			{
				canvas[position_y][position_x] = 0;//��ԭλ�ñ�Ϊ�ո�
				if(position_x<WIDTH-1)
					position_x++;
				canvas[position_y][position_x] = 1;
			}
			if (input == 'w')
			{
				canvas[position_y][position_x] = 0;//��ԭλ�ñ�Ϊ�ո�
				if(position_y>0)
					position_y--;
				canvas[position_y][position_x] = 1;
			}
			if (input == 's')
			{
				canvas[position_y][position_x] = 0;//��ԭλ�ñ�Ϊ�ո�
				if(position_y<HIGH-1)
					position_y++;
				canvas[position_y][position_x] = 1;
			}

			if (BulletNumber > 0)
			{
				if (input == ' ')
				{
					int Bulletleft, BulletRight;
					Bulletleft = position_x - BulletWidth;
					if (Bulletleft < 0)
						Bulletleft = 0;
					BulletRight = position_x + BulletWidth;
					if (BulletRight >= WIDTH - 1)
						BulletRight = WIDTH - 1;
					bullet_y = position_y - 1;
					bullet_x = position_x;

					for (int i = Bulletleft; i <= BulletRight; i++)
					{
						canvas[bullet_y][i] = 2;
					}
					
					BulletNumber--;
				}
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
