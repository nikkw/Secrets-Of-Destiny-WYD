#include "DLLMain.h"

int jmp_padr;

__declspec(naked) void NKD_CMP001()//0x410ED3
{
	__asm
	{
		CMP DWORD PTR DS:[EDX + 0x318],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x410EED
		RETN 4
	}
}

__declspec(naked) void NKD_CMP002()//0x410F3B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x10],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x410F52
		RETN 4
	}
}

__declspec(naked) void NKD_CMP003()//0x4114C6
{
	__asm
	{
		CMP DWORD PTR DS:[EDX + 0x318],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4114D9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP004()//0x4114EB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4114FB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP005()//0x41192E
{
	__asm
	{
		CMP ECX,MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x411951
		RETN 4
	}
}

__declspec(naked) void NKD_CMP006()//0x411955
{
	__asm
	{
		CMP ECX,MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x411974
		RETN 4
	}
}

__declspec(naked) void NKD_CMP007()//0x411c25
{
	__asm
	{
		CMP EDX,MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x411C9E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP008()//0x411D74
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x411D8A
		RETN 4
	}
}

__declspec(naked) void NKD_PUSH01()//0x4121BC
{
	__asm
	{
		PUSH MAX_PLAYER
		MOV ECX,DWORD PTR SS:[EBP - 0x4]

		MOV jmp_padr, 0x4121C1
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP009()//0x4123E3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4123F9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP010()//0x4123F9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x412488
		RETN 4
	}
}

__declspec(naked) void NKD_CMP011()//0x00412488
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x412509
		RETN 4
	}
}

__declspec(naked) void NKD_CMP012()//0x412520
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x412543
		RETN 4
	}
}

__declspec(naked) void NKD_CMP013()//0x413CF1
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x30],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x413D14
		RETN 4
	}
}

__declspec(naked) void NKD_CMP014()//0x41ABCE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41ABD8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP015()//0x41C550
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41C5F9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP016()//0x41C69D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41C6CC
		RETN 4
	}
}

__declspec(naked) void NKD_CMP017()//0x41CAE0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41CB6D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP018()//0x41CC11
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41CC40
		RETN 4
	}
}

__declspec(naked) void NKD_CMP019()//0x41D2EE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41D8D8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP020()//0x41D94B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41D985
		RETN 4
	}
}

__declspec(naked) void NKD_CMP021()//0x41D98F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41D9AE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP022()//0x41D9AE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41D9CD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP023()//0x41DAFA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41DB19
		RETN 4
	}
}

__declspec(naked) void NKD_CMP024()//0x41DE22
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41DE80
		RETN 4
	}
}

__declspec(naked) void NKD_CMP025()//0x41DE86
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41DEB9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP026()//0x41E4BE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E4C8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP027()//0x41E52E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E538
		RETN 4
	}
}

__declspec(naked) void NKD_CMP028()//0x41E5BE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E5C6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP029()//0x41E63E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E646
		RETN 4
	}
}

__declspec(naked) void NKD_CMP030()//0x41E7CE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E7D6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP031()//0x41E84E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41E856
		RETN 4
	}
}

__declspec(naked) void NKD_CMP032()//0x41E8DA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x41E92F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP033()//0x41EA90
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41EA9B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP034()//0x41FBAB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x41FBB6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP035()//0x42094E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x420959
		RETN 4
	}
}

__declspec(naked) void NKD_CMP036()//0x4209E2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4209ED
		RETN 4
	}
}

__declspec(naked) void NKD_CMP037()//0x420E53
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x420E74
		RETN 4
	}
}

__declspec(naked) void NKD_CMP038()//0x420EC3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x420ECE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP039()//0x42117A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x421185
		RETN 4
	}
}

__declspec(naked) void NKD_CMP040()//0x421DAE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x421DB9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP041()//0x42215F
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4221B5
		RETN 4
	}
}

__declspec(naked) void NKD_CMP042()//0x4221BB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4221D6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP043()//0x422955
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x58],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x422960
		RETN 4
	}
}

__declspec(naked) void NKD_CMP044()//0x42554C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x42557E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP045()//0x4255C2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4255D9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP046()//0x42569E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4256FC
		RETN 4
	}
}

__declspec(naked) void NKD_CMP047()//0x425ACB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x425AE2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP048()//0x425B5A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x425B7D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP049()//0x425BEC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x425C06
		RETN 4
	}
}

__declspec(naked) void NKD_CMP050()//0x425F3C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x425F54
		RETN 4
	}
}

__declspec(naked) void NKD_CMP051()//0x425FC8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x42602E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP052()//0x4262EF
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x426371
		RETN 4
	}
}

__declspec(naked) void NKD_CMP053()//0x426383
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x426476
		RETN 4
	}
}

__declspec(naked) void NKD_MOV01()//0x426390
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x368],MAX_PLAYER
		JMP Pula

		RETN

Pula:
		PUSH 0X4263AB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP054()//0x4265B0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4265E3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP055()//0x426848
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x3A0],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x426853
		RETN 4
	}
}

__declspec(naked) void NKD_CMP056()//0x426A09
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x426A2E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP057()//0x426B80
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x426BA0
		RETN 4
	}
}

__declspec(naked) void NKD_CMP058()//0x426C59
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x426C82
		RETN 4
	}
}

__declspec(naked) void NKD_CMP059()//0x426E2A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x426E53
		RETN 4
	}
}

__declspec(naked) void NKD_CMP060()//0x426FF8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x45C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x42704D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP061()//0x42711B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x468],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x427170
		RETN 4
	}
}

__declspec(naked) void NKD_CMP062()//0x42729B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4272C3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP063()//0x4273F6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x427417
		RETN 4
	}
}

__declspec(naked) void NKD_CMP064()//0x427523
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x42753F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP065()//0x42754B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4275CF
		RETN 4
	}
}

__declspec(naked) void NKD_CMP066()//0x42758D
{
	__asm
	{
		CMP DWORD PTR DS:[EDX + 0x15C6DA4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4275CF
		RETN 4
	}
}

__declspec(naked) void NKD_CMP067()//0x4275CF
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x484],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x427941
		RETN 4
	}
}

__declspec(naked) void NKD_CMP068()//0x427951
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x42798D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP069()//0x427C05
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x427C20
		RETN 4
	}
}

