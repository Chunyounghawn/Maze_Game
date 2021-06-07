#include "Main_Func.h"
#include "Incld.h"
#include "util.h"
#include "Maze_Func.h"
#include "Word_Func.h"


void main() {
    check = 1;
    playsound();               // �뷡 ���
    SetConsoleTitle(TEXT("MazeRunner"));     // ���� ����
    setMenuSize();             // �޴� ������ ����
    hidingCursor();            // Ŀ�� �����
    Animation(false);          // �ִϸ��̼� ����(true, false)�� ����
    Menu();
}

void Menukeyget() { //�޴� Ű�Է�
    int x = 18, y = 23;
    char c;

    do {
        c = getch();
        switch (c) {
            case UP: {
                if (x > 18) {               
                    selection(x, y, "  ");
                    selection(x -= 2, y, "��");                   
                } break;
            }
            case DOWN: {
                if (x < 26) {
                    selection(x, y, "  ");
                    selection(x += 2, y, "��");
                } break;
            }
            case ENTER: //���� �Է½� cls�� �ܼ� �ʱ�ȭ
                keyvalue = (x - 18) / 2;
                break;
            }
    } while (c != ENTER);

    if (keyvalue == 0) {
        system("cls");
        //Mk_MazeMap();
        serverselect();
    }
    else if (keyvalue == 1) {
        system("cls");
        Ranking();
    }
    else if (keyvalue == 2) { // Setting ����
        system("cls");
        Setting();
    }
    else if (keyvalue == 3) { // Help ����
        system("cls");
        Help();
    } 
    else if (keyvalue == 4) {
        printf("������ �����մϴ�.");
        exit(1);
    }
}

void Setting() {
    int x = 18, y = 2;
    selection(x, y - 1, "��  ���� ����");
    selection(x + 2, y + 1, "������");

    while (1) {
        char c = getch();
        switch (c) {
        case UP:
            if (x > 18) {
                selection(x, y - 1, "  ");
                selection(x -= 2, y - 1, "��");
            } break;
        case DOWN:
            if (x < 20) {
                selection(x, y - 1, "  ");
                selection(x += 2, y - 1, "��");
            } break;
        case ENTER:
            keyvalue = (x - 18) / 2;
            Settingexcute();
            break;
        }
    }

}
void Ranking() {
    int x = 18, y = 4;
    selection(x, y - 1, "��  ��ŷ ����");
    selection(x + 2, y + 1, "������");
    while (1) {
        char c = getch();
        switch (c) {
            case UP:
                if (x > 18) {
                    selection(x, y - 1, "  ");
                    selection(x -= 2, y - 1, "��");
                } break;
            case DOWN:
                if (x < 20) {        
                    selection(x, y - 1, "  ");
                    selection(x += 2, y - 1, "��");
                } break;
            case ENTER:
                keyvalue = (x - 18) / 2;
                Rankingexcute();
                break;
        }
    }
}

void Rankingexcute() {
    int x = 10, y = 2;
    if (keyvalue == 0) {
        system("cls");
        printf("���̵�          Ŭ���� �ð�          ��¥          ����\n");
        printf("abc             20:30:40             2021-05-18      1 \n");
        printf("def             30:10:17             2021-05-08      2 \n");
        printf("ghi             42:30:55             2021-05-01      3 \n");
        printf("jkl             55:30:44             2021-05-17      4 \n");

        selection(x, y - 1, "��  ������");
        selection(x + 2, y + 1, "�޴��� ������");

        char c;
        do {
            c = getch();
            switch (c) {
                case UP:
                    if (x > 10) {
                        selection(x, y - 1, "  ");
                        selection(x -= 2, y - 1, "��");
                    } break;
                case DOWN:
                    if (x < 12) {
                        selection(x, y - 1, "  ");
                        selection(x += 2, y - 1, "��");
                    } break;
                case ENTER:
                    keyvalue = (x - 10) / 2;
                    break;
            }
        } while (c != ENTER);
    }
    if (keyvalue == 0) {
        system("cls");
        Ranking();
    }
    else if (keyvalue == 1) {
        system("cls");
        Menu();
    }
}

void SoundVolume() {
    int x = 18, y = 10;
    gotoxy(x, y);
    if (check) selection(x, y, "On  ");
    else selection(x, y, "Off");

    while (1) {
        switch (getch()) {
            case UP:
                check = 1;
                selection(x, y, "On  ");
                playsound();
                break;
            case DOWN:
                check = 0;
                selection(x, y, "Off");
                playsound();
                break;
            case ENTER:
                system("cls");
                Setting();
                break;
        }
    }
}

void playsound() {
    if (check) PlaySound(TEXT("a.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
    else PlaySound(NULL, 0, 0);
}

void Settingexcute() {
    if (keyvalue == 0) {
        SoundVolume();
    }
    else if (keyvalue == 1) {
        system("cls");
        Menu();
    }
}

void Help() {
    int x = 4, y = 3;     // ���� ��ǥ
    for (i = 0; i < 9; i++) selection(i + 2, 5, key_help[i]);       // ���۹� ����â
    for (i = 0; i < 9; i++) selection(i + 2, 30, rule_help[i]);       // ��Ģ ����â
    for (i = 0; i < 5; i++) selection(i + 12, 5, item_help[i]);     // ������ ����â
    for (i = 0; i < 5; i++) selection(i + 12, 30, maker_help[i]);     // ������ ����â
    selection(37, 25, "�� ������");

    char c;
    do {
        c = getch();
        switch (c) {
        case ENTER:
            system("cls");
            Menu();
            break;
        }
    } while (c != ENTER);
}


void Menu() {// �޴� ȭ��
    int x = 18, y = 25;

    Animation(false);

    selection(x, y - 2, "��");

    selection(x, y, "Game Start");
    selection(x + 2, y, "Ranking");
    selection(x + 4, y, "Setting");
    selection(x + 6, y, "Help");
    selection(x + 8, y, "Exit");

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
void serverselect() {
    int x = 18, y = 4;
    selection(x, y - 1, "��  1�ο� ����");
    selection(x + 2, y + 1, "2�ο� ����");
    selection(x + 4, y + 1, "������");
    while (1) {
        char c = getch();
        switch (c) {
        case UP: {
            if (x > 18) {
                selection(x, y - 1, "  ");
                selection(x -= 2, y - 1, "��");
            } break;
        }
        case DOWN: {
            if (x < 22) {
                selection(x, y - 1, "  ");
                selection(x += 2, y - 1, "��");
            } break;
        }
        case ENTER:
            keyvalue = (x - 18) / 2;
            serverexcute();
            break;
        }
    }
}

void serverexcute() {
    int x = 10, y = 2;
    if (keyvalue == 0) {
        system("cls");
        Mk_MazeMap();
    }
    else if (keyvalue == 1) {
        system("cls");
        selection(x, y - 1, "��  ����(ȣ��Ʈ Player 1)");
        selection(x + 2, y + 1, "Ŭ���̾�Ʈ(Player 2)");
        selection(x + 4, y + 1, "������");

        char c;
        do {
            c = getch();
            switch (c) {
            case UP: {
                if (x > 10) {
                    selection(x, y - 1, "  ");
                    selection(x -= 2, y - 1, "��");
                } break;
            }
            case DOWN: {
                if (x < 14) {
                    selection(x, y - 1, "  ");
                    selection(x += 2, y - 1, "��");
                } break;
            }
            case ENTER:
                keyvalue = (x - 10) / 2;
                break;
            }
        } while (c != ENTER);
    }
    if (keyvalue == 0) {
        system("cls");
        server();
        servercount = 1;
        clientcount = 0;
    }
    else if (keyvalue == 1) {
        system("cls");
        client();
        clientcount = 1;
        servercount = 0;
    }
    else if (keyvalue == 2) {
        system("cls");
        Menu();
        Menukeyget();
    }
}

void server() {
    system("cls");
    SOCKET      s, cs;            // ������ Ŭ���̾�Ʈ�� ���� �ڵ� ����ü
    WSADATA      wsaData;         // ���� ������ ���� ����ü 
    SOCKADDR_IN sin, cli_addr;      // ������ Ŭ���̾�Ʈ�� ���� �ּ������� ���� ����ü


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
    sin.sin_family = AF_INET;                  // ����ϴ� �ּ�ü�� ���
    sin.sin_port = htons(9190);                  // ���� ��Ʈ��ȣ ����
    sin.sin_addr.s_addr = htonl(ADDR_ANY);
    //   sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);      // ��� Ŭ���̾�Ʈ�� ���� ���

       // �����ڵ� s�� ������ �����ּ�����(sin) ��� , ���� �� SOCKET_ERROR ��ȯ
    if (bind(s, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
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

    char message[BUFSIZE];   // �����͸� �޾ƿ� ���� ����

    // ������ ���� , recv(Ŭ���̾�Ʈ�����ڵ�,������ �޾ƿ� ����,������ ������ �ִ� ����, ������ ���� ��ȣ);
    recv(cs, message, 1024, 0);
    printf("[Ŭ���̾�Ʈ�� ���� ������]\n%s\n", message);


    // ������ �۽� , send(Ŭ���̾�Ʈ�����ڵ�,���� ������ ����,���� ������ ����, ������ ���� ��ȣ);
    printf("������ ���� ������ �Է� : ");


    char send_y[BUFSIZE];   //�ϴ� BUFSIZE�� �غ�, char�� 2����Ʈ�ε� ��¥ 2�������� �������� �˳��ϰ� �� �ͱ�
    char send_x[BUFSIZE];
    Mk_MazeMap();
    /*
    send(cs, mazeMap, sizeof(mazeMap), 0);// sizeof(mazeMap)==10404 4*51*51
    Eye(user_x, user_y);
    while (1) {
        //send(s, user_x, strlen(user_x), 0);
        //send(s, user_y, strlen(user_y), 0);
        recv(s, send_y, 1024, 0); //char�� 2����Ʈ�ε� ��¥ 2�������� �������� �˳��ϰ� �� �ͱ�
        recv(s, send_x, 1024, 0);
        gotoxy(user_x, user_y);
        printf("  ");
        user_y = atoi(send_y);
        user_x = atoi(send_x);
    //    move();
    }*/
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
void client() {
    system("cls");
    SOCKET s;
    WSADATA wsaData;
    SOCKADDR_IN sin;

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

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(sAddr);
    //   sin.sin_addr.S_un.S_addr = inet_addr(sAddr);
    sin.sin_port = htons(sPort);


    if (connect(s, (SOCKADDR*)&sin, sizeof(sin)) != 0) {
        printf("���� ����, �����ڵ� : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("������ ����Ǿ����ϴ�.\n ������ ������ ������ �Է� : ");


    gets(message);

    send(s, message, strlen(message) + 1, 0);

    printf("������ ���� ����!\n");
    Mk_MazeMap();
    /*
    recv(s, mazeMap, sizeof(mazeMap), 0);

    Eye(user_x, user_y); 
    
    clientmove(s);
    */
    if (closesocket(s) != 0) {
        printf("���� ���� ����, ���� �ڵ� : %d\n", WSAGetLastError());
        WSACleanup();
    }

    if (WSACleanup() != 0) {
        printf("WSACleanup ����, �����ڵ� : %d\n", WSAGetLastError());
    }
    closesocket(s);
    WSACleanup();

}


void endMenu() {
    int x = 4, y = 3;     // ���� ��ǥ
    if (clientcount == 0 && servercount == -1) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, server_end_menu[i]);     // ������ ����â
        selection(37, 25, "�� ������");
    }
    else if (clientcount == -1 && servercount == 0){
        for (i = 0; i < 5; i++) selection(i + 12, 30, client_end_menu[i]);     // ������ ����â
        selection(37, 25, "�� ������");
    }
    else if (clientcount == 1 && servercount == 2) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, server_end_menu[i]);     // ������ ����â
        selection(37, 25, "�� ������");
    }
    else if (clientcount == 2 && servercount == 1) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, client_end_menu[i]);     // ������ ����â
        selection(37, 25, "�� ������");
    }


    char c;
    do {
        c = getch();
        switch (c) {
        case ENTER:
            system("cls");
            Menu();
            break;
        }
    } while (c != ENTER);
}