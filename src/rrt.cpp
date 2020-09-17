#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "rrt.h"



int RRT::generate_random(int max)
{
	int result = (rand() % (max));
	return result;
}

Node* RRT::get_nearest_node(int x, int y)
{
	//cout<<"\nI'm in nearest node";
	float min_dist = pow(10,7);
	float dist;
	Node *nearest_node = NULL;
	vector <float> distance_list;
	
	for (auto i = nodelist.begin(); i != nodelist.end(); ++i) {
	
		dist = sqrt((float)pow((x - (*i)->pos[0]),2) + (float)pow((y - (*i)->pos[1]),2));

		if (dist < min_dist) {
			min_dist = dist;
			nearest_node = (*i);
		}
	}

	//cout<<"\nI'm out nearest node\n"<<nearest_node<<nearest_node->pos[0]<<nearest_node->pos[1]<<nearest_node->parent;
	//cout << "min dist : "<<min_dist <<" x:"<<nearest_node->pos[0] <<" y:"<<nearest_node->pos[1]<<"\n";
	return nearest_node;
}

bool RRT::is_out_of_map(Map m, int x, int y)
{

	if ((x < 0 || x > m.get_rows()) || (y < 0 || y > m.get_columns()))
		return true;

	return false;
}

bool RRT::is_node_present_list(int x, int y)
{
	for (auto i = nodelist.begin(); i != nodelist.end(); ++i) {
		if ((x == (*i)->pos[0]) && (y == (*i)->pos[1]))
			return true;
	}
	return false;
}

bool RRT::is_collide(Map m, int x, int y)
{
	if (m.get_state(x, y) == '1')
		return true;

	return false;
}

float RRT::euclidean_dist(int a[2], int b[2])
{
	float result = sqrt(pow((b[0] - a[0]),2) + pow((b[1] - a[1]),2));
	return result;
}

int* RRT::new_node_vector(Node n, int x, int y) {


	int *new_pos = new int[3];

	float step, theta=0.0;
	float d = (float)(x - n.pos[0]);
	float nu = (float)(y - n.pos[1]);
	
	if (d != 0) {
		float k = (float)(y - n.pos[1]) / (float)(x - n.pos[0]);
		theta = atan(k);
	}
	
	if (d == 0 || nu == 0) {
		

		if (d == 0 && nu > 0) {

			new_pos[0] = n.pos[0];
			new_pos[1] = n.pos[1] + 1;
			new_pos[2] = 1;
		}
		if (d == 0 && nu < 0) {

			new_pos[0] = n.pos[0];
			new_pos[1] = n.pos[1] - 1;
			new_pos[2] = 1;
		}
		if (d > 0 && nu == 0) {

			new_pos[0] = n.pos[0] + 1;
			new_pos[1] = n.pos[1];
			new_pos[2] = 2;
		}
		if (d < 0 && nu == 0) {

			new_pos[0] = n.pos[0] - 1;
			new_pos[1] = n.pos[1];
			new_pos[2] = 2;
		}

	}
	else {

		if (d > 0 && nu > 0) {

			new_pos[0] = n.pos[0] + 1;
			new_pos[1] = n.pos[1] + 1;
			new_pos[2] = 3;
		}
		if (d > 0 && nu < 0) {

			new_pos[0] = n.pos[0] + 1;
			new_pos[1] = n.pos[1] - 1;
			new_pos[2] = 4;
		}
		if (d < 0 && nu < 0) {

			new_pos[0] = n.pos[0] - 1;
			new_pos[1] = n.pos[1] - 1;
			new_pos[2] = 3;
		}
		if (d < 0 && nu > 0) {

			new_pos[0] = n.pos[0] - 1;
			new_pos[1] = n.pos[1] + 1;
			new_pos[2] = 4;
		}

	}
	return new_pos;
}


