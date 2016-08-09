//---
// Secrets Of Destiny TEAM
//---

#include "main.h"

#include "..\..\Source\Common\st_Base.h"
#include "..\..\Source\TMSrv\ItemEffect.h"

int jmp_addr;         
INT32 ColorDesc = 0xFFFFFFFF;

__inline void AddLine()
{
	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP - 010h]
		MOV ECX,DWORD PTR SS:[EBP - 018h]
		MOV DWORD PTR DS:[EAX + 027680h],ECX

		PUSH 0
		LEA ECX,DWORD PTR SS:[EBP - 0A8h]
		PUSH ECX
		MOV EDX,DWORD PTR SS:[EBP - 028h]
		MOV EAX,DWORD PTR SS:[EBP - 010h]
		MOV ECX,DWORD PTR DS:[EAX + EDX * 04h + 0278C0h]
		MOV EDX,DWORD PTR SS:[EBP - 028h]
		MOV EAX,DWORD PTR SS:[EBP - 010h]
		MOV EDX,DWORD PTR DS:[EAX + EDX * 04h + 0278C0h]
		MOV EAX,DWORD PTR DS:[EDX]
		CALL DWORD PTR DS:[EAX + 080h]

		PUSH ColorDesc

		MOV ECX,DWORD PTR SS:[EBP - 028h]
		MOV EDX,DWORD PTR SS:[EBP - 010h]
		MOV ECX,DWORD PTR DS:[EDX + ECX * 04h + 0278C0h]
		MOV EAX,DWORD PTR SS:[EBP - 028h]
		MOV EDX,DWORD PTR SS:[EBP - 010h]
		MOV EAX,DWORD PTR DS:[EDX + EAX * 04h + 0278C0h]
		MOV EDX,DWORD PTR DS:[EAX]
		CALL DWORD PTR DS:[EDX + 084h]

		MOV EAX,DWORD PTR SS:[EBP - 028h]
		ADD EAX,01h
		MOV DWORD PTR SS:[EBP - 028h],EAX
	}
}

__declspec(naked) void DescricaoItem()
{
	static char *szName;
	static st_Item *item;
	__asm
	{
		MOV ECX,DWORD PTR SS:[EBP - 08h]
		MOV EDX,DWORD PTR DS:[ECX + 0670h]

		MOVSX EAX,WORD PTR DS:[EDX]

		CMP EAX, 0CFCh
		JE lbl_continuePesa

		CMP EAX, 0x1FC
		JE lbl_PutName

		CMP EAX, 0x1FD
		JE lbl_PutName

		CMP EAX, 0x20E
		JE lbl_PutName

		CMP EAX, 0x20F
		JE lbl_PutName

		CMP EAX, 0x210
		JE lbl_PutName
		
		JMP lbl_nextCMP

	lbl_PutName:
		LEA EDX, DWORD PTR SS:[EBP - 0A8h]
		MOV szName, EDX
			
		MOV ECX,DWORD PTR SS:[EBP - 08h]
		MOV EDX,DWORD PTR DS:[ECX + 0670h]

		MOV DWORD PTR DS:[item],EDX
	}

	ColorDesc = 0xFFFFFFFF;

	if(item->Index == 508 || item->Index == 509 || (item->Index >= 526 && item->Index <= 528))
	{
		sprintf(szName, "Nome: %s", Guild.GuildName);
		AddLine();
		 
		sprintf(szName, "Lider: %s", Guild.LiderName);
		AddLine();

		sprintf(szName, "Numero de membros: %d", Guild.Members);
		AddLine();

		if(item->Index != 508)
		{
			sprintf(szName, "GuildFame: %d", Guild.FAME);
			AddLine();
		}	
	}
	/*else if (item->Index >= 3021 && item->Index <= 3026)
	{
		for (int i = 0; i < 3; i++)
		{
			if (item->Effect[i].Index == EF_SANC || (item->Effect[i].Index >= 116 && item->Effect[i].Index <= 125))
			{
				int sanc = item->Effect[i].Value;

				/*if (sanc >= 230)
					sanc = 10 + ((sanc - 230) / 4);
					

				if (item->Effect[i].Value > 9)
				{
					if (item->Effect[i].Value >= 230 && item->Effect[i].Value <= 233)
						sanc = 10;
					else if (item->Effect[i].Value >= 234 && item->Effect[i].Value <= 237)
						sanc = 11;
					else if (item->Effect[i].Value >= 238 && item->Effect[i].Value <= 241)
						sanc = 12;
					else if (item->Effect[i].Value >= 242 && item->Effect[i].Value <= 245)
						sanc = 13;
					else if (item->Effect[i].Value >= 246 && item->Effect[i].Value <= 249)
						sanc = 14;
					else if (item->Effect[i].Value >= 250 && item->Effect[i].Value <= 253)
						sanc = 15;
					else
						sanc = 0;
				}

				sprintf(szName, "Refinação: %d", sanc);
				AddLine();

				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (item->Effect[i].Index == EF_GETHP || item->Effect[i].Index == EF_GETMP)
			{
				int sanc = 0;

			    INT16 value = item->Effect[i].Value;

				for (int e = 0; e < 3; e++)
					if (item->Effect[e].Index == EF_SANC)
						sanc = item->Effect[e].Value;

				if (sanc <= 0)
					continue;

				if (sanc >= 230)
					sanc = 10 + ((sanc - 230) / 4);

				if (sanc <= 10)
					value = (((sanc + 10) * value) / 10);
				else
				{
					static INT16 Power[] = {
						220, 250, 280, 320, 370
					};

					int val = Power[sanc - 11];
					value = (((value * 10) * val) / 1000);
				}

				sprintf(szName, "Índice de extração de %s: %.2f (%.2f)%%", item->Effect[i].Index == EF_GETHP ? "HP" : "MP", (float)(item->Effect[i].Value / 100.0), (float)(value / 100.0));

				ColorDesc = 0xFF1E90FF;

				AddLine();
			}
		}
	}*/

	__asm
	{
lbl_nextCMP:
		MOV EAX,0041C948h
		JMP EAX

lbl_continuePesa:
		MOV EAX,0041C9D1h
		JMP EAX
	}
}