__declspec(naked) void NKD_CMP070()//0x427C2D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x427CBE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP071()//0x427CED
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x427D7E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP072()//0x427F3D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x427F7F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP073()//0x427F7F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2CC],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x427FAF
		RETN 4
	}
}

__declspec(naked) void NKD_CMP074()//0x4280C2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x564],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x4280CD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP075()//0x4281D0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x568],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x4281DB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP076()//0x4289D8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x81C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x428A6F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP077()//0x428B96
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x830],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x428BAB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP078()//0x42A74C
{
	__asm
	{
		CMP EDX,MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x42A760
		RETN 4
	}
}

__declspec(naked) void NKD_CMP079()//0x42BBEF
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xCAC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x42BC0E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP080()//0x43057B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1174],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43058F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP081()//0x431022
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1238],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43103C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP082()//0x4316AD
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x129C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x431753
		RETN 4
	}
}

__declspec(naked) void NKD_CMP083()//0x431779
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x12A0],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x431816
		RETN 4
	}
}

__declspec(naked) void NKD_CMP084()//0x4318F5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x12BC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x431903
		RETN 4
	}
}

__declspec(naked) void NKD_CMP085()//0x431AF3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x12D0],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x431B01
		RETN 4
	}
}

__declspec(naked) void NKD_CMP086()//0x43246B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1514],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4324C3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP087()//0x43369B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x19A8],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x4336CB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP088()//0x4359C8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1CB4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x435A6B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP089()//0x435AD9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1CB8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x435C0C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP090()//0x435B85
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1CC0],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x435B99
		RETN 4
	}
}

__declspec(naked) void NKD_CMP091()//0x436115
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x436195
		RETN 4
	}
}

__declspec(naked) void NKD_CMP092()//0x436B5A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1F18],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x436B93
		RETN 4
	}
}

__declspec(naked) void NKD_CMP093()//0x4374CC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1F7C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43756C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP094()//0x437591
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1F80],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43762E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP095()//0x437963
{
	__asm
	{
		CMP ECX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x437977
		RETN 4
	}
}

__declspec(naked) void NKD_CMP096()//0x437D18
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1FB4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x437D2D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP097()//0x4381F1
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1FF4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438297
		RETN 4
	}
}

__declspec(naked) void NKD_CMP098()//0x4382BC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1FF8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438359
		RETN 4
	}
}

__declspec(naked) void NKD_CMP099()//0x43850F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2020],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438549
		RETN 4
	}
}

__declspec(naked) void NKD_CMP100()//0x4385C9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2028],MAX_PLAYER
		JGE Pula


		RETN

Pula:
		PUSH 0x4385DD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP101()//0x438643
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x202C],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43867E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP102()//0x4387C6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438834
		RETN 4
	}
}

__declspec(naked) void NKD_CMP103()//0x438881
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2050],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4388BC
		RETN 4
	}
}

__declspec(naked) void NKD_CMP104()//0x43891C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x204C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438930
		RETN 4
	}
}

__declspec(naked) void NKD_CMP105()//0x438ACA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x438B38
		RETN 4
	}
}

__declspec(naked) void NKD_CMP106()//0x43EB14
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43EB1C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP107()//0x43EC10
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43EC45
		RETN 4
	}
}

__declspec(naked) void NKD_CMP108()//0x43ECF7
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43EE1A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP109()//0x43EEDE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F027
		RETN 4
	}
}

__declspec(naked) void NKD_CMP110()//0x43F0CA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F149
		RETN 4
	}
}

__declspec(naked) void NKD_CMP111()//0x43F1BA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F1FF
		RETN 4
	}
}

__declspec(naked) void NKD_CMP112()//0x43F254
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43F25C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP113()//0x43F4DA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F539
		RETN 4
	}
}

__declspec(naked) void NKD_CMP114()//0x43F594
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F5BE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP115()//0x43F5C9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F638
		RETN 4
	}
}

__declspec(naked) void NKD_CMP116()//0x43F9D4
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x43F9E6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP117()//0x43F9E0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43F9EB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP118()//0x43FB52
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x43FB5D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP119()//0x43FE44
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43FE60
		RETN 4
	}
}

__declspec(naked) void NKD_CMP120()//0x43FEFB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x43FF17
		RETN 4
	}
}

__declspec(naked) void NKD_CMP121()//0x440240
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x140],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44026D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP122()//0x4402AB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x140],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4402CB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP123()//0x4402CB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4402E8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP124()//0x440405
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44044D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP125()//0x4404AD
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x14C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4404F8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP126()//0x4404F8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440543
		RETN 4
	}
}

__declspec(naked) void NKD_CMP127()//0x44055A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x14C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440617
		RETN 4
	}
}

__declspec(naked) void NKD_CMP128()//0x440B09
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440B55
		RETN 4
	}
}

__declspec(naked) void NKD_CMP129()//0x440D4B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440DBA
		RETN 4
	}
}

__declspec(naked) void NKD_CMP130()//0x440DCE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x18],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440EE9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP131()//0x440E50
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x38],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x440E5E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP132()//0x440FDE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x441008
		RETN 4
	}
}

__declspec(naked) void NKD_CMP133()//0x441374
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4413A2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP134()//0x44149B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4414F5
		RETN 4
	}
}

__declspec(naked) void NKD_CMP135()//0x4415CE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4415F8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP136()//0x44172E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x441758
		RETN 4
	}
}

__declspec(naked) void NKD_CMP137()//0x441874
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x110],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x441965
		RETN 4
	}
}

__declspec(naked) void NKD_CMP138()//0x441D94
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x441DBE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP139()//0x44214E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x442178
		RETN 4
	}
}

__declspec(naked) void NKD_CMP140()//0x4422BE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4422E8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP141()//0x44242E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x442458
		RETN 4
	}
}

__declspec(naked) void NKD_CMP142()//0x442514
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44253E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP143()//0x442674
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x14],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x442726
		RETN 4
	}
}

__declspec(naked) void NKD_CMP144()//0x44279E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4427C8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP145()//0x4428FE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x442928
		RETN 4
	}
}

