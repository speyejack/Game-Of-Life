// GameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Screen.h"
#include "Board.h"
#include "Queue.h"
#define OFFSHIFT 5

#define SIZE 30
class GameOfLife {
private:
	Queue *curr_alive;
	Queue *pred_alive;
	Board *curr_board = new Board();
	Board *pred_board = new Board();

	void evalSquare(int x, int y);
	bool getStatus(int x, int y);
	void setPredDead(int x, int y);
	void setPredAlive(int x, int y);
	void switchMaps();
public:
	Screen *screen;
	GameOfLife();
	~GameOfLife();

	void tick();
	void birth(int x, int y);
};

GameOfLife::GameOfLife() {
	screen = new Screen(SIZE);
	curr_alive = new Queue();
	pred_alive = new Queue();
	/*for (int x = 0; x < SIZE;x++) {
		for (int y = 0; y < SIZE;y++) {
			curr_map[x][y] = false;
			pred_map[x][y] = false;
		}
	}*/

}

GameOfLife::~GameOfLife() {
	delete screen;
	delete curr_alive;
	delete pred_alive;
}

void GameOfLife::switchMaps() {
	delete curr_board;
	curr_board = pred_board;
	pred_board = new Board();

	delete curr_alive;
	curr_alive = pred_alive;
	pred_alive = new Queue();
}

void GameOfLife::setPredDead(int x, int y) {
	screen->clearSquare(x, y);
	return;
}

void GameOfLife::setPredAlive(int x, int y) {
	int pos[2] = { x,y };
	if (!pred_alive->contains(pos)) {
		pred_alive->queue(pos);
	}
	pred_board->addPoint(x, y);
	screen->fillSquare(x, y);
}

void GameOfLife::evalSquare(int x, int y) {
	bool status = getStatus(x, y);
	int alive = 0;
	for (int xc = -1; xc < 2; xc++) {
		for (int yc = -1; yc < 2; yc++) {
			if (!(xc == yc && xc == 0)) {
				if (getStatus(x + xc, y + yc))
					alive++;
				else if (status)
					evalSquare(x + xc, y + yc);
			}
		}
	}
	if (alive == 3 || (status && alive == 2))
		setPredAlive(x, y);
	else
		setPredDead(x, y);
}

void GameOfLife::tick() {
	//board->clearSquare(4, 2);
	ListNode *n = curr_alive->getFirst();
	while (n != NULL) {

		//std::cout << n->pos[0] << ":" << n->pos[1] << "\n";
		evalSquare(n->pos[0], n->pos[1]);
		n = n->n;
	}
	//board->fillSquare(4, 2);

	switchMaps();
}

void GameOfLife::birth(int x, int y){
	int pos[2] = { x,y };
	if (!curr_alive->contains(pos)) {
		curr_alive->queue(pos);
	}
	curr_board->addPoint(x, y);
	screen->fillSquare(x, y);
}

bool GameOfLife::getStatus(int x, int y){
	return curr_board->checkPoint(x, y);
}

int main() {
	//_CrtSetBreakAlloc(1000);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameOfLife* game = new GameOfLife();
	HDC screenDC = ::GetDC(0);
	::Rectangle(screenDC, 0, 0, 10, 10);
	ReleaseDC(0,screenDC);
	std::cin.ignore();

	/*
	game.birth(7, 7);
	game.birth(6, 7);
	game.birth(8, 7);
	game.birth(8, 6);
	game.birth(7, 5);
	*/
	/*
	game->birth(7, 7);
	game->birth(6, 7);
	game->birth(8, 7);
	game->birth(8, 6);
	game->birth(7, 5);
	*/
	
	game->birth(10 - OFFSHIFT, 12 - OFFSHIFT);
	game->birth(14 - OFFSHIFT, 12 - OFFSHIFT);
	game->birth(10 - OFFSHIFT, 11 - OFFSHIFT);
	game->birth(14 - OFFSHIFT, 11 - OFFSHIFT);
	game->birth(10 - OFFSHIFT, 10 - OFFSHIFT);
	game->birth(14 - OFFSHIFT, 10 - OFFSHIFT);
	game->birth(10 - OFFSHIFT, 13 - OFFSHIFT);
	game->birth(14 - OFFSHIFT, 13 - OFFSHIFT);
	game->birth(10 - OFFSHIFT, 14 - OFFSHIFT);
	game->birth(14 - OFFSHIFT, 14 - OFFSHIFT);
	game->birth(12 - OFFSHIFT, 14 - OFFSHIFT);
	game->birth(12 - OFFSHIFT, 10 - OFFSHIFT);
	std::cin.ignore();

	//while (true) {
	for (int i = 0; i < 40; i++) {
		Sleep(100);
		//std::cin.ignore();

		game->tick();
	}
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			game->screen->clearSquare(x, y);

		}
	}
	Sleep(10);
	delete game;
	

}