Map RRT::planner(Map m, int *start, int *end, int max_iterations) {

	int rand_point[2];
	int* new_pos;
	int new_x, new_y, dir;
	Node* nearest_node;
	Node* current_node;
	Node* head_node = new Node(start[0], start[1],0, NULL);
	vector<int> path_point;


	// initialize the node list by putting the start position node in the node list
	nodelist.push_back(head_node);
	
	// run loop to start exploring the map until max iterations is reached

	for (int i = 1; i < max_iterations; i++) {

		// select a random node as a sample

		rand_point[0] = generate_random(m.get_rows());
		rand_point[1] = generate_random(m.get_columns());

		
		
		//check if random point gnerated is outside of the space of goal and start
		// if (((rand_point[0] >= start[0] && rand_point[0] <= end[0]) ||
		// 	(rand_point[0] <= start[0] && rand_point[0] >= end[0])) ||
		// 	((rand_point[1] >= start[1] && rand_point[1] <= end[1]) ||
		// 	(rand_point[1] <= start[1] && rand_point[1] >= end[1])))
		// {

		// }
		// else
		// 	continue;
		
		
		// find the nearest node to the random node
		nearest_node = get_nearest_node(rand_point[0], rand_point[1]);

		// create a new node to the tree in the direction of that random node
		new_pos = new_node_vector(*nearest_node, rand_point[0], rand_point[1]);
		
		new_x = new_pos[0];
		new_y = new_pos[1];
		dir   = new_pos[2];
		

		
		cout <<"\n"<< i <<"  :  "<< nodelist.size() << "\n";

		// check if the newly created node goes outside the map


		if (euclidean_dist(new_pos, nearest_node->pos) >= 1.45)
			continue;
            
		if (is_out_of_map(m, new_x, new_y))
			continue;


		// check if the newly created node already exists in the node list

		if (is_node_present_list(new_x, new_y))
			continue;

		// check if the newly created node collides with an obstacle

		if (is_collide(m, new_x, new_y))
			continue;


		// if the above conditions are not satisfied, add the new node to the node list
		Node *newnode = new Node(new_x, new_y, dir, nearest_node);

		if((*newnode).pos[2] == 1)
			m.update((*newnode).pos[0], (*newnode).pos[1], '-');
		else if((*newnode).pos[2] == 2)
			m.update((*newnode).pos[0], (*newnode).pos[1], '|');
		else if((*newnode).pos[2] == 3)
			m.update((*newnode).pos[0], (*newnode).pos[1], 'y');
		else
			m.update((*newnode).pos[0], (*newnode).pos[1], '/');


		nodelist.push_back(newnode);
		cout <<"\n"<<euclidean_dist((*newnode).pos, end)<<"\n";
						
		// check if the new node distance from the goal is less than step size
		if (euclidean_dist((*newnode).pos, end) >= 1 && euclidean_dist((*newnode).pos, end) <= 1.5) {
			cout << "\nAlmost there\n";
			//add the goal state to the final path vector
			path_point.push_back(end[0]);
			path_point.push_back(end[1]);
			final_path.push_back(path_point);
			//set the current node to last node in nodelist
			current_node = (nodelist.back());
			
			//add the position of the current node to the final path vector

			//run a loop to find the parent of the current node and keep appending the final path vector
			while (current_node != NULL) {
				path_point[0] = current_node->pos[0];
				path_point[1] = current_node->pos[1];
				final_path.push_back(path_point);
				current_node = (current_node->parent);
			}
			//reverse the final path vector
			reverse(final_path.begin(), final_path.end());

			//update the map with the elements of the final path vector
			for (int i = 0; i < final_path.size(); i++) {

				if(final_path[i][0]==start[0] && final_path[i][1]==start[1])
					m.update(final_path[i][0], final_path[i][1],'S');
				else if(final_path[i][0]==end[0] && final_path[i][1]==end[1])
					m.update(final_path[i][0], final_path[i][1],'E');
				else
					m.update(final_path[i][0], final_path[i][1],'+');
			}
			//m.print();
			break;
		}
		
	}

	if(final_path.size()==0){
		cout <<" **** Path not found *****";
	}

	for (int j = 0; j < nodelist.size(); j++) {
		cout << "\n" << (*nodelist[j]).pos[0] << " , " << (*nodelist[j]).pos[1] << (*nodelist[j]).pos[2];	
	}


	cout << "\n------Final path-------";
	for (int k = 0; k < final_path.size(); k++) {
		cout << "\n" << "(" << final_path[k][0]<< "," << final_path[k][1] << ")";
	}

	

	// return the map
	return m;
}