#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>


int bird_x, bird_y;//С������
int high, width;//��Ϸ����ߴ�
int bar_x, bar_yTOP, bar_yDOWN;//�ϰ�������
int randPosition ;//�������
int score;
int speed;

void PrintBorder(int _i, int _j);
void GameOver();
void enemydown();

void gotoxy(int x, int y)  //����ƶ���(x,y)��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()  //���ݳ�ʼ��
{
	srand((unsigned)time(NULL));//���������
	randPosition = rand() % (high - 3);

	high = 15;
	width = 25;

	bar_x = width-2;
	bar_yTOP = randPosition;
	bar_yDOWN = randPosition + high / 3;
	

	bird_y = high/2;
	bird_x = 5;

	speed = 0;
	score = 0;

}

void show()  //��ʾ����
{

	int i, j;//i��y�� j��x��
	gotoxy(0, 0); //�������� ����ƶ������Ͻ�

	for (i = 0; i <= high; i++)
	{
		//printf("|");
		for (j = 0; j <= width; j++)
		{
			if (i == bird_y && j == bird_x)
				printf("@");//���С�� @
			else if (i == high && j < width)
				printf("-");
			else if (j == width - 1 && i < high)
				printf("|");
			else if((i<=bar_yTOP||(i>=bar_yDOWN&&i<=high))&&j==bar_x)
				printf("*");
			else
				printf(" ");

		}
		printf("\n");
	}
	printf("score:%d", score/30);//30�ǳ���speed
}

void updateWithoutInput() //�û������޹صĲ���
{
	speed++;
	if (speed == 30)//���ٺ���
	{
		if (bar_x > 0)
		{
			bar_x--;
		}
		else
		{
			bar_x = width-2;

			srand((unsigned)time(NULL));//���������
			randPosition = rand() % (high - 3);
			bar_yTOP = randPosition;
			bar_yDOWN = randPosition + high/3 ;
		}
		bird_y++;
		speed = 0;//���ٺ�������
	}
	if (bird_x == bar_x && (bird_y <= bar_yTOP || bird_y >= bar_yDOWN))
	{
		printf("\nGame Over!");
		system("pause");
	}
	else if (bird_y == high)
	{
		printf("\nGame Over!");
		system("pause");
	}
	else if(bird_x == bar_x && (bird_y > bar_yTOP && bird_y < bar_yDOWN))
	{
		score++;
	}
	
}
void updateWithInput() //��������
{
	char input;
	if (_kbhit())//������ʱִ��
	{
		input = _getch();
		if (bird_y >= 2)
		{
			if (input == ' ')
			{
				bird_y -= 2;
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
}


int main()
{
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