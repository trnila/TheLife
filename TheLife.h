#pragma once

class TheLife {
public:
	TheLife(int width, int height);
	~TheLife();

	void setLive(int x, int y);
	void setDead(int x, int y);
	bool isLive(int x, int y);

	void clear();
	void generate();
	void step();
	void render();

private:
	enum class Cell {Dead = 0, Live = 1};

	int height;
	int width;
	Cell **current;
	Cell **next;
	int cycle;

	Cell** createGrid();
	int sumNeighboards(int x, int y);
	bool isPositionValid(int x, int y);

};