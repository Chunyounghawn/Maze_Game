#include "Incld.h"
#include "Main_Func.h"
#include "Maze_Func.h"
#include "Word_Func.h"
#include "util.h"

void Eye(int x, int y) {		// ��ǥ �������� �þ� ����
	int mx = x - myEye, my = y - myEye, px = x + myEye, py = y + myEye;		//mx= ������ǥ - ������ �þ߹���(��� ���� �翷ĭ ����)
	// myEye = ĭ ��

	if (mx < 5) mx = 5;							//minus x���� �׵θ� ������ �Ѿ�� �׵θ������� ����
	if (my < 0) my = 0;							//minus y���� �׵θ� ������ �Ѿ�� �׵θ������� ����
	if (px > SIZE * 2 + 5) px = SIZE * 2 + 5;
	if (py > SIZE * 2) py = SIZE * 2;

	// ���� ����� ��(�ε��� : 3)
	for (i = mx; i <= px; i++) {
		for (j = my; j <= py; j++) {
			gotoxy(i, j);
			if (mazeMap[i - 5][j] == 0) printf("��");
			else if (mazeMap[i - 5][j] == 1) printf("  ");
			else if (mazeMap[i - 5][j] == 8) setColor(8, "��");			// ���ڱ����� ���̴� ���� �ذ��� ���� ��ġ
			else if (mazeMap[i - 5][j] == 2) printf("��");
			else if (mazeMap[i - 5][j] == 4) printf("��");				// Ű
			else if (mazeMap[i - 5][j] == 5) setColor(12, "��");		// ������
			else if (mazeMap[i - 5][j] == 6) setColor(9, "��");			// �þ� ����
			else if (mazeMap[i - 5][j] == 7) setColor(8, "��");			// ���ڱ�
			else if (mazeMap[i - 5][j] == 9) setColor(10, "��");		// ��������
			else if (mazeMap[i - 5][j] == 10) setColor(10, "��");		// ��������
		}
	}
}

void darkEye() {				// �����±� �þ� ������
	// x���� fx(because, x��ǥ�� ��ü������ 5�� �̵��߱⶧����), y���� user_y�� ����
	int myEyeSum = myEye + 1;
	for (i = user_y - myEyeSum; i <= user_y + myEyeSum; i++)
		if (fx + myEyeSum <= SIZE * 2 + 6 && i < SIZE * 2 + 1 && i >= 0)
			selection(fx + myEyeSum, i, "  ");			// �ؿ� ����

	for (i = user_y - myEyeSum; i <= user_y + myEyeSum; i++)
		if (fx - myEyeSum >= 5 && i < SIZE * 2 + 1 && i >= 0)			// 5�� ���� x��ǥ
			selection(fx - myEyeSum, i, "  ");			// ���� ����

	for (i = fx - myEyeSum; i <= fx + myEyeSum; i++)
		if (user_y + myEyeSum < SIZE * 2 + 1 && i <= SIZE * 2 + 6 && i >= 5) 
			selection(i, user_y + myEyeSum, "  ");	// ������ ����

	for (i = fx - myEyeSum; i <= fx + myEyeSum ; i++)
		if (user_y - myEyeSum >= 0 && i <= SIZE * 2 + 6 && i >= 5)
			selection(i, user_y - myEyeSum, "  ");	//���� ����
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
		solocount = 0;
		servercount++;
		clientcount++;
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