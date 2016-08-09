#include "PE_Patch.h"
int jmp_addr;

void PE_Patch()
{
	PATCH_SetEncDec();
	TranslateClassFiles();
	DoLimitofPlayers();
}

__declspec(naked) void NKD_DisableAccount_FixKey()
{
	static const char* mFIX = "!!%&#%s";
	__asm
	{
		PUSH mFIX
		RETN
	}
}

__declspec(naked) void NKD_MOV01()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x411144
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV02()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x411152
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV03()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41433A
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV04()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41440A
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV05()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x414B96
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV06()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x414BA4
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV07()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41A12B
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV08()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41A13F
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV09()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41C651
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV10()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41C665
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV11()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41E3C4
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MOV12()
{
	__asm
	{
		MOV ECX,MAX_PLAYER

		MOV jmp_addr, 0x41E3D8
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_CMP01()
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4111AD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP02()
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41BAEA
		RETN 4
	}
}

__declspec(naked) void NKD_CMP03()
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41BFE3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP04()
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x153C],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41C6AE
		RETN 4
	}
}

__declspec(naked) void NKD_IMUL01()
{
	__asm
	{
		IMUL EAX,EAX,MAX_PLAYER
		ADD EAX,DWORD PTR SS:[EBP + 0x0C]

		MOV jmp_addr, 0x414A96
		JMP jmp_addr
	}
}

void DoLimitofPlayers()
{
	JMP_NEAR(0x41113F, NKD_MOV01);
	JMP_NEAR(0x41114D, NKD_MOV02);
	JMP_NEAR(0x414335, NKD_MOV03);
	JMP_NEAR(0x414405, NKD_MOV04);
	JMP_NEAR(0x414B91, NKD_MOV05);
	JMP_NEAR(0x414B9F, NKD_MOV06);
	JMP_NEAR(0x41A126, NKD_MOV07);
	JMP_NEAR(0x41A13A, NKD_MOV08);
	JMP_NEAR(0x41C64C, NKD_MOV09);
	JMP_NEAR(0x41C660, NKD_MOV10);
	JMP_NEAR(0x41E3BF, NKD_MOV11);
	JMP_NEAR(0x41E3D3, NKD_MOV12);
	JMP_NEAR(0x414A90, NKD_IMUL01, 1);

	// CMP
	CALL_NEAR(0x411198, NKD_CMP01);
	CALL_NEAR(0x41BA8D, NKD_CMP02);
	CALL_NEAR(0x41BF81, NKD_CMP03);
	CALL_NEAR(0x41C688, NKD_CMP04, 4);
}


void TranslateClassFiles()
{
	// Def npc's files
	strcpy((char*)0x457328, "npc/TransKnight");
	strcpy((char*)0x457304, "npc/Foema");
	strcpy((char*)0x4572DC, "npc/BeastMaster");
	strcpy((char*)0x4572BC, "npc/Huntress");
}

void PATCH_SetEncDec()
{
	// Set Cli-Keys hash table
	memcpy((BYTE*)0x45E984, &keys[0], 512);

	// Set Enc Keys
	CALL_NEAR(0x417643, NKD_AddMessage);
	JMP_NEAR(0x417829, NKD_AddMessage_EncKey_1, 2);

	*(BYTE*)0x41789E = 0x5;
	*(BYTE*)0x4177F2 = 0x51;
	*(BYTE*)0x417865 = 0x91;

	// Set Dec Keys
	JGE_NEAR(0x41716F, NKD_ReadMessage);
	*(WORD*)0x4171D0 = 0xE1D1;
	*(BYTE*)0x4171D2 = 0x90;
	JMP_NEAR(0x4171F5, NKD_ReadMessage_DecKey_1, 2);
	JMP_NEAR(0x417218, NKD_ReadMessage_DecKey_2, 2);
	*(BYTE*)0x41723E = 0x5;

	// Desativa leitura das guilds
	*(INT8*)0x0040DFB0 = 0xC3; 
	*(INT8*)0x0040E350 = 0xC3; 

	// Tira a verificação para nicks
	*(BYTE*)0x00414706 = 0xEB;
	JMP_NEAR(0x004146BF, (void*)0x004146C4);

	// Cria conta ao logar
	JMP_NEAR(0x00411ED5, &NKD_AddAccount_CreateAccount);
}

BYTE __stdcall CreateAccount(p20D *p, UINT32 addr)
{
	FILE*pFile = NULL;

	stAccount acc;
	memset(&acc, 0, sizeof acc);

	strncpy(acc.Username, p->Login, 16);
	strncpy(acc.Password, p->Password, 16);

	char firstKey[4];
	char szTMP[256];
	BASE_GetFirstKey(p->Login, firstKey);

	sprintf(szTMP, "account\\%s\\%s", firstKey, p->Login);

	pFile = fopen(szTMP, "wb+");
	if(pFile)
	{
		fwrite((void*)&acc, sizeof stAccount, 1, pFile);

		fclose(pFile);
		return 1;
	}
	return 0;
}

__declspec(naked) void NKD_AddAccount_CreateAccount()
{
	_asm
	{
		PUSH DWORD PTR SS:[EBP - 04h]
		PUSH DWORD PTR SS:[EBP - 01068h]
		CALL CreateAccount

		TEST EAX,EAX
		JNZ lbl_accountSucess

		PUSH 0421h

		MOV EDX,00411EDAh
		JMP EDX

		lbl_accountSucess:
		MOV EDX,00411E65h
		JMP EDX
	}
} 

__declspec(naked) void NKD_AddMessage()
{
	__asm
	{
		PUSH [EBP + 0xC]
		PUSH [EBP + 0x8]
		CALL HKD_AddMessage
		ADD ESP, 0x8

		PUSH EAX

		MOV EAX, 0x41F8C0
		CALL EAX

		POP EAX

		MOV DWORD PTR SS:[EBP + 0x8], EAX
		MOV DWORD PTR SS:[EBP - 0x108], EAX

		RETN
	}
}

__declspec(naked) void NKD_ReadMessage()
{
	__asm
	{

		PUSH EAX
		PUSH [EBP - 0x28]
		CALL HKD_ReadMessage
		ADD ESP, 0x8
		
		MOV DWORD PTR SS:[EBP - 0x28], EAX

		MOV jmp_addr, 0x417264
		JMP jmp_addr
	}
}