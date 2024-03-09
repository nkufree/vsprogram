#include<iostream>
#include<Windows.h>

using namespace std;

const int N = 10000;
int a[N + 1][N + 1] = {};
int vec[N + 1] = {};
int out1[N + 1] = {};
int out2[N + 1] = {};
int out3[N + 1] = {};

void init()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] = i + j;
	for (int i = 0; i < N; i++)
		vec[i] = i;
	return;
}

//ƽ���㷨
void solve1()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			out1[i] += a[j][i] * vec[j];
	return;
}

//cache�Ż��㷨
void solve2()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			out2[j] += a[i][j] * vec[i];
	return;
}
//2*1ѭ��չ��
void solve3()
{
	for (int i = 0; i < N; i+=1)
		for (int j = 0; j < N; j += 2)
		{
			out3[j] += a[i][j] * vec[i];
			out3[j + 1] += a[i][j + 1] * vec[i + 1];
		}
	return;
}
int main()
{
	init();
	long long time0, time1,freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&time0);
	solve1();
	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	cout << "ƽ���㷨��ʱ��Ϊ" << (time1 - time0) * 1000.0 / freq << "ms" << endl;

	QueryPerformanceCounter((LARGE_INTEGER*)&time0);
	solve2();
	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	cout << "cache�Ż��㷨��ʱ��Ϊ" << (time1 - time0) * 1000.0 / freq << "ms" << endl;

	QueryPerformanceCounter((LARGE_INTEGER*)&time0);
	solve3();
	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	cout << "ѭ��չ���㷨��cache�Ż��㷨��ϵ�ʱ��Ϊ" << (time1 - time0) * 1000.0 / freq << "ms" << endl;
	return 0;
}