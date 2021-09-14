#pragma once
#include "Incld.h"

//Maze �Լ���-----------------------------------------------------------------------------------
void Mk_MazeMap();
void makingMap(int prev_x, int prev_y, int way_x, int way_y);
int isEmpty(int n);
int pop(int arr[][SIZE][SZ], int row, int col, int size[][SIZE]);
void move();
void GamePause();
void PauseCancel();
void ArrayReset();
void Timer_UI();
void Timer();
void TimerUpdate();
void Eye(int x, int y);
void darkEye();
void KeyStatus();
void HaveKey(int cnt);
void AllPrint();

int mazeMap[SIZE * 2 + 1][SIZE * 2 + 1];		//���� ��ũ��
int way[SIZE][SIZE];							//����ϴ� �� && �湮 ���� Ȯ��
int offset_x[SIZE][SIZE][SZ];							// x�� �̵���ǥ ����
int offset_y[SIZE][SIZE][SZ];							// y�� �̵���ǥ ����
int size_x[SIZE][SIZE];									// x�̵� ��ǥ�� ������ ����
int size_y[SIZE][SIZE];									// y�̵� ��ǥ�� ������ ����
int prev[SIZE][SIZE];									// ������

int user_x, user_y;		//���� ���� ��ġ
int goal_x, goal_y;				//���� ��ġ

int countTime, endTime; // �ܿ��ð�, ����ð�
int ps;
int myEye, fx;

// {1,0} �� ���� ����

