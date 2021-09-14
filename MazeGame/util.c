#include "Incld.h"
#include "util.h"

void setMenuSize() 
{
    system("mode con cols=120 lines=40");	 // 크기 지정
}

void hidingCursor()         // 커서 없애기
{
    CONSOLE_CURSOR_INFO cci;

    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void selection(int x, int y, char str[])                                    //위치로 이동하고 문자를 출력
{      
    gotoxy(x, y);
    printf("%s\n", str);
}

void gotoxy(int x, int y)                                                   //위치로 이동하기
{
    COORD pos = { y * 2, x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isEmpty(int n) 
{
    if (n == 0) return 1;		//배열의 인덱스가 0임
    return 0;
}

int pop(int arr[][SIZE][SZ], int row, int col, int size[][SIZE])            //스택 pop기능 구현
{			
    if (!isEmpty(size[row][col])) {
        int num = arr[row][col][size[row][col] - 1];
        size[row][col]--;
        return num;
    }
}

void setColor(int color, char str[])                                        // 글자에 색입히고 원래 색으로 돌리기
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%s\n", str);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void seeMenu(void (*fc)()) {                                                // 화면을 지우고 함수를 호출하여 화면에 출력
    system("cls");
    fc();
}