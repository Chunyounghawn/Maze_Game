#include "Maze_Func.h"
#include "Main_Func.h"
#include "Word_Func.h"
#include "util.h"

int keyCount = 0;

void Mk_MazeMap() {
	int rnd, cnt = 0, rnd2;
	int freq[4] = { 0 };

	system("mode con cols=110 lines=50");		// �ܼ� ũ�� ����

	user_x = 1; user_y = 0;						// ���� ���� ��ġ
	countTime = 0; endTime = 0;					// �ð� �ʱ�ȭ
	ps = 0;										// �Ͻ����� ���� (0 : �Ͻ����� �ƴ�, 1 : �Ͻ����� ����)
	myEye = 2;									// �þ� ����

	ArrayReset();

	srand((unsigned)time(NULL));
	for (i = 0; i < SIZE; i++) {		//��ǥ�� �迭 �ʱ�ȭ
		for (j = 0; j < SIZE; j++) {
			cnt = 0;
			for (k = 0; k < SZ; k++)		//�� �迭 �ʱ�ȭ
				freq[k] = 0;

			while (cnt != 4) {				//�迭�� ��� ä������ ����������
				rnd = rand() % 4;
				if (freq[rnd] != 1) {		//������ �ߺ� Ȯ��
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

	makingMap(0, 0, 0, 0);		//�̷� ���� �Լ� ȣ��
	mazeMap[1][0] = 2;			//��������

	while (1) {					//������
		rnd = rand() % SIZE * 2;
		if (mazeMap[rnd][SIZE * 2 - 1] != 0) {	//������ �տ� ���� �������� ����
			mazeMap[rnd][SIZE * 2] = 2;
			goal_x = rnd;					//�������� x��ǥ ����
			goal_y = SIZE * 2;				//�������� y��ǥ ����
			break;
		}
	}

	cnt = 0;
	while (cnt != 2) {							//����Ѹ���(cnt ������ŭ)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		if (mazeMap[rnd][rnd2] != 0) {			//���� �ƴҶ�
			mazeMap[rnd][rnd2] = 4;				//���� �ε���
			cnt++;
		}
	}

	cnt = 0;
	while (cnt != 4) {							//�ð� ������ �Ѹ���(cnt ������ŭ)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4) {			//���� �����ڸ��� �ƴҶ�
			mazeMap[rnd][rnd2] = 5;				//�ð� �ε���
			cnt++;
		}
	}

	Eye(6, 0);
	selection(6, 0, "��");		//���� ��ġ

	Timer_UI();					//Ÿ�̸� �׵θ�
	KeyStatus();				//Ű ��Ȳ �׵θ�
	HaveKey(keyCount);

	move();					
}


void makingMap(int prev_x, int prev_y, int way_x, int way_y) {
	int x, y;
	int nx, ny;

	x = prev_x - way_x;
	y = prev_y - way_y;
	mazeMap[(way_x + 1) * 2 - 1 + x][(way_y + 1) * 2 - 1 + y] = 1;			//way�迭�� mazeMap�� ũ�Ⱑ �ٸ��� ������ ���� ������ ����
	way[way_x][way_y] = 1;
	mazeMap[(way_x + 1) * 2 - 1][(way_y + 1) * 2 - 1] = 1;					//�������� �����ϴ� ��

	while (1) {
		if (size_x[way_x][way_y] == 0) break;		//�̵���ǥ�� ��� ����ϸ� ����������
		nx = pop(offset_x, way_x, way_y, size_x);		//x�̵� ��ǥ ����
		ny = pop(offset_y, way_x, way_y, size_y);		//y�̵� ��ǥ ����

		if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {		//x�� y�� ���� ���� �ȿ� ������
			if (way[nx][ny] != 1) {								//�湮���� ������
				makingMap(way_x, way_y, nx, ny);
			}
		}
	}
}

void move() {
	char key;

	if (ps != 1) endTime = (unsigned)time(NULL) + 180; // ����ð� = ����ð� + 180��
	else ps = 0;			// �Ͻ����� ���¿����� ����

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
				ps = 1;            //�Ͻ����� ���� 1 = �Ͻ�����
				GamePause();
				break;
			}
			if (ps != 1) {
				px = user_x + 5;
				if (user_x == 1 && user_y == 1) selection(6, 0, "��");		// �������� ����� ȭ��ǥ�� �������� ���� ��ġ�� ���� �ڵ�
				Eye(px, user_y);
				darkEye();
				selection(px, user_y, "��");
			}
		}
	}

}

void GamePause() {
	int x = 4, y = 16;
	for (i = 0; i < 5; i++) 			//ESC �޴� ����â UI
		selection(x + i - 1, y, ESCMenu[i]);

	char key = NULL;
	do {
		if (kbhit()) {
			key = getch();
			switch (key) {
				case UP:
					if (x - 2 == 4) {
						selection(x, y + 2, "  ");
						selection(x -= 2, y + 2, "��");
					}
					break;
				case DOWN:
					if (x + 2 == 6) {
						selection(x, y + 2, "  ");
						selection(x += 2, y + 2, "��");
					}
					break;
				case ENTER:
					if (x == 6) {
						PauseCancel();
					}
					else {
						user_x = 1; user_y = 0;
						ps = 0;					// ������ �ϸ� �Ͻ����� ���¸� false
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
	Eye(user_x + 5, user_y);					// ���̴� �þ� ǥ��
	selection(user_x + 5, user_y, "��");		// �Ͻ����� �ߴ� ��ġ �ҷ�����
	Timer_UI();				// Ÿ�̸� �׵θ�
	Timer();				// Ÿ�̸� ����	
	KeyStatus();			//Ű ��Ȳ �׵θ�
	HaveKey(keyCount);		//Ű ���� ����
	move();
}

void ArrayReset() {
	for (i = 0; i < SIZE * 2 + 1; i++) {
		for (j = 0; j < SIZE * 2 + 1; j++) {
			mazeMap[i][j] = 0;
		}
	}
	for (i = 0; i < SIZE; i++) {			//pop�Լ����� ����� ������� �ʱ�ȭ
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
