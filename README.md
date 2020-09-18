# Simple RRT Planner
#### Author : Ankur Bodhe <ankurbodhe@gmail.com>

---
Summary  
This is a simple RRT (Rapidly Random exploring Tree) planner program.
This is used for finding a path from start position to the end position in a constrained two dimensional space. The constraints are in form of obstacles in the two dimensional space.  
The program provides command line interface. User provides information about space dimensions, number of obstacles, obstacle co-ordinates, start position and the end position.

Usage
```
$> ./rrt_planner
```
User inputs:  
    Map size:  
    User is prompted to add the map. Provide map size in the following format: rows columns.   \
    Maximum map size is: 50 x 50  
    e.g.  
    ```
    $> Enter map dimensions: 20 20 
    ```  
    Number of Obstacles:  
    User is prompted to enter the number of obstacles.  
    e.g.  
    ```
     $> Enter number of obstacles: 5
    ```  
    Obstacle Coordinates:  
    User is prompted to enter obstacle coordinates in the following format: row_number column_number  
    e.g.  
    ```
	  $> Enter obstacle 1: 2 0
	  $> Enter obstacle 2: 7 8
    ```  
    Start Position:  
    User is prompted to enter the start position in the following format: row_number column_number  
    e.g.  
    ```
    $> Enter the start position : 2 4
    ```  
    Goal Position:  
    User is prompted to enter the goal position in the following format: row_number column_number  
    e.g.  
    ```
    $> Enter the goal position: 9 6
    ```  
    Number of iterations:  
    User is prompted to enter number of iterations which the planner should use to reach the goal.  
    eg.  
    ```
    $> Enter the number of iterations to to compute the planner: 1000  
    ```  
  
  Program outputs  
  The program outputs the following :  
  A grid map with the path, obstacles, start and goal positions.  
  Color legend for the visualization is as follows:  
  a) Green: Path  
  b) Red: Start Position  
  c) Blue: End Position  
  d) Black: Obstacles  
  e) Brown: Boundary for the map

Limitations:  
For demonstation and visualization purposes, the map size is restricted to a grid of 50x50. However, the algorithm runs for a map of any size (with different visualization schemes).  
Also, the step size is currently fixed at 1 pixel (or one grid block) movement. This is done for current visualization scheme. However, the algorithm can use different step size for other types of visualization schemes.  

When a path cannot be generated, the program prints following message:  
```
$> ****** path not found *******
```
### Installation and Building

  Clone the repository
  ```
	    git clone https://github.com/ankurbodhe/simple_RRT_planner.git
  ```
  
  Install openGL and GLUT dependancy
  if you are using Ubuntu system, use the following command
  ```
	    $> sudo apt-get install freeglut3-dev
  ```
  for other OS, please refer to the following link : https://www.prinmath.com/csci5229/misc/install.html  
  
  Build the code  
  ```
	    $> make
  ```  
  
  Execute the program
  ```
         $> ./rrt_planner
  ```
