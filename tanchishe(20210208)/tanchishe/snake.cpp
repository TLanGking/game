#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

struct X_Y
{
	int x;
	int y;
};
enum keycode
{
	right = 77,
	left = 75,
	down = 80,
	up = 72
};

struct SNAKE
{
	int Postion;
	int num;
	X_Y sxy[100];
}snake;
struct FOOD
{
	X_Y fxy;
	int live;
	int grade;
}food;

void initsnake();
void printsnake();
void movesnake();
void initfood();
void printfood();
void keydown();
int judgesnake();
void printgrade();
//void gamehome();

HWND hwnd = NULL;
MOUSEMSG m;
IMAGE img;
int main() {
	hwnd = initgraph(640, 480);
	//gamehome();
	setbkcolor(WHITE);
	cleardevice();
	initsnake();
	int temp = 0;
	food.grade = 0;
	while (1)
	{
		cleardevice();
		if (temp == 0)
		{
			initfood();
			temp++;
		}
		printfood();
		printgrade();
		if (judgesnake())
			break;
		printsnake();
		X_Y tip;
		tip.x = snake.sxy[snake.num - 1].x;
		tip.y = snake.sxy[snake.num - 1].y;
		movesnake();
		if (snake.sxy[0].x == food.fxy.x && snake.sxy[0].y == food.fxy.y)
		{
			temp = 0;
			snake.num++;
			food.grade += 10;
			snake.sxy[snake.num - 1].x = tip.x;
			snake.sxy[snake.num - 1].y = tip.y;
		}
		if (_kbhit())
			keydown();	
		Sleep(130);
	}
	
	closegraph();
	return 0;
}

void initsnake()
{
	snake.num = 3;
	snake.Postion = right;

	snake.sxy[2].x = 0;
	snake.sxy[2].y = 0;

	snake.sxy[1].x = 20;
	snake.sxy[1].y = 0;

	snake.sxy[0].x = 40;
	snake.sxy[0].y = 0;
}

void printsnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(GREEN);
		setfillcolor(BLUE);
		fillrectangle(snake.sxy[i].x, snake.sxy[i].y, snake.sxy[i].x + 20, snake.sxy[i].y + 20);
	}
}

void movesnake()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.sxy[i].x = snake.sxy[i - 1].x;
		snake.sxy[i].y = snake.sxy[i - 1].y;
	}
	switch (snake.Postion)
	{
	case right:
		snake.sxy[0].x += 20;
		break;
	case left:
		snake.sxy[0].x -= 20;
		break;
	case up:
		snake.sxy[0].y -= 20;
		break;
	case down:
		snake.sxy[0].y += 20;
	default:
		break;
	}
}

int judgesnake()
{
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.sxy[0].x == snake.sxy[i].x && snake.sxy[0].y == snake.sxy[i].y)
		{
			MessageBox(hwnd, "你tm把自己咬死了！", "游戏结束", MB_OK);
			return 1;
		}
	}
	if (snake.sxy[0].x < 0 || snake.sxy[0].x >= 640 || snake.sxy[0].y < 0 || snake.sxy[0].y >= 480)
	{
		MessageBox(hwnd, "你tm撞到南墙了！", "游戏结束", MB_OK);
		return 1;
	}
	return 0;
}


void keydown()
{
	char key = _getch();
	switch (key)
	{
	case right:
		if (snake.Postion != left)
			snake.Postion = right;
		break;
	case left:
		if (snake.Postion != right)
			snake.Postion = left;
		break;
	case up:
		if (snake.Postion != down)
			snake.Postion = up;
		break;
	case down:
		if (snake.Postion != up)
			snake.Postion = down;
		break;
	default:
		break;
	}
}


void initfood()
{
	srand(unsigned int(time(NULL)));
	while (1)
	{
		food.fxy.x = rand() % 32 * 20;
		food.fxy.y = rand() % 24 * 20;
		food.live = 1;
		int i = 0;
		for (i = 0; i < snake.num; i++)
		{
			if (food.fxy.x == snake.sxy[i].x && food.fxy.y == snake.sxy[i].y)
			{			
				break;
			}
		}
		if (i == snake.num)
		{		
			break;
		}
	}
}

void printfood()
{
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	fillcircle(food.fxy.x + 20 / 2, food.fxy.y + 20 / 2, 20 / 2);
}

void printgrade()
{
	char grade[100] = "";
	sprintf(grade, "%d", food.grade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTGREEN);
	outtextxy(560, 20, "分数：");
	outtextxy(580 + 50 - 20, 20, grade);
}

//void gamehome()
//{
//	cleardevice();
//	loadimage(&img, "666.jpg", 640, 480);
//	putimage(0, 0, &img);
//	setbkmode(TRANSPARENT);
//	settextstyle(30, 0, "宋体");
//	int btextn = 280;
//	while (1)
//	{		
//		outtextxy(250, btextn, "开始游戏");
//		outtextxy(250, btextn + 50, "更多游戏");
//		outtextxy(250, btextn + 50 * 2, "游戏设置");
//		outtextxy(250, btextn + 50 * 3, "退出游戏");
//		m = GetMouseMsg();
//		if (m.x >= 250 && m.x <= 250 + 30 * 4 && m.y >= btextn && m.y <= btextn + 30)
//		{
//			rectangle(250, btextn, 250 + 30 * 4, btextn + 30);
//			MOUSEMSG mm = GetMouseMsg();
//			if (mm.uMsg == MK_LBUTTON)
//				break;
//		}
//		else if (m.x >= 250 && m.x <= 250 + 30 * 4 && m.y >= btextn + 50 && m.y <= btextn + 50 + 30)
//		{
//			rectangle(250, btextn + 50, 250 + 30 * 4, btextn + 50 + 30);
//		}
//		else if (m.x >= 250 && m.x <= 250 + 30 * 4 && m.y >= btextn + 50 * 2 && m.y <= btextn + 50 * 2 + 30)
//		{
//			rectangle(250, btextn + 50 * 2, 250 + 30 * 4, btextn + 50 * 2 + 30);
//		}
//
//		else if (m.x >= 250 && m.x <= 250 + 30 * 4 && m.y >= btextn + 50 * 3 && m.y <= btextn + 50 * 3 + 30)
//		{
//			rectangle(250, btextn + 50 * 3, 250 + 30 * 4, btextn + 50 * 3 + 30);
//		}
//		else
//			putimage(0, 0, &img);
//	}
//}
