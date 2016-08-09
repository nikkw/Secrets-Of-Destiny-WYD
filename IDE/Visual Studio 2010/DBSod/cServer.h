#include <Windows.h>
#include <WinSock.h>
#include <cstdio>

#include "..\StdInfo\StdInfo.h"

#ifndef __CSERVER_H__
#define __CSERVER_H__

#define TIMER_SEC 0
#define TIMER_MIN 1
#define TIMER_HOUR 2
#define TIMER_YUT 5

#define WM_SOCKET WM_USER
#define ACCEPT_USER WM_USER + 1
#define RECV_USER WM_USER + 2

#define MAX_CHANNEL 10
#define MAX_PLAYER 750
#define MAX_ITEMLIST 6500

struct stGUI
{
	HWND Gui,     // Janela
		 hButton; // Botão de iniciar

	ATOM Class;
};

#pragma comment (lib, "WS2_32.lib")

struct stGameServer
{
	UINT8 Status,
		  GameID,
		  recvBuffer[65535],
		  sendBuffer[65535];

	char CIP[16];

	UINT32 Socket,
		   SizeOfData;
};

// Variáveis extern
extern UINT32       hServer;
extern SOCKADDR_IN  Service;
extern stGUI        GUI;
extern stGameServer GMSrv[MAX_CHANNEL];
extern stAccount    cAccounts[MAX_CHANNEL][MAX_PLAYER];

// Funcs
void createGUI(void);
bool createServer(void);
void ProcessSecTimer(void);
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int main(void);

#endif