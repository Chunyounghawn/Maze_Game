#include "Maze_Func.h"
#include "Main_Func.h"
#include "Word_Func.h"
#include "util.h"

int keyCount = 0;
int footprint = 0;
int checkpoint = 0;

void Mk_MazeMap() {
	
	int rnd, cnt = 0, rnd2;
	int freq[4] = { 0 };

	system("mode con cols=110 lines=50");		// �ܼ� ũ�� ����
	keyCount = 0;
	user_x = 1; user_y = 0;						// ���� ���� ��ġ
	countTime = 0; endTime = 0;					// �ð� �ʱ�ȭ
	ps = 0;										// �Ͻ����� ���� (0 : �Ͻ����� �ƴ�, 1 : �Ͻ����� ����)
	myEye = 3;									// �þ� ���� ����
	footprint = 0;
	checkpoint = 0;

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

	if (TimerMode == true) {
		cnt = 0;
		while (cnt != 4) {							//�ð� ������ �Ѹ���(cnt ������ŭ)
			rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
			rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
			if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4) {			//���� �����ڸ��� �ƴҶ�
				mazeMap[rnd][rnd2] = 5;				//�ð� �ε���
				cnt++;
			}
		}
	}

	if (EyeMode == true) {
		cnt = 0;
		while (cnt != 2) {							//�þ� ���� ������ �Ѹ���(cnt ������ŭ)
			rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
			rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
			if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4 && mazeMap[rnd][rnd2] != 5) {			//���� ����, �ð� �ڸ��� �ƴҶ�
				mazeMap[rnd][rnd2] = 6;				//�þ� ���� ������ �ε���
				cnt++;
			}
		}
	}

	cnt = 0;
	while (cnt != 1) {							//���ڱ� Ž���� �Ѹ���(cnt ������ŭ)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4 && mazeMap[rnd][rnd2] != 5 && mazeMap[rnd][rnd2] != 6) {			//���� ����, �ð�, �þ� ������ �ڸ��� �ƴҶ�
			mazeMap[rnd][rnd2] = 7;				//���ڱ� Ž���� �ε���
			cnt++;
		}
	}

	cnt = 0;
	while (cnt != 1) {							//�������� �Ѹ���(cnt ������ŭ)
		rnd = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		rnd2 = rand() % (SIZE - 1) * 2 + 1;		//�׵θ� ������ ����
		if (mazeMap[rnd][rnd2] != 0 && mazeMap[rnd][rnd2] != 4 && mazeMap[rnd][rnd2] != 5 && mazeMap[rnd][rnd2] != 6 && mazeMap[rnd][rnd2] != 7) {			//���� ����, �ð�, �þ�, ���ڱ� Ž���� �ڸ��� �ƴҶ�
			mazeMap[rnd][rnd2] = 9;				//�������� �ε���
			cnt++;
		}
	}

	if (EyeMode == false) AllPrint();
	
	Eye(6, 0);
	selection(user_x + 5, user_y, "��");		//���� ��ġ


	Timer_UI();					//Ÿ�̸� �׵θ�
	KeyStatus();				//Ű ��Ȳ �׵θ�
	HaveKey(keyCount);

	move();					
}

