#include "PE_Patch.h"

INT32 jmp_addr;
static INT32 reg_aux;
static INT32 st_newmob_addr;
static INT32 st_newmob_size;

void DoIndirections()
{
	// ReadMessage Indirections
	JMP_NEAR(0x0040124E, NKD_ReadMessage);
	JMP_NEAR(0x00419555, NKD_ReadMessage_DecKey_1, 2);
	JMP_NEAR(0x00419578, NKD_ReadMessage_DecKey_2, 2);

	// AddMessage Indirections
	JMP_NEAR(0x00401221, NKD_AddMessage);
	JMP_NEAR(0x00419B89, NKD_AddMessage_EncKey_1, 2);

	// MobKilled Indirections
	JMP_NEAR(0x0045D58F, NKD_MobKilled_DropGold, 1);
	JMP_NEAR(0x004283CC, &NKD_MobKilled_EventDead, 2);
	JMP_NEAR(0x0045DCC1, &NKD_MobKilled_ControlDropItem, 2);	

	// Limite de crítico até 102%, e também acaba protegendo contra critical hack do whook
	CALL_NEAR(0x0040C3B8, &NKD_GetDoubleCritical_SetNewCriticalRate, 3);
	CALL_NEAR(0x00412567, &NKD_GetGetCurrentScore_FixCriticalRate, 5);

	// Retira o crash da divisão por 0 
	CALL_NEAR(0x00427BA1, &Fix_IntegerDivisionByZero, 3);		

	// Faz um HOOK na skill espectral, dando +1 de distância
	JMP_NEAR(0x0040549F, &NKD_GetMobAbility_Spectral);		
		
	// Controle de Evasão
	JMP_NEAR(0x004278DF, &NKD_GetParryRate_FixEvasion, 1);
	JMP_NEAR(0x00454841, &NKD_GetParryRate_FixEvasion_2, 1);    

	// Quando uma conexão é fechada
	JMP_NEAR(0x00459465, &NKD_CloseUser, 5);

	// Liberação para Celestiais comprarem skill's a qualquer level
	JMP_NEAR(0x004368AC, SkillLvCele);

	// Funções de tempo em tempo
	JMP_NEAR(0x00401082, &Server_ProcessMinTimer);

	// Limite de buffs
	JGE_NEAR(0x0044D80E, &FixAffects);
	JMP_NEAR(0x00401505, &CheckAffects);
	JMP_NEAR(0x00412543, &GetBuffer, 5);
	JMP_NEAR(0x00412580, &AfterAffects, 1);
	JMP_NEAR(0x00452467, &RemoveAffects);

	// Edições das Evocações
	st_newmob_addr = (int)mBuffer[0].Affects;
	st_newmob_size = sizeof(stBuffer);
	JMP_NEAR(0x00410EF7, NKD_StandingByProcessor_VerifyAbility_1, 5);
	JMP_NEAR(0x00412543, NKD_GetCurrentScore_VerifyAbility_1, 4);
	JMP_NEAR(0x00446273, &NKD_GenerateSummon_CanSummon, 4);

	// Score Bonus
	JMP_NEAR(0x00401E98, NKD_BASE_GetBonusSkillPoint, 2);

	// FixLevel	 	
	JMP_NEAR(0x00413495, &NKD_FixMaxLevel_CheckGetLevel, 1);	
	JMP_NEAR(0x0045B03E, &NKD_FixMaxLevel_MobKilled, 5); 
	JMP_NEAR(0x0042EA97, &NKD_FixMaxLevel_ProcessClientMessage, 8);
	JMP_NEAR(0x0044E305, &NKD_FixMaxLevel_ProcessDBMessage, 1);	
	JMP_NEAR(0x0041344D, &NKD_CheckGetLevel_FixClass, 2);
	JMP_NEAR(0x004135E7, &NKD_ControlCheckGetLevel, 2);

	// Desativa guerras originais
	JMP_NEAR(0x004013D9, (void*)0x0045792A); 
	JMP_NEAR(0x00457A20, (void*)0x00458921);

	// Correção no login na cidade
	JMP_NEAR(0x0044DFF4, &NKD_CorrectPositionGoWorld, 1);	
	JMP_NEAR(0x0044DF8C, (void*)0x0044DFF4, 3);
	CALL_NEAR(0x0044E248, &NKD_ProcessDBMessage_LoadBuffs, 1);

	// Controle dos teleportes
	JMP_NEAR(0x428905, &NKD_ControlTeleportPosition, 1);		

	// Correções nas refinações		
	JMP_NEAR(0x00404CEE, &NKD_CorrectRefs, 2);

	// Controle total do Campo de Treino
	JMP_NEAR(0x00423D31, &NKD_FixTrainningCamp, 4); 	

	// Faz um HOOK no Salve da TMSRV
	JMP_NEAR(0x0040158C, HKD_SaveUser);

	// Beast Master Controle
	*(INT8*)(0x004075EA + 6) = 5;
	JMP_NEAR(0x00407605, &NKD_Base_GetCurrentScore_FixTrans, 1);
	JMP_NEAR(0x00406F77, &NKD_Base_GetCurrentScore_FixFaceArch, 2);
	JMP_NEAR(0x0040774A, &NKD_Base_GetCurrentScore_FixEdenStatus, 2);	
	JMP_NEAR(0x00407765, &NKD_GetCurrentScore_SancTransform, 2);	
		
	// Controle de Status e Bloqueios
	JMP_NEAR(0x004014C9, HKD_BASE_GetCurrentScore_FixStatus);	
	JMP_NEAR(0x0041275E, &NKD_BASE_GetCurrentScore_BlockStatus, 8);	

	// Variados
	JNZ_NEAR(0x004346A8, NKD_ProcessClientMessage_ReadCommand);
	JMP_NEAR(0x0042FA12, &NKD_ProcessClientMessage_UseMountFeed, 1);	
	JMP_NEAR(0x004365E0, &NKD_ProcessClientMessage_ApplyBonus, 4);	
    JMP_NEAR(0x00422164, &NKD_DisableUnkPacket);	
	JMP_NEAR(0x0040F798, &NKD_DisableCheckPacket, 1);
	JMP_NEAR(0x0044AF6B, &NKD_CorrectRecvPacket, 6);
	JMP_NEAR(0x0044BA1D, &NKD_CorrectSleip, 3);	
	
	// Experiência acumulada
    JMP_NEAR(0x0045C5AE, &NKD_ExpInPesaAllArea, 1);

	// Reescreve a função GetParryRate
	JMP_NEAR(0x0040113B, GetParryRate);
		
	// Controle de EXP
	JMP_NEAR(0x0045C6EE, &NKD_MobKilled_ControlExp, 2);	
	JMP_NEAR(0x004282AC, &NKD_ProcessClientMessage_ControlEXP, 4);
	JMP_NEAR(0x0045C6D1, &NKD_MobKilled_FixClassExp, 1);

	//Class Info
	JMP_NEAR(0x409113, NKD_BASE_CanEquip_VerifClassInfo, 2);

	//Class Arch
	CALL_NEAR(0x409248, NKD_BASE_CanEquip_REQ_SIDC, 1);
	CALL_NEAR(0x409258, NKD_BASE_CanEquip_REQ_SIDC, 1);
	CALL_NEAR(0x409268, NKD_BASE_CanEquip_REQ_SIDC, 1);
	CALL_NEAR(0x409278, NKD_BASE_CanEquip_REQ_SIDC, 1);
	CALL_NEAR(0x409288, NKD_BASE_CanEquip_REQ_SIDC, 1);

	// Reescreve a função BASE_GetHpMp
	JMP_NEAR(0x00401307, BASE_GetHpMp);

	// Reescreve a função BASE_GetBonusScorePoint
	JMP_NEAR(0x0040133E, BASE_GetBonusScorePoint);

	// Reescreve a função RegenMob
	JMP_NEAR(0x00401587, RegenMob);

	// Reescreve a função BASE_RemoveParty
	JMP_NEAR(0x00401366, RemoveParty);

	// Comandos via hook
	JNZ_NEAR(0x00434D14, &NKD_ProcessClientMessage_Command);

	//Faz um hook no kick player do grupo
	//JMP_NEAR(0x0043846D, &NKD_ProcessClientMessage_KickPlayer, 4);

	JMP_NEAR(0x4323F4, &NKD_NewTrade, 2);

	// GetDamage
	 JMP_NEAR(0x4255D9, &NKD_ChangeDamage_3, 1);
	 // GetSkillDamage
	 JMP_NEAR(0x425B24, &NKD_ChangeDamage_1, 1);
	 // GetAttack
	 JMP_NEAR(0x41D8EB, &NKD_ChangeDamage_2); 

	// Desativa a função nativa do controle de mana
	JMP_NEAR(0x00407B3C, (void*)0x00407B99);

	// Correção na Jóia da Armazenagem
	JMP_NEAR(0x0433633, (void*)0x04337CC); // Eric Santos
	
	JMP_NEAR(0x0040F1DA, &NKD_CorrectDamageCele, 2);

	/*
	// ProcessSecTimer, ajeita o limite de hp/mp
	JMP_NEAR(0x00454E29, NKD_ProcessSecTimer_CorrectHpMpLimit_1, 2);
	JMP_NEAR(0x00454DF1, NKD_ProcessSecTimer_CorrectHpMpLimit_2, 2);
	// ProcessClientMessage, ajeita o limite de hp/mp
	JMP_NEAR(0x00424E7A, NKD_ProcessClientMessage_CorrectHpMpLimit_3, 2);
	JMP_NEAR(0x00425E8C, NKD_ProcessClientMessage_CorrectHpMpLimit_4, 2);
	JMP_NEAR(0x00425EC3, NKD_ProcessClientMessage_CorrectHpMpLimit_5, 2);
	JMP_NEAR(0x00423665, NKD_ProcessClientMessage_CorrectHpMpLimit_6, 2);
	*/
}

