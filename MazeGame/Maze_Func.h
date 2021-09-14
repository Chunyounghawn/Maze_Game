#pragma once
#include "Incld.h"

//Maze 함수들-----------------------------------------------------------------------------------
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

int mazeMap[SIZE * 2 + 1][SIZE * 2 + 1];		//실제 맵크기
int way[SIZE][SIZE];							//계산하는 맵 && 방문 여부 확인
int offset_x[SIZE][SIZE][SZ];							// x의 이동좌표 저장
int offset_y[SIZE][SIZE][SZ];							// y의 이동좌표 저장
int size_x[SIZE][SIZE];									// x이동 좌표의 사이즈 저장
int size_y[SIZE][SIZE];									// y이동 좌표의 사이즈 저장
int prev[SIZE][SIZE];									// 이전방

int user_x, user_y;		//유저 시작 위치
int goal_x, goal_y;				//도착 위치

int countTime, endTime; // 잔여시간, 종료시간
int ps;
int myEye, fx;

// {1,0} 이 시작 지점