void makingMap(int prev_x, int prev_y, int way_x, int way_y) {		// �ٽ� �̷� ��ô �˰���(��Ʈ��ŷ)
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
		if (TimerMode == true) {
			Timer();
		}
		else {
			gotoxy(2, 3);
			printf("�ð����Ѿ���");
		}
		if (_kbhit()) {
			key = _getch();
			gotoxy(user_x + 5, user_y);
			if (footprint == 0) printf("  ");
			else {
				if (mazeMap[user_x][user_y] == 1) {
					mazeMap[user_x][user_y] = 8;			// ���ڱ� ǥ��
				}
			}

			switch (key) {
			case UP:
				if (mazeMap[user_x - 1][user_y] != 0) user_x -= 1;
				break;
			case DOWN:
				if (mazeMap[user_x + 1][user_y] != 0) user_x += 1;
				break;
			case LEFT:
				if (mazeMap[user_x][user_y - 1] != 0) user_y -= 1;
				break;
			case RIGHT:
				if (mazeMap[user_x][user_y + 1] != 0) user_y += 1;
				break;
			case SP:
				if (checkpoint > 0) {
					if (mazeMap[user_x][user_y] == 1 || mazeMap[user_x][user_y] == 8) {
						mazeMap[user_x][user_y] = 10;
						mciSendString(L"play useSpray.wav", NULL, 0, NULL);
						checkpoint--;
					}
				}
				if (mazeMap[user_x][user_y] == 4) {		// Ű ȹ��
					mazeMap[user_x][user_y] = 1;
					mciSendString(L"play key.wav", NULL, 0, NULL);
					keyCount++;
					HaveKey(keyCount);
				}
				if (mazeMap[user_x][user_y] == 5) {		// Ÿ�̸� ȹ��
					mazeMap[user_x][user_y] = 1;
					mciSendString(L"play time.wav", NULL, 0, NULL);
					TimerUpdate();
				}
				if (mazeMap[user_x][user_y] == 6) {		// �þ� ���� ������ ȹ��
					mazeMap[user_x][user_y] = 1;
					mciSendString(L"play eye.wav", NULL, 0, NULL);
					myEye += 2;
				}
				if (mazeMap[user_x][user_y] == 7) {		// ���ڱ� Ž���� ȹ��
					mazeMap[user_x][user_y] = 1;
					mciSendString(L"play foot.wav", NULL, 0, NULL);
					footprint = 1;
				}
				if (mazeMap[user_x][user_y] == 9) {		// �������� ȹ��
					mazeMap[user_x][user_y] = 1;
					mciSendString(L"play spray.wav", NULL, 0, NULL);
					checkpoint = 3;
				}
				if (user_x == goal_x && user_y == goal_y && keyCount == 2) {
					system("cls");
					solocount = 1;
					servercount--;
					clientcount--;
					endMenu();
					break;
				}
				break;
			case ESC:
				system("cls");
				ps = 1;            //�Ͻ����� ���� 1 = �Ͻ�����(PauSe)
				GamePause();
				break;
			}
			if (ps != 1) {
				fx = user_x + 5;
				Eye(fx, user_y);
				if (EyeMode == true) {
					darkEye();
				}
				selection(fx, user_y, "��");
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
		if (_kbhit()) {
			key = _getch();
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
						closesocket(cs);
						closesocket(s);
						WSACleanup();
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
	if (EyeMode == true) Eye(user_x + 5, user_y);					// ���̴� �þ� ǥ��
	else AllPrint();
	selection(user_x + 5, user_y, "��");		// �Ͻ����� �ߴ� ��ġ �ҷ�����
	Timer_UI();				// Ÿ�̸� �׵θ�
	if (TimerMode == true) Timer();				// Ÿ�̸� ����
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

void AllPrint() {
	for (i = 0; i < SIZE * 2 + 1; i++) {
		for (j = 0; j < SIZE * 2 + 1; j++) {
			gotoxy(i + 5, j);
			if (mazeMap[i][j] == 0) printf("��");
			else if (mazeMap[i][j] == 1) printf("  ");
			else if (mazeMap[i][j] == 8) setColor(8, "��");			// ���ڱ����� ���̴� ���� �ذ��� ���� ��ġ
			else if (mazeMap[i][j] == 2) printf("��");
			else if (mazeMap[i][j] == 4) printf("��");				// Ű
			else if (mazeMap[i][j] == 5) setColor(12, "��");		// ������
			else if (mazeMap[i][j] == 6) setColor(9, "��");			// �þ� ����
			else if (mazeMap[i][j] == 7) setColor(8, "��");			// ���ڱ�
			else if (mazeMap[i][j] == 9) setColor(10, "��");		// ��������
			else if (mazeMap[i][j] == 10) setColor(10, "��");		// ��������
		}
	}
}