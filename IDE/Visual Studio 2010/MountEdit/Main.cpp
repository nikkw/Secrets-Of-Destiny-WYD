#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "../../../Source/Common/st_Base.h"

static char MountsNames[50][20] = 
{
	"",
	"Porco",
	"Javali",
	"Lobo",
	"Dragão_Menor",
	"Urso",
	"Dente_de_sabre",
	"S/sela_N",
	"Fantasma_N",
	"Leve_N",
	"Equipado_N",
	"Andaluz_N",
	"S/sela_B",
	"Fantasma_B",
	"Leve_B",
	"Equipado_B",
	"Andaluz_B",
	"Fenrir",
	"Dragão",
	"Fenrir_das_sombras",
	"Tigre_de_Fogo",
	"Dragão_Vermelho",
	"Unicornio",
	"Pegasus",
	"Unisus",
	"Grifo",
	"Hipogrifo",
	"Grifo_Sangrento",
	"Svaldfire",
	"Sleipnir",
	"Pantera_Negra"
	"","","","",
	"","","","",
	"","","","",
	"","","","",
	"","","",""
};	

st_TransBonus  TransBonus[5];
st_MountData   MountBuffer[50];
INT8 MountSelected, TransSelected;
Events Event;

bool ReadTransData()
{
	BYTE buffer[sizeof TransBonus];

	FILE* pFile = NULL;

	pFile = fopen("transData.bin", "rb");

	if(pFile == NULL)
	{
		MessageBox(NULL, "Arquivo transData.bin não encontrado.", "Error : fopen", MB_OK);
		
		return false;
	}
	
	fread(&buffer[0], 1, sizeof TransBonus, pFile);

	fclose(pFile);

	memcpy(&TransBonus[0], &buffer[0], sizeof TransBonus);

	return true;
}

bool ReadMountData()
{
	FILE *fs;
	BYTE buffer[1000];

	fs = fopen("mountData.bin", "rb");	

	if(fs == NULL)
	{
		MessageBox(NULL, "Arquivo mountData.bin não encontrado.", "Error : fopen", MB_OK);
		
		return false;
	}

	fread(&buffer[0], sizeof(BYTE), 50 * 20, fs);

	fclose(fs);
		
	memcpy(&MountBuffer[0], &buffer[0], (50 * sizeof(st_MountData)));

	return true;
}

bool WriteMountData()
{
	char szTMP[1024];
	FILE *pFile = NULL;

	sprintf_s(szTMP, "mountData.bin");

	fopen_s(&pFile, szTMP, "wb");

	if(pFile)
	{
		int mobSize = sizeof(st_MountData) * 50;

		fwrite((void*)&MountBuffer, 1, mobSize, pFile);

		fclose(pFile);		

		return true;
	}

	return false;
}

bool WriteTransData()
{
	char szTMP[1024];
	FILE *pFile = NULL;

	sprintf_s(szTMP, "transData.bin");

	fopen_s(&pFile, szTMP, "wb");

	if(pFile)
	{
		int mobSize = sizeof(st_TransBonus) * 5;

		fwrite((void*)&TransBonus, 1, mobSize, pFile);

		fclose(pFile);		

		return true;
	}

	return false;
}

bool WriteEventData()
{
	char szTMP[1024];
	FILE *pFile = NULL;

	sprintf_s(szTMP, "eventData.bin");

	fopen_s(&pFile, szTMP, "wb");

	if(pFile)
	{
		fwrite((void*)&Event, 1, sizeof Events, pFile);

		fclose(pFile);		

		return true;
	}

	return false;
}

