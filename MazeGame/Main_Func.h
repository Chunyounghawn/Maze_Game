#pragma once
#include "Incld.h"
//Main �Լ���-----------------------------------------------------------------------------------

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

SOCKET      s, cs;            // ������ Ŭ���̾�Ʈ�� ���� �ڵ� ����ü
WSADATA      wsaData;         // ���� ������ ���� ����ü 
SOCKADDR_IN si, cli_addr;      // ������ Ŭ���̾�Ʈ�� ���� �ּ������� ���� ����ü