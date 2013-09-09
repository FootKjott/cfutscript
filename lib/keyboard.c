#include <string.h>
#include <unistd.h>
#include <windows.h>
#include "keyboard.h"

void keydown(BYTE bVk)
{
	keybd_event(bVk, 0x45, 0, 0);
}

void keyup(BYTE bVk)
{
	keybd_event(bVk, 0x45, 2, 0);
}

void tapkey(BYTE bVk, int useconds)
{
	keydown(bVk);
	usleep(useconds);
	keyup(bVk);
}

void type(char* str) 
{
	int len = strlen(str);
	int shiftstate = (GetAsyncKeyState(0x10) == -32767);

	for(int i = 0; i < len; i++)
	{
		SHORT keycode = VkKeyScan(str[i]);
		if(keycode != -1)
		{
			if(keycode / 256 == 1)
			{
				if(!shiftstate)
				{
					keydown(0x10);
					shiftstate = 1;
				}
			}
			else
			{
				if(shiftstate)
				{
					keyup(0x10);
					shiftstate = 0;
				}
			}
			tapkey(keycode % 256, 20000);
		}
		usleep(20000);
	}
	if(shiftstate)
	{
		keyup(0x10);
	}
}
