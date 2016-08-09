#include "cServer.h"

UINT32       hServer;
SOCKADDR_IN  Service;
stGUI        GUI;
stGameServer GMSrv[MAX_CHANNEL];
stAccount    cAccounts[MAX_CHANNEL][MAX_PLAYER];

void createGUI(void)
{
	WNDCLASSEX wcex;

	HINSTANCE hInstance = GetModuleHandle(NULL);
	BOOL successful     = TRUE;
	
	const char* szWindowClass = "Secrets Of Destiny";
	const char* szWindowTitle = "SOD - v754 DataBase Emulator";

	wcex.cbSize         = sizeof WNDCLASSEX;
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = &WndProc;
	wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)COLOR_WINDOW;
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if(!(GUI.Class = RegisterClassEx(&wcex)))
	{
		MessageBoxA(0, "RegisterClassEx error", "Server::RegisterClassEx", 4096);
		successful = false;
	}
	else if(!(GUI.Gui = CreateWindow(szWindowClass, szWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 630, 440, NULL, NULL, hInstance, NULL)))
	{
		MessageBoxA(0, "CreateWindow error", "Server::CreateWindow", 4096);
		successful = false;
	}
	else if(!(GUI.hButton = CreateWindow("BUTTON", "Start", WS_VISIBLE | WS_CHILD | WS_GROUP | WS_TABSTOP | BS_PUSHBUTTON, 530, 8, 75, 25, GUI.Gui, NULL, hInstance, NULL)))
	{
		MessageBoxA(0, "CreateWindow error", "Server::CreateWindow", 4096);
		successful = false;
	}

	if(!successful)
		PostQuitMessage(1);

	ShowWindow(GUI.Gui, SW_SHOW);
	UpdateWindow(GUI.Gui);

	SetConsoleTitle(szWindowTitle);
	
	MSG Message;
	while(GetMessage(&Message, NULL, NULL, NULL))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		Sleep(50);
	}
}

bool createServer(void)
{
	bool retn = true;

	Service.sin_family      = AF_INET;
	Service.sin_port        = htons(7540);
	Service.sin_addr.s_addr = inet_addr("192.168.0.1");

	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(1, 1), &wsaData) != NO_ERROR)
	{
		MessageBoxA(0, "WSAStartup error", "Não foi possível carregar Winsock.dll", MB_OK);

		retn = false;
	}
	else if((hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		MessageBoxA(0, "socket error", "socket error", MB_OK);

		retn = false;
	}
	else if(bind(hServer, (SOCKADDR*)&Service, sizeof SOCKADDR_IN) == SOCKET_ERROR)
	{
		MessageBoxA(0, "bind error", "bind error", MB_OK);

		retn = false;
	}
	else if(listen(hServer, MAX_CHANNEL) == SOCKET_ERROR)
	{
		MessageBoxA(0, "listen error", "listen error", MB_OK);

		retn = false;
	}
	else if(WSAAsyncSelect(hServer, GUI.Gui, WM_SOCKET, FD_ACCEPT) == SOCKET_ERROR)
	{
		MessageBoxA(0, "WSAAsyncSelect error", "WSAAsyncSelect error", MB_OK);

		retn = false;
	}

	if(!retn)
	{
		if(hServer != INVALID_SOCKET)
			closesocket(hServer);

		WSACleanup();
	}

	return retn;
}

void ProcessSecTimer(void)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	printf("%02d:%02d:02d %02d/%02d/%04d\n", time.wHour, time.wMinute, time.wSecond, time.wDay, time.wMonth, time.wYear);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_SOCKET:
			{
				switch(wParam)
				{
					// Início de conexão
					case FD_ACCEPT:

						break;

					// Recebimento de pacote
					case FD_READ:

						break;

					// Conexão terminada
					case FD_CLOSE:

						break;
				}
			}
			break;

		case WM_COMMAND:
			if((HWND)lParam == GUI.hButton)
			{
				if(!createServer())
					printf("Falha durante a inicializacao do servidor.\n");
				else
					printf("Servidor iniciado com sucesso ! \n");
			}
			break;
			
		case WM_CLOSE: case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}

	return TRUE;
}

int main(void)
{
	printf("|------------------------------------------------|\n");
	printf("Todos os direitos reservados - Secrets of Destiny \n");
	printf("|------------------------------------------------|\n\n");

	createGUI();
}