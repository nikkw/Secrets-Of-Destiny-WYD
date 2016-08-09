#include "DLLMain.h"


/*
int jmp_addr;

void __declspec(naked) NKD_CurrentHP1() //JMP_NEAR(0x411C01, NKD_CurrentHP1, 2);
{
	static int Hp;
	static int dwJg = 0x411C21;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x15C6A04]
		MOV Hp, EDX
		TEST Hp, Hp
		JG dwJg

		MOV jmp_addr, 0x411C0C
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP2() //JMP_NEAR(0x413CCA, NKD_CurrentHP2, 2);
{
	static int Hp;
	static int dwJg = 0x413CDA;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x15C6A04]
		MOV Hp, EAX
		TEST Hp, Hp
		JG dwJg

		MOV jmp_addr, 0x413CD5
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP3() //JMP_NEAR(0x423293, NKD_CurrentHP3, 2);
{
	static int Hp;
	static int dwJle = 0x4232B0;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x15C6A04]
		MOV Hp, EAX
		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x42329E
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP4() //JMP_NEAR(0x4233D2, NKD_CurrentHP4, 2);
{
	static int Hp;
	static int dwJle = 0x4233EF;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x4233DD
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP5() //JMP_NEAR(0x42354F, NKD_CurrentHP5, 2);
{
	static int Hp;
	static int dwJg = 0x42357B;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		TEST Hp, Hp
		JG dwJg

		MOV jmp_addr, 0x42355A
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP6() //JMP_NEAR(0x42444A, NKD_CurrentHP6, 2);
{
	static int Hp;
	static int dwJle = 0x424467;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x424455
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP7() //JMP_NEAR(0x424536, NKD_CurrentHP7, 2);
{
	static int Hp;
	static int dwJle = 0x424553;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x15C6A04]
		MOV Hp, EAX
		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x424541
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP8() //JMP_NEAR(0x4250DF, NKD_CurrentHP8, 2);
{
	static int Hp;
	static int dwJg = 0x42512C;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		TEST Hp, Hp
		JG dwJg

		MOV jmp_addr, 0x4250EA
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP9() //JMP_NEAR(0x425EEF, NKD_CurrentHP9, 2);
{
	static int Hp;
	static int dwJle = 0x425F33;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		MOV EAX, WORD PTR DS:[EDX + 0x15C6A00]

		CMP Hp, EAX
		JLE dwJle

		MOV jmp_addr, 0x425F0D
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP10() //JMP_NEAR(0x4261CB, NKD_CurrentHP10, 2);
{
	static int Hp;
	static int dwJg = 0x4261EC;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x15C6A04]
		MOV Hp, ECX
		TEST Hp, Hp
		JG dwJg

		MOV jmp_addr, 0x4261D6
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP01() // JMP_NEAR(0x0042DE71, NKD_MaxHP01, 2);
{
	static int Hp;
	static int dwJle = 0x0042DE96;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x15C6A00]
		MOV Hp, EAX

		CMP DWORD PTR SS:[EBP-0xE8C], Hp
		JLE dwJle

		MOV jmp_addr, 0x0042DE80
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP02() // JMP_NEAR(0x00446AE7, NKD_MaxHP02, 2);
{
	static int Hp;
	static int dwJle = 0x00446B09;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX+0x15C6A00]
		MOV Hp, EAX

		CMP ECX, Hp
		JLE dwJle

		MOV jmp_addr, 0x00446AF2
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP03() // JMP_NEAR(0x0045DFC6, NKD_MaxHP03, 2);
{
	static int Hp;
	static int dwJle = 0x0045E001;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x15C6A04]
		MOV Hp, EDX
		MOV ECX, WORD PTR DS:[EAX + 0x15C6A00]
		
		CMP Hp, ECX
		JLE dwJle

		MOV jmp_addr, 0x0045DFE1
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP04() // JMP_NEAR(0x00462E3A, NKD_MaxHP04, 2);
{
	static int Hp;
	static int dwJle = 0x00462E68;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x15C6A00]
		MOV Hp, EDX

		CMP DWORD PTR DS:[EAX + 0x007B32340], Hp
		JLE dwJle

		MOV jmp_addr, 0x00462E49
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP05() // JMP_NEAR(0x004630C2, NKD_MaxHP05, 2);
{
	static int Hp;
	static int dwJle = 0x004630FD;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x0015C6A04]
		MOV Hp, ECX
		MOV EDX, WORD PTR DS:[EAX + 0x0015C6A00]

		CMP Hp, EDX
		JLE dwJle

		MOV jmp_addr, 0x004630DD
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxMP01() // JMP_NEAR(0x0042DEFB, NKD_MaxMP01, 2);
{
	static int Mp;
	static int dwJle = 0x0042DF20;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x0015C6A02]
		MOV Mp, ECX

		CMP DWORD PTR SS:[EBP - 0xE8C], Mp
		JLE dwJle

		MOV jmp_addr, 0x0042DF0A
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxMP02() // JMP_NEAR(0x00462F7A, NKD_MaxMP02, 2);
{
	static int Mp;
	static int dwJle = 0x00462FA8;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x15C6A02]
		MOV Mp, EDX

		CMP DWORD PTR DS:[EAX + 0x007B32344], Mp
		JLE dwJle

		MOV jmp_addr, 0x00462F89
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxMP03() // JMP_NEAR(0x004631B2, NKD_MaxMP03, 2);
{
	static int Mp;
	static int dwJle = 0x004631ED;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x0015C6A06]
		MOV Mp, ECX
		MOV EDX, WORD PTR DS:[EAX + 0x0015C6A02]

		CMP Mp, EDX
		JLE dwJle

		MOV jmp_addr, 0x004631CD
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_MaxHP06() // JMP_NEAR(0x004265C5, NKD_MaxHP06, 2);
{
	static int Hp;
	static int dwJge = 0x004265E8;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x0015C6A04]
		MOV Hp, ECX
		MOV EDX, WORD PTR DS:[EAX + 0x0015C6A00]

		CMP Hp, EDX
		JGE dwJge

		MOV jmp_addr, 0x00425028
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP11() // JMP_NEAR(0x00427DFB, NKD_CurrentHP11, 2);
{
	static int Hp;
	static int dwJle = 0x00427E23;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x0015C6A04]
		MOV Hp, EAX

		CMP DWORD PTR SS:[EBP - 0x554], Hp
		JLE dwJle

		MOV jmp_addr, 0x00427E0A
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP12() // JMP_NEAR(0x00427E5D, NKD_CurrentHP12, 2);
{
	static int Hp;
	static int dwJle = 0x00427E85;

	__asm
	{
		MOV CX, WORD PTR DS:[EAX + 0x0015C6A04]
		MOV Hp, ECX

		CMP DWORD PTR SS:[EBP - 0x554], Hp
		JLE dwJle

		MOV jmp_addr, 0x00427E6C
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP13() // JMP_NEAR(0x0042801A, NKD_CurrentHP13, 2);
{
	static int Hp;
	static int dwJle = 0x00428266;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x0015C6A04]
		MOV Hp, EDX

		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x00428029
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP14() // JMP_NEAR(0x0045383C, NKD_CurrentHP14, 2);
{
	static int Hp;
	static int dwJle = 0x00453889;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x0015C6A04]
		MOV Hp, EAX

		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x00453847
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP15() // JMP_NEAR(0x0045C3B7, NKD_CurrentHP15, 2);
{
	static int Hp;
	static int dwJle = 0x0045C436;

	__asm
	{
		MOV AX, WORD PTR DS:[EDX + 0x0015C6A04]
		MOV Hp, EAX

		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x0045C3C2
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP16() // JMP_NEAR(0x0045C5A3, NKD_CurrentHP16, 2);
{
	static int Hp;
	static int dwJle = 0x0045C622;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x0015C6A04]
		MOV Hp, EDX

		TEST Hp, Hp
		JLE dwJle

		MOV jmp_addr, 0x0045C5AE
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentHP17() // JMP_NEAR(0x00462EDB, NKD_CurrentHP17, 2);
{
	static int Hp;
	static int dwJle = 0x00462EFB;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x0015C6A04]
		MOV Hp, EDX

		CMP Hp, DWORD PTR SS:[EBP - 0x8]
		JLE dwJle

		MOV jmp_addr, 0x00462EE7
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CurrentMP1() // JMP_NEAR(0x0046301B, NKD_CurrentMP1, 2);
{
	static int Mp;
	static int dwJle = 0x0046303B;

	__asm
	{
		MOV DX, WORD PTR DS:[ECX + 0x0015C6A06]
		MOV Hp, EDX

		CMP Hp, DWORD PTR SS:[EBP - 0x8]
		JLE dwJle

		MOV jmp_addr, 0x00463027
		JMP jmp_addr
	}
}

void MaxHpMp()
{
	// BaseScore - CurrentHp - 0x15C69E8
	//nem uma para alterar

	// BaseScore - CurrentMp - 0x15C69EA
	//nem uma para alterar

	// BaseScore - MaxHp - 0x15C69E4
	*(BYTE*)0x446569 = 0xB7;

	// BaseScore - MaxMp - 0x15C69E6
	*(BYTE*)0x447559 = 0xB7;

	// CurrentScore - CurrentHp - 0x15C6A04
	*(BYTE*)0x41D704 = 0xB7;
	*(BYTE*)0x41D739 = 0xB7;
	*(BYTE*)0x425006 = 0xB7;
	*(BYTE*)0x425E25 = 0xB7;
	*(BYTE*)0x425E8B = 0xB7;
	*(BYTE*)0x425EC4 = 0xB7;
	*(BYTE*)0x425F61 = 0xB7;

	// Hooks
	JMP_NEAR(0x411C01, NKD_CurrentHP1, 2);
	JMP_NEAR(0x413CCA, NKD_CurrentHP2, 2);
	JMP_NEAR(0x423293, NKD_CurrentHP3, 2);
	JMP_NEAR(0x4233D2, NKD_CurrentHP4, 2);
	JMP_NEAR(0x42354F, NKD_CurrentHP5, 2);
	JMP_NEAR(0x42444A, NKD_CurrentHP6, 2);
	JMP_NEAR(0x424536, NKD_CurrentHP7, 2);
	JMP_NEAR(0x4250DF, NKD_CurrentHP8, 2);
	JMP_NEAR(0x425EEF, NKD_CurrentHP9, 2);
	JMP_NEAR(0x4261CB, NKD_CurrentHP10, 2);
	JMP_NEAR(0x00427DFB, NKD_CurrentHP11, 2);
	JMP_NEAR(0x00427E5D, NKD_CurrentHP12, 2);
	JMP_NEAR(0x0042801A, NKD_CurrentHP13, 2);
	JMP_NEAR(0x0045383C, NKD_CurrentHP14, 2);
	JMP_NEAR(0x0045C3B7, NKD_CurrentHP15, 2);
	JMP_NEAR(0x0045C5A3, NKD_CurrentHP16, 2);
	JMP_NEAR(0x00462EDB, NKD_CurrentHP17, 2);

	JMP_NEAR(0x0046301B, NKD_CurrentMP1, 2);

	JMP_NEAR(0x0042DE71, NKD_MaxHP01, 2);
	JMP_NEAR(0x00446AE7, NKD_MaxHP02, 2);
	JMP_NEAR(0x0045DFC6, NKD_MaxHP03, 2);
	JMP_NEAR(0x00462E3A, NKD_MaxHP04, 2);
	JMP_NEAR(0x004630C2, NKD_MaxHP05, 2);
	JMP_NEAR(0x004265C5, NKD_MaxHP06, 2);

	JMP_NEAR(0x0042DEFB, NKD_MaxMP01, 2);
	JMP_NEAR(0x00462F7A, NKD_MaxMP02, 2);
	JMP_NEAR(0x004631B2, NKD_MaxMP03, 2);
}*/