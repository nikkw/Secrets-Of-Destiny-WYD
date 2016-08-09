#include "GlobalData.h"

st_ItemList ItemList[6500];
st_MountData mountBuffer[50];

st_MountData *GetMountBuffer()
{
	return &mountBuffer[0];
}