void DoChangesOnMounts()
{
	memset(&MountBuffer, 0x0, sizeof(st_MountData));

	if(!ReadMountData())
	{
		printf("Erro na leitura das mounts.\n");

		return;
	}
	
	for(int i = 0; i < 50; i++)
	{
		printf("Mount: %s Atk Físico: %d Atk Mágico: %d Resis: %d VelMov: %d Evasao: %d\n", MountsNames[i],
		MountBuffer[i].AtaqFisico, MountBuffer[i].AtaqMagico, MountBuffer[i].Resistencia, 
		MountBuffer[i].VelocidadeMov, MountBuffer[i].Evasao);
	}

	MountSelected = -1;

	char Command[20];

	do
	{
		printf("Entre com a montaria desejada (1-50):");

		scanf("%d", &MountSelected);

		if(MountSelected > 0 && MountSelected <= 50)
			MountSelected--;
		else
			MountSelected = -1;
	}while(MountSelected < 0 || MountSelected > 49);

	// Mostra denovo para saber que é esta mesmo que deve ser editada
	printf("Montaria escolhida: %s Status da mesma:\n", MountsNames[MountSelected]);
	printf("Atk Fis: %d Atk Mg: %d Vel Mov: %d Resistencia: %d Evasao: %d\n", MountBuffer[MountSelected].AtaqFisico,
		MountBuffer[MountSelected].AtaqMagico, MountBuffer[MountSelected].VelocidadeMov, MountBuffer[MountSelected].Resistencia,
		MountBuffer[MountSelected].Evasao);

	bool saida = false;

	while(!saida)
	{
		printf("Digite o status que deseja editar, out para sair, h para ajuda:");

		scanf("%20s", Command);

		DWORD value = 0;

		if(!stricmp(Command, "out"))
			saida = true;
		else if(!stricmp(Command, "atkfis"))
		{
			printf("Digite o novo valor desejado:");

			scanf("%d", &value);

			MountBuffer[MountSelected].AtaqFisico = value;
	        
			printf("Novo valor: %d\n", MountBuffer[MountSelected].AtaqFisico);
		}
		else if(!stricmp(Command, "atkmag"))
		{
			printf("Digite o novo valor desejado:");

			scanf("%d", &value);

			MountBuffer[MountSelected].AtaqMagico = value;
	        
			printf("Novo valor: %d\n", MountBuffer[MountSelected].AtaqMagico);
		}
		else if(!stricmp(Command, "evasao"))
		{
			printf("Digite o novo valor desejado:");

			scanf("%d", &value);

			MountBuffer[MountSelected].Evasao = value;
	        
			printf("Novo valor: %d\n", MountBuffer[MountSelected].Evasao);
		}
		else if(!stricmp(Command, "resis"))
		{
			printf("Digite o novo valor desejado:");

			scanf("%d", &value);

			MountBuffer[MountSelected].Resistencia = value;
	        
			printf("Novo valor: %d\n", MountBuffer[MountSelected].Resistencia);
		}
		else if(!stricmp(Command, "velmov"))
		{
			printf("Digite o novo valor desejado:");

			scanf("%d", &value);

			MountBuffer[MountSelected].VelocidadeMov = value;
	        
			printf("Novo valor: %d\n", MountBuffer[MountSelected].VelocidadeMov);
		}
		else if(Command[0] == 'h')
		{
			printf("Comandos disponíveis:\n");
			printf("Resis: altere a resistência da mount.\n");
			printf("Atkfis: altere o ataque físico da mesma.\n");
			printf("Atkmag: altere o ataque mago da mesma.\n");
			printf("Evasao: altere a evasão dada pela montaria.\n");
			printf("velmov: altere o valor unknow(provavelmente a velocidade) da mount.\n");
		}
	}

	if(!WriteMountData())
		printf("Falha ao salvar as edições.\n");
}

void DoChangesOnTrans()
{
	if(!ReadTransData())
	{
		printf("Erro na leitura das transformações.\n");

		return;
	}

	for(int i = 0; i < 5; i++)
	{
		printf("Trans: %d MinAtk: %d MaxAtk: %d MinDef: %d MaxDef: %d MinHp: %d MaxHp: %d Unk24: %d Unk28: %d SpeedAtk: %d SpeedMove: %d Unk40: %d Unk44: %d Unk48: %d Unk52: %d Unk56: %d Unk60: %d Sanc: %d\n\n", i, 
			TransBonus[i].MinAttack, TransBonus[i].MaxAttack, TransBonus[i].MinDefense, TransBonus[i].MaxDefense, TransBonus[i].MinHp,
			TransBonus[i].MaxHp, TransBonus[i].Unknown_24, TransBonus[i].Unknown_28, TransBonus[i].SpeedAttack, TransBonus[i].SpeedMove,
			TransBonus[i].Unknown_40, TransBonus[i].Unknown_44, TransBonus[i].Unknown_48, TransBonus[i].Unknown_52, TransBonus[i].Unknown_56,
			TransBonus[i].Unknown_60, TransBonus[i].Sanc);
	}

	if(!WriteTransData())
		printf("Erro ao salvar as transformações.\n");
}

