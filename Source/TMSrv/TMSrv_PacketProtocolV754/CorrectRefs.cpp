#include "DLLMain.h"

INT32 __stdcall HKD_GetItemSanc_FixSanc(st_Item* item)
{
	INT32 value = 0;		

	for(char i = 0; i < 3; i ++)				
		if(item->Effect[i].Index == 43 || (item->Effect[i].Index >= 116 && item->Effect[i].Index <= 125))					
			value = item->Effect[i].Value;	

	if(value < 230)
		value %= 10;
	else
	{
		value = 10 + ((value - 230) / 4);
		if(value >= 15)
			value += 3;
		if(value > 10)
			value += value - 5;
	}		

	return value;
}