void __declspec(naked) NKD_CorrectDamageCele()
{
	static const DWORD dwContinue = 0x0040F1E1;
	_asm
	{
		MOVSX ECX, BYTE PTR SS : [EDX + 62h]

	    CMP ECX, CELESTIAL
		JGE lbl_IncressDamage

		MOVSX ECX, WORD PTR DS : [EDX + 040h]
		MOV DWORD PTR SS : [EBP - 0Ch], ECX

		JMP lbl_NormalExecute

		lbl_IncressDamage :
		MOVSX ECX, WORD PTR DS : [EDX + 040h]
        ADD ECX, 0C8h

	    MOV DWORD PTR SS : [EBP - 0Ch], ECX

		lbl_NormalExecute :
		CMP DWORD PTR SS : [EBP - 0Ch], 0
		JMP dwContinue
	}
}

void __declspec(naked) NKD_ProcessClientMessage_CorrectHpMpLimit_6()
{
	static DWORD dwContinue = 0x0042366C;
	// 00423665  |. 66:8B82 066A5C>MOV AX,WORD PTR DS:[EDX+15C6A06]
	__asm
	{
		MOV AX, WORD PTR DS:[EAX+15C6A06h]
		MOV EDX, DWORD PTR SS:[EBP - 0A0h]

		CMP EAX, EDX
		JL lbl_setZero

		JMP dwContinue

lbl_setZero:
		MOV EAX, DWORD PTR SS:[EBP+8]
		IMUL EAX, EAX, 0410h
		MOV WORD PTR DS:[EAX + 015C6A06h],0

		MOV EAX, 00423683h
		JMP EAX
	}
}

