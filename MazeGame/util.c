#include "Incld.h"
#include "util.h"

void setMenuSize() 
{
    system("mode con cols=120 lines=40");	 // ũ�� ����
}

void hidingCursor()         // Ŀ�� ���ֱ�
{
    CONSOLE_CURSOR_INFO cci;

    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void selection(int x, int y, char str[])                                    //��ġ�� �̵��ϰ� ���ڸ� ���
{      
    gotoxy(x, y);
    printf("%s\n", str);
}

void gotoxy(int x, int y)                                                   //��ġ�� �̵��ϱ�
{
    COORD pos = { y * 2, x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isEmpty(int n) 
{
    if (n == 0) return 1;		//�迭�� �ε����� 0��
    return 0;
}

int pop(int arr[][SIZE][SZ], int row, int col, int size[][SIZE])            //���� pop��� ����
{			
    if (!isEmpty(size[row][col])) {
        int num = arr[row][col][size[row][col] - 1];
        size[row][col]--;
        return num;
    }
}

void setColor(int color, char str[])                                        // ���ڿ� �������� ���� ������ ������
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%s\n", str);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void seeMenu(void (*fc)()) {                                                // ȭ���� ����� �Լ��� ȣ���Ͽ� ȭ�鿡 ���
    system("cls");
    fc();
}