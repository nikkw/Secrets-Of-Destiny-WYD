#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "../../../Source/Common/st_Base.h"

// Este será o visualizador remoto
// Ainda tenho de desenvolver toda a parte do socket e dos botões
// Esse demora mais a sair, preguiça domina o ser humano

#define StartThread(thread) (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, 0))
#define NOT_SELECTED -1

static const char ConfigsName[10][10] = {
						{"Full STR"},
						{"Full INT"},
						{"Full DEX"},
						{"Full CON"},
						{"Str / Con"},
						{"Int / Con"},
						{"Dex / Con"},
						{"Con / Str"},
						{"Con / Int"},
						{"Con / Dex"}
					};

void WINAPI MainThread()
{
	while(1)
	{
		time_t rawnow = time(NULL);
		struct tm *now = localtime(&rawnow);

		char szMsg[160];

		sprintf(szMsg, "Secrets of Destiny - Visualizador de Dados [%02d:%02d:%02d]", now->tm_hour, now->tm_min, now->tm_sec);

		SetConsoleTitle(szMsg);

		if(IsDebuggerPresent())
			ExitProcess(1);

		Sleep(1000);
	}
}

struct Infos
{
	STRUCT_ACCOUNTFILE AccountInfos;

	wdBase NewInfos;

	INT8 PersoSelected;
};

Infos User;

bool LoadOInfo(char *szLogin)
{
	if(!szLogin[0]) // Caso não tenha digitado o login
		return false;
	else if(strlen(szLogin) < 4) // Caso o id seja com 3 caracteres ou menos
		return false;
	else
	{
		// Zera os dados anteriores da conta, por segurança
		memset(&User.AccountInfos, 0x0, sizeof STRUCT_ACCOUNTFILE);

		char szTMP[1024];
		FILE *pFile = NULL;

		// Diretório padrão dos dados da account
		bool verify = true;

		for(int i = 0; i < strlen(Etc); i++)
		{
			if(Etc[i] == szLogin[0])
			{
			    sprintf_s(szTMP, "C:/WydServer/DBSRV/run/account/etc/%s", szLogin);

				verify = false;

				break;
			}
		}

		if(verify)
			sprintf_s(szTMP, "C:/WydServer/DBSRV/run/account/%c/%s", szLogin[0], szLogin);

		fopen_s(&pFile, szTMP, "rb");

		if(pFile) // Conseguiu abrir e fazer o load dos dados da nova acc
		{
			fread(&User.AccountInfos, 1, sizeof STRUCT_ACCOUNTFILE, pFile);

			fclose(pFile);

			return true;
		}
	}

	return false;
}

bool LoadNInfo(char *szLogin)
{
	if(!szLogin[0]) // Caso não tenha digitado o login
		return false;
	else if(strlen(szLogin) < 4) // Caso o id seja com 3 caracteres ou menos
		return false;
	else
	{
		// Zera os dados anteriores da conta, por segurança
		memset(&User.NewInfos, 0x0, sizeof wdBase - sizeof User.NewInfos.Ingame);

		char szTMP[1024];
		FILE *pFile = NULL;

		// Diretório padrão dos dados da account
		sprintf_s(szTMP, "C:/WydServer/TMSRV/run/Plugin/TMSRV_SOD/Data/%s.bin", szLogin);

		fopen_s(&pFile, szTMP, "rb");

		if(pFile) // Conseguiu abrir e fazer o load dos dados da nova acc
		{
			int mobSize = sizeof wdBase - (sizeof User.NewInfos.Ingame);
		
			fread(&User, 1, mobSize, pFile);

			fclose(pFile);

			return true;
		}
	}

	return false;
}

