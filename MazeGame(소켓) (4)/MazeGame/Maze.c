#include "Maze_Func.h"
#include "Main_Func.h"
#include "Word_Func.h"
#include "util.h"

int keyCount = 0;

void Mk_MazeMap() {
	int rnd, cnt = 0, rnd2;
	int freq[4] = { 0 };

	system("mode con cols=110 lines=50");		// 콘솔 크기 설정

	user_x = 1; user_y = 0;						// 유저 시작 위치
	countTime = 0; endTime = 0;					// 시간 초기화
	ps = 0;										// 일시정지 상태 (0 : 일시정지 아님, 1 : 일시정지 상태)
	myEye = 2;									// 시야 범위

	ArrayReset();

	srand((unsigned)time(NULL));
	for (i = 0; i < SIZE; i++) {		//좌표로 배열 초기화
		for (j = 0; j < SIZE; j++) {
			cnt = 0;
			for (k = 0; k < SZ; k++)		//빈도 배열 초기화
				freq[k] = 0;

			while (cnt != 4) {				//배열을 모두 채웠을때 빠져나오기
				rnd = rand() % 4;
				if (freq[rnd] != 1) {		//랜덤값 중복 확인
					if (rnd == 0) {
						offset_x[i][j][cnt] = i + 1;
						offset_y[i][j][cnt] = j;
					}
					else if (rnd == 1) {
						offset_x[i][j][cnt] = i;
						offset_y[i][j][cnt] = j + 1;
					}
					else if (rnd == 2) {
						offset_x[i][j][cnt] = i - 1;
						offset_y[i][j][cnt] = j;
					}
					else {
						offset_x[i][j][cnt] = i;
						offset_y[i][j][cnt] = j - 1;
					}
					cnt++;
					freq[rnd] = 1;
				}
			}
		}
	}

	makingMap(0, 0, 0, 0);		//미로 구성 함수 호출
	mazeMap[1][0] = 2;			//시작지점

	while (1) {					//끝지점
		rnd = rand() % SIZE * 2;
		if (mazeMap[rnd][SIZE * 2 - 1] != 0) {	//끝지점 앞에 블럭이 없을때만 생성
			mazeMap[rnd][SIZE * 2] = 2;
			goal_x = rnd;					//도착지점 x좌표 저장
			goal_y = SIZE * 2;				//도착지점 y좌표 저장
			break;
		}
	}

	cnt = 0;
	while (cnt != 2) {							//열쇠뿌리기(cnt 개수만큼)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//테두리 내에서 랜덤
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//테두리 내에서 랜덤
		if (mazeMap[rnd][rnd2] != 0) {			//벽이 아닐때
			mazeMap[rnd][rnd2] = 4;				//열쇠 인덱스
			cnt++;
		}
	}

	cnt = 0;
	while (cnt != 4) {							//시간 아이템 뿌리기(cnt 개수만큼)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//테두리 내에서 랜덤
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//테두리 내에서 랜덤
		if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4) {			//벽과 열쇠자리가 아닐때
			mazeMap[rnd][rnd2] = 5;				//시간 인덱스
			cnt++;
		}
	}

	Eye(6, 0);
	selection(6, 0, "★");		//시작 위치

	Timer_UI();					//타이머 테두리
	KeyStatus();				//키 현황 테두리
	HaveKey(keyCount);

	move();					
}


void makingMap(int prev_x, int prev_y, int way_x, int way_y) {
	int x, y;
	int nx, ny;

	x = prev_x - way_x;
	y = prev_y - way_y;
	mazeMap[(way_x + 1) * 2 - 1 + x][(way_y + 1) * 2 - 1 + y] = 1;			//way배열과 mazeMap의 크기가 다르기 때문에 먼저 기준점 생성
	way[way_x][way_y] = 1;
	mazeMap[(way_x + 1) * 2 - 1][(way_y + 1) * 2 - 1] = 1;					//기준점과 연결하는 부

	while (1) {
		if (size_x[way_x][way_y] == 0) break;		//이동좌표를 모두 사용하면 빠져나가기
		nx = pop(offset_x, way_x, way_y, size_x);		//x이동 좌표 저장
		ny = pop(offset_y, way_x, way_y, size_y);		//y이동 좌표 저장

		if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {		//x와 y의 값이 범위 안에 있으면
			if (way[nx][ny] != 1) {								//방문한적 없을때
				makingMap(way_x, way_y, nx, ny);
			}
		}
	}
}

