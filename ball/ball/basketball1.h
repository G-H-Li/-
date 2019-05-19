#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
#include <Mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

class basketball1
{
private:
	const string ball = "��";  //���������״
	typedef void(*pf)(int, int);
	int y;
public:
	basketball1() { ballY = 15; xOffset = yOffset = 1; };
	~basketball1();
	static int xOffset, yOffset;  //�����ʼ�������������ƫ����
	static int ballY, ballX;  //������ĳ�ʼ��ʾλ��
	void initBall(int color);
	void showBall(int color);
	void judgeBoard(pf clearBoard, vector<vector<int>> &obstacle);
	void judgeCXK(const int &CXKx, const int &CXKy, int &state);
	void judgeX();
	void judgeY(int &state);
	void judgeBall(const int &x, const int &y, const int &offx, const int &offy);
	void moveBall(const int &CXKx, const int &CXKy, int &state, pf clearBoard, vector<vector<int>> &obstacle);
	void clearBall();
	void ballRefresh();

	void moveTo(int x, int y, int color = 7);
	void hide();
	void music(const char file[]);
};