bool CheckCommand(char *Command)
{
    if(!stricmp(Command, "out"))
		return true;
	else if(!stricmp(Command, "cargoinfo"))
	{
		for(int i = 0; i < 128; i++)
		{
			printf("Slot %d: %d %d %d %d %d %d %d\n", i, User.AccountInfos.Cargo[i].Index, User.AccountInfos.Cargo[i].EF1, User.AccountInfos.Cargo[i].EFV1,
				User.AccountInfos.Cargo[i].EF2, User.AccountInfos.Cargo[i].EFV2, User.AccountInfos.Cargo[i].EF3, User.AccountInfos.Cargo[i].EFV3);
		}
	}
	else if(Command[0] == 'h') 
	{
		// Tela de ajuda
		// Exibe os comandos disponíveis no executavel
		printf("Lista de comandos disponíveis:\n Cargoinfo: Visualize os itens do cargo separadamente.\n");
		printf("Após definir qual personagem deseja olhar, os seguintes comandos são liberados:\n");
		printf("NT: Visualiza quantas entradas para o pesa o personagem tem.\n");
		printf("RVRP: Visualiza quantos pontos do antigo sistema RVR o usuário tem.\n");
		printf("RespMortal: Mortal referente a este personagem(somente para archs+).\n");
		printf("Fame: Visualiza quanto de fame o personagem possui.\n");
		printf("ExpBonus: Visualiza quantos por cento de bonus na exp o usuario possui (referente ao set, bau de exp, fadas, entre outros).\n"); 
	    printf("Exp: Visualiza o total de exp do personagem.\n");
		printf("Gold: Visualize a quantidade de gold no personagem.\n");
		printf("Equips: Veja todos os equips em sequencia (fora a face).\n");
		printf("Face: Visualize as infos da face.\n");
		printf("Build: Veja a build do personagem (referente ao bStatus, sem itens e buffs).\n");
		printf("Inventory: Lista todos os itens do inventário.\n");
		printf("nInventory: Lista todos os itens do segundo inventário (caso possua).\n");
	}
	else
	{
		if(User.PersoSelected == NOT_SELECTED)
		{
			INT8 perso = -1;

			do
			{
				printf("Entre com o personagem desejado(1-4, posição e não o nick!!!):");

				scanf("%d", &perso);

				if(perso >= 1 && perso <= 4)
				{
					// Decrementa o valor para acessar a posição correta da array e termina o loop
					perso--;
					break;
				}
				else // Seta com um valor padrão para a continuação do loop
					perso = -1;
			}while(perso < 1 || perso > 4);

			User.PersoSelected = perso;
		}
		else
		{
			if(!stricmp(Command, "NT"))
				printf("NTs: %d\n", User.NewInfos.Chars[User.PersoSelected].NTs);
			else if(!stricmp(Command, "RVRP"))
				printf("RvRPoints: %d\n", User.NewInfos.Chars[User.PersoSelected].RvRPoints);
			else if(!stricmp(Command, "Soul"))
			{
				if(User.NewInfos.Chars[User.PersoSelected].SoulInfo < 10)
					printf("SoulInfo: %s\n", ConfigsName[User.NewInfos.Chars[User.PersoSelected].SoulInfo]);
			}
			else if(!stricmp(Command, "RespMortal"))
				printf("RespectiveMortal: %d\n", User.NewInfos.Chars[User.PersoSelected].RespectiveMortal);
			else if(!stricmp(Command, "Fame"))
				printf("Fame: %d\n", User.NewInfos.Chars[User.PersoSelected].Fame);
			else if(!stricmp(Command, "ExpBonus"))
				printf("ExpBonus: %d\n", User.NewInfos.Chars[User.PersoSelected].ExpBonus);
			else if(!stricmp(Command, "Exp"))
				printf("ExpAtual: %d\n", User.AccountInfos.Char[User.PersoSelected].Exp);
			else if(!stricmp(Command, "gold"))
				printf("Gold: %d\n", User.AccountInfos.Char[User.PersoSelected].Gold);
			else if(!stricmp(Command, "equips"))
			{
				for(int i = 1; i < 16; i++)
				{
					printf("Slot %d: %d %d %d %d %d %d %d\n", i, User.AccountInfos.Char[User.PersoSelected].Equip[i].Index,
					User.AccountInfos.Char[User.PersoSelected].Equip[i].EF1, User.AccountInfos.Char[User.PersoSelected].Equip[i].EFV1,
					User.AccountInfos.Char[User.PersoSelected].Equip[i].EF2, User.AccountInfos.Char[User.PersoSelected].Equip[i].EFV2,
					User.AccountInfos.Char[User.PersoSelected].Equip[i].EF3, User.AccountInfos.Char[User.PersoSelected].Equip[i].EFV3);
				}
			}
			else if(!stricmp(Command, "face"))
				printf("Face: %d %d %d %d %d %d %d\n", User.AccountInfos.Char[User.PersoSelected].Equip[0].Index, User.AccountInfos.Char[User.PersoSelected].Equip[0].EF1,
				User.AccountInfos.Char[User.PersoSelected].Equip[0].EFV1, User.AccountInfos.Char[User.PersoSelected].Equip[0].EF2,
				User.AccountInfos.Char[User.PersoSelected].Equip[0].EFV2, User.AccountInfos.Char[User.PersoSelected].Equip[0].EF3,
				User.AccountInfos.Char[User.PersoSelected].Equip[0].EFV3);
			else if(stricmp(Command, "build"))
				printf("Str: %d Dex: %d Int: %d Con: %d", User.AccountInfos.Char[User.PersoSelected].bStatus.STR,
				User.AccountInfos.Char[User.PersoSelected].bStatus.DEX, User.AccountInfos.Char[User.PersoSelected].bStatus.INT,
				User.AccountInfos.Char[User.PersoSelected].bStatus.CON);
			else if(!stricmp(Command, "Inventory"))
			{
				for(int i = 0; i < 63; i++)
				{
				    printf("Slot %d: %d %d %d %d %d %d %d\n", i, User.AccountInfos.Char[User.PersoSelected].Inventory[i].Index,
					User.AccountInfos.Char[User.PersoSelected].Inventory[i].EF1, User.AccountInfos.Char[User.PersoSelected].Inventory[i].EFV1,
					User.AccountInfos.Char[User.PersoSelected].Inventory[i].EF2, User.AccountInfos.Char[User.PersoSelected].Inventory[i].EFV2,
					User.AccountInfos.Char[User.PersoSelected].Inventory[i].EF3, User.AccountInfos.Char[User.PersoSelected].Inventory[i].EFV3);
				}
			}
			else if(!stricmp(Command, "nInventory"))
			{
				if(User.NewInfos.Chars[User.PersoSelected].nInvent.hasBuyed)
				{
					for(int i = 0; i < 63; i++)
					{
						printf("Slot %d: %d %d %d %d %d %d %d\n", i, User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].Index,
						User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EF1, User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EFV1,
						User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EF2, User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EFV2,
						User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EF3, User.NewInfos.Chars[User.PersoSelected].nInvent.sInv1[i].EFV3);
					}
				}
				else
					printf("Usuário não possui segundo inventário.\n");
			}
			else
				printf("Digite um comando válido.\n ");
		}
	}
	
	// Oi
	return false;
}