void PutItemData(st_Item *Item)
{
	printf("Digite o index do item:");

	scanf("%d", &Item->Index);

	printf("Digite o EF1 do item:");

	scanf("%d", &Item->EF1);

	printf("Digite o EFV1 do item:");

	scanf("%d", &Item->EFV1);

	printf("Digite o EF2 do item:");

	scanf("%d", &Item->EF2);

	printf("Digite o EFV2 do item:");

	scanf("%d", &Item->EFV2);

	printf("Digite o EF3 do item:");

	scanf("%d", &Item->EF3);

	printf("Digite o EFV3 do item:");

	scanf("%d", &Item->EFV3);
}

void DoChangesOnEvent()
{
	memset(&Event, 0x0, sizeof Events);

	INT16 selectedEvent = -1;

	printf("Bem vindo a edição de evento.\nAqui é possível editar o evento de trocas.\nEntre com a troca que deseja editar:");
	
	scanf("%d", &selectedEvent);

	if(selectedEvent < 0 || selectedEvent > 5)
	{
		printf("Valor inválido...\n");

		DoChangesOnEvent();

		return;
	}

	printf("Digite qual informação deseja editar(premios ou requestItem)(sair para terminar):");

	char command[25];

	scanf("%25s", &command);

	while(stricmp(command, "sair"))
	{
		INT16 EditCount = -1;

		if(!stricmp(command, "requestItem"))
		{
			printf("Digite qual posição deseja editar (5 posições possíveis, são os itens a serem entregues ao npc.):");

			scanf("%d", &EditCount);

			if(EditCount >= 0 && EditCount <= 4)
				PutItemData(&Event.Trade[selectedEvent].RequestItem[EditCount]);
			else
				printf("Valor inválido...\n");
		}
		else if(!stricmp(command, "premios"))
		{
			printf("Digite qual posição deseja editar (5 posições possíveis, são os itens a serem entregues pelo npc.):");

			scanf("%d", &EditCount);

			if(EditCount >= 0 && EditCount <= 4)
				PutItemData(&Event.Trade[selectedEvent].SendedItem[EditCount]);
			else
				printf("Valor inválido...\n");
		}

		printf("Digite qual informação deseja editar(premios ou requestItem)(sair para terminar):");

		scanf("%25s", &command);
	}

	for(int i = 0; i < 6; i++)
	{
		printf("Troca %d:\n", i);

		printf("Itens requisitados:\n");

		for(int e = 0; e < 5; e++)
			printf("Index: %d, EF1: %d EFV1: %d EF2: %d EFV2: %d EF3: %d EFV3: %d\n", Event.Trade[i].RequestItem[e].Index,
			Event.Trade[i].RequestItem[e].EF1, Event.Trade[i].RequestItem[e].EFV1, Event.Trade[i].RequestItem[e].EF2, 
			Event.Trade[i].RequestItem[e].EFV2, Event.Trade[i].RequestItem[e].EF3, Event.Trade[i].RequestItem[e].EFV3);

		printf("Possíveis prêmios:\n");

		for(int e = 0; e < 5; e++)
		    printf("Index: %d, EF1: %d EFV1: %d EF2: %d EFV2: %d EF3: %d EFV3: %d\n", Event.Trade[i].SendedItem[e].Index,
			Event.Trade[i].SendedItem[e].EF1,  Event.Trade[i].SendedItem[e].EFV1, Event.Trade[i].SendedItem[e].EF2, 
			Event.Trade[i].SendedItem[e].EFV2, Event.Trade[i].SendedItem[e].EF3,  Event.Trade[i].SendedItem[e].EFV3);
	}

	if(!WriteEventData())
		printf("Houve um erro ao salvar.");
}

void main()
{
	setlocale(LC_ALL, "Portuguese");

	SetConsoleTitle("Secrets of Destiny");

	printf("Editor de Files SOD.\n Com ele é possível editar informações de transformações e de eventos!\n Bom uso.\n");
	printf("Para editar os arquivos é necessário que eles estejam nesta mesma pasta.\n");

	while(1)
	{
		printf("Digite qual arquivo deseja editar, out para sair:");

		char cmd[20];

		scanf("%20s", cmd);

		if(!stricmp(cmd, "out"))
			break;
		else
		{
			/*if(!stricmp(cmd, "Mounts"))
				DoChangesOnMounts();
			else */
			if(!stricmp(cmd, "Trans"))
			    DoChangesOnTrans();
			else if(!stricmp(cmd, "Event"))
				DoChangesOnEvent();
			else if(!stricmp(cmd, "help"))
			{

			}
			else
				printf("Comando inválido.\n");
		}
	}
}