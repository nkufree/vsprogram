#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
#define cli mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0)
HWND h;
void weixin()
{
	POINT p1 = { 837,513 };
}

int main()
{
	Sleep(1000 * 5);
	POINT p = {};
	Sleep(1000 * 5);
	h = GetForegroundWindow();
	GetCursorPos(&p);
	ClientToScreen(h, &p);
	//ScreenToClient(h, &p);
	cout << p.x << " " << p.y << endl;
	int i = 2000;
	while (i--)
	{ 
		SetCursorPos(1480, 203);
		cli;
		Sleep(10000);
		SetCursorPos(1500, 600);
		cli;
		Sleep(100);
		if (_kbhit())
		{
			return 0;
		}
	}
	return 0;

	
}	