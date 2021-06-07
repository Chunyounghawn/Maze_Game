#include "Incld.h"
#include "Maze_Func.h"
#include "Word_Func.h"
#include "Main_Func.h"
#include "util.h"

//static int 
void Eye(int x, int y) {
	int mx = x - myEye, my = y - myEye, px = x + myEye, py = y + myEye;		//mx= ������ǥ - ������ �þ߹���(��� ���� �翷ĭ ����)

	if (mx < 0) mx = 0;
	if (my < 0) my = 0;
	if (px > SIZE * 2 + 5) px = SIZE * 2 + 5;
	if (py > SIZE * 2) py = SIZE * 2;

	for (i = mx; i <= px; i++) {
		for (j = my; j <= py; j++) {
			gotoxy(i, j);
			if (mazeMap[i - 5][j] == 0) printf("��");
			else if (mazeMap[i - 5][j] == 1) printf("  ");
			else if (mazeMap[i - 5][j] == 2) printf("��");
			else if (mazeMap[i - 5][j] == 3) printf("��");
			else if (mazeMap[i - 5][j] == 4) printf("��");
			else if (mazeMap[i - 5][j] == 5) setColor(12, "��");		// ������
		}
	}
}

void darkEye() {
	for (i = user_y - myEye; i <= user_y + myEye; i++)
		if (px + 3 <= SIZE * 2 + 6) selection(px + 3, i, "  ");			// �ؿ� ����
	for (i = user_y - myEye; i <= user_y + myEye; i++)
		if (px - 3 >= 5) selection(px - 3, i, "  ");			// ���� ����
	for (i = px - myEye; i <= px + myEye; i++)
		if (user_y + 3 <= SIZE * 2 + 1) selection(i, user_y + 3, "  ");	// ������ ����
	for (i = px - myEye; i <= px + myEye; i++)
		if (user_y - 3 >= 0) selection(i, user_y - 3, "  ");	//���� ����
}

void Timer_UI() {
	int x = 1, y = 1;
	for (i = 0; i < 3; i++)			//Timer UI
		selection(x + i, y, TimeSet[i]);
}

void Timer() {
	int startTime = (unsigned)time(NULL);		//���� �ð�
	if (ps == 1) endTime = (unsigned)time(NULL) + countTime;			// �Ͻ����� �����̸� ����ð� = ����ð� + �ܿ��ð�
	else countTime = endTime - startTime;			// ī��Ʈ�ð� = ����ð� - ����ð�
	gotoxy(2, 2);
	printf("P1:%03d��", countTime);
	if (countTime <= 0) // ���ѽð� �ʰ�
	{
		system("cls");
		printf("TimeOver\n");
		Sleep(10000);
		clientcount++;
		servercount++;
		endMenu();
	}
}

void TimerUpdate() {
	countTime += 20;		//20�� ����
	if (countTime > 180) countTime = 180;
	endTime = (unsigned)time(NULL) + countTime; // ���� �ð��� ����ð����� �ʱ�ȭ && ���� �ð��������� �ܿ��ð��� ���� �ð����� ���� �ð������� �缳��
}

void KeyStatus() {
	int x = 1, y = 15;
	for (i = 0; i < 3; i++)			//������ Ű �׵θ�
		selection(x + i, y, myKey[i]);
}

void HaveKey(int cnt) {
	gotoxy(2, 20);
	printf("%d��", cnt);
}