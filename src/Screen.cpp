#include "Screen.h"
#define WIDTH 15
#define HEIGHT 15
	

HRGN Screen::getRect(int x, int y) {
	return CreateRectRgn(x*WIDTH + 1, y*HEIGHT + 1, (x + 1)*WIDTH-1, (y + 1)*HEIGHT-1);
}

void Screen::clearSquare(int x, int y) {
	HDC dc = GetDC(console);
	FillRgn(dc, getRect(x, y), CreateSolidBrush(RGB(0, 0, 0)));

	ReleaseDC(console, dc);
	// FillRgn(dc, getRect(x, y));
}

void Screen::fillSquare(int x, int y) {
	HDC dc = GetDC(console);
	//Rectangle(dc, x*WIDTH+1, y*HEIGHT+1, (x + 1)*WIDTH-1, (y + 1)*HEIGHT-1);
	FillRgn(dc, getRect(x, y), CreateSolidBrush(RGB(255, 255, 255)));

	ReleaseDC(console, dc);
}

Screen::Screen(int size) {
	console = GetConsoleWindow();
	ShowCursor(false);
	HDC dc = GetDC(console);
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			RECT rec = { x*WIDTH, y*HEIGHT, (x + 1)*WIDTH, (y + 1)*HEIGHT };
			DrawEdge(dc, &rec, BDR_SUNKENINNER, BF_RECT);
		}
	}
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	ReleaseDC(console, dc);
}

Screen::~Screen() {
	//std::cin.ignore();
}
