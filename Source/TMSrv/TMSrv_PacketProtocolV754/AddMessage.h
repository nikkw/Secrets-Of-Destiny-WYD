// ---
// by ptr0x
// ---

#ifndef __ADD_MESSAGE_H__
#define __ADD_MESSAGE_H__

#include <Windows.h>
#include <stdio.h>

#include "PacketControl.h"

int __stdcall HKD_AddMessage(int instModule, PacketHeader *oldPacketBuffer, int packetSize);

#endif // __ADD_MESSAGE_H__