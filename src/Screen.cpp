#include "Screen.h"
#include <assert.h>
#define WIDTH 15
#define HEIGHT 15
	
int Screen::xyToIndex(int x, int y){
	return y * this->height + x;
}

void Screen::draw(){
	std::system("clear");
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; x++){
			int index = xyToIndex(x,y);
			char c = 0;
			buffer[index] ? c = '#' : c = ' ';
			printf(c);
			buffer[index] = false;
		}
		printf("\n");
	}
}

void Screen::clearSquare(int x, int y) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	buffer[xyToIndex(x, y)] = false;
}

void Screen::fillSquare(int x, int y) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	buffer[xyToIndex(x, y)] = true;
	
}

Screen::Screen(int height, int width) {
	this->height = height;
	this->width = width;
	
	buffer = new(sizeof(bool) * height * width);
}

Screen::~Screen() {
	delete buffer;
}
