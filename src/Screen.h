#pragma once

class Screen {
private:
bool* buffer;
int height;
int width;
int xyToIndex(int x, int y);
public:
	void draw();
	void clearSquare(int x, int y);
	void fillSquare(int x, int y);
	Screen(int size);
	~Screen();
};
