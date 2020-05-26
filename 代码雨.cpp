#include <iostream>
#include <graphics.h>
#include <ctime>
#include <Winuser.h>
#define SCREEN_WIDTH 1920		//屏幕宽度，看个人电脑分辨率
#define SCREEN_HEIGHT 1080		//屏幕亮度，看个人电脑分辨率
#define CODE_RAIN 100			//字符串数量

char StrRain[CODE_RAIN][10];	//代码雨的字符串
POINT RainPos[CODE_RAIN];		//代码雨开始的位置,为点类型

void init()
{
	char RandChar;
	for (int i = 0; i < CODE_RAIN; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			while (1)
			{
				RandChar = rand() % 123; //123是Z的下一个ACSII码大小
				if (RandChar >= '0' && RandChar <= '9' || RandChar >= 'a' && RandChar <= 'z' || RandChar >= 'A' && RandChar <= 'Z')
					break;
			}
			StrRain[i][j] = RandChar;
		}
	}
	//随机生成位置
	for (int i = 0; i < CODE_RAIN; i++)
	{
		RainPos[i].x = rand() % SCREEN_WIDTH;
		RainPos[i].y = rand() % SCREEN_HEIGHT;
	}
}

void update()
{
	for (int i = 0; i < CODE_RAIN; i++)
	{
		RainPos[i].y += 15; //屏幕左上角坐标为(0,0)，y+15表示下降15
		if (RainPos[i].y - 10 * 15 >= SCREEN_HEIGHT)
		{
			RainPos[i].x = rand() % SCREEN_WIDTH;
			RainPos[i].y = 0;
		}
	}
}

void Render()
{
	BeginBatchDraw();
	cleardevice();		//清空屏幕
	for (int i = 0; i < CODE_RAIN; i++)
	{
		//设置字体颜色
		settextcolor(RGB(255, 255, 255)); //白色
		for (int j = 0; j < 8; j++)
		{
			outtextxy(RainPos[i].x, RainPos[i].y - 15 * j, StrRain[i][j]);
			settextcolor(RGB(0,255 - 28*j,0));
		}
	}
	EndBatchDraw();
	Sleep(100); //休息0.1秒
}

int main()
{
	//创建窗口
	HWND hwnd = initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//设置窗口风格
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	//设置窗口位置
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
	//设置为透明
	LONG WindowLong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	//设置窗口口风格
	SetWindowLong(hwnd, GWL_EXSTYLE, WindowLong);
	//背景修改为黑色
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	srand((unsigned)time(NULL));
	init();
	while (1)
	{
		Render();
		update();
	}
	closegraph();
	return 0;
}