#include <iostream>
#include <graphics.h>
#include <ctime>
#include <Winuser.h>
#define SCREEN_WIDTH 1920		//��Ļ��ȣ������˵��Էֱ���
#define SCREEN_HEIGHT 1080		//��Ļ���ȣ������˵��Էֱ���
#define CODE_RAIN 100			//�ַ�������

char StrRain[CODE_RAIN][10];	//��������ַ���
POINT RainPos[CODE_RAIN];		//�����꿪ʼ��λ��,Ϊ������

void init()
{
	char RandChar;
	for (int i = 0; i < CODE_RAIN; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			while (1)
			{
				RandChar = rand() % 123; //123��Z����һ��ACSII���С
				if (RandChar >= '0' && RandChar <= '9' || RandChar >= 'a' && RandChar <= 'z' || RandChar >= 'A' && RandChar <= 'Z')
					break;
			}
			StrRain[i][j] = RandChar;
		}
	}
	//�������λ��
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
		RainPos[i].y += 15; //��Ļ���Ͻ�����Ϊ(0,0)��y+15��ʾ�½�15
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
	cleardevice();		//�����Ļ
	for (int i = 0; i < CODE_RAIN; i++)
	{
		//����������ɫ
		settextcolor(RGB(255, 255, 255)); //��ɫ
		for (int j = 0; j < 8; j++)
		{
			outtextxy(RainPos[i].x, RainPos[i].y - 15 * j, StrRain[i][j]);
			settextcolor(RGB(0,255 - 28*j,0));
		}
	}
	EndBatchDraw();
	Sleep(100); //��Ϣ0.1��
}

int main()
{
	//��������
	HWND hwnd = initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//���ô��ڷ��
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	//���ô���λ��
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
	//����Ϊ͸��
	LONG WindowLong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	//���ô��ڿڷ��
	SetWindowLong(hwnd, GWL_EXSTYLE, WindowLong);
	//�����޸�Ϊ��ɫ
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