void move() {
	char key;

	if (ps != 1) endTime = (unsigned)time(NULL) + 180; // 종료시간 = 현재시간 + 180초
	else ps = 0;			// 일시정지 상태였으면 해제

	while (1) {
		Timer();
		if (kbhit()) {
			key = getch();
			gotoxy(user_x + 5, user_y);
			printf("  ");
			switch (key) {
			case UP:
				if (mazeMap[user_x - 1][user_y] != 0)  user_x -= 1;
				break;
			case DOWN:
				if (mazeMap[user_x + 1][user_y] != 0)  user_x += 1;
				break;
			case LEFT:
				if (mazeMap[user_x][user_y - 1] != 0)  user_y -= 1;
				break;
			case RIGHT:
				if (mazeMap[user_x][user_y + 1] != 0)  user_y += 1;
				break;
			case SP:
				if (mazeMap[user_x][user_y] == 4) {
					mazeMap[user_x][user_y] = 1;
					keyCount++;
					HaveKey(keyCount);
				}
				if (mazeMap[user_x][user_y] == 5) {
					mazeMap[user_x][user_y] = 1;
					TimerUpdate();
				}
				if (user_x == goal_x && user_y == goal_y && keyCount == 2) {
					system("cls");
					clientcount--;
					servercount--;
					endMenu();
					break;
				}
				break;
			case ESC:
				system("cls");
				ps = 1;            //일시중지 여부 1 = 일시중지
				GamePause();
				break;
			}
			if (ps != 1) {
				px = user_x + 5;
				if (user_x == 1 && user_y == 1) selection(6, 0, "→");		// 시작점을 벗어날때 화살표가 지워지는 버그 고치기 위한 코드
				Eye(px, user_y);
				darkEye();
				selection(px, user_y, "★");
			}
		}
	}

}

void GamePause() {
	int x = 4, y = 16;
	for (i = 0; i < 5; i++) 			//ESC 메뉴 선택창 UI
		selection(x + i - 1, y, ESCMenu[i]);

	char key = NULL;
	do {
		if (kbhit()) {
			key = getch();
			switch (key) {
				case UP:
					if (x - 2 == 4) {
						selection(x, y + 2, "  ");
						selection(x -= 2, y + 2, "▶");
					}
					break;
				case DOWN:
					if (x + 2 == 6) {
						selection(x, y + 2, "  ");
						selection(x += 2, y + 2, "▶");
					}
					break;
				case ENTER:
					if (x == 6) {
						PauseCancel();
					}
					else {
						user_x = 1; user_y = 0;
						ps = 0;					// 나가기 하면 일시정지 상태를 false
						setMenuSize();
						Menu();
					}
					break;
				case ESC:
					PauseCancel();
					break;
			}
		}
	} while (!(key == ENTER || key == ESC));
}

void PauseCancel() {
	system("cls");
	Eye(user_x + 5, user_y);					// 보이는 시야 표시
	selection(user_x + 5, user_y, "★");		// 일시정지 했던 위치 불러오기
	Timer_UI();				// 타이머 테두리
	Timer();				// 타이머 갱신	
	KeyStatus();			//키 현황 테두리
	HaveKey(keyCount);		//키 개수 갱신
	move();
}

void ArrayReset() {
	for (i = 0; i < SIZE * 2 + 1; i++) {
		for (j = 0; j < SIZE * 2 + 1; j++) {
			mazeMap[i][j] = 0;
		}
	}
	for (i = 0; i < SIZE; i++) {			//pop함수에서 사용할 사이즈들 초기화
		for (j = 0; j < SIZE; j++) {
			size_x[i][j] = 4;
			size_y[i][j] = 4;

			way[i][j] = 0;
			prev[i][j] = 0;
			for (k = 0; k < SZ; k++) {
				offset_x[i][j][k] = 0;
				offset_y[i][j][k] = 0;
			}
		}
	}
}