void main()
{
	// Faz os acentos aparecerem
	setlocale(LC_ALL, "Portuguese");

	memset(&User, 0x0, sizeof Infos);

	StartThread(MainThread);

	system("cls");

	printf("Ferramenta para visualização de dados de account SOD.\n");
	printf("Só serão exibidos dados referentes ao ultimo Save da account.\n");
	printf("Lembre-se: as contas são salvas de 12 em 12 segundos.\n");
	printf("Para sair digite out.\n");

	while(1)
	{
		char szLogin[16];

		printf("Entre com o id desejado, digite out para sair:");
		scanf("%16s", szLogin);

		if(!stricmp(szLogin, "out"))
			break;
		else if(!LoadNInfo(szLogin) || !LoadOInfo(szLogin))
			printf("Erro ao fazer o load da conta.\n");
		else
		{
			printf("Senha: %s\n", User.AccountInfos.AccountPass);
			printf("Senha Numérica: %s\n", User.NewInfos.Numerica);
			printf("Cash: %d\n", User.NewInfos.Cash);
			printf("Gold do Baú: %d\n", User.AccountInfos.Gold);
			//printf("Personagens: %s %s %s %s\n", User.AccountInfos.Char[0].Name, User.AccountInfos.Char[1].Name, User.AccountInfos.Char[2].Name, User.AccountInfos.Char[3].Name);
		    
			User.PersoSelected = NOT_SELECTED;

			bool saida = false;

			while(!saida)
			{
			    char Command[20];
			    printf("Digite a informação desejada, ou out para sair:\n");

			    scanf("%20s", Command);

			    saida = CheckCommand(Command);
			}
		}
	}
}