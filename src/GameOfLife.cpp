// GameOfLife.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Screen.h"
#include "Board.h"
#include "Queue.h"
#include <unistd.h>
//#define OFFSHIFT 5

#define SIZE 5
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
	void print_alive();
};

GameOfLife::GameOfLife() {
	screen = new Screen(SIZE, SIZE);
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
	return;
}

void GameOfLife::setPredAlive(int x, int y) {
	int pos[2] = { x,y };
	if (!pred_alive->contains(pos)) {
		pred_alive->queue(pos);
	}
	pred_board->addPoint(x, y);
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
	ListNode *n = curr_alive->getFirst();
	while (n != NULL) {

		screen->fillSquare(n->pos[0], n->pos[1]);
		evalSquare(n->pos[0], n->pos[1]);
		n = n->n;
	}

	switchMaps();
}

void GameOfLife::birth(int x, int y){
	int pos[2] = { x,y };
	if (!curr_alive->contains(pos)) {
		curr_alive->queue(pos);
	}
	curr_board->addPoint(x, y);
}

bool GameOfLife::getStatus(int x, int y){
	return curr_board->checkPoint(x, y);
}

void GameOfLife::print_alive(){
	std::cout << *curr_alive;
}

int main() {
	GameOfLife* game = new GameOfLife();
	game->birth(1,2);
	game->birth(2,2);
	game->birth(3,2);

	/*
	game->birth(7, 7);
	game->birth(6, 7);
	game->birth(8, 7);
	game->birth(8, 6);
	game->birth(7, 5);
	*/
	/*
	game->birth(7, 7);
	game->birth(6, 7);
	game->birth(8, 7);
	game->birth(8, 6);
	game->birth(7, 5);
	*/
	/*
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
	*/
	
	// while (true) {
	game->screen->draw();
	for (int i = 0; i < 3; i++) {
		printf("Alive: \n");
		game->print_alive();
		printf("\n----------------\n");
		system("sleep 2");
		game->tick();
		game->screen->draw();
		
		//usleep(100 * 1000);
	}
	delete game;
}
