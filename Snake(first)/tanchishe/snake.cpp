#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
//游戏属性
struct GameProperties
{
	int WindowWidth;
	int WindowHighly;
	int Buttonx;
	int Buttony;
	int SnakeSpeed;
	IMAGE BackgroundPhoto;
	HWND hwnd = NULL;
	MOUSEMSG m;
	int TextSize;
}first;


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
void initgame();
void initsnake();
void printsnake();
void movesnake();
void initfood();
void printfood();
void keydown();
int judgesnake();
void printgrade();
void gamehome();
int mousejudge();
int MouseLeft(int ret);


void initgame()
{	
	first.hwnd = NULL;
	first.WindowWidth = 800;
	first.WindowHighly = 600;
	first.TextSize = 50;
	first.Buttonx = first.WindowHighly / 2;
	first.Buttony = first.WindowHighly - first.TextSize * 5;
}

int main() {
	initgame();
	first.hwnd = initgraph(first.WindowWidth, first.WindowHighly);
	gamehome();
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
		{
			keydown();
			Sleep(10);
		}
		Sleep(180);
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
		setlinecolor(RGB(rand() % 225, rand() % 225, rand() % 225));
		if (i == 0)
			setfillcolor(RGB(rand() % 225, rand() % 225, rand() % 225));
		else
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
	IMAGE cniosc;
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.sxy[0].x == snake.sxy[i].x && snake.sxy[0].y == snake.sxy[i].y)
		{
			MessageBox(first.hwnd, "你把自己咬死了！", "游戏结束", MB_OK);
			return 1;
		}
	}
	if (snake.sxy[0].x < 0 || snake.sxy[0].x >= first.WindowWidth || snake.sxy[0].y < 0 || snake.sxy[0].y >= first.WindowHighly)
	{		
		MessageBox(first.hwnd, "你撞到南墙了！", "游戏结束", MB_OK);
		return 1;
	}
	return 0;
}


void keydown()
{
	char key = getch();
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
		food.fxy.x = rand() % first.WindowWidth / 20 * 20;
		food.fxy.y = rand() % first.WindowHighly / 20 * 20;
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
	setlinecolor(RGB(rand()%225, rand() % 225, rand() % 225));
	setfillcolor(GREEN);
	fillcircle(food.fxy.x + 20 / 2, food.fxy.y + 20 / 2, 20 / 2);
}

void printgrade()
{
	char grade[100] = "分数：";
	char arr[10] = "";
	sprintf(arr, "%d", food.grade);
	strcat(grade, arr);
	int len = strlen(grade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTGREEN);
	settextstyle(first.TextSize / 2,0,"宋体");
	setlinecolor(LIGHTGREEN);
	outtextxy(first.WindowWidth - (len * first.TextSize) / 3, first.TextSize / 2, grade);
	rectangle(first.WindowWidth - (len * first.TextSize ) / 3, first.TextSize / 2, first.WindowWidth - first.TextSize / 2, first.TextSize);
}

void gamehome()
{
	cleardevice();
	loadimage(&first.BackgroundPhoto, "666.jpg", first.WindowWidth, first.WindowHighly);
	putimage(0, 0, &first.BackgroundPhoto);
	setbkmode(TRANSPARENT);
	settextstyle(first.TextSize, 0, "楷体");        
	settextcolor(RED);			
	do
	{
		outtextxy(first.Buttonx, first.Buttony, TEXT("开始游戏"));
		outtextxy(first.Buttonx, first.Buttony + first.TextSize +10, TEXT("更多游戏"));
		outtextxy(first.Buttonx, first.Buttony + (first.TextSize + 10) * 2, TEXT("游戏设置"));
		outtextxy(first.Buttonx, first.Buttony + (first.TextSize + 10) * 3, TEXT("退出游戏"));
	} while (mousejudge());
}
int mousejudge()
{

	int btextn = 280;
	first.m = GetMouseMsg();
 	if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony && first.m.y <= first.Buttony + first.TextSize)
	{
		rectangle(first.Buttonx, first.Buttony, first.Buttonx + first.TextSize * 4, first.Buttony + first.TextSize);
		return MouseLeft(1);
	}
	else if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + first.TextSize + 10 && first.m.y <= first.Buttony + first.TextSize * 2 +10)
	{
		rectangle(first.Buttonx, first.Buttony + first.TextSize + 10, first.Buttonx + first.TextSize * 4, first.Buttony + first.TextSize * 2 + 10);
		return MouseLeft(2);
	}
	else if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + (first.TextSize + 10) * 2 && first.m.y <= first.Buttony + (first.TextSize + 10) * 2 + first.TextSize)
	{
		rectangle(first.Buttonx, first.Buttony + (first.TextSize + 10) * 2, first.Buttonx + first.TextSize * 4, first.Buttony + (first.TextSize + 10) * 2 + first.TextSize);
		return MouseLeft(3);
	}
	else if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + (first.TextSize + 10) * 3 && first.m.y <= first.Buttony + (first.TextSize + 10) * 3 + first.TextSize)
	{
		rectangle(first.Buttonx, first.Buttony + (first.TextSize + 10) * 3, first.Buttonx + first.TextSize * 4, first.Buttony + (first.TextSize + 10) * 3 + first.TextSize);
		return MouseLeft(4);
	}
	else
	{
		putimage(0, 0, &first.BackgroundPhoto);
		return 	1;
	}
}
int MouseLeft(int ret)
{
	first.m = GetMouseMsg();
	if (first.m.uMsg == WM_LBUTTONDOWN)
	{
		switch (ret)
		{
		case 1:
			return 0;
			break;
		case 2:
			system("start https://www.ali213.net/");
			return 1;
			break;
		case 3:
			//SetGame();
			return 1;
			break;
		case 4:
			closegraph();
			exit(0);
			break;
		default:
			break;
		}
	}
	else
		return 1;
}