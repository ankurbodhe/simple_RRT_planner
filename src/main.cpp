#include <iostream>
#include <GL/glut.h>
#include "map.h"
#include "rrt.h"

using namespace std;

static int MROWS = 50;
static int MCOLUMNS = 50;
static int map_rows;
static int map_columns;

char DMAP[50][50];

void initialize_graphics(){

	for(int i = 0; i < MROWS; i++){
		for(int j = 0; j < MCOLUMNS; j++)
			DMAP[i][j] = 'X';
	}

}

void generate_map_graphics(Map m){

	map_rows = m.get_rows();
	map_columns = m.get_columns();
	for(int i = 0; i < m.get_rows(); i++)
		for(int j = 0; j < m.get_columns(); j++)
			DMAP[j+1][i+1]=m.get_state(i,j);
}


void myInit(void){

	// making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.6, 0.6, 0.6, 1.0); 
      
    // making picture color green (in RGB mode), as middle argument is 1.0 
    glColor3f(0.0, 1.0, 0.0); 
      
    // breadth of picture boundary is 1 pixel 
    glPointSize(10.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-2, MROWS, MCOLUMNS, -3); 

}

void genrate_map(){

    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINTS); 
    float x, y; 

	for (int i =0; i < MROWS; i++){
		for(int j = 0; j < MCOLUMNS; j++){

			if(DMAP[i][j] == '1'){

				
				glColor3f(0.0, 0.0, 0.0);
				glVertex2i(i, j); 

			}

			if(DMAP[i][j] == 'X'){

				
				glColor3f(0.6, 0.6, 0.6);
				glVertex2i(i, j); 

			}
			if(DMAP[i][j] == '+'){

				glColor3f(0.0, 1.0, 0.0);
				glVertex2i(i, j); 

			}
			if(DMAP[i][j] == 'y'){

				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '*');

			}
			if(DMAP[i][j] == 'S'){

				glColor3f(1.0, 0.0, 0.0);
				glVertex2i(i, j); 

			}
			if(DMAP[i][j] == 'E'){

				glColor3f(0.0, 0.0, 1.0);
				glVertex2i(i, j); 
			}

		}
	}
	for(int i = 0; i <=map_columns; i++){
		glColor3f(0.4, 0.0, 0.0);
		glVertex2i(i, 0);
	}
	for(int i = 0; i <=map_columns; i++){
		glColor3f(0.4, 0.0, 0.0);
		glVertex2i(i, map_rows);
	}
	for(int i = 0; i <=map_rows; i++){
		glColor3f(0.4, 0.0, 0.0);
		glVertex2i(0, i);
	}
	for(int i = 0; i <=map_rows; i++){
		glColor3f(0.4, 0.0, 0.0);
		glVertex2i(map_columns, i);
	}


    glEnd(); 
    glFlush(); 

}

void render_map(int* argc, char** argv){

	glutInit(argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1000, 1000); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Circle Drawing"); 
    myInit(); 
      
    glutDisplayFunc(genrate_map); 
    glutMainLoop(); 

}

int main(int argc, char** argv) {


	int mx = 0, my = 0, x = 0, y = 0;
	int n_obs = 0, iter = 0, flag1 = 0, flag2 = 0, flag3 = 0;
	int sx = 0, sy = 0, ex = 0, ey = 0;


	while (true){
		
		cout << "\nEnter the map dimensions (for demostration purposes, the boundary condition for map size is (50,50) : ";
		cin >> mx >> my;

		if(mx >50 || my > 50)
			cout <<"Input map sizes are out of range, re enter map sizes";
		else
			break;
	}


    Map m(mx, my);
	RRT rrt;
    	
	int start[2] = {8,7};
	int end[2] = { 0, 0};
	
	
	
	
	//initialize a map
	initialize_graphics();

	//----------------------------------- add obstacles ----------------------------------------------//
	cout << "\nEnter the number of obstacles : ";
	cin >> n_obs;
	int **arr = new int*[n_obs];

	for (int i = 0; i< n_obs; i++){
		arr[i]= new int[2];
	}
	for (int i = 0; i < n_obs; i++)
	{
		cout << "\nEnter obstacle "<<(i+1)<<" : ";
		cin >> x >> y;
		while(true){

			flag1 = 0;
			flag2 = 0;
			if( i > 0 ){
				for(int k = 0; k < i; k++){
					if(arr[k][0]==x && arr[k][1]==y){
						flag1 = 1;
						break;
					}
				}
			}
			
			if(flag1 == 1){
				cout <<"\nObstacle already exists , re enter obstacle coordinates : ";
				cin >> x >> y;
			}
			else
				flag1 = 0;
			
			
			if ((x >= mx || x < 0) || (y >= my || y < 0)){
				cout <<"\nObstacle outside map , re enter obstacle coordinates : ";
				cin >> x >> y;
				flag1 = 1;
			}
			else
				flag2 = 0;
			
			if(flag1 == 0 && flag2 == 0)
				break;
			else
				continue;
						
		}
		m.add_obstacle(x, y);
		arr[i][0] = x;
		arr[i][1] = y;
		flag1 = 0;
		flag2 = 0;

	}
	//----------------------------- enter start and end goal ---------------------------------------//

	cout << "\nEnter the start position : ";
	cin >> sx >> sy;

	while(true){
		
		flag1 = 0;
		flag2 = 0;

		for(int k = 0; k < n_obs; k++){

			if(arr[k][0]==sx && arr[k][1]==sy){
				flag1 = 1;
				break;
			}
		}
		if(flag1 == 1){
			cout <<"\nStar position coincides with obstacle , re enter start position coordinates : ";
			cin >> sx >> sy;
		} 
		else
			flag1 = 0;
				
		if((sx >= mx || sx < 0) || (sy >= my || sy < 0)){
			cout << "\nStart position out of map, re enter start position : ";
			cin >> sx >> sy;
			flag2 = 1;
		}
		else
			flag2 = 0;	
		
		if(flag1 == 0 && flag2 == 0)
			break;
		else
			continue;
		
	}
	start[0] = sx;
	start[1] = sy;
	
	
	cout << "\nEnter the goal position : ";
	cin >> ex >> ey;
	while(true){
		
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		for(int k = 0; k < n_obs; k++){

			if(arr[k][0]==ex && arr[k][1]==ey){
				flag1 = 1;
				break;
			}
		}
		if(flag1 == 1){
			cout <<"\nGoal position coincides with obstacle , re enter goal position coordinates : ";
			cin >> ex >> ey;
		} 
		else
			flag1 = 0;
		
		if((ex > mx || ex < 0) || (ey > my || ey < 0)){
			cout << "\nGoal position out of map, re enter goal position : ";
			cin >> ex >> ey;
			flag2 = 1;
		}
		else
			flag2 = 0;
		
		if (ex == sx && ey == sy){
			cout <<"\nGoal position coincides with start position , re enter goal position coordinates : ";
			cin >> ex >> ey;
			flag3 = 1;
		}
		else
			flag3 = 0;
			
		if(flag1 == 0 && flag2 == 0 && flag3 == 0)
			break;
		else
			continue;
	}

	end[0] = ex;
	end[1] = ey;


	cout << "\nEnter the number of iterations to to compute the planner : ";
	cin >> iter;

	m = rrt.planner(m, start, end, iter);
	//m.print();
	
	generate_map_graphics(m);

	render_map(&argc, argv);
		
}