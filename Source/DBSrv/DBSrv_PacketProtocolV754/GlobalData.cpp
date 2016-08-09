#include "GlobalData.h"

st_ItemList itemlistBuffer[6500];

st_ItemList *GetItemlistBuffer()
{
	return &itemlistBuffer[0];
}