void __declspec(naked) NKD_ProcessClientMessage_CorrectHpMpLimit_5()
{
	static DWORD dwContinue = 0x00425ECA;
	//00425EC3  |. 0FBF88 046A5C0>|MOVSX ECX,WORD PTR DS:[EAX+15C6A04]
	__asm
	{
		MOVZX ECX, WORD PTR DS:[EAX+15C6A04h]
		MOV EDX, DWORD PTR SS:[EBP-2D0h]

		CMP ECX, EDX
		JL lbl_setZero

		JMP dwContinue

lbl_setZero:
		MOV EAX, DWORD PTR SS:[EBP-2CCh]
		IMUL EAX, EAX, 0410h
		MOV WORD PTR DS:[EAX + 015C6A04h],0

		MOV EAX, 00425EE3h
		JMP EAX
	}
}

void __declspec(naked) NKD_ProcessClientMessage_CorrectHpMpLimit_4()
{
	static DWORD dwContinue = 0x00425E99;
	// 00425E8C  |. 0FBF88 046A5C0>|MOVSX ECX,WORD PTR DS:[EAX+15C6A04]
	__asm
	{
		MOVZX ECX, WORD PTR DS:[EAX+15C6A04h]
		MOV EAX,DWORD PTR SS:[EBP-2D0h]

		CMP ECX, EAX
		JL lbl_setZero

		JMP dwContinue

lbl_setZero:
		MOV EAX, DWORD PTR SS:[EBP-2CCh]
		IMUL EAX, EAX, 0410h
		MOV WORD PTR DS:[EAX + 015C6A04h],0

		MOV EAX, 00425EB5h
		JMP EAX
	}
}

void __declspec(naked) NKD_ProcessClientMessage_CorrectHpMpLimit_3()
{
	static DWORD dwContinue = 0x00424E81;
	//00424E7A  |. 0FBF88 066A5C01 MOVSX ECX,WORD PTR DS:[EAX+15C6A06]
	__asm
	{
		MOVZX ECX,WORD PTR DS:[EAX + 15C6A06h]
		MOVSX EDX,WORD PTR SS:[EBP - 2A8h]

		CMP ECX,EDX
		JL lbl_setZero

		JMP dwContinue

		lbl_setZero:
		MOV EAX, DWORD PTR SS:[EBP + 8h]
		IMUL EAX, EAX, 0410h
		MOV WORD PTR DS:[EAX + 015C6A06h],0

		MOV EAX, 00424E97h
		JMP EAX
	}
}

void __declspec(naked) NKD_ProcessSecTimer_CorrectHpMpLimit_2()
{
	static DWORD dwContinue = 0x00454DFF;
	//00454DF1  |. 0FBF89 046A5C0>|MOVSX ECX,WORD PTR DS:[ECX+15C6A04]
	__asm
	{
		MOVZX ECX,WORD PTR DS:[ECX + 015C6A04h]
		MOVSX EDX,WORD PTR SS:[EBP - 0292h]

		CMP ECX,EDX
		JL lbl_setZero

		JMP dwContinue

		lbl_setZero:
		MOV EAX,DWORD PTR SS:[EBP - 0290h]
		IMUL EAX,EAX,0410h
		MOV WORD PTR DS:[EAX + 015C6A04h],0

		MOV EAX, 00454E1Bh
		JMP EAX
	}
}

void __declspec(naked) NKD_ProcessSecTimer_CorrectHpMpLimit_1()
{
	static DWORD dwContinue = 0x00454E37;
	//00454E29  |. 0FB788 046A5C0>|MOVZX ECX,WORD PTR DS:[EAX+15C6A04]
	__asm
	{
		MOVZX ECX, WORD PTR DS:[EAX + 015C6A04h]
		MOVSX EDX, WORD PTR SS:[EBP - 0292h]

		CMP ECX,EDX
		JL lbl_setZero

		JMP dwContinue

		lbl_setZero:
		MOV EAX,DWORD PTR SS:[EBP - 0290h]
		IMUL EAX,EAX,0410h
		MOV WORD PTR DS:[EAX + 015C6A04h],0

		MOV EAX,00454E4Ch
		JMP EAX
	}
}

void __declspec(naked) NKD_ChangeDamage_1()
{
	 static const int dwContinue = 0x00425B47;
	 static const int dwCall = 0x0040103C;
	 __asm
	 {
		MOV EDX, DWORD PTR SS:[EBP - 0x2AC]
		PUSH EDX

		MOV EAX, DWORD PTR SS:[EBP - 0x324]
		PUSH EAX

		MOV ECX, DWORD PTR SS:[EBP - 0x2D0]
		PUSH ECX

		CALL dwCall
		ADD ESP, 0x0C

		MOV DWORD PTR SS:[EBP - 0x2D0],EAX

		MOV EDX, DWORD PTR SS:[EBP - 0x2D0] // Damage
		PUSH EDX
		PUSH DWORD PTR SS:[EBP + 0x8] // attacker
		PUSH DWORD PTR SS:[EBP - 0x2CC] // ATTACKED

		CALL HKD_ChangeDamage

		MOV DWORD PTR SS:[EBP - 0x2D0], EAX

		JMP dwContinue
	 }
}

