#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
//游戏属性
struct GameProperties
{
	int WindowWidth = 0;
	int WindowHighly = 0;
	int Buttonx = 0;
	int Buttony = 0;
	int SnakeSpeed = 0;
	IMAGE BackgroundPhoto;
	HWND hwnd = NULL;
	MOUSEMSG m;
	int TextSize = 0;
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
void initGame();
void GameFighting();
void initSnake();
void DrawSnake();
void MoveSnake();
void ProduceFood();
void DrawFood();
void keydown();
int judgesnake();
void ShowGrade();
void gamehome();
int MouseJudge();

void initGame()
{	
	first.hwnd = NULL;
	first.WindowWidth = 1000;
	first.WindowHighly = 800;
	first.TextSize = 50;
	first.Buttonx = first.WindowHighly / 2;
	first.Buttony = first.WindowHighly - first.TextSize * 5;
	first.SnakeSpeed = 180;
	first.hwnd = initgraph(first.WindowWidth, first.WindowHighly);
	initSnake();
	setbkcolor(WHITE);
	food.grade = 0;
}

int main() {
	initGame();
	gamehome();
	cleardevice();
	GameFighting();
	closegraph();
	return 0;
}
void GameFighting()
{
	int temp = 0;
	while (1)
	{
		cleardevice();
		if (temp == 0)
		{
			ProduceFood();
			temp++;
		}
		DrawFood();
		ShowGrade();
		if (judgesnake())
			break;
		DrawSnake();
		X_Y tip;
		tip.x = snake.sxy[snake.num - 1].x;
		tip.y = snake.sxy[snake.num - 1].y;
		if (_kbhit())
		{
			keydown();
			Sleep(10);
		}
		MoveSnake();
		if (snake.sxy[0].x == food.fxy.x && snake.sxy[0].y == food.fxy.y)
		{
			temp = 0;
			snake.num++;
			food.grade += 10;
			snake.sxy[snake.num - 1].x = tip.x;
			snake.sxy[snake.num - 1].y = tip.y;
		}
		Sleep(first.SnakeSpeed);
	}
}

void initSnake()
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

void DrawSnake()
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

void MoveSnake()
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


void ProduceFood()
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

void DrawFood()
{
	setlinecolor(RGB(rand()%225, rand() % 225, rand() % 225));
	setfillcolor(GREEN);
	fillcircle(food.fxy.x + 20 / 2, food.fxy.y + 20 / 2, 20 / 2);
}

void ShowGrade()
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
void ButtonText()
{
	putimage(0, 0, &first.BackgroundPhoto);
	outtextxy(first.Buttonx, first.Buttony, TEXT("开始游戏"));
	outtextxy(first.Buttonx, first.Buttony + first.TextSize + 10, TEXT("更多游戏"));
	outtextxy(first.Buttonx, first.Buttony + (first.TextSize + 10) * 2, TEXT("游戏设置"));
	outtextxy(first.Buttonx, first.Buttony + (first.TextSize + 10) * 3, TEXT("退出游戏"));
}
void gamehome()
{
	cleardevice();
	loadimage(&first.BackgroundPhoto, "666.jpg", first.WindowWidth, first.WindowHighly);
	setbkmode(TRANSPARENT);
	settextstyle(first.TextSize, 0, "楷体");        
	settextcolor(RED);	
	short temp = 0;
	do
	{
		MOUSEMSG ret;
		do
		{
			ButtonText();
			temp = MouseJudge();
			ret = GetMouseMsg();
		} while (ret.uMsg != WM_LBUTTONDOWN && temp);
		switch (temp)
		{
		case 1:
			break;
		case 2:
			system("start https://www.ali213.net/");
			break;
		case 3:
			//SetGame();
			break;
		case 4:
			closegraph();
			exit(0);
			break;
		default:
			break;
		}
	} while (temp != 1);
}
int MouseJudge()
{
	first.m = GetMouseMsg();
 	if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony && first.m.y <= first.Buttony + first.TextSize)
	{
		ButtonText();
		rectangle(first.Buttonx, first.Buttony, first.Buttonx + first.TextSize * 4, first.Buttony + first.TextSize);
		return 1;
	}
	if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + first.TextSize + 10 && first.m.y <= first.Buttony + first.TextSize * 2 +10)
	{
		ButtonText();
		rectangle(first.Buttonx, first.Buttony + first.TextSize + 10, first.Buttonx + first.TextSize * 4, first.Buttony + first.TextSize * 2 + 10);
		return 2;
	}
	if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + (first.TextSize + 10) * 2 && first.m.y <= first.Buttony + (first.TextSize + 10) * 2 + first.TextSize)
	{
		ButtonText();
		rectangle(first.Buttonx, first.Buttony + (first.TextSize + 10) * 2, first.Buttonx + first.TextSize * 4, first.Buttony + (first.TextSize + 10) * 2 + first.TextSize);
		return 3;
	}
	if (first.m.x >= first.Buttonx && first.m.x <= first.Buttonx + first.TextSize * 4
		&& first.m.y >= first.Buttony + (first.TextSize + 10) * 3 && first.m.y <= first.Buttony + (first.TextSize + 10) * 3 + first.TextSize)
	{
		ButtonText();
		rectangle(first.Buttonx, first.Buttony + (first.TextSize + 10) * 3, first.Buttonx + first.TextSize * 4, first.Buttony + (first.TextSize + 10) * 3 + first.TextSize);
		return 4;
	}
	ButtonText();
	return 5;
}