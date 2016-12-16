#pragma once
#include <Windows.h>
class Screen {
private:
	HWND console;
	HRGN getRect(int x, int y);
public:
	void clearSquare(int x, int y);
	void fillSquare(int x, int y);
	Screen(int size);
	~Screen();
};