__declspec(naked) void NKD_PUSH02()//0x442E72
{
	__asm
	{
		PUSH MAX_PLAYER
		PUSH 0x0C4C

		MOV jmp_padr, 0x442E79
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_PUSH03()//0x442F1D //
{
	__asm
	{
		PUSH MAX_PLAYER
		PUSH 0x0C4C

		MOV jmp_padr, 0x442F24
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP146()//0x4439BE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4439CB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP147()//0x445EA8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x445EB7
		RETN 4
	}
}

__declspec(naked) void NKD_PUSH04()//0x446972
{
	__asm
	{
		PUSH MAX_PLAYER
		MOV ECX,DWORD PTR SS:[EBP - 0x8]

		MOV jmp_padr, 0x446977
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP148()//0x447258
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x10],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x447315
		RETN 4
	}
}

__declspec(naked) void NKD_PUSH05()//0x4473AF
{
	__asm
	{
		PUSH MAX_PLAYER
		MOV ECX,DWORD PTR SS:[EBP - 0x4]

		MOV jmp_padr, 0x4473B4
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP149()//0x447C78
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x34],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x447D35
		RETN 4
	}
}

__declspec(naked) void NKD_PUSH06()//0x447DEE
{
	__asm
	{
		PUSH MAX_PLAYER
		MOV ECX,DWORD PTR SS:[EBP - 0x28]

		MOV jmp_padr, 0x447DF3
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_PUSH07()//0x4484D7
{
	__asm
	{
		PUSH MAX_PLAYER
		MOV ECX,DWORD PTR SS:[EBP - 0xB4]

		MOV jmp_padr, 0x4484DF
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_MOV02()//0x448D95
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x4],MAX_PLAYER

		MOV jmp_padr, 0x448D9C
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_MOV03()//0x448E02
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x4],MAX_PLAYER

		MOV jmp_padr, 0x448E09
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP150()//0x44B541
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44B5F2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP151()//0x44B818
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN	

Pula:
		PUSH 0x44B827
		RETN 4
	}
}

__declspec(naked) void NKD_CMP152()//0x44B888
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x44B893
		RETN 4
	}
}

__declspec(naked) void NKD_CMP153()//0x44BADC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44BB02
		RETN 4
	}
}

__declspec(naked) void NKD_CMP154()//0x44BC16
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x44BC52
		RETN 4
	}
}

__declspec(naked) void NKD_CMP155()//0x44C60D
{
	__asm
	{
		CMP EAX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x44C669
		RETN 4
	}
}

__declspec(naked) void NKD_CMP156()//0x44C832
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44C86D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP157()//0x44C873
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xC],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x44C8B2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP158()//0x44E5BF
{
	__asm
	{
		CMP EDX,MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x44E5DD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP159()//0x44F1D0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44F204
		RETN 4
	}
}

__declspec(naked) void NKD_CMP160()//0x44F216
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44F24F
		RETN 4
	}
}

__declspec(naked) void NKD_MOV04()//0x44F24F
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x4],MAX_PLAYER

		MOV jmp_padr, 0x44F256
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP161()//0x44F354
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x44F35F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP162()//0x44F50C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44F520
		RETN 4
	}
}

__declspec(naked) void NKD_MOV05()//0x44F967
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0xC4],MAX_PLAYER

		MOV jmp_padr, 0x44F971
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP163()//0x44FBDF
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x44FBFC
		RETN 4
	}
}

__declspec(naked) void NKD_CMP164()//0x45017D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4505D9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP165()//0x450279
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450294
		RETN 4
	}
}

__declspec(naked) void NKD_CMP166()//0x4502BD
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4502DA
		RETN 4
	}
}

__declspec(naked) void NKD_CMP167()//0x4503AC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x450427
		RETN 4
	}
}

__declspec(naked) void NKD_CMP168()//0x450496
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4504A1
		RETN 4
	}
}

__declspec(naked) void NKD_CMP169()//0x45072D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450748
		RETN 4
	}
}

__declspec(naked) void NKD_CMP170()//0x450780
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4507A3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP171()//0x450843
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45086A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP172()//0x450871
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x450898
		RETN 4
	}
}

__declspec(naked) void NKD_CMP173()//0x450BC8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x450C58
		RETN 4
	}
}

__declspec(naked) void NKD_CMP174()//0x450BE4
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xD4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450BFF
		RETN 4
	}
}

__declspec(naked) void NKD_CMP175()//0x450C16
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xD4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450C31
		RETN 4
	}
}

__declspec(naked) void NKD_CMP176()//0x450C58
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xD4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450C6F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP177()//0x450C78
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xD4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x450C86
		RETN 4
	}
}

__declspec(naked) void NKD_CMP178()//0x4510BA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4510C8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP179()//0x4510E7
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x451178
		RETN 4
	}
}

__declspec(naked) void NKD_CMP180()//0x451103
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45111E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP181()//0x451136
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x451151
		RETN 4
	}
}

__declspec(naked) void NKD_CMP182()//0x451178
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x104],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45118F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP183()//0x451594
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4515B2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP184()//0x451750
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x19C],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x45175B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP185()//0x451844
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4518C9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP186()//0x45197E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18C],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x4519AE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP187()//0x4519D6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x18C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x451A1B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP188()//0x451AA3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x451AAE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP189()//0x451D60
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x214],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x451E23
		RETN 4
	}
}

__declspec(naked) void NKD_CMP190()//0x451D7F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x214],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x451D9A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP191()//0x451DB2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x214],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x451DCD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP192()//0x451E51
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x451EA9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP193()//0x451E89
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x214],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x451EA9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP194()//0x451EB2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x214],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x451EC0
		RETN 4
	}
}

__declspec(naked) void NKD_CMP195()//0x4520FF
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x258],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45210D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP196()//0x45226B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4522FB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP197()//0x452287
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x258],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4522A2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP198()//0x4522B9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x258],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4522D4
		RETN 4
	}
}

__declspec(naked) void NKD_CMP199()//0x4522FB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x258],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x452312
		RETN 4
	}
}

__declspec(naked) void NKD_CMP200()//0x4524C5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4524E3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP201()//0x452F2A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4530E8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP202()//0x4531F2
{
	__asm
	{
		CMP DWORD PTR DS:[0x4CBBD4],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45324D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP203()//0x453567
{
	__asm
	{
		CMP DWORD PTR DS:[0x4CBBD8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45357A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP204()//0x45368D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x19C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x453741
		RETN 4
	}
}

__declspec(naked) void NKD_CMP205()//0x4537B5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1B8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4539A5
		RETN 4
	}
}

__declspec(naked) void NKD_ADD01()//0x453B0A
{
	__asm
	{
		ADD EDX,MAX_PLAYER
		MOV DWORD PTR SS:[EBP - 0x1B8],EDX

		MOV jmp_padr, 0x453B13
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP206()//0x453D89
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1E4],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x453D94
		RETN 4
	}
}

