#pragma once
#include "Incld.h"
//Main 함수들-----------------------------------------------------------------------------------

void Menukeyget();
void Setting();
void SoundVolume();
void Help();
void Animation(bool sleepTF);
void playsound();
void Menu();
void GameMode();
int MoveSelet(int x, int y, int maxX);
void SelectMode();
void MultiMode();
void Server();
void Client();
void endMenu();

int keyvalue;		//0
int check;		//1
int clientcount;
int servercount;
int solocount;
bool EyeMode;
bool TimerMode;

SOCKET      s, cs;            // 서버와 클라이언트의 소켓 핸들 구조체
WSADATA      wsaData;         // 윈속 정보를 담을 구조체 
SOCKADDR_IN si, cli_addr;      // 서버와 클라이언트의 소켓 주소정보를 담을 구조체