void __declspec(naked) NKD_ChangeDamage_2()
{
	 static const int dwContinue = 0x0041D90D;
	 static const int dwCall = 0x00401041;
	 __asm
	 {
		PUSH 0

		MOV EDX, DWORD PTR SS:[EBP + 0xC]
		IMUL EDX, EDX, 0x410
		MOVSX EAX, WORD PTR DS:[EDX + 0x15C69FA]
		PUSH EAX

		MOV ECX, DWORD PTR SS:[EBP - 0x50]
		PUSH ECX
		CALL dwCall
		ADD ESP, 0x0C

		MOV DWORD PTR SS:[EBP - 0x50], EAX

		MOV EDX, DWORD PTR SS:[EBP - 0x50] // Damage
		PUSH EDX
		PUSH DWORD PTR SS:[EBP + 0x8] // Attacker
		PUSH DWORD PTR SS:[EBP + 0xC] // Attacked
		CALL HKD_ChangeDamage

		MOV DWORD PTR SS:[EBP - 0x50], EAX //coloca o retorno da função HKD_ChangeDamage na devida variavel 

		JMP dwContinue
	 }
}

void __declspec(naked) NKD_ChangeDamage_3()
{
	 static const int dwContinue = 0x004255FC;
	 static const int dwCall = 0x00401041;
	 __asm
	 {
		MOV EDX, DWORD PTR SS:[EBP - 0x2AC]
		PUSH EDX
		MOV EAX, DWORD PTR SS:[EBP - 0x300]
		PUSH EAX
		MOV ECX, DWORD PTR SS:[EBP - 0x2D0]
		PUSH ECX

		CALL dwCall
		ADD ESP, 0x0C

		MOV DWORD PTR SS:[EBP - 0x2D0], EAX

		MOV EDX, DWORD PTR SS:[EBP - 0x2D0] // Damage
		PUSH EDX
		PUSH DWORD PTR SS:[EBP + 0x8]   // Attacker
		PUSH DWORD PTR SS:[EBP - 0x2CC] // Attacked

		CALL HKD_ChangeDamage

		MOV DWORD PTR SS:[EBP - 0x2D0], EAX

		JMP dwContinue
	 }
}

void __declspec(naked) NKD_NewTrade()
{
        static const int dwContinue = 0x00438D57;
    __asm
    {
        PUSH [EBP + 08h]
        PUSH [EBP + 0Ch]
        CALL NKD_SystemTrade
        JMP dwContinue
    }
}

__declspec(naked) void NKD_ProcessClientMessage_KickPlayer()
{      
   static int dwCall = 0x00401366;
    __asm
    {
            MOV ECX,DWORD PTR SS:[EBP + 0Ch]
            PUSH ECX
                       
            CALL HKD_ProcessClientMessage_KickPlayer
            ADD ESP,04h
 
            MOV EAX,00438D57h
            JMP EAX
    }
}

__declspec(naked) void NKD_BASE_CanEquip_VerifClassInfo()
{
	__asm
	{
		MOV EAX, DWORD PTR SS:[EBP + 0xC]
		SUB EAX, 64
		PUSH EAX
		CALL HKD_BASE_CanEquip
		ADD ESP, 4

		CMP EAX, 0
		JNZ lbl_ContinueFunc

lbl_ExitFunc:
		XOR EAX, EAX
		PUSH 0x409293
		RETN

lbl_ContinueFunc:
		PUSH 0x40911A
		RETN
	}
}

__declspec(naked) void NKD_BASE_CanEquip_REQ_SIDC()
{
	__asm
	{
		JLE lbl_ContinueFunc

		MOV EAX, DWORD PTR SS:[EBP + 0xC]
		SUB EAX, 64
		PUSH EAX
		CALL HKD_BASE_CanEquip
		ADD ESP, 4

		CMP EAX, 0
		JNZ lbl_ContinueFunc

lbl_ExitFunc:
		POP EAX
		XOR EAX, EAX
		PUSH 0x409293
		RETN

lbl_ContinueFunc:
		RETN
	}
}

__declspec(naked) void NKD_MobKilled_FixClassExp()
{
	static const INT32 mNOINC = 0x0045C6EE;
	static const INT32 mINCREMENT = 0x0045C6D7;
	__asm{
		MOV EAX, DWORD PTR SS:[EBP-020Ch]
		IMUL EAX,EAX,0410h	
		MOVSX ECX,BYTE PTR DS:[EAX+0015C6A19h] 

		CMP ECX, 01h
		JE lbl_Increment

		JMP mNOINC		

lbl_Increment:
		MOV EAX,DWORD PTR SS:[EBP-01F0h]
		JMP mINCREMENT	
	}
}

__declspec(naked) void NKD_MobKilled_ControlExp()
{
	static const INT32 mContinue = 0x0045C536;
	__asm
	{
		PUSH 0h
		PUSH DWORD PTR SS:[EBP-0220h]		
		PUSH DWORD PTR SS:[EBP-020Ch]
		CALL HKD_ControlEXP		
		JMP mContinue
	}
}

__declspec(naked) void NKD_ProcessClientMessage_ControlEXP()
{ 
	static const DWORD mContinue = 0x004282F9;
	__asm
	{
		PUSH 1h
		PUSH DWORD PTR SS:[EBP-02B0h]
		PUSH DWORD PTR SS:[EBP+08h]
		CALL HKD_ControlEXP	
		JMP mContinue
	}
}

__declspec(naked) void NKD_BASE_GetCurrentScore_BlockStatus()
{
	static const INT32 mContinue = 0x0041286E;
	__asm
	{
		PUSH DWORD PTR SS:[EBP + 08h]
		CALL HKD_BASE_GetCurrentScore_BlockStatus	
		JMP mContinue		
	}
}

__declspec(naked) void NKD_ExpInPesaAllArea()
{
    static const DWORD dwFail = 0x0045C5B4;
    static const DWORD dwContinue = 0x0045C627;
    __asm
    {
        PUSH DWORD PTR SS:[EBP - 0208h] // Y
        PUSH DWORD PTR SS:[EBP - 0204h] // X
        PUSH DWORD PTR SS:[EBP - 020Ch] // otherClientId
 
        CALL HKD_ExpInPesaAllArea
        ADD ESP,0Ch
 
        TEST EAX,EAX
        JE Fail
 
        JMP dwContinue
 
Fail:
        MOV EAX,DWORD PTR SS:[EBP - 020Ch]
        JMP dwFail
    }
}

