#pragma once

class Map {

	int rows;
	int columns;
	char** map;

public:
	Map();
	Map(int r, int c);
	int get_rows();
	int get_columns();
	char get_state(int x, int y);
	void print();
	void update(int x, int y, char c);
	void add_obstacle(int x, int y);
};