#include "Incld.h"
#include "Maze_Func.h"
#include "Word_Func.h"

void Eye(int x, int y) {
	int mx = x - myEye, my = y - myEye, px = x + myEye, py = y + myEye;		//mx= 현재좌표 - 보여질 시야범위(가운데 기준 양옆칸 길이)

	if (mx < 0) mx = 0;
	if (my < 0) my = 0;
	if (px > SIZE * 2 + 5) px = SIZE * 2 + 5;
	if (py > SIZE * 2) py = SIZE * 2;

	for (i = mx; i <= px; i++) {
		for (j = my; j <= py; j++) {
			gotoxy(i, j);
			if (mazeMap[i - 5][j] == 0) printf("■");
			else if (mazeMap[i - 5][j] == 1) printf("  ");
			else if (mazeMap[i - 5][j] == 2) printf("→");
			else if (mazeMap[i - 5][j] == 3) printf("★");
			else if (mazeMap[i - 5][j] == 4) printf("♀");
			else if (mazeMap[i - 5][j] == 5) printf("♥");
		}
	}
}

void darkEye() {
	for (i = user_y - myEye; i <= user_y + myEye; i++)
		if (px + 3 <= SIZE * 2 + 6) selection(px + 3, i, "  ");			// 밑에 없앰
	for (i = user_y - myEye; i <= user_y + myEye; i++)
		if (px - 3 >= 5) selection(px - 3, i, "  ");			// 위에 없앰
	for (i = px - myEye; i <= px + myEye; i++)
		if (user_y + 3 <= SIZE * 2 + 1) selection(i, user_y + 3, "  ");	// 오른쪽 없앰
	for (i = px - myEye; i <= px + myEye; i++)
		if (user_y - 3 >= 0) selection(i, user_y - 3, "  ");	//왼쪽 없앰
}

void Timer_UI() {
	int x = 1, y = 1;
	for (i = 0; i < 3; i++)			//Timer UI
		selection(x + i, y, TimeSet[i]);
}

void Timer() {
	int startTime = (unsigned)time(NULL);		//현재 시간
	if (ps == 1) endTime = (unsigned)time(NULL) + countTime;			// 일시정지 상태이면 종료시간 = 현재시간 + 잔여시간
	else countTime = endTime - startTime;			// 카운트시간 = 종료시간 - 현재시간
	gotoxy(2, 2);
	printf("P1:%03d초", countTime);
	if (countTime <= 0) // 제한시간 초과
	{
		system("cls");
		printf("TimeOver\n");
		exit(0);
	}
}

void TimerUpdate() {
	countTime += 20;		//20초 증가
	if (countTime > 180) countTime = 180;
	endTime = (unsigned)time(NULL) + countTime; // 종료 시간을 현재시간으로 초기화 && 현재 시간기준으로 잔여시간을 더한 시간값을 종료 시간값으로 재설정
}

void KeyStatus() {
	int x = 1, y = 15;
	for (i = 0; i < 3; i++)			//소유한 키 테두리
		selection(x + i, y, myKey[i]);
}

void HaveKey(int cnt) {
	gotoxy(2, 20);
	printf("%d개", cnt);
}