void __declspec(naked) DecryptPacket()
{
	__asm
	{
		PUSH DWORD PTR SS: [EBP-18h]
		CALL PacketControl
		ADD ESP, 04h
		MOV EAX, 00426EBFh
		JMP EAX
	}
}

void __declspec(naked) Implement_New_Set() //implementa os novos trajes no cliente 754
{
	static DWORD dwRet = 0x50027E;

	__asm
	{
		MOVSX ECX, WORD PTR DS:[EAX + 0x784]
		CMP ECX, 0x1037
		JNE lbl1

		MOV WORD PTR SS:[EBP - 0x14], 0xFFFF

lbl1:
		CMP ECX, 0x1038
		JNE lbl2

		MOV WORD PTR SS:[EBP - 0x14], 0x1

lbl2:
		CMP ECX, 0x1039
		JNE lbl3

		MOV WORD PTR SS:[EBP - 0x14], 0x2
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x166], 0x1D
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x168], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x16A], 0x1E
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x16E], 0x1E
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x172], 0x1E
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x176], 0x1E
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x17A], 0x1E
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x170], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x170], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x174], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x178], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x17C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl3:
		CMP ECX, 0x103A
		JNE lbl4

		MOV WORD PTR SS:[EBP - 0x14], 0x3
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x166], 0xC
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x168], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x16A], 0x24
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x16E], 0x24
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x172], 0x24
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x176], 0x24
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x17A], 0x24
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x170], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x170], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x174], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x178], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x17C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl4:
		CMP ECX, 0x103B
		JNE lbl5

		MOV WORD PTR SS:[EBP - 0x14], 0x4
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x166], 0x24
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x168], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x16A], 0x24
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x16E], 0x24
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x172], 0x24
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x176], 0x24
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x17A], 0x24
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x170], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x170], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x174], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x178], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x17C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl5:
		CMP ECX, 0x103C
		JNE lbl6

		MOV WORD PTR SS:[EBP - 0x14], 0x5
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x166], 0x10
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x168], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x16A], 0x10
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x16E], 0x10
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x172], 0x10
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x176], 0x10
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x17A], 0x10
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x170], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x170], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x174], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x178], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x17C], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x16C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl6:
		CMP ECX, 0x103D
		JNE lbl7

		MOV WORD PTR SS:[EBP - 0x14], 0x7
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x166], 0x60
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x168], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x16A], 0x60
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x16E], 0x60
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x172], 0x60
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x176], 0x60
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x17A], 0x60
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x170], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x170], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x174], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x178], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x17C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl7:
		CMP ECX, 0x103E
		JE lbl8

		MOV jmp_addr, 0x50027E
		JMP jmp_addr

lbl8:
		MOV WORD PTR SS:[EBP - 0x14], 0x6
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x166], 0x5E
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x168], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x16A], 0x5E
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x16E], 0x5E
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x172], 0x5E
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x176], 0x5E
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x17A], 0x5E
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x170], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x170], 0
		MOV EAX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EAX + 0x174], 0
		MOV ECX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[ECX + 0x178], 0
		MOV EDX, DWORD PTR SS:[EBP - 0x354]
		MOV WORD PTR DS:[EDX + 0x17C], 0

		MOV jmp_addr, 0x50027E
		JMP jmp_addr
	}
}

__declspec(naked) void ChangeCliver_01()
{
	static const INT32 szContinue = 0x004AE003;
	__asm{
		MOV DWORD PTR SS : [EBP - 0xA00], CLIVER
		JMP szContinue
	}
}

__declspec(naked) void ChangeCliver_02()
{
	static const INT32 szContinue = 0x00480863;
	__asm{
		MOV DWORD PTR SS : [EBP - 0x2CC], CLIVER
		JMP szContinue
	}
}

void LoadHooks()
{
	JGE_NEAR(0x00426DC9, DecryptPacket);

	JMP_NEAR(0x0041C931, DescricaoItem);
	JMP_NEAR(0x004ADFF9, ChangeCliver_01, 5);
	JMP_NEAR(0x00480859, ChangeCliver_02, 5);
	
	//*(INT8*)(0x00480859 + 7) = CLIVER;
	//*(INT8*)(0x00480859 + 6) = 800;
	//*(INT8*)(0x004ADFF9 + 7) = CLIVER;

	//altera as checagens dos ids dos trajes
	/*(DWORD*)0x4FFE12 = 4150;
	*(DWORD*)0x4FFE2A = 4200;
	JMP_NEAR(0x4FFF2A, Implement_New_Set, 2);*/
}