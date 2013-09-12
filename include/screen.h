#ifndef _SCREEN_H
#define _SCREEN_H

typedef struct 
{
	int width;
	int height;
	int size;
	unsigned char* data;
} image;

typedef struct 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color;

image capturescreenarea(int x, int y, int width, int height);

image captureallscreens();

color getimagepixel(image img, int x, int y);

void freeimage(image img);

color getscreenpixel(int x, int y);

color makecolor(unsigned char r, unsigned char g, unsigned char b);

int coloristolerantof(color a, color b, unsigned char tolerance);

int waitforpxbase(int x, int y, color waitcolor, unsigned char tolerance, int timeout, int is);

int waitforpx(int x, int y, color waitcolor, unsigned char tolerance, int timeout);

int waitforpxnot(int x, int y, color waitcolor, unsigned char tolerance, int timeout);

int waitforpxchange(int x, int y, unsigned char tolerance, int timeout);

#endif