__declspec(naked) void NKD_CMP207()//0x453E22
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1D8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x453F3D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP208()//0x453EA4
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x1F0],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x453EAF
		RETN 4
	}
}

__declspec(naked) void NKD_ADD02()//0x454350
{
	__asm
	{
		ADD EAX,MAX_PLAYER
		MOV DWORD PTR SS:[EBP - 0x1B8],EAX

		MOV jmp_padr, 0x454359
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP209()//0x4547F8
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x290],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4548D1
		RETN 4
	}
}

__declspec(naked) void NKD_CMP210()//0x454999
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2E0],MAX_PLAYER
		JG Pula

		RETN

Pula:
		PUSH 0x4549A4
		RETN 4
	}
}

__declspec(naked) void NKD_CMP211()//0x454A7C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x290],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x454CC7
		RETN 4
	}
}

__declspec(naked) void NKD_CMP212()//0x454A96
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2E4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x454CC7
		RETN 4
	}
}

__declspec(naked) void NKD_CMP213()//0x454D12
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x290],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x454D97
		RETN 4
	}
}

__declspec(naked) void NKD_CMP214()//0x454E4C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x290],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x454E7C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP215()//0x454EDB
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x290],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x454F20
		RETN 4
	}
}

__declspec(naked) void NKD_CMP216()//0x45648C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x456568
		RETN 4
	}
}

__declspec(naked) void NKD_CMP217()//0x45660C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45672B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP218()//0x4567CA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x456862
		RETN 4
	}
}

__declspec(naked) void NKD_CMP219()//0x4568DA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4569A1
		RETN 4
	}
}

__declspec(naked) void NKD_CMP220()//0x456A2A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x456ADE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP221()//0x456B5A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x456C2C
		RETN 4
	}
}

__declspec(naked) void NKD_CMP222()//0x456CC6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x14],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x456D5E
		RETN 4
	}
}

__declspec(naked) void NKD_MOV06()//0x457138
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x4],MAX_PLAYER

		MOV jmp_padr, 0x45713F
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP223()//0x4576C5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x220],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x4576D0
		RETN 4
	}
}

__declspec(naked) void NKD_CMP224()//0x457B2C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x34],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x457B64
		RETN 4
	}
}

__declspec(naked) void NKD_CMP225()//0x457F08
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x48],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x457FA9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP226()//0x4580C0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x458161
		RETN 4
	}
}

__declspec(naked) void NKD_CMP227()//0x458DEE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x458E5D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP228()//0x4590AA
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4590CB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP229()//0x45911A
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x459139
		RETN 4
	}
}

__declspec(naked) void NKD_MOV07()//0x4591F4
{
	__asm
	{
		MOV DWORD PTR DS:[0x4CBBE4],MAX_PLAYER

		MOV jmp_padr, 0x4591FE
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_MOV08()//0x459239
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x8],MAX_PLAYER

		MOV jmp_padr, 0x459240
		JMP jmp_padr
	}
}

__declspec(naked) void NKD_CMP230()//0x4592EE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x459343
		RETN 4
	}
}

__declspec(naked) void NKD_CMP231()//0x459359
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4593AD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP232()//0x4595BE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x10],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4595F9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP233()//0x459D1C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x459D89
		RETN 4
	}
}

__declspec(naked) void NKD_CMP234()//0x45A056
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45A091
		RETN 4
	}
}

__declspec(naked) void NKD_CMP235()//0x45A919
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45A936
		RETN 4
	}
}

__declspec(naked) void NKD_CMP236()//0x45ABF5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45AC2B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP237()//0x45AC59
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45AC6B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP238()//0x45ACB5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45ACD6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP239()//0x45ACE9
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45AF04
		RETN 4
	}
}

__declspec(naked) void NKD_CMP240()//0x45AD26
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x45AF04
		RETN 4
	}
}

__declspec(naked) void NKD_CMP241()//0x45AD65
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x10],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45AF04
		RETN 4
	}
}

__declspec(naked) void NKD_CMP242()//0x45AF56
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45AFF2
		RETN 4
	}
}

__declspec(naked) void NKD_CMP243()//0x45AF8D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x3C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45AFA5
		RETN 4
	}
}

__declspec(naked) void NKD_CMP244()//0x45AFD3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x45AFE7
		RETN 4
	}
}

__declspec(naked) void NKD_CMP245()//0x45AFF2
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45C18F
		RETN 4
	}
}

__declspec(naked) void NKD_CMP246()//0x45B255
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45B360
		RETN 4
	}
}

__declspec(naked) void NKD_CMP247()//0x45B4A0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45B4C9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP248()//0x45B528
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45B561
		RETN 4
	}
}

__declspec(naked) void NKD_CMP249()//0x45BE33
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45BE7E
		RETN 4
	}
}

__declspec(naked) void NKD_CMP250()//0x45C18F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45C208
		RETN 4
	}
}

__declspec(naked) void NKD_CMP251()//0x45C208
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45C223
		RETN 4
	}
}

__declspec(naked) void NKD_CMP252()//0x45C3A0
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x20C],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45C3AB
		RETN 4
	}
}

__declspec(naked) void NKD_CMP253()//0x45C58C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x20C],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x45C597
		RETN 4
	}
}

__declspec(naked) void NKD_CMP254()//0x45CD27
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x284],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45CDE3
		RETN 4
	}
}

__declspec(naked) void NKD_CMP255()//0x45DC7D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45DC98
		RETN 4
	}
}

__declspec(naked) void NKD_CMP256()//0x45DD6B
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45DDD9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP257()//0x45DE03
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45DF1D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP258()//0x45E023
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45E041
		RETN 4
	}
}

__declspec(naked) void NKD_CMP259()//0x45F148
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F283
		RETN 4
	}
}

__declspec(naked) void NKD_CMP260()//0x45F375
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x4],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F403
		RETN 4
	}
}

__declspec(naked) void NKD_CMP261()//0x45F409
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F41D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP262()//0x45F4A5
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F4CD
		RETN 4
	}
}

