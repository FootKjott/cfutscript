#include <unistd.h>
#include <stdlib.h>
#include <windows.h>

int random(int min, int max)
{
	return rand() % (max - min) + min;
}

void leftclick(int useconds)
{
	POINT loc;
	GetCursorPos(&loc);
	mouse_event(0x0002, loc.x, loc.y, 0, 0);
	usleep(useconds);
	GetCursorPos(&loc);
	mouse_event(0x0004, loc.x, loc.y, 0, 0);
}

void rightclick(int useconds)
{
	POINT loc;
	GetCursorPos(&loc);
	mouse_event(0x08, loc.x, loc.y, 0, 0);
	usleep(useconds);
	GetCursorPos(&loc);
	mouse_event(0x10, loc.x, loc.y, 0, 0);
}

void moveto(int x, int y, int speed)
{
	POINT destination, loc;
	int xdif, ydif;
	destination.x = x;
	destination.y = y;
	GetCursorPos(&loc);

	while(destination.x != loc.x || destination.y != loc.y)
	{
		if(loc.x < destination.x)
		{
			loc.x++;
		}
		else if(loc.x > destination.x)
		{
			loc.x--;
		}

		if(loc.y < destination.y)
		{
			loc.y++;
		}
		else if(loc.y > destination.y)
		{
			loc.y--;
		}

		SetCursorPos(loc.x, loc.y);
		usleep(speed);
		GetCursorPos(&loc);
	}
}

void movefrom(int x, int y, int speed)
{
	POINT loc;
	GetCursorPos(&loc);
	moveto(loc.x + x, loc.y + y, speed);
}
