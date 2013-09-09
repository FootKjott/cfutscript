#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <windows.h>

void keydown(BYTE bVk);

void keyup(BYTE bVk);

void tapkey(BYTE bVk, int useconds);

void type(char* str);

#endif