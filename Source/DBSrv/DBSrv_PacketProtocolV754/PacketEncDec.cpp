#include "PacketEncDec.h"

__declspec(naked) void NKD_AddMessage_EncKey_1()
{
	static int jmp1 = 0x417830;
	__asm
	{
		SAR ECX, 0x3
		SUB EAX, ECX
		MOV EDX,DWORD PTR SS:[EBP - 0x4]

		JMP jmp1
	}
}

__declspec(naked) void NKD_ReadMessage_DecKey_1()
{
	static int jmp1 = 0x4171FC;
	__asm
	{
		SAR EDX, 0x3
		ADD ECX, EDX
		MOV EAX, DWORD PTR SS:[EBP - 0x28]
		
		JMP jmp1
	}
}

__declspec(naked) void NKD_ReadMessage_DecKey_2()
{
	static int jmp1 = 0x41721F;
	__asm
	{
		SHL EAX, 0x2
		SUB EDX, EAX
		MOV ECX, DWORD PTR SS:[EBP - 0x28]

		JMP jmp1
	}
}