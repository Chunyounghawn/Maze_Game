#include "Main_Func.h"
#include "util.h"
#include "Maze_Func.h"
#include "Word_Func.h"

void main() {
    check = 1;
    playsound();               // 노래 재생
    SetConsoleTitle(TEXT("MazeRunner"));     // 제목 설정
    setMenuSize();             // 메뉴 사이즈 조절
    hidingCursor();            // 커서 숨기기
    Animation(true);          // 애니메이션 실행(true, false)로 구분
    Menu();
}

void Menukeyget() { //메뉴 키입력
    keyvalue = MoveSelet(18, 23, 4);

    if (keyvalue == 0) { seeMenu(*GameMode); }              // 게임 모드 선택 메뉴
    else if (keyvalue == 1) { seeMenu(*Setting); }          // 설정 하기
    else if (keyvalue == 2) { seeMenu(*Help); }             // 도움말
    else if (keyvalue == 3) {                               // 게임 종료
        printf("게임을 종료합니다.");
        exit(1);
    }
}

void GameMode() {
    int x = 18, y = 4;
    selection(x, y, "▶  1인용");
    selection(x + 2, y + 2, "2인용");
    selection(x + 4, y + 2, "모드설정");
    selection(x + 6, y + 2, "나가기");
    
    keyvalue = MoveSelet(x, y, 4);

    if (keyvalue == 0) seeMenu(*Mk_MazeMap);               // 모드 설정
    else if (keyvalue == 1) seeMenu(*MultiMode);            // 멀티 모드 메뉴
    else if (keyvalue == 2) seeMenu(*SelectMode);                 // 모드 설정
    else if (keyvalue == 3) seeMenu(*Menu);           // 메인 메뉴
}