__declspec(naked) void NKD_ProcessDBMessage_LoadBuffs()
{
	__asm{
		PUSH DWORD PTR SS:[EBP-0Ch]		
		CALL HKD_ProcessDBMessage_LoadBuffs
		MOV EDX, DWORD PTR SS:[EBP-0390h]
		RETN
	}
}

__declspec(naked) void NKD_Base_GetCurrentScore_FixEdenStatus()
{	
	static const INT32 mContinue = 0x00407765;
	static const INT32 foundEden = 0x0040770C;
	static const INT32 foundTita = 0x00407756;
	__asm{
		MOV EDX,DWORD PTR SS:[EBP+08h]
		MOVSX EAX,WORD PTR DS:[EDX+05Ch]

		CMP EAX, 19h
		JE lbl_Tita

		CMP EAX, 20h
		JE lbl_Eden

		JMP mContinue

lbl_Tita:
		JMP foundTita

lbl_Eden:
		CMP DWORD PTR SS:[EBP-0E4h],0
		JNZ lbl_FixStatus
		JMP mContinue

lbl_FixStatus:
		JMP foundEden
	}
}

void __declspec(naked) NKD_Base_GetCurrentScore_FixFaceArch()
{
	static const INT32 mContinue = 0x00406F8C;
	__asm{
		PUSH DWORD PTR SS:[EBP+08h]
		CALL HKD_Base_GetCurrentScore_FixFaceArch
		JMP mContinue
	}
}

void __declspec(naked) NKD_Base_GetCurrentScore_FixTrans()
{
	static const INT32 mContinue = 0x00407615;
	__asm
	{	
		PUSH DWORD PTR SS:[EBP-0C8h]
		PUSH DWORD PTR SS:[EBP+08h]
		CALL HKD_Base_GetCurrentScore_FixTrans
		JMP mContinue		
	}
}

__declspec(naked) void NKD_GetCurrentScore_SancTransform()
{ 
	__asm { 
		MOV EDX,DWORD PTR SS:[EBP + 08h] 
		MOVSX EAX,BYTE PTR DS:[EDX+ 061h]
		CMP EAX,03h 
		JGE lbl_noCalc
		MOV EDX,DWORD PTR SS:[EBP + 08h] 
		MOVSX EAX,WORD PTR DS:[EDX + 040h]
		MOV ECX,0040776Ch
		JMP ECX 
lbl_noCalc: 
		MOV DWORD PTR SS:[EBP - 0ECh],09h 
		MOV EAX,004077A3h 
		JMP EAX
	} 
}


void __declspec(naked) NKD_FixTrainningCamp(){
	static const INT32 jmpFail = 0x00438D57;
	static const INT32 mContinue = 0x00423DDD;

	__asm{
		PUSH DWORD PTR SS:[EBP+08h]
		CALL HKD_FixTrainningCamp

		CMP EAX, TRUE
		JE lbl_Continue

		JMP jmpFail

lbl_Continue:
		JMP mContinue
	}
}

void __declspec(naked) NKD_CorrectRefs()
{ 
	static const DWORD dwContinue = 0x00404DD2;
	_asm
	{
		PUSH DWORD PTR SS:[EBP+08h]		
		CALL HKD_GetItemSanc_FixSanc				
		JMP dwContinue
	}
}

__declspec(naked) void NKD_GetParryRate_FixEvasion()
{
	static const DWORD mContinue = 0x004278E5;
	_asm
	{
		PUSH EAX		
		PUSH DWORD PTR SS:[EBP+08h]
		PUSH DWORD PTR SS:[EBP-02CCh]

		CALL HKD_GetParryRate_FixEvasion		

		MOV DWORD PTR SS:[EBP - 0528h],EAX

		JMP mContinue
	}
}

__declspec(naked) void NKD_GetParryRate_FixEvasion_2()
{
	static const DWORD mContinue = 0x00454847;
	_asm
	{
		PUSH EAX
		PUSH DWORD PTR SS:[EBP-01B8h]
		PUSH DWORD PTR SS:[EBP-0290h]

		CALL HKD_GetParryRate_FixEvasion		

		MOV DWORD PTR SS:[EBP - 02D0h],EAX

		JMP mContinue
	}
}

__declspec(naked) void NKD_ControlTeleportPosition()
{ //by ptr0x
	__asm
	{
		LEA EDX,DWORD PTR SS:[EBP-0x810]
		PUSH EDX
		LEA EAX,DWORD PTR SS:[EBP-0x80C]
		PUSH EAX
		PUSH DWORD PTR SS:[EBP+0x8]
		CALL HKD_ControlTeleportPosition
		ADD ESP,0xC

		CMP EAX,-1
		JNZ 0x42891B

		LEA EDX,DWORD PTR SS:[EBP-0x810]
		MOV EAX, 0x042890B
		JMP EAX
	}
}

void __declspec(naked) NKD_CorrectSleip()
{ 
	static const DWORD dwContinue = 0x044BA25; 
	_asm { 
		MOVSX EAX,WORD PTR DS:[EDX] 
		CMP EAX,954h 
		JNZ dwCorrect 
		SUB EAX,939h 
		JMP dwContinue 
dwCorrect: 
		SUB EAX,938h 
		JMP dwContinue 
	} 
}