__declspec(naked) void NKD_CMP263()//0x45F547
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x14],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F56D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP264()//0x45F8A6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x30],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45F8C6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP265()//0x45FB5C
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45FB84
		RETN 4
	}
}

__declspec(naked) void NKD_CMP266()//0x45FD88
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x28],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45FDE7
		RETN 4
	}
}

__declspec(naked) void NKD_CMP267()//0x45FF03
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x2C],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x45FF61
		RETN 4
	}
}

__declspec(naked) void NKD_CMP268()//0x460262
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x28],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4602A8
		RETN 4
	}
}

__declspec(naked) void NKD_CMP269()//0x46036E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x46038D
		RETN 4
	}
}

__declspec(naked) void NKD_CMP270()//0x4603BC
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4603D4
		RETN 4
	}
}

__declspec(naked) void NKD_CMP271()//0x460A7D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0xC],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x460B84
		RETN 4
	}
}

__declspec(naked) void NKD_CMP272()//0x460FA3
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x20],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x4610AA
		RETN 4
	}
}

__declspec(naked) void NKD_CMP273()//0x46122E
{
	__asm
	{
		CMP DWORD PTR DS:[0x8BF1880],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x461327
		RETN 4
	}
}

__declspec(naked) void NKD_CMP274()//0x461248
{
	__asm
	{
		CMP DWORD PTR DS:[0x8BF1884],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x461327
		RETN 4
	}
}

__declspec(naked) void NKD_CMP275()//0x46171F
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0xC],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x46172A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP276()//0x461730
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x10],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x46173B
		RETN 4
	}
}

__declspec(naked) void NKD_CMP277()//0x461A78
{
	__asm
	{
		CMP DWORD PTR SS:[EBP - 0x24],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x461A80
		RETN 4
	}
}

__declspec(naked) void NKD_CMP278()//0x461CCE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x461CD6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP279()//0x461DD6
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x461DFE
		RETN 4
	}
}

__declspec(naked) void NKD_CMP280()//0x461E9E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JGE Pula

		RETN

Pula:
		PUSH 0x461EC6
		RETN 4
	}
}

__declspec(naked) void NKD_CMP281()//0x461F4D
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x461F5A
		RETN 4
	}
}

__declspec(naked) void NKD_CMP282()//0x4621ED
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JLE Pula

		RETN

Pula:
		PUSH 0x4621FA
		RETN 4
	}
}

__declspec(naked) void NKD_CMP283()//0x462B65
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x462B70
		RETN 4
	}
}

__declspec(naked) void NKD_CMP284()//0x4630AE
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4630B9
		RETN 4
	}
}

__declspec(naked) void NKD_CMP285()//0x46319E
{
	__asm
	{
		CMP DWORD PTR SS:[EBP + 0x8],MAX_PLAYER
		JL Pula

		RETN

Pula:
		PUSH 0x4631A9
		RETN 4
	}
}

__declspec(naked) void NKD_CLIENTID()//0x459108
{
	__asm
	{
		MOV DWORD PTR SS:[EBP - 0x4], 990
		
		MOV jmp_padr, 0x45910F
		JMP jmp_padr
	}
}

