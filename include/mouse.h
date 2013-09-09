#ifndef _MOUSE_H
#define _MOUSE_H

int random(int min, int max);

void leftclick(int useconds);

void rightclick(int useconds);

void moveto(int x, int y, int speed);

void movefrom(int x, int y, int speed);

#endif