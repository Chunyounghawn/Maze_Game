#include "Main_Func.h"
#include "Incld.h"
#include "util.h"
#include "Maze_Func.h"
#include "Word_Func.h"


void main() {
    check = 1;
    playsound();               // 노래 재생
    SetConsoleTitle(TEXT("MazeRunner"));     // 제목 설정
    setMenuSize();             // 메뉴 사이즈 조절
    hidingCursor();            // 커서 숨기기
    Animation(false);          // 애니메이션 실행(true, false)로 구분
    Menu();
}

void Menukeyget() { //메뉴 키입력
    int x = 18, y = 23;
    char c;

    do {
        c = getch();
        switch (c) {
            case UP: {
                if (x > 18) {               
                    selection(x, y, "  ");
                    selection(x -= 2, y, "▶");                   
                } break;
            }
            case DOWN: {
                if (x < 26) {
                    selection(x, y, "  ");
                    selection(x += 2, y, "▶");
                } break;
            }
            case ENTER: //엔터 입력시 cls로 콘솔 초기화
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
    else if (keyvalue == 2) { // Setting 실행
        system("cls");
        Setting();
    }
    else if (keyvalue == 3) { // Help 실행
        system("cls");
        Help();
    } 
    else if (keyvalue == 4) {
        printf("게임을 종료합니다.");
        exit(1);
    }
}

void Setting() {
    int x = 18, y = 2;
    selection(x, y - 1, "▶  사운드 설정");
    selection(x + 2, y + 1, "나가기");

    while (1) {
        char c = getch();
        switch (c) {
        case UP:
            if (x > 18) {
                selection(x, y - 1, "  ");
                selection(x -= 2, y - 1, "▶");
            } break;
        case DOWN:
            if (x < 20) {
                selection(x, y - 1, "  ");
                selection(x += 2, y - 1, "▶");
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
    selection(x, y - 1, "▶  랭킹 보기");
    selection(x + 2, y + 1, "나가기");
    while (1) {
        char c = getch();
        switch (c) {
            case UP:
                if (x > 18) {
                    selection(x, y - 1, "  ");
                    selection(x -= 2, y - 1, "▶");
                } break;
            case DOWN:
                if (x < 20) {        
                    selection(x, y - 1, "  ");
                    selection(x += 2, y - 1, "▶");
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
        printf("아이디          클리어 시간          날짜          순위\n");
        printf("abc             20:30:40             2021-05-18      1 \n");
        printf("def             30:10:17             2021-05-08      2 \n");
        printf("ghi             42:30:55             2021-05-01      3 \n");
        printf("jkl             55:30:44             2021-05-17      4 \n");

        selection(x, y - 1, "▶  나가기");
        selection(x + 2, y + 1, "메뉴로 나가기");

        char c;
        do {
            c = getch();
            switch (c) {
                case UP:
                    if (x > 10) {
                        selection(x, y - 1, "  ");
                        selection(x -= 2, y - 1, "▶");
                    } break;
                case DOWN:
                    if (x < 12) {
                        selection(x, y - 1, "  ");
                        selection(x += 2, y - 1, "▶");
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
    int x = 4, y = 3;     // 기준 좌표
    for (i = 0; i < 9; i++) selection(i + 2, 5, key_help[i]);       // 조작법 설명창
    for (i = 0; i < 9; i++) selection(i + 2, 30, rule_help[i]);       // 규칙 설명창
    for (i = 0; i < 5; i++) selection(i + 12, 5, item_help[i]);     // 아이템 설명창
    for (i = 0; i < 5; i++) selection(i + 12, 30, maker_help[i]);     // 제작진 설명창
    selection(37, 25, "▶ 나가기");

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


void Menu() {// 메뉴 화면
    int x = 18, y = 25;

    Animation(false);

    selection(x, y - 2, "▶");

    selection(x, y, "Game Start");
    selection(x + 2, y, "Ranking");
    selection(x + 4, y, "Setting");
    selection(x + 6, y, "Help");
    selection(x + 8, y, "Exit");

    Menukeyget();
}

void Animation(bool sleepTF) {      //sleepTF로 애니메이션을 작동할지 아니면 그냥 출력만할지 결정
    int cnt = 0;
    int num[] = { 7, 19, 31, 43 };

    gotoxy(2, 4);
    for (i = 0; i < 52; i++) {
        printf("□");
        if (sleepTF) Sleep(10);
    }
    for (i = 3; i < 17; i++) {
        selection(i, 55, "□");
        if (sleepTF) Sleep(10);
    }
    for (i = 54; i > 3; i--) {
        selection(16, i, "□");
        if (sleepTF) Sleep(10);
    }
    for (i = 15; i >= 3; i--) {
        selection(i, 4, "□");
        if (sleepTF) Sleep(10);
    }

    for (i = 0; i < 44; i++) {              //MAZE 문자모양을 딴 배열
        selection((i % 11) + 4, num[cnt], MAZE_ch[i]);  //한 문자씩 끊어서 자리 옮기기  //한줄씩 출력
        if (sleepTF) Sleep(50);
        if ((i + 1) % 11 == 0) cnt++;       
    }
}
void serverselect() {
    int x = 18, y = 4;
    selection(x, y - 1, "▶  1인용 게임");
    selection(x + 2, y + 1, "2인용 게임");
    selection(x + 4, y + 1, "나가기");
    while (1) {
        char c = getch();
        switch (c) {
        case UP: {
            if (x > 18) {
                selection(x, y - 1, "  ");
                selection(x -= 2, y - 1, "▶");
            } break;
        }
        case DOWN: {
            if (x < 22) {
                selection(x, y - 1, "  ");
                selection(x += 2, y - 1, "▶");
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
        selection(x, y - 1, "▶  서버(호스트 Player 1)");
        selection(x + 2, y + 1, "클라이언트(Player 2)");
        selection(x + 4, y + 1, "나가기");

        char c;
        do {
            c = getch();
            switch (c) {
            case UP: {
                if (x > 10) {
                    selection(x, y - 1, "  ");
                    selection(x -= 2, y - 1, "▶");
                } break;
            }
            case DOWN: {
                if (x < 14) {
                    selection(x, y - 1, "  ");
                    selection(x += 2, y - 1, "▶");
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
    SOCKET      s, cs;            // 서버와 클라이언트의 소켓 핸들 구조체
    WSADATA      wsaData;         // 윈속 정보를 담을 구조체 
    SOCKADDR_IN sin, cli_addr;      // 서버와 클라이언트의 소켓 주소정보를 담을 구조체


    // 윈속 버전 2.2를 사용할수있는지 운영체제에 확인, 
    // 사용 가능하면 wsaData에 값을 채워준다.
    if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {

        printf("WSAStartup 실패, 에러코드 : %d\n", WSAGetLastError());
    }

    // 소켓생성 , socket(사용할 주소체계, 소켓타입, 데이터전송방식);
    // AF_INET : IPv4 주소 사용
    // SOCK_STREAM : 연결지향형 (소켓이 연결된 클라이언트와만 데이터 송수신 가능) 
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // socket함수로 소켓생성 실패시 INVALID_SOCKET 반환
    if (s == INVALID_SOCKET) {
        printf("소켓 생성 실패, 에러코드 : %d\n", WSAGetLastError());
        WSACleanup();
    }

    // 소켓이 생성되면 소켓주소정보를 채워준다.
    sin.sin_family = AF_INET;                  // 사용하는 주소체계 명시
    sin.sin_port = htons(9190);                  // 서버 포트번호 설정
    sin.sin_addr.s_addr = htonl(ADDR_ANY);
    //   sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);      // 모든 클라이언트의 접속 허용

       // 소켓핸들 s에 설정한 소켓주소정보(sin) 담기 , 실패 시 SOCKET_ERROR 반환
    if (bind(s, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
        printf("bind 실패 , 에러코드 : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }

    // 클라이언트 접속대기 , listen(소켓핸들, 접속 대기자수)
    if (listen(s, SOMAXCONN) == 1) {
        printf("listen 모드 설정 실패 , 에러코드 : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("서버를 시작합니다\n");
    printf("클라이언트로부터의 접속을 기다리고 있습니다 ...\n");

    int cli_size = sizeof(cli_addr);   // accept함수에 cli_addr의 크기를 주소로 넘겨줘야하므로 변수를 만든다.

    // 클라이언트와 연결, 클라이언트의 접속이 있을때까지 무한대기.
    // 클라이언트와 연결 후 클라이언트소켓핸들(cs)에 클라이언트의 정보를 가지고 있는다.
    cs = accept(s, (SOCKADDR*)&cli_addr, &cli_size);
    if (cs == INVALID_SOCKET) {
        printf("접속 승인 실패, 에러코드 : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }

    printf("클라이언트와 연결되었습니다\n");

    char message[BUFSIZE];   // 데이터를 받아올 변수 생성

    // 데이터 수신 , recv(클라이언트소켓핸들,데이터 받아올 변수,수신할 데이터 최대 길이, 데이터 수신 기호);
    recv(cs, message, 1024, 0);
    printf("[클라이언트가 보낸 데이터]\n%s\n", message);


    // 데이터 송신 , send(클라이언트소켓핸들,보낼 데이터 변수,보낼 데이터 길이, 데이터 수신 기호);
    printf("서버에 보낼 데이터 입력 : ");


    char send_y[BUFSIZE];   //일단 BUFSIZE로 해봄, char는 2바이트인데 진짜 2만받으면 오류나서 넉넉하게 줌 왤까
    char send_x[BUFSIZE];
    Mk_MazeMap();
    /*
    send(cs, mazeMap, sizeof(mazeMap), 0);// sizeof(mazeMap)==10404 4*51*51
    Eye(user_x, user_y);
    while (1) {
        //send(s, user_x, strlen(user_x), 0);
        //send(s, user_y, strlen(user_y), 0);
        recv(s, send_y, 1024, 0); //char는 2바이트인데 진짜 2만받으면 오류나서 넉넉하게 줌 왤까
        recv(s, send_x, 1024, 0);
        gotoxy(user_x, user_y);
        printf("  ");
        user_y = atoi(send_y);
        user_x = atoi(send_x);
    //    move();
    }*/
    if (closesocket(cs) != 0 || closesocket(s) != 0) {
        printf("소켓 제거 실패, 에러코드 : %d\n", WSAGetLastError());
        WSACleanup();
    }

    if (WSACleanup() != 0) {
        printf("WSACleanup 실패, 에러코드 : %d\n", WSAGetLastError());
    }

    printf("서버를 종료합니다\n");
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
        printf("WSAStartup 실패, 에러코드 : %d\n", WSAGetLastError());
    }

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (s == INVALID_SOCKET) {
        printf("소켓 생성 실패, 에러코드 : %d\n", WSAGetLastError());
        WSACleanup();
    }

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(sAddr);
    //   sin.sin_addr.S_un.S_addr = inet_addr(sAddr);
    sin.sin_port = htons(sPort);


    if (connect(s, (SOCKADDR*)&sin, sizeof(sin)) != 0) {
        printf("접속 실패, 에러코드 : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("서버와 연결되었습니다.\n 서버에 전송할 데이터 입력 : ");


    gets(message);

    send(s, message, strlen(message) + 1, 0);

    printf("데이터 전송 성공!\n");
    Mk_MazeMap();
    /*
    recv(s, mazeMap, sizeof(mazeMap), 0);

    Eye(user_x, user_y); 
    
    clientmove(s);
    */
    if (closesocket(s) != 0) {
        printf("소켓 제거 실패, 에러 코드 : %d\n", WSAGetLastError());
        WSACleanup();
    }

    if (WSACleanup() != 0) {
        printf("WSACleanup 실패, 에러코드 : %d\n", WSAGetLastError());
    }
    closesocket(s);
    WSACleanup();

}


void endMenu() {
    int x = 4, y = 3;     // 기준 좌표
    if (clientcount == 0 && servercount == -1) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, server_end_menu[i]);     // 제작진 설명창
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == -1 && servercount == 0){
        for (i = 0; i < 5; i++) selection(i + 12, 30, client_end_menu[i]);     // 제작진 설명창
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == 1 && servercount == 2) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, server_end_menu[i]);     // 제작진 설명창
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == 2 && servercount == 1) {
        for (i = 0; i < 5; i++) selection(i + 12, 30, client_end_menu[i]);     // 제작진 설명창
        selection(37, 25, "▶ 나가기");
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