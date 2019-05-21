#include "pch.h"
#include "basketball.h"

//�ƶ����ĺ���������Ϊ�������������,����ַ�����ɫ
void basketball::moveTo(int x, int y, int color)
{
	HANDLE hout;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, color);
	SetConsoleCursorPosition(hout, pos);
}

//���ع�꣬����û�����
void basketball::hide()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

//��������
void basketball::music(const char file[])
{
	PlaySoundA(file, NULL, SND_FILENAME | SND_ASYNC);
}

//��ʼ����
void basketball::initBall(int color)
{
	srand((unsigned)time(0));
	ballX = rand() % 39 + 11;
	showBall(color);
	//��ʼ������˶�����
	xOffset = rand() % 2;
	if (xOffset == 0)
	{
		xOffset = -1;
	}
}

//��ʾ��
void basketball::showBall(int color)
{
	moveTo(ballX, ballY, color);
	cout << ball;
	hide();

}

//���ϰ������ײ�ж�
void basketball::judgeBoard(pf clearBoard, vector<vector<int>> &obstacle)
{
	vector<int> temp;
	for (unsigned int i = 0; i < obstacle.size(); i++)
	{
		if (ballY == obstacle[i][1])//������ϰ�����ͬһ��
		{
			if (ballX >= obstacle[i][0] && ballX < (obstacle[i][0] + 7)) //�����һ���任λ�����ϰ����ڲ�
			{
				if ((ballY - yOffset) > obstacle[i][1])
				{
					ballY = obstacle[i][1] + 1;
					yOffset = 1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
				else if ((ballY - yOffset) < obstacle[i][1])
				{
					ballY = obstacle[i][1] - 1;
					yOffset = -1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
			}
			else  //����¸��任λ�����ϰ����ⲿ
			{
				if (ballX == (obstacle[i][0] - 2) || ballX == (obstacle[i][0] - 1))  //���ϰ������
				{
					ballX = obstacle[i][0] - 2;
					xOffset = -1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
				else if (ballX == (obstacle[i][0] + 7) || ballX == (obstacle[i][0] + 6)) //���ϰ����Ҳ�
				{
					yOffset = -yOffset;
					xOffset = 1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
			}
		}
		else if (ballY == (obstacle[i][1] + 1) || ballY == (obstacle[i][1] - 1)) //��������ϰ�����ͬһ�У������ϰ����Ϸ����·�
		{
			if (ballX >= obstacle[i][0] && ballX <= (obstacle[i][0] + 7))
			{
				yOffset = -yOffset;
				music("music1.wav");
				for (int h = 0; h < 2; h++)
				{
					temp.push_back(obstacle[i][0]);
					temp.push_back(obstacle[i][1]);
				}
				clearBoard(temp[0], temp[1]);
				break;
			}
		}
	}
}

//��ײ����˵���ײ�ж�
void basketball::judgeCXK(const int &CXKx, const int &CXKy, int &state)
{
	if (ballY == 25)
	{
		if (ballX >= (CXKx - 2) && ballX <= (CXKx + 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY == 26)
	{
		if (ballX >= CXKx && ballX <= (CXKx + 2))
		{
			ballY = 25;
			yOffset = -1;
			music("music0.wav");
		}
		else if (ballX == (CXKx + 3) || ballX == (CXKx - 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY == 27)
	{
		if (ballX > (CXKx - 2) && ballX < (CXKx + 3))
		{
			ballY = 25;
			yOffset = -1;
			music("music0.wav");
		}
		else if (ballX == (CXKx + 3) || ballX == (CXKx - 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY >= 28)
	{
		state = 0;
	}
}

//�������ϵı߽��ж�
void basketball::judgeX()
{
	if (ballX >= 59)
	{
		ballX = 58;
		xOffset = -1;
		music("music2.wav");
	}
	else if (ballX <= 0)
	{
		ballX = 1;
		xOffset = 1;
		music("music2.wav");
	}
}

//�������ϵı߽��ж�
void basketball::judgeY(int &state)
{
	if (ballY <= 0)
	{
		ballY = 1;
		yOffset = 1;
		music("music2.wav");
	}
	else if (ballY >= 28)
	{
		state = 0;
	}
}

//�ж�������֮�����ײ
void basketball::judgeBall(const int &x, const int &y, const int &offx, const int &offy)
{
	if (ballY == y)//��һ��λ����ͬһ��
	{
		if (ballX >= (x - 1) && ballX <= (x + 1))
		{
			if (yOffset != offy)
			{
				if (xOffset > 0)
				{
					ballX = x - 2;
					xOffset = -1;
					music("music2.wav");
				}
				else
				{
					ballX = x + 2;
					xOffset = 1;
					music("music2.wav");
				}
			}
			else
			{
				if (xOffset > 0)
				{
					ballX = x - 1;
					if ((ballY - yOffset) < y)
					{
						ballY = y - 1;
					}
					else if ((ballY - yOffset) > y)
					{
						ballY = y + 1;
					}
				}
				else
				{
					ballX = x + 1;
					if ((ballY - yOffset) < y)
					{
						ballY = y - 1;
					}
					else if ((ballY - yOffset) > y)
					{
						ballY = y + 1;
					}
				}
			}
		}
		else if (ballX == (x - 2) || ballX == (x + 2))
		{
			if (xOffset != offx)
			{
				xOffset = -xOffset;
				music("music2.wav");
			}
		}
	}
	else if (ballY == (y + 1) || ballY == (y - 1))
	{
		if (ballX >= (x - 1) && ballX < (x + 1))
		{
			if (xOffset = offx && yOffset != offy)
			{
				yOffset = -yOffset;
				music("music2.wav");
			}
			else if (xOffset = offx && yOffset == offy)
			{
				if (yOffset > 0)
				{
					if (ballY < y)
					{
						yOffset = -yOffset;
						xOffset = -xOffset;
						music("music2.wav");
					}
				}
				else
				{
					if (ballY > y)
					{
						yOffset = -yOffset;
						xOffset = -xOffset;
						music("music2.wav");
					}
				}
			}
		}
	}
}

//��������ƶ�������Ϊ�������ٶ��������������ٶ�����
void basketball::moveBall(const int &CXKx, const int &CXKy, int &state, pf clearBoard, vector<vector<int>> &obstacle)
{
	ballX += xOffset;
	judgeX();
	ballY += yOffset;
	judgeY(state);
	judgeCXK(CXKx, CXKy, state);
	judgeBoard(clearBoard, obstacle);
}

//�����
void basketball::clearBall()
{
	moveTo(ballX, ballY);
	cout << "  ";
}

//����ˢ��
void basketball::ballRefresh()
{
	ballX = ballY = 1;
	xOffset = yOffset = 1;
}


basketball::~basketball()
{
}
