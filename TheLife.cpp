#include "TheLife.h"
#include <stdio.h>
#include <stdlib.h>

TheLife::TheLife(int width, int height): width(width), height(height) {
	current = createGrid();
	next = createGrid();

	clear();
}

TheLife::~TheLife() {
	for(int i = 0; i < width; i++) {
		delete[] current[i];
		delete[] next[i];
	}
	delete[] current;
	delete[] next;
}

TheLife::Cell** TheLife::createGrid() {
	Cell **grid = new Cell*[width];
	for(int i = 0; i < width; i++) {
		grid[i] = new Cell[height];
	}

	return grid;
}

void TheLife::clear() {
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			setDead(x, y);
		}
	}

	cycle = 0;
}

void TheLife::generate() {
	for(int row = 0; row < width; row++) {
		for(int col = 0; col < height; col++) {
			current[row][col] = rand() % 2 == 1 ? Cell::Live : Cell::Dead;
		}
	}
}

void TheLife::setLive(int x, int y) {
	if(isPositionValid(x, y)) {
		current[x][y] = Cell::Live;
	}
}

void TheLife::setDead(int x, int y) {
	if(isPositionValid(x, y)) {
		current[x][y] = Cell::Dead;
	}
}

bool TheLife::isPositionValid(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool TheLife::isLive(int x, int y) {
	return isPositionValid(x, y) && current[x][y] == Cell::Live;
}

int TheLife::sumNeighboards(int x, int y) {
	return isLive(x-1, y-1) + isLive(x, y-1) + isLive(x+1, y-1)
		+ isLive(x-1, y) + isLive(x+1, y)
		+ isLive(x-1, y+1)	+ isLive(x, y+1) + isLive(x+1, y+1);
}

void TheLife::step() {
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			int sum = sumNeighboards(x, y);

			if(isLive(x, y)) {
				if(sum < 2 || sum > 3) {
					next[x][y] = Cell::Dead;
				} else {
					next[x][y] = Cell::Live;
				}
			} else {
				if(sum == 3) {
					next[x][y] = Cell::Live;
				} else {
					next[x][y] = Cell::Dead;
				}
			}
		}
	}

	// swap current and next generation
	Cell** tmp = current;
	current = next;
	next = tmp;
}

void TheLife::render() {
	cycle++;
	int lives = 0;

	// clear terminal page
	printf("\033c");

	printf("┌");
	for(int x = 0; x < width; x++) {
		printf("─");
	}
	printf("┐\n");

	for(int y = 0; y < height; y++) {
		printf("│");
		for(int x = 0; x < width; x++) {
			if(isLive(x, y)) {
				printf("♚");
				lives++;
			} else {
				printf(" ");
			}
		}
		printf("│\n");
	}

	printf("└");
	for(int x = 0; x < width; x++) {
		printf("─");
	}
	printf("┘\n");

	printf("cycle: %d\tlives: %d", cycle, lives);
	fflush(stdout);
}