void LimitPlayers()
{
	// Limite de Players, bastante extenso
	CALL_NEAR(0x410ED3, NKD_CMP001, 4);
	CALL_NEAR(0x410F3B, NKD_CMP002, 1);
	CALL_NEAR(0x4114C6, NKD_CMP003, 4);
	CALL_NEAR(0x4114EB, NKD_CMP004, 1);
	CALL_NEAR(0x41192E, NKD_CMP005);
	CALL_NEAR(0x411955, NKD_CMP006);
	CALL_NEAR(0x411C25, NKD_CMP007); 
	CALL_NEAR(0x411D74, NKD_CMP008);
	CALL_NEAR(0x4123E3, NKD_CMP009, 1);
	CALL_NEAR(0x4123F9, NKD_CMP010, 5);
	CALL_NEAR(0x412488, NKD_CMP011, 1);
	CALL_NEAR(0x412520, NKD_CMP012, 1);
	CALL_NEAR(0x413CF1, NKD_CMP013, 1);
	CALL_NEAR(0x41ABCE, NKD_CMP014, 1);
	CALL_NEAR(0x41C550, NKD_CMP015, 5);
	CALL_NEAR(0x41C69D, NKD_CMP016, 1);
	CALL_NEAR(0x41CAE0, NKD_CMP017, 5);
	CALL_NEAR(0x41CC11, NKD_CMP018, 1);
	CALL_NEAR(0x41D2EE, NKD_CMP019, 5);
	CALL_NEAR(0x41D94B, NKD_CMP020, 1);
	CALL_NEAR(0x41D98F, NKD_CMP021, 1);
	CALL_NEAR(0x41D9AE, NKD_CMP022, 1);
	CALL_NEAR(0x41DAFA, NKD_CMP023, 1);
	CALL_NEAR(0x41DE22, NKD_CMP024, 1);
	CALL_NEAR(0x41DE86, NKD_CMP025, 1);
	CALL_NEAR(0x41E4BE, NKD_CMP026, 1);
	CALL_NEAR(0x41E52E, NKD_CMP027, 1);
	CALL_NEAR(0x41E5BE, NKD_CMP028, 1);
	CALL_NEAR(0x41E63E, NKD_CMP029, 1);
	CALL_NEAR(0x41E7CE, NKD_CMP030, 1);
	CALL_NEAR(0x41E84E, NKD_CMP031, 1);
	CALL_NEAR(0x41E8DA, NKD_CMP032, 1);
	CALL_NEAR(0x41EA90, NKD_CMP033, 1);
	CALL_NEAR(0x41FBAB, NKD_CMP034, 1);
	CALL_NEAR(0x42094E, NKD_CMP035, 1);
	CALL_NEAR(0x4209E2, NKD_CMP036, 1);
	CALL_NEAR(0x420E53, NKD_CMP037, 1);
	CALL_NEAR(0x420EC3, NKD_CMP038, 1);
	CALL_NEAR(0x42117A, NKD_CMP039, 1);
	CALL_NEAR(0x421DAE, NKD_CMP040, 1);
	CALL_NEAR(0x42215F, NKD_CMP041);
	CALL_NEAR(0x4221BB, NKD_CMP042, 1);
	CALL_NEAR(0x422955, NKD_CMP043, 1);
	CALL_NEAR(0x42554C, NKD_CMP044, 4);
	CALL_NEAR(0x4255C2, NKD_CMP045, 4);
	CALL_NEAR(0x42569E, NKD_CMP046, 4);
	CALL_NEAR(0x425ACB, NKD_CMP047, 4);
	CALL_NEAR(0x425B5A, NKD_CMP048, 4);
	CALL_NEAR(0x425BEC, NKD_CMP049, 4);
	CALL_NEAR(0x425F3C, NKD_CMP050, 4);
	CALL_NEAR(0x425FC8, NKD_CMP051, 1);
	CALL_NEAR(0x4262EF, NKD_CMP052, 4);
	CALL_NEAR(0x426383, NKD_CMP053, 8);
	CALL_NEAR(0x4265B0, NKD_CMP054, 4);
	CALL_NEAR(0x426848, NKD_CMP055, 4);
	CALL_NEAR(0x426A09, NKD_CMP056, 4);
	CALL_NEAR(0x426B80, NKD_CMP057, 4);
	CALL_NEAR(0x426C59, NKD_CMP058, 4);
	CALL_NEAR(0x426E2A, NKD_CMP059, 4);
	CALL_NEAR(0x426FF8, NKD_CMP060, 4);
	CALL_NEAR(0x42711B, NKD_CMP061, 4);
	CALL_NEAR(0x42729B, NKD_CMP062, 1);
	CALL_NEAR(0x4273F6, NKD_CMP063, 4);
	CALL_NEAR(0x427523, NKD_CMP064, 4);
	CALL_NEAR(0x42754B, NKD_CMP065, 4);
	CALL_NEAR(0x42758D, NKD_CMP066, 4);
	CALL_NEAR(0x4275CF, NKD_CMP067, 8);
	CALL_NEAR(0x427951, NKD_CMP068, 4);
	CALL_NEAR(0x427C05, NKD_CMP069, 4);
	CALL_NEAR(0x427C2D, NKD_CMP070, 8);
	CALL_NEAR(0x427CED, NKD_CMP071, 8);
	CALL_NEAR(0x427F3D, NKD_CMP072, 4);
	CALL_NEAR(0x427F7F, NKD_CMP073, 4);
	CALL_NEAR(0x4280C2, NKD_CMP074, 4);
	CALL_NEAR(0x4281D0, NKD_CMP075, 4);
	CALL_NEAR(0x4289D8, NKD_CMP076, 8);
	CALL_NEAR(0x428B96, NKD_CMP077, 4);
	CALL_NEAR(0x42A74C, NKD_CMP078);
	CALL_NEAR(0x42BBEF, NKD_CMP079, 4);
	CALL_NEAR(0x43057B, NKD_CMP080, 4);
	CALL_NEAR(0x431022, NKD_CMP081, 4);
	CALL_NEAR(0x4316AD, NKD_CMP082, 8);
	CALL_NEAR(0x431779, NKD_CMP083, 8);
	CALL_NEAR(0x4318F5, NKD_CMP084, 4);
	CALL_NEAR(0x431AF3, NKD_CMP085, 4);
	CALL_NEAR(0x43246B, NKD_CMP086, 4);
	CALL_NEAR(0x43369B, NKD_CMP087, 4);
	CALL_NEAR(0x4359C8, NKD_CMP088, 8);
	CALL_NEAR(0x435AD9, NKD_CMP089, 8);
	CALL_NEAR(0x435B85, NKD_CMP090, 4);
	CALL_NEAR(0x436115, NKD_CMP091, 1);
	CALL_NEAR(0x436B5A, NKD_CMP092, 4);
	CALL_NEAR(0x4374CC, NKD_CMP093, 8);
	CALL_NEAR(0x437591, NKD_CMP094, 8);
	CALL_NEAR(0x437963, NKD_CMP095);
	CALL_NEAR(0x437D18, NKD_CMP096, 4);
	CALL_NEAR(0x4381F1, NKD_CMP097, 8);
	CALL_NEAR(0x4382BC, NKD_CMP098, 8);
	CALL_NEAR(0x43850F, NKD_CMP099, 4);
	CALL_NEAR(0x4385C9, NKD_CMP100, 4);
	CALL_NEAR(0x438643, NKD_CMP101, 4);
	CALL_NEAR(0x4387C6, NKD_CMP102, 1);
	CALL_NEAR(0x438881, NKD_CMP103, 4);
	CALL_NEAR(0x43891C, NKD_CMP104, 4);
	CALL_NEAR(0x438ACA, NKD_CMP105, 1);
	CALL_NEAR(0x43EB14, NKD_CMP106, 1);
	CALL_NEAR(0x43EC10, NKD_CMP107, 4);
	CALL_NEAR(0x43ECF7, NKD_CMP108, 8);
	CALL_NEAR(0x43EEDE, NKD_CMP109, 5);
	CALL_NEAR(0x43F0CA, NKD_CMP110, 1);
	CALL_NEAR(0x43F1BA, NKD_CMP111, 1);
	CALL_NEAR(0x43F254, NKD_CMP112, 1);
	CALL_NEAR(0x43F4DA, NKD_CMP113, 1);
	CALL_NEAR(0x43F594, NKD_CMP114, 1);
	CALL_NEAR(0x43F5C9, NKD_CMP115, 1);
	CALL_NEAR(0x43F9D4, NKD_CMP116, 1);
	CALL_NEAR(0x43F9E0, NKD_CMP117, 1);
	CALL_NEAR(0x43FB52, NKD_CMP118, 1);
	CALL_NEAR(0x43FE44, NKD_CMP119, 1);
	CALL_NEAR(0x43FEFB, NKD_CMP120, 1);
	CALL_NEAR(0x440240, NKD_CMP121, 4);
	CALL_NEAR(0x4402AB, NKD_CMP122, 4);
	CALL_NEAR(0x4402CB, NKD_CMP123, 1);
	CALL_NEAR(0x440405, NKD_CMP124, 1);
	CALL_NEAR(0x4404AD, NKD_CMP125, 4);
	CALL_NEAR(0x4404F8, NKD_CMP126, 1);
	CALL_NEAR(0x44055A, NKD_CMP127, 8);
	CALL_NEAR(0x440B09, NKD_CMP128, 1);
	CALL_NEAR(0x440D4B, NKD_CMP129, 1);
	CALL_NEAR(0x440DCE, NKD_CMP130, 5);
	CALL_NEAR(0x440E50, NKD_CMP131, 1);
	CALL_NEAR(0x440FDE, NKD_CMP132, 1);
	CALL_NEAR(0x441374, NKD_CMP133, 1);
	CALL_NEAR(0x44149B, NKD_CMP134, 1);
	CALL_NEAR(0x4415CE, NKD_CMP135, 1);
	CALL_NEAR(0x44172E, NKD_CMP136, 1);
	CALL_NEAR(0x441874, NKD_CMP137, 8);
	CALL_NEAR(0x441D94, NKD_CMP138, 1);
	CALL_NEAR(0x44214E, NKD_CMP139, 1);
	CALL_NEAR(0x4422BE, NKD_CMP140, 1);
	CALL_NEAR(0x44242E, NKD_CMP141, 1);
	CALL_NEAR(0x442514, NKD_CMP142, 1);
	CALL_NEAR(0x442674, NKD_CMP143, 5);
	CALL_NEAR(0x44279E, NKD_CMP144, 1);
	CALL_NEAR(0x4428FE, NKD_CMP145, 1);
	CALL_NEAR(0x4439BE, NKD_CMP146, 1);
	CALL_NEAR(0x445EA8, NKD_CMP147, 1);
	CALL_NEAR(0x447258, NKD_CMP148, 5);
	CALL_NEAR(0x447C78, NKD_CMP149, 5);
	CALL_NEAR(0x44B541, NKD_CMP150, 5);
	CALL_NEAR(0x44B818, NKD_CMP151, 1);
	CALL_NEAR(0x44B888, NKD_CMP152, 1);
	CALL_NEAR(0x44BADC, NKD_CMP153, 1);
	CALL_NEAR(0x44BC16, NKD_CMP154, 1);
	CALL_NEAR(0x44C60D, NKD_CMP155);
	CALL_NEAR(0x44C832, NKD_CMP156, 1);
	CALL_NEAR(0x44C873, NKD_CMP157, 1);
	CALL_NEAR(0x44E5BF, NKD_CMP158);
	CALL_NEAR(0x44F1D0, NKD_CMP159, 1);
	CALL_NEAR(0x44F216, NKD_CMP160, 1);
	CALL_NEAR(0x44F354, NKD_CMP161, 1);
	CALL_NEAR(0x44F50C, NKD_CMP162, 1);
	CALL_NEAR(0x44FBDF, NKD_CMP163, 1);
	CALL_NEAR(0x45017D, NKD_CMP164, 5);
	CALL_NEAR(0x450279, NKD_CMP165, 1);
	CALL_NEAR(0x4502BD, NKD_CMP166, 1);
	CALL_NEAR(0x4503AC, NKD_CMP167, 1);
	CALL_NEAR(0x450496, NKD_CMP168, 1);
	CALL_NEAR(0x45072D, NKD_CMP169, 1);
	CALL_NEAR(0x450780, NKD_CMP170, 1);
	CALL_NEAR(0x450843, NKD_CMP171, 1);
	CALL_NEAR(0x450871, NKD_CMP172, 1);
	CALL_NEAR(0x450BC8, NKD_CMP173, 5);
	CALL_NEAR(0x450BE4, NKD_CMP174, 4);
	CALL_NEAR(0x450C16, NKD_CMP175, 4);
	CALL_NEAR(0x450C58, NKD_CMP176, 4);
	CALL_NEAR(0x450C78, NKD_CMP177, 4);
	CALL_NEAR(0x4510BA, NKD_CMP178, 4);
	CALL_NEAR(0x4510E7, NKD_CMP179, 5);
	CALL_NEAR(0x451103, NKD_CMP180, 4);
	CALL_NEAR(0x451136, NKD_CMP181, 4);
	CALL_NEAR(0x451178, NKD_CMP182, 4);
	CALL_NEAR(0x451594, NKD_CMP183, 1);
	CALL_NEAR(0x451750, NKD_CMP184, 4);
	CALL_NEAR(0x451844, NKD_CMP185, 4);
	CALL_NEAR(0x45197E, NKD_CMP186, 4);
	CALL_NEAR(0x4519D6, NKD_CMP187, 4);
	CALL_NEAR(0x451AA3, NKD_CMP188, 1);
	CALL_NEAR(0x451D60, NKD_CMP189, 8);
	CALL_NEAR(0x451D7F, NKD_CMP190, 4);
	CALL_NEAR(0x451DB2, NKD_CMP191, 4);
	CALL_NEAR(0x451E51, NKD_CMP192, 1);
	CALL_NEAR(0x451E89, NKD_CMP193, 4);
	CALL_NEAR(0x451EB2, NKD_CMP194, 4);
	CALL_NEAR(0x4520FF, NKD_CMP195, 4);
	CALL_NEAR(0x45226B, NKD_CMP196, 5);
	CALL_NEAR(0x452287, NKD_CMP197, 4);
	CALL_NEAR(0x4522B9, NKD_CMP198, 4);
	CALL_NEAR(0x4522FB, NKD_CMP199, 4);
	CALL_NEAR(0x4524C5, NKD_CMP200, 1);
	CALL_NEAR(0x452F2A, NKD_CMP201, 5);
	CALL_NEAR(0x4531F2, NKD_CMP202, 4);
	CALL_NEAR(0x453567, NKD_CMP203, 4);
	CALL_NEAR(0x45368D, NKD_CMP204, 8);
	CALL_NEAR(0x4537B5, NKD_CMP205, 8);
	CALL_NEAR(0x453D89, NKD_CMP206, 4);
	CALL_NEAR(0x453E22, NKD_CMP207, 8);
	CALL_NEAR(0x453EA4, NKD_CMP208, 4);
	CALL_NEAR(0x4547F8, NKD_CMP209, 8);
	CALL_NEAR(0x454999, NKD_CMP210, 4);
	CALL_NEAR(0x454A7C, NKD_CMP211, 8);
	CALL_NEAR(0x454A96, NKD_CMP212, 8);
	CALL_NEAR(0x454D12, NKD_CMP213, 4);
	CALL_NEAR(0x454E4C, NKD_CMP214, 4);
	CALL_NEAR(0x454EDB, NKD_CMP215, 4);
	CALL_NEAR(0x45648C, NKD_CMP216, 5);
	CALL_NEAR(0x45660C, NKD_CMP217, 5);
	CALL_NEAR(0x4567CA, NKD_CMP218, 5);
	CALL_NEAR(0x4568DA, NKD_CMP219, 5);
	CALL_NEAR(0x456A2A, NKD_CMP220, 5);
	CALL_NEAR(0x456B5A, NKD_CMP221, 5);
	CALL_NEAR(0x456CC6, NKD_CMP222, 5);
	CALL_NEAR(0x4576C5, NKD_CMP223, 4);
	CALL_NEAR(0x457B2C, NKD_CMP224, 1);
	CALL_NEAR(0x457F08, NKD_CMP225, 5);
	CALL_NEAR(0x4580C0, NKD_CMP226, 5);
	CALL_NEAR(0x458DEE, NKD_CMP227, 1);
	CALL_NEAR(0x4590AA, NKD_CMP228, 1);
	CALL_NEAR(0x45911A, NKD_CMP229, 1);
	CALL_NEAR(0x4592EE, NKD_CMP230, 1);
	CALL_NEAR(0x459359, NKD_CMP231, 1);
	CALL_NEAR(0x4595BE, NKD_CMP232, 1);
	CALL_NEAR(0x459D1C, NKD_CMP233, 1);
	CALL_NEAR(0x45A056, NKD_CMP234, 1);
	CALL_NEAR(0x45A919, NKD_CMP235, 1);
	CALL_NEAR(0x45ABF5, NKD_CMP236, 1);
	CALL_NEAR(0x45AC59, NKD_CMP237, 1);
	CALL_NEAR(0x45ACB5, NKD_CMP238, 1);
	CALL_NEAR(0x45ACE9, NKD_CMP239, 5);
	CALL_NEAR(0x45AD26, NKD_CMP240, 5);
	CALL_NEAR(0x45AD65, NKD_CMP241, 5);
	CALL_NEAR(0x45AF56, NKD_CMP242, 5);
	CALL_NEAR(0x45AF8D, NKD_CMP243, 1);
	CALL_NEAR(0x45AFD3, NKD_CMP244, 1);
	CALL_NEAR(0x45AFF2, NKD_CMP245, 5);
	CALL_NEAR(0x45B255, NKD_CMP246, 5);
	CALL_NEAR(0x45B4A0, NKD_CMP247, 1);
	CALL_NEAR(0x45B528, NKD_CMP248, 1);
	CALL_NEAR(0x45BE33, NKD_CMP249, 1);
	CALL_NEAR(0x45C18F, NKD_CMP250, 1);
	CALL_NEAR(0x45C208, NKD_CMP251, 1);
	CALL_NEAR(0x45C3A0, NKD_CMP252, 4);
	CALL_NEAR(0x45C58C, NKD_CMP253, 4);
	CALL_NEAR(0x45CD27, NKD_CMP254, 8);
	CALL_NEAR(0x45DC7D, NKD_CMP255, 1);
	CALL_NEAR(0x45DD6B, NKD_CMP256, 1);
	CALL_NEAR(0x45DE03, NKD_CMP257, 5);
	CALL_NEAR(0x45E023, NKD_CMP258, 1);
	CALL_NEAR(0x45F148, NKD_CMP259, 5);
	CALL_NEAR(0x45F375, NKD_CMP260, 5);
	CALL_NEAR(0x45F409, NKD_CMP261, 1);
	CALL_NEAR(0x45F4A5, NKD_CMP262, 1);
	CALL_NEAR(0x45F547, NKD_CMP263, 1);
	CALL_NEAR(0x45F8A6, NKD_CMP264, 1);
	CALL_NEAR(0x45FB5C, NKD_CMP265, 1);
	CALL_NEAR(0x45FD88, NKD_CMP266, 1);
	CALL_NEAR(0x45FF03, NKD_CMP267, 1);
	CALL_NEAR(0x460262, NKD_CMP268, 1);
	CALL_NEAR(0x46036E, NKD_CMP269, 1);
	CALL_NEAR(0x4603BC, NKD_CMP270, 1);
	CALL_NEAR(0x460A7D, NKD_CMP271, 5);
	CALL_NEAR(0x460FA3, NKD_CMP272, 5);
	CALL_NEAR(0x46122E, NKD_CMP273, 8);
	CALL_NEAR(0x461248, NKD_CMP274, 8);
	CALL_NEAR(0x46171F, NKD_CMP275, 1);
	CALL_NEAR(0x461730, NKD_CMP276, 1);
	CALL_NEAR(0x461A78, NKD_CMP277, 1);
	CALL_NEAR(0x461CCE, NKD_CMP278, 1);
	CALL_NEAR(0x461DD6, NKD_CMP279, 1);
	CALL_NEAR(0x461E9E, NKD_CMP280, 1);
	CALL_NEAR(0x461F4D, NKD_CMP281, 1);
	CALL_NEAR(0x4621ED, NKD_CMP282, 1);
	CALL_NEAR(0x462B65, NKD_CMP283, 1);
	CALL_NEAR(0x4630AE, NKD_CMP284, 1);
	CALL_NEAR(0x46319E, NKD_CMP285, 1);

	
    //MOV
    CALL_NEAR(0x426390, NKD_MOV01,7);
    JMP_NEAR(0x448D95, NKD_MOV02, 2);
    JMP_NEAR(0x448E02, NKD_MOV03, 2);
    JMP_NEAR(0x44F24F, NKD_MOV04, 2);
    JMP_NEAR(0x44F967, NKD_MOV05, 5);
    JMP_NEAR(0x457138, NKD_MOV06, 2);
    JMP_NEAR(0x4591F4, NKD_MOV07, 5);
    JMP_NEAR(0x459239, NKD_MOV08, 2);

	
	//PUSH
	JMP_NEAR(0x4121BC, NKD_PUSH01);
	JMP_NEAR(0x442E72, NKD_PUSH02, 2);
	JMP_NEAR(0x442F1D, NKD_PUSH03, 2);
	JMP_NEAR(0x446972, NKD_PUSH04);
	JMP_NEAR(0x4473AF, NKD_PUSH05);
	JMP_NEAR(0x447DEE, NKD_PUSH06);
	JMP_NEAR(0x4484D7, NKD_PUSH07, 3);
}