__declspec(naked) void NKD_MobKilled_ControlDropItem()
{
	__asm
	{
		PUSH DWORD PTR SS:[EBP-033Ch]
		PUSH DWORD PTR SS:[EBP+0Ch]

		CALL HKD_MobKilled_ControlDropItem		

		MOV jmp_addr, 0045DCF2h
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MobKilled_EventDead()
{
	__asm
	{
		MOV EDX,DWORD PTR SS:[EBP+8h]
		PUSH EDX

		MOV EAX,DWORD PTR SS:[EBP-056Ch]
		XOR ECX,ECX
		MOV CX,WORD PTR SS:[EBP+EAX*2h-0250h]
		PUSH ECX

		CALL HKD_MobKilled_EventDead	

		PUSH 0
		PUSH 0
		MOV EDX,DWORD PTR SS:[EBP+8h]

		MOV jmp_addr, 004283D3h
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_CorrectPositionGoWorld()
{
	static const DWORD dwJNZ = 0x0044E05A;
	static const DWORD dwContinue = 0x0044E01D;
	_asm
	{
		LEA EDX,DWORD PTR SS:[EBP - 380h]
		PUSH EDX
		LEA EDX,DWORD PTR SS:[EBP - 37Ch]
		PUSH EDX
		PUSH DWORD PTR SS:[EBP-0Ch]
		CALL HKD_CorrectPositionGoWorld

		ADD ESP, 0Ch

		MOV DWORD PTR SS:[EBP-0394h],EAX
		CMP DWORD PTR SS:[EBP-0394h],0

		JNZ Sucess
		JMP dwContinue
Sucess:
		JMP dwJNZ
	}
}

void __declspec(naked) NKD_ControlCheckGetLevel()
{ 
	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP-04h] //pointer	

		LEA ECX, WORD PTR DS:[EAX+02E0h] //points	
		PUSH ECX

		PUSH EAX

		CALL HKD_ControlCheckGetLevel				

		MOV jmp_addr, 00413650h
		JMP jmp_addr	
	}
}

__declspec(naked) void NKD_CheckGetLevel_FixClass()
{
	static const INT32 mContinue = 0x00413454;
	static const INT32 mFinish = 0x00413742;
	__asm{
		PUSH DWORD PTR SS:[EBP-04h]
		CALL HKD_CheckGetLevel_FixClass

		CMP EAX, 1
		JE lbl_Continue

		JMP mFinish

lbl_Continue:		
		MOV DWORD PTR SS:[EBP-08h],0h
		JMP mContinue
	}
}

__declspec(naked) void NKD_FixMaxLevel_CheckGetLevel()
{	//hook antigo e feio, mas funciona melhor que o novo '-'
	static int mExpTable = NULL;	
	static st_Mob *mob = NULL;
	static BYTE dwClass = NULL;

	__asm
	{		
		MOV EAX,DWORD PTR SS:[EBP-04h]
		MOV ECX,DWORD PTR DS:[EAX+01Ch]
		MOV DWORD PTR SS:[EBP-018h],ECX	

		MOV EAX,DWORD PTR SS:[EBP-04h]
		MOV mob, EAX
	}	

	dwClass = mob->Equip[0].EFV2;

	if(dwClass == MORTAL || dwClass == ARCH)
		mExpTable = (int)(exp_table[mob->bStatus.Level]);
	else
		mExpTable = (int)(exp_table_2[mob->bStatus.Level]);

	__asm 
	{
		MOV EAX, mExpTable
		MOV DWORD PTR SS:[EBP-01Ch], EAX
	}

	if(dwClass == MORTAL || dwClass == ARCH)
		mExpTable = (int)((exp_table)[mob->bStatus.Level+1]);
	else
		mExpTable = (int)((exp_table_2)[mob->bStatus.Level+1]);

	__asm
	{
		MOV EAX, mExpTable
		MOV DWORD PTR SS:[EBP-020h], EAX		
		MOV jmp_addr, 004134B5h
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_FixMaxLevel_MobKilled()
{
	static const INT32 mContinue = 0x0045B058;
	__asm{		
		PUSH 1h
		PUSH DWORD PTR SS:[EBP+08h]		
		CALL FixMaxLevel		
		JMP mContinue
	}
}

__declspec(naked) void NKD_FixMaxLevel_ProcessClientMessage()
{
	static const INT32 mContinue = 0x0042EAB6;
	__asm{
		PUSH 2h
		PUSH DWORD PTR SS:[EBP+08h]				
		CALL FixMaxLevel			
		JMP mContinue
	}
}

__declspec(naked) void NKD_FixMaxLevel_ProcessDBMessage()
{
	static const INT32 mContinue = 0x0044E32B;
	__asm{
		PUSH 3h
		PUSH DWORD PTR SS:[EBP-0Ch]				
		CALL FixMaxLevel		
		JMP mContinue
	}
}

void __declspec(naked) NKD_GenerateSummon_CanSummon() 
{ 
	static const DWORD dwCanSummon = 0x0044630E; 
	static const DWORD dwContinue = 0x0044627C; 
	_asm 
	{ 
		PUSH DWORD PTR SS:[EBP - 0Ch] 
		PUSH EAX 
		CALL HKD_GenerateSummon_CanSummon 
		
		ADD ESP,08h 

		TEST EAX,EAX 
		JNZ lbl_canSummon 

		JMP dwContinue 
lbl_canSummon: 
		JMP dwCanSummon 
	} 
}

__declspec(naked) void NKD_BASE_GetBonusSkillPoint()
{
	static const INT32 mContinue = 0x401EC3;
	__asm
	{
		PUSH DWORD PTR SS:[EBP + 8]
		CALL HKD_BASE_GetBonusSkillPoint
		ADD ESP, 4

		MOV DWORD PTR SS:[EBP - 4], EAX

		JMP mContinue
	}
}

__declspec(naked) void NKD_GetCurrentScore_VerifyAbility_1()
{	__asm
	{
		MOV EAX, DWORD PTR SS:[EBP - 4]
		SUB EAX, 0x15C69B8
		MOV ECX, 0x410
		XOR EDX, EDX
		DIV ECX

		MOV EDX, st_newmob_size
		IMUL EDX, EAX
		ADD EDX, st_newmob_addr

		PUSH EDX

		MOV jmp_addr, 0x41254D
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_StandingByProcessor_VerifyAbility_1()
{
	__asm
	{
		MOV EAX,DWORD PTR SS:[EBP-0x04]
		SUB EAX,0x015C69B8
		CDQ
		MOV ECX,0x410
		IDIV ECX

		MOV ECX,st_newmob_size
		IMUL EAX,ECX
		ADD EAX,st_newmob_addr
		MOVSX ECX,WORD PTR DS:[EAX]

		MOV jmp_addr, 0x0410F01
		JMP jmp_addr
	}
}

void __declspec(naked) NKD_CorrectRecvPacket()
{
	static const DWORD dwContinue = 0x0044AF71;
	__asm
	{
		MOV EAX, DWORD PTR SS:[EBP-54h]
		MOV DWORD PTR SS:[EBP-58h], EAX
		PUSH DWORD PTR SS:[EBP-40h]
		PUSH DWORD PTR DS:[EBP-54h]
		CALL HKD_CorrectRecvPacket
		JMP dwContinue
	}
}

__declspec(naked) void NKD_ProcessClientMessage_ApplyBonus()
{
	__asm{
		PUSH DWORD PTR SS:[EBP + 08h]
        PUSH DWORD PTR SS:[EBP - 1EE4h]
 
        CALL HKD_ProcessClientMessage_ApplyBonus
        ADD ESP,08h
 
        TEST EAX,EAX
        JE lbl_cantAdd
 
        MOV EAX,0043661Ah
        JMP EAX
 
lbl_cantAdd:
		MOV EAX,00436604h
        JMP EAX
	}
}

void __stdcall ZeroAffect(UINT16 ClientID)
{
	if(ClientID >= 1 && ClientID < MAX_PLAYER)
		for(UINT8 i = 0; i <= 15; i++)
			memset(&mBuffer[ClientID].Affects[i], 0, sizeof stAffects);	
}

void __declspec(naked) CheckAffects()
{
	__asm{
		PUSH EBP
		MOV EBP, ESP
		MOV EDX, DWORD PTR SS:[EBP+08h]
		CMP EDX, 00h
		JLE mERROR
		CMP EDX, 65h
		JGE mERROR
		LEA EAX, DWORD PTR DS:[mBuffer]
		IMUL EDX, EDX, 410h
		ADD EAX, EDX
		MOV ECX, 00h
	mLOOP:
		CMP ECX, 10h
		JGE mERROR
		CMP WORD PTR DS:[ECX*08h+EAX], 01Ch
		JE mSUCESSFUL
		INC ECX
		JMP mLOOP
	mERROR:
		XOR EAX, EAX
		JMP mRETURN
	mSUCESSFUL:
		MOV EAX, 01h
	mRETURN:
		MOV ESP, EBP
		POP EBP
		RETN
	}
}

void __declspec(naked) FixAffects(){
	static const UINT32 dwContinue = 0x0044D940;
	__asm{
		PUSH DWORD PTR SS:[EBP-0Ch]
		CALL ZeroAffect
		JMP dwContinue
	}
}

void __declspec(naked) RemoveAffects(){
	static const UINT32 dwContinue = 0x004505E2;
	__asm{
		LEA EAX, DWORD PTR DS:[mBuffer]
		MOV EDX, DWORD PTR SS:[EBP+08h]
		IMUL EDX, EDX, 410h
		MOV ECX, DWORD PTR SS:[EBP-70h]
		IMUL ECX, ECX, 08h
		ADD ECX, EDX
		MOV DWORD PTR DS:[ECX+EAX], 00h
		MOV WORD PTR DS:[ECX+EAX+04h], 00h
		PUSH DWORD PTR SS:[EBP+08h]
		CALL SendAffect
		MOV DWORD PTR SS:[EBP-04h], 01h
		JMP dwContinue
	}
}

void __declspec(naked) GetBuffer(){
	static const UINT32 dwContinue = 0x0041254D;
	__asm{
		MOV EAX, DWORD PTR SS:[EBP-04h]
		SUB EAX, 015C69B8h
		LEA EDX, DWORD PTR DS:[mBuffer]
		ADD EAX, EDX
		PUSH EAX
		JMP dwContinue
	}
}

void __declspec(naked) AfterAffects(){
	static const UINT32 dwContinue = 0x00412586;
	__asm{
		MOV BYTE PTR DS:[EDX+2E6h], AL
		MOV EAX, DWORD PTR SS:[EBP-04h]
		SUB EAX, 015C69B8h
		MOV ECX, 410h
		XOR EDX, EDX
		IDIV ECX
		PUSH EAX
		CALL SendAffect
		PUSH DWORD PTR SS:[EBP+08h]
		CALL SendAffect
		JMP dwContinue
	}
}

__declspec(naked) void NKD_ProcessClientMessage_UseMountFeed()
{
	__asm
	{
		PUSH EAX
		PUSH EDX
		PUSH ECX

		PUSH EAX
		MOV EAX, EBP
		SUB EAX, 0x1010
		PUSH EAX
		CALL HKD_ProcessClientMessage_UseMountFeed
		ADD ESP, 0x8
		
		POP ECX
		POP EDX
		POP EAX

		CDQ
		MOV ECX, 0x1E

		MOV jmp_addr, 0x42FA18
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_CloseUser()
{
	static const DWORD dwContinue = 0x0045946C;

	__asm
	{
		PUSH DWORD PTR SS:[EBP+08h]
		CALL HKD_CloseUser
		
		ADD ESP,04h

		MOV DWORD PTR SS:[EBP-08h], 00h
		MOV EAX,DWORD PTR SS:[EBP+08h]

		JMP dwContinue
	}
}

__declspec(naked) void NKD_GetMobAbility_Spectral()
{
	static const INT32 dwContinue = 0x00405733;
	__asm
	{
		MOV ECX, DWORD PTR SS:[EBP + 08h]

		TEST DWORD PTR DS:[ECX + 02DCh], 20000000h
		JE lbl_NoIncrease
  
		INC EAX

lbl_NoIncrease:

		JMP dwContinue
	}
}

__declspec(naked) void Fix_IntegerDivisionByZero()
{ 
	__asm
	{
		MOVSX ECX,WORD PTR DS:[EDX + 015C6A00h]
		CDQ

		TEST ECX,ECX
		JNZ Normal

		MOV ECX,01h
Normal:
		IDIV ECX

		MOV DWORD PTR SS:[EBP-544h],EAX
		RETN
	}
}

__declspec(naked) void NKD_GetDoubleCritical_SetNewCriticalRate()
{
	__asm
	{
		CALL Rand
		CDQ
		
		MOV ECX, 255
		
		IDIV ECX
		MOV ECX, EDX
		RETN
	}
}

__declspec(naked) void NKD_GetGetCurrentScore_FixCriticalRate()
{
	__asm
	{
		CMP EAX, 00h
		JE lbl_ContinueNormalExec
			
		CDQ
		MOV ECX, 04h
		IDIV ECX

lbl_ContinueNormalExec:
		MOV DWORD PTR SS:[EBP - 0Ch], EAX
		CMP DWORD PTR SS:[EBP - 0Ch], 0FFh
		RETN
	}
}

void __declspec(naked) NKD_DisableUnkPacket()
{
	__asm
	{
		MOV jmp_addr, 00438D57h
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_DisableCheckPacket()
{
	__asm
	{
		MOV EAX, 0
		MOV jmp_addr, 00410884h
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_MobKilled_DropGold()
{
	__asm
	{
		PUSH EAX
		PUSH [EBP + 0xC]
		CALL HKD_MobKilled_DropGold
		ADD ESP, 8

		MOV EAX, 0x45D646
		JMP EAX
	}
}


__declspec(naked) void NKD_AddMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HKD_AddMessage
	}
}

__declspec(naked) void NKD_ReadMessage()
{
	__asm
	{
		POP reg_aux

		PUSH ECX

		PUSH reg_aux

		JMP HKD_ReadMessage
	}
}

__declspec(naked) void NKD_AddMessage_EncKey_1()
{
	__asm
	{
		SAR ECX, 0x3
		SUB EAX, ECX
		MOV EDX,DWORD PTR SS:[EBP - 0x4]

		MOV jmp_addr, 0x419B90
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_ReadMessage_DecKey_1()
{
	__asm
	{
		SAR EDX, 0x3
		ADD ECX, EDX
		MOV EAX, DWORD PTR SS:[EBP - 0x28]
		
		MOV jmp_addr, 0x41955C
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_ReadMessage_DecKey_2()
{
	__asm
	{
		SHL EAX, 0x2
		SUB EDX, EAX
		MOV ECX, DWORD PTR SS:[EBP - 0x28]

		MOV jmp_addr, 0x41957F
		JMP jmp_addr
	}
}

__declspec(naked) void NKD_ProcessClientMessage_ReadCommand()
{
	static char *msgCmd = "day";
	static char *msgSend = "!#11  2";
	__asm
	{
		PUSH msgCmd

		MOV EAX, DWORD PTR SS:[EBP - 0x1A1C]
		ADD EAX, 0xC
		PUSH EAX

		MOV EAX, 0x464450
		CALL EAX
		ADD ESP, 8

		TEST EAX, EAX
		JNZ Exit_1

		PUSH msgSend
		PUSH DWORD PTR SS:[EBP + 8]
		CALL SendClientMessage
		ADD ESP, 8

		MOV jmp_addr, 0x438D57
		JMP jmp_addr

		RETN

Exit_1:
		MOV jmp_addr, 0x43480B
		JMP jmp_addr
	}
}

__declspec(naked) void SkillLvCele()
{
	int volta, vai, adr, adr2;
	_asm
	{
		MOV volta, 0x00438D57
		MOV vai, 0x004368C2
		MOV adr, 0x007D3CD8
		MOV adr2, 0x004010FF
		PUSH [EBP + 0x8]
		CALL BuySkillCele
		ADD ESP,4
		CMP EAX,1
		JE succ
		PUSH adr
		MOV EAX,DWORD PTR SS:[EBP+8]
		PUSH EAX
		CALL adr2
		ADD ESP,8
		JMP volta
succ:
		JMP vai
	}
}

__declspec(naked) void NKD_ProcessClientMessage_Command()
{
	static const DWORD dwContinue = 0x00438D57;
	__asm
	{
		PUSH DWORD PTR SS:[EBP - 01A1Ch]

		CALL HKD_ProcessClientMessage_Command
		ADD ESP,04h

		JMP dwContinue
	}
}
/*
__declspec(naked) void NKD_ProcessClientMessage_OpenRuneMenu()
{
 __asm
 {
  MOV ECX,DWORD PTR SS:[EBP - 010h]

  CMP DWORD PTR DS:[ECX + 0E8h],064h
  JNZ lbl_openNormalShop

  MOV DWORD PTR SS:[cRune],TRUE

lbl_openNormalShop:
  MOV ECX,DWORD PTR SS:[EBP - 010h]

  CMP DWORD PTR DS:[ECX + 0Ch],01h
  JNZ lbl_nextCheck

  MOV EAX,0048DA96h
  JMP EAX

lbl_nextCheck:
  MOV EAX,0048DC43h
  JMP EAX
 }
}*/