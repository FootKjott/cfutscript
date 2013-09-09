#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include "screen.h"

image capturescreenarea(int x, int y, int width, int height)
{
	image ret;
	BITMAPINFO bmi;
	HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
	HDC hdc_dest = CreateCompatibleDC(hdc);
	HBITMAP h_bitmap = CreateCompatibleBitmap(hdc, width, height);
	
	ret.width = width;
	ret.height = height;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = 0;

	SelectObject(hdc_dest, h_bitmap);
	BitBlt(hdc_dest, 0, 0, width, height, hdc, x + GetSystemMetrics(76), 
		y + GetSystemMetrics(77), 0x40000000 | 0x00CC0020);

	GetDIBits(hdc_dest, h_bitmap, 0, height, NULL, &bmi, DIB_RGB_COLORS);
	ret.size = bmi.bmiHeader.biSizeImage;
	ret.data = (unsigned char*)malloc(bmi.bmiHeader.biSizeImage);
	GetDIBits(hdc_dest, h_bitmap, 0, height, ret.data, &bmi, DIB_RGB_COLORS);

	DeleteObject(h_bitmap);
	DeleteDC(hdc_dest);
	DeleteDC(hdc);

	return ret;
}

image captureallscreens()
{
	return capturescreenarea(0, 0, GetSystemMetrics(78), GetSystemMetrics(79));
}

color getimagepixel(image img, int x, int y)
{
	int redindex;
	color ret;
	y = img.height - y - 1;
	redindex = (y * img.width + x) * 3;

	assert(0 <= redindex && redindex + 2 < img.size);
	
	ret.r = img.data[redindex];
	ret.g = img.data[redindex + 1];
	ret.b = img.data[redindex + 2];
	return ret;
}

void freeimage(image img)
{
	free(img.data);
}

color getscreenpixel(int x, int y)
{
	COLORREF c = GetPixel(CreateDC("DISPLAY", NULL, NULL, NULL), x, y);
	color ret;
	ret.b = c % 256;
	ret.g = (c / 256) % 256;
	ret.r = (c / 65536) % 256;
	return ret;
}

int coloristolerantof(color a, color b, unsigned char tolerance)
{
	return (abs(a.r - b.r) <= tolerance &&
			abs(a.g - b.g) <= tolerance &&
			abs(a.b - b.b) <= tolerance);
}

int waitforpxbase(int x, int y, color waitcolor, unsigned char tolerance, int timeout, int is)
{
	time_t start;
	time_t end;
	time(&start);
	
	while(is != coloristolerantof(waitcolor, getscreenpixel(x, y), tolerance))
	{
		usleep(100000);
		time(&end);
		if((int)difftime(end, start) > timeout)
		{
			return 0;
		}
	}
	return 1;
}

int waitforpx(int x, int y, color waitcolor, unsigned char tolerance, int timeout)
{
	return waitforpxbase(x, y, waitcolor, tolerance, timeout, 1);
}

int waitforpxnot(int x, int y, color waitcolor, unsigned char tolerance, int timeout)
{
	return waitforpxbase(x, y, waitcolor, tolerance, timeout, 0);
}
