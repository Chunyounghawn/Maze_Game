#include "Incld.h"
#include "Main_Func.h"
#include "Maze_Func.h"
#include "Word_Func.h"
#include "util.h"

void Eye(int x, int y) {		// 좌표 기준으로 시야 생성
	int mx = x - myEye, my = y - myEye, px = x + myEye, py = y + myEye;		//mx= 현재좌표 - 보여질 시야범위(가운데 기준 양옆칸 길이)
	// myEye = 칸 수

	if (mx < 5) mx = 5;							//minus x값이 테두리 밖으로 넘어가면 테두리까지로 조정
	if (my < 0) my = 0;							//minus y값이 테두리 밖으로 넘어가면 테두리까지로 조정
	if (px > SIZE * 2 + 5) px = SIZE * 2 + 5;
	if (py > SIZE * 2) py = SIZE * 2;

	// 유저 모양은 ★(인덱스 : 3)
	for (i = mx; i <= px; i++) {
		for (j = my; j <= py; j++) {
			gotoxy(i, j);
			if (mazeMap[i - 5][j] == 0) printf("▣");
			else if (mazeMap[i - 5][j] == 1) printf("  ");
			else if (mazeMap[i - 5][j] == 8) setColor(8, "О");			// 발자국으로 덮이는 문제 해결을 위한 위치
			else if (mazeMap[i - 5][j] == 2) printf("→");
			else if (mazeMap[i - 5][j] == 4) printf("♀");				// 키
			else if (mazeMap[i - 5][j] == 5) setColor(12, "♥");		// 빨간색
			else if (mazeMap[i - 5][j] == 6) setColor(9, "ㆀ");			// 시야 증가
			else if (mazeMap[i - 5][j] == 7) setColor(8, "О");			// 발자국
			else if (mazeMap[i - 5][j] == 9) setColor(10, "●");		// 스프레이
			else if (mazeMap[i - 5][j] == 10) setColor(10, "●");		// 스프레이
		}
	}
}

void darkEye() {				// 지나온길 시야 가리기
	// x값은 fx(because, x좌표가 전체적으로 5씩 이동했기때문에), y값은 user_y로 받음
	int myEyeSum = myEye + 1;
	for (i = user_y - myEyeSum; i <= user_y + myEyeSum; i++)
		if (fx + myEyeSum <= SIZE * 2 + 6 && i < SIZE * 2 + 1 && i >= 0)
			selection(fx + myEyeSum, i, "  ");			// 밑에 없앰

	for (i = user_y - myEyeSum; i <= user_y + myEyeSum; i++)
		if (fx - myEyeSum >= 5 && i < SIZE * 2 + 1 && i >= 0)			// 5가 벽의 x좌표
			selection(fx - myEyeSum, i, "  ");			// 위에 없앰

	for (i = fx - myEyeSum; i <= fx + myEyeSum; i++)
		if (user_y + myEyeSum < SIZE * 2 + 1 && i <= SIZE * 2 + 6 && i >= 5) 
			selection(i, user_y + myEyeSum, "  ");	// 오른쪽 없앰

	for (i = fx - myEyeSum; i <= fx + myEyeSum ; i++)
		if (user_y - myEyeSum >= 0 && i <= SIZE * 2 + 6 && i >= 5)
			selection(i, user_y - myEyeSum, "  ");	//왼쪽 없앰
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
		solocount = 0;
		servercount++;
		clientcount++;
		endMenu();
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