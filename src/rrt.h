# pragma once

#include <iostream>
#include <vector>
#include "map.h"

using namespace std;

struct Node {

	int pos[3];
	Node* parent;
public:
	Node() {
		pos[0] = 0;
		pos[1] = 0;
		pos[2] = 0;
		parent = NULL;
	}
	Node(int x, int y, int t, Node* p) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = t;
		parent = p;
	}
};

class RRT {

	vector<Node*> nodelist;
	vector<vector <int>> final_path;

public:
	Map planner(Map m, int *start, int *end, int max_iterations);
	int generate_random(int max);
	Node* get_nearest_node(int x, int y);
	bool is_out_of_map(Map m, int x, int y);
	bool is_node_present_list(int x, int y);
	bool is_collide(Map m, int x, int y);
	float euclidean_dist(int a[2], int b[2]); 
	int* new_node_vector(Node n, int x, int y);
};