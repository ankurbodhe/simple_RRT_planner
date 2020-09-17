#include "map.h"
#include <iostream>

using namespace std;

Map::Map() {

	rows = 10;
	columns = 10;
	map = new char* [rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new char[columns];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = '0';
		}
	}
}

Map::Map(int r, int c) {
	rows = r;
	columns = c;
	map = new char* [rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new char[columns];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			map[i][j] = '0';
		}
	}
}

void Map::print() {

	for (int i = 0; i < rows; i++) {
		cout << "\n";
		for (int j = 0; j < columns; j++) {
			cout << map[i][j] << " ";
		}
	}

}

void Map::update(int x, int y, char c) {

	map[x][y] = c;

}

void Map::add_obstacle(int x, int y) {

	map[x][y] = '1';
}

int Map::get_rows() {
	return rows;
}

int Map::get_columns() {
	return columns;
}

char Map::get_state(int x, int y) {
	return map[x][y];
}