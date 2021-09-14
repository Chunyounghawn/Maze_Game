#include "Main_Func.h"
#include "util.h"
#include "Maze_Func.h"
#include "Word_Func.h"

void main() {
    check = 1;
    playsound();               // �뷡 ���
    SetConsoleTitle(TEXT("MazeRunner"));     // ���� ����
    setMenuSize();             // �޴� ������ ����
    hidingCursor();            // Ŀ�� �����
    Animation(true);          // �ִϸ��̼� ����(true, false)�� ����
    Menu();
}

void Menukeyget() { //�޴� Ű�Է�
    keyvalue = MoveSelet(18, 23, 4);

    if (keyvalue == 0) { seeMenu(*GameMode); }              // ���� ��� ���� �޴�
    else if (keyvalue == 1) { seeMenu(*Setting); }          // ���� �ϱ�
    else if (keyvalue == 2) { seeMenu(*Help); }             // ����
    else if (keyvalue == 3) {                               // ���� ����
        printf("������ �����մϴ�.");
        exit(1);
    }
}

void GameMode() {
    int x = 18, y = 4;
    selection(x, y, "��  1�ο�");
    selection(x + 2, y + 2, "2�ο�");
    selection(x + 4, y + 2, "��弳��");
    selection(x + 6, y + 2, "������");
    
    keyvalue = MoveSelet(x, y, 4);

    if (keyvalue == 0) seeMenu(*Mk_MazeMap);               // ��� ����
    else if (keyvalue == 1) seeMenu(*MultiMode);            // ��Ƽ ��� �޴�
    else if (keyvalue == 2) seeMenu(*SelectMode);                 // ��� ����
    else if (keyvalue == 3) seeMenu(*Menu);           // ���� �޴�
}

void SelectMode() {
    int x = 18, y = 4;

    if (EyeMode == true)
        selection(x, y, "��  �� �þ� ����");
    else 
        selection(x, y, "��  �� �þ� ����");

    if (TimerMode == true)
        selection(x + 2, y + 2, "�� Ÿ�̸�");
    else 
        selection(x + 2, y + 2, "�� Ÿ�̸�");
    selection(x + 4, y + 2, "-  ������");
    char c;
    int s = 18;
    do {
        c = _getch();
        switch (c) {
        case UP: {
            if (s > x) {
                selection(s, y, "  ");
                selection(s -= 2, y, "��");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case DOWN: {
            if (s < 24) {
                selection(s, y, "  ");
                selection(s += 2, y, "��");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case ENTER:
            s = (s - x) / 2;
            if (s == 0) {
                if (EyeMode == true) {
                    selection(x, y + 2, "��");
                    s = s * 2 + x;
                    EyeMode = false;
                }
                else {
                    selection(x, y + 2, "��");
                    s = s * 2 + x;
                    EyeMode = true;
                }
                c = DOWN;
            }
            else if (s == 1) {
                if (TimerMode == true) {
                    selection(x + 2, y + 2, "��");
                    s = s * 2 + x;
                    TimerMode = false;
                }
                else {
                    selection(x + 2, y + 2, "��");
                    s = s * 2 + x;
                    TimerMode = true;
                }
                c = DOWN;
            }
            break;
        }
    } while (c != ENTER);

    if (s == 2) seeMenu(*GameMode);
}

void MultiMode() {
    int x = 18, y = 4;    
    selection(x, y, "��  �游���");
    selection(x + 2, y + 2, "�����ϱ�");
    selection(x + 4, y + 2, "������");

    keyvalue = MoveSelet(x, y, 3);

    if (keyvalue == 0) {
        system("cls");
        servercount = 1;
        clientcount = 0;
        Server();
        
    }
    else if (keyvalue == 1) {
        system("cls");
        clientcount = 1;
        servercount = 0;
        Client();
        
    }
    else if (keyvalue == 2) {
        seeMenu(*GameMode);
    }
}

void Setting() {
    int x = 18, y = 4;
    selection(x, y, "��  ���� ����");
    selection(x + 2, y + 2, "������");

    keyvalue = MoveSelet(x, y, 2);

    if (keyvalue == 0) SoundVolume();
    else if (keyvalue == 1) seeMenu(*Menu);
}

void SoundVolume() {
    int x = 18, y = 14;

    gotoxy(x, y);
    if (check) setColor(9, "On ");
    else setColor(12, "Off");

    char c;
    do {
        c = _getch();
        switch (c) {
        case UP:
            check = 1;
            gotoxy(x, y);
            setColor(9, "On ");
            playsound();
            break;
        case DOWN:
            check = 0;
            gotoxy(x, y);
            setColor(12, "Off");
            playsound();
            break;
        case ENTER:
            break;
        }
    } while (c != ENTER);
    seeMenu(*Setting);
}

void playsound() {
    if (check)
        mciSendString(L"play a.wav", NULL, 0, NULL);
    else
        mciSendString(L"stop a.wav", NULL, 0, NULL);
}

void Help() {
    int x = 4, y = 3;     // ���� ��ǥ
    for (i = 0; i < 9; i++) selection(i + 2, 5, key_help[i]);       // ���۹� ����â
    for (i = 0; i < 9; i++) selection(i + 2, 30, rule_help[i]);       // ��Ģ ����â
    for (i = 0; i < 7; i++) selection(i + 12, 5, item_help[i]);     // ������ ����â
    for (i = 0; i < 5; i++) selection(i + 12, 30, maker_help[i]);     // ������ ����â
    gotoxy(13, 6); setColor(12, "��");		 // ������
    gotoxy(15, 6); setColor(9, "��");       // �Ķ���
    gotoxy(16, 6); setColor(8, "��");       // ȸ��
    gotoxy(17, 6); setColor(10, "��");       // �ʷϻ�

    selection(37, 25, "��  ������");

    char c;
    do {
        c = _getch();
    } while (c != ENTER);
    seeMenu(*Menu);
}

void Menu() {// �޴� ȭ��
    int x = 18, y = 25;

    Animation(false);

    selection(x, y - 2, "��");

    selection(x, y, "Game Start");
    selection(x + 2, y, "Setting");
    selection(x + 4, y, "Help");
    selection(x + 6, y, "Exit");

    Menukeyget();
}

void Animation(bool sleepTF) {      //sleepTF�� �ִϸ��̼��� �۵����� �ƴϸ� �׳� ��¸����� ����
    int cnt = 0;
    int num[] = { 7, 19, 31, 43 };

    gotoxy(2, 4);
    for (i = 0; i < 52; i++) {
        printf("��");
        if (sleepTF) Sleep(10);
    }
    for (i = 3; i < 17; i++) {
        selection(i, 55, "��");
        if (sleepTF) Sleep(10);
    }
    for (i = 54; i > 3; i--) {
        selection(16, i, "��");
        if (sleepTF) Sleep(10);
    }
    for (i = 15; i >= 3; i--) {
        selection(i, 4, "��");
        if (sleepTF) Sleep(10);
    }

    for (i = 0; i < 44; i++) {              //MAZE ���ڸ���� �� �迭
        selection((i % 11) + 4, num[cnt], MAZE_ch[i]);  //�� ���ھ� ��� �ڸ� �ű��  //���پ� ���
        if (sleepTF) Sleep(50);
        if ((i + 1) % 11 == 0) cnt++;       
    }
}

// �޴� �����Ҷ� ������ �Լ�
int MoveSelet(int x, int y, int maxX) {     // x��ǥ, y��ǥ, maxX = �޴� ����
    char c;
    int nowX = x;
    int s = 0;
    maxX = x + ((maxX * 2) - 2);
    do {
        c = _getch();
        switch (c) {
        case UP: {
            if (nowX > x) {
                selection(nowX, y, "  ");
                selection(nowX -= 2, y, "��");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case DOWN: {
            if (nowX < maxX) {
                selection(nowX, y, "  ");
                selection(nowX += 2, y, "��");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case ENTER:
            s = (nowX - x) / 2;
            break;
        }
    } while (c != ENTER);

    return s;
}

void Client() {
    system("cls");
    char sAddr[15];
    int sPort;
    char message[BUFSIZE];

    printf("Server Address : ");       gets(sAddr);
    printf("Port Number : ");       gets(message);
    sPort = atoi(message);

    if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
        printf("WSAStartup ����, �����ڵ� : %d\n", WSAGetLastError());
    }

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (s == INVALID_SOCKET) {
        printf("���� ���� ����, �����ڵ� : %d\n", WSAGetLastError());
        WSACleanup();
    }

    si.sin_family = AF_INET;
    si.sin_addr.s_addr = inet_addr(sAddr);
    //   sin.sin_addr.S_un.S_addr = inet_addr(sAddr);
    si.sin_port = htons(sPort);


    if (connect(s, (SOCKADDR*)&si, sizeof(si)) != 0) {
        printf("���� ����, �����ڵ� : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("������ ����Ǿ����ϴ�.");
    Sleep(1000);
    Mk_MazeMap();
}

void Server() {
    system("cls");
    // ���� ���� 2.2�� ����Ҽ��ִ��� �ü���� Ȯ��, 
    // ��� �����ϸ� wsaData�� ���� ä���ش�.
    if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {

        printf("WSAStartup ����, �����ڵ� : %d\n", WSAGetLastError());
    }

    // ���ϻ��� , socket(����� �ּ�ü��, ����Ÿ��, ���������۹��);
    // AF_INET : IPv4 �ּ� ���
    // SOCK_STREAM : ���������� (������ ����� Ŭ���̾�Ʈ�͸� ������ �ۼ��� ����) 
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // socket�Լ��� ���ϻ��� ���н� INVALID_SOCKET ��ȯ
    if (s == INVALID_SOCKET) {
        printf("���� ���� ����, �����ڵ� : %d\n", WSAGetLastError());
        WSACleanup();
    }

    // ������ �����Ǹ� �����ּ������� ä���ش�.
    si.sin_family = AF_INET;                  // ����ϴ� �ּ�ü�� ���
    si.sin_port = htons(9190);                  // ���� ��Ʈ��ȣ ����
    si.sin_addr.s_addr = htonl(ADDR_ANY);
    //   sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);      // ��� Ŭ���̾�Ʈ�� ���� ���

       // �����ڵ� s�� ������ �����ּ�����(sin) ��� , ���� �� SOCKET_ERROR ��ȯ
    if (bind(s, (SOCKADDR*)&si, sizeof(si)) == SOCKET_ERROR) {
        printf("bind ���� , �����ڵ� : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }

    // Ŭ���̾�Ʈ ���Ӵ�� , listen(�����ڵ�, ���� ����ڼ�)
    if (listen(s, SOMAXCONN) == 1) {
        printf("listen ��� ���� ���� , �����ڵ� : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("������ �����մϴ�\n");
    printf("Ŭ���̾�Ʈ�κ����� ������ ��ٸ��� �ֽ��ϴ� ...\n");

    int cli_size = sizeof(cli_addr);   // accept�Լ��� cli_addr�� ũ�⸦ �ּҷ� �Ѱ�����ϹǷ� ������ �����.

    // Ŭ���̾�Ʈ�� ����, Ŭ���̾�Ʈ�� ������ ���������� ���Ѵ��.
    // Ŭ���̾�Ʈ�� ���� �� Ŭ���̾�Ʈ�����ڵ�(cs)�� Ŭ���̾�Ʈ�� ������ ������ �ִ´�.
    cs = accept(s, (SOCKADDR*)&cli_addr, &cli_size);
    if (cs == INVALID_SOCKET) {
        printf("���� ���� ����, �����ڵ� : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }

    printf("Ŭ���̾�Ʈ�� ����Ǿ����ϴ�\n");
    Sleep(1000);
    Mk_MazeMap();
    if (closesocket(cs) != 0 || closesocket(s) != 0) {
        printf("���� ���� ����, �����ڵ� : %d\n", WSAGetLastError());
        WSACleanup();
    }

    if (WSACleanup() != 0) {
        printf("WSACleanup ����, �����ڵ� : %d\n", WSAGetLastError());
    }

    printf("������ �����մϴ�\n");
    closesocket(cs);
    closesocket(s);
    WSACleanup();

}


void endMenu() {
    int x = 4, y = 3;     // ���� ��ǥ
    if (clientcount == 0 && servercount == -1) {  // Ŭ���̾�Ʈ �¸�
        for (i = 0; i < 5; i++) selection(i + 12, 15, client_end_menu[i]);
        selection(37, 25, "�� ������");
    }
    else if (clientcount == -1 && servercount == 0) { // ���� �¸�
        for (i = 0; i < 5; i++) selection(i + 12, 15, server_end_menu[i]);
        selection(37, 25, "�� ������");
    }
    else if (clientcount == 1 && servercount == 2) { // ���� �й�
        for (i = 0; i < 5; i++) selection(i + 12, 15, server_end_menu2[i]);
        selection(37, 25, "�� ������");
    }
    else if (clientcount == 2 && servercount == 1) { // Ŭ���̾�Ʈ �й�
        for (i = 0; i < 5; i++) selection(i + 12, 15, client_end_menu2[i]);
        selection(37, 25, "�� ������");
    }
    else if (solocount == 0) {
        for (i = 0; i < 5; i++) selection(i + 12, 15, solo_end_menu[i]);
        selection(37, 25, "�� ������");
    }
    else if (solocount == 1) {
        for (i = 0; i < 5; i++) selection(i + 12, 15, solo_end_menu2[i]);
        selection(37, 25, "�� ������");
    }

    char c;
    do {
        c = _getch();
        switch (c) {
        case ENTER:
            if (closesocket(s) != 0) {
                printf("���� ���� ����, ���� �ڵ� : %d\n", WSAGetLastError());
                WSACleanup();
            }

            if (WSACleanup() != 0) {
                printf("WSACleanup ����, �����ڵ� : %d\n", WSAGetLastError());
            }
            closesocket(cs);
            closesocket(s);
            WSACleanup();
            setMenuSize();
            seeMenu(*Menu);
            break;
        }
    } while (c != ENTER);
}