void SelectMode() {
    int x = 18, y = 4;

    if (EyeMode == true)
        selection(x, y, "▶  ■ 시야 제한");
    else 
        selection(x, y, "▶  □ 시야 제한");

    if (TimerMode == true)
        selection(x + 2, y + 2, "■ 타이머");
    else 
        selection(x + 2, y + 2, "□ 타이머");
    selection(x + 4, y + 2, "-  나가기");
    char c;
    int s = 18;
    do {
        c = _getch();
        switch (c) {
        case UP: {
            if (s > x) {
                selection(s, y, "  ");
                selection(s -= 2, y, "▶");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case DOWN: {
            if (s < 24) {
                selection(s, y, "  ");
                selection(s += 2, y, "▶");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case ENTER:
            s = (s - x) / 2;
            if (s == 0) {
                if (EyeMode == true) {
                    selection(x, y + 2, "□");
                    s = s * 2 + x;
                    EyeMode = false;
                }
                else {
                    selection(x, y + 2, "■");
                    s = s * 2 + x;
                    EyeMode = true;
                }
                c = DOWN;
            }
            else if (s == 1) {
                if (TimerMode == true) {
                    selection(x + 2, y + 2, "□");
                    s = s * 2 + x;
                    TimerMode = false;
                }
                else {
                    selection(x + 2, y + 2, "■");
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
    selection(x, y, "▶  방만들기");
    selection(x + 2, y + 2, "참여하기");
    selection(x + 4, y + 2, "나가기");

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
    selection(x, y, "▶  사운드 설정");
    selection(x + 2, y + 2, "나가기");

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
    int x = 4, y = 3;     // 기준 좌표
    for (i = 0; i < 9; i++) selection(i + 2, 5, key_help[i]);       // 조작법 설명창
    for (i = 0; i < 9; i++) selection(i + 2, 30, rule_help[i]);       // 규칙 설명창
    for (i = 0; i < 7; i++) selection(i + 12, 5, item_help[i]);     // 아이템 설명창
    for (i = 0; i < 5; i++) selection(i + 12, 30, maker_help[i]);     // 제작진 설명창
    gotoxy(13, 6); setColor(12, "♥");		 // 빨간색
    gotoxy(15, 6); setColor(9, "ㆀ");       // 파란색
    gotoxy(16, 6); setColor(8, "О");       // 회색
    gotoxy(17, 6); setColor(10, "●");       // 초록색

    selection(37, 25, "▶  나가기");

    char c;
    do {
        c = _getch();
    } while (c != ENTER);
    seeMenu(*Menu);
}

void Menu() {// 메뉴 화면
    int x = 18, y = 25;

    Animation(false);

    selection(x, y - 2, "▶");

    selection(x, y, "Game Start");
    selection(x + 2, y, "Setting");
    selection(x + 4, y, "Help");
    selection(x + 6, y, "Exit");

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

// 메뉴 선택할때 움직임 함수
int MoveSelet(int x, int y, int maxX) {     // x좌표, y좌표, maxX = 메뉴 개수
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
                selection(nowX -= 2, y, "▶");
                PlaySound(TEXT("select_sound.wav"), NULL, SND_ASYNC);
            } break;
        }
        case DOWN: {
            if (nowX < maxX) {
                selection(nowX, y, "  ");
                selection(nowX += 2, y, "▶");
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
        printf("WSAStartup 실패, 에러코드 : %d\n", WSAGetLastError());
    }

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (s == INVALID_SOCKET) {
        printf("소켓 생성 실패, 에러코드 : %d\n", WSAGetLastError());
        WSACleanup();
    }

    si.sin_family = AF_INET;
    si.sin_addr.s_addr = inet_addr(sAddr);
    //   sin.sin_addr.S_un.S_addr = inet_addr(sAddr);
    si.sin_port = htons(sPort);


    if (connect(s, (SOCKADDR*)&si, sizeof(si)) != 0) {
        printf("접속 실패, 에러코드 : %d\n", WSAGetLastError());
        closesocket(s); WSACleanup();
    }
    printf("서버와 연결되었습니다.");
    Sleep(1000);
    Mk_MazeMap();
}

void Server() {
    system("cls");
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
    si.sin_family = AF_INET;                  // 사용하는 주소체계 명시
    si.sin_port = htons(9190);                  // 서버 포트번호 설정
    si.sin_addr.s_addr = htonl(ADDR_ANY);
    //   sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);      // 모든 클라이언트의 접속 허용

       // 소켓핸들 s에 설정한 소켓주소정보(sin) 담기 , 실패 시 SOCKET_ERROR 반환
    if (bind(s, (SOCKADDR*)&si, sizeof(si)) == SOCKET_ERROR) {
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
    Sleep(1000);
    Mk_MazeMap();
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


void endMenu() {
    int x = 4, y = 3;     // 기준 좌표
    if (clientcount == 0 && servercount == -1) {  // 클라이언트 승리
        for (i = 0; i < 5; i++) selection(i + 12, 15, client_end_menu[i]);
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == -1 && servercount == 0) { // 서버 승리
        for (i = 0; i < 5; i++) selection(i + 12, 15, server_end_menu[i]);
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == 1 && servercount == 2) { // 서버 패배
        for (i = 0; i < 5; i++) selection(i + 12, 15, server_end_menu2[i]);
        selection(37, 25, "▶ 나가기");
    }
    else if (clientcount == 2 && servercount == 1) { // 클라이언트 패배
        for (i = 0; i < 5; i++) selection(i + 12, 15, client_end_menu2[i]);
        selection(37, 25, "▶ 나가기");
    }
    else if (solocount == 0) {
        for (i = 0; i < 5; i++) selection(i + 12, 15, solo_end_menu[i]);
        selection(37, 25, "▶ 나가기");
    }
    else if (solocount == 1) {
        for (i = 0; i < 5; i++) selection(i + 12, 15, solo_end_menu2[i]);
        selection(37, 25, "▶ 나가기");
    }

    char c;
    do {
        c = _getch();
        switch (c) {
        case ENTER:
            if (closesocket(s) != 0) {
                printf("소켓 제거 실패, 에러 코드 : %d\n", WSAGetLastError());
                WSACleanup();
            }

            if (WSACleanup() != 0) {
                printf("WSACleanup 실패, 에러코드 : %d\n", WSAGetLastError());
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
