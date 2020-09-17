# Simple RRT Planner
#### Author : Ankur Bodhe

---
This is program is a simple RRT planner that takes in an input map with dimensions from the user, the number of obstacles and obstacle coordinates and the start and goal positions.

The program provides an interactive command line method for accepting inputs from the user.

The program takes in the following inputs :  
1) Map size :  
  The user is prompted to add the map by providing the size in the following format : <rows> <columns>  
  Example :  
  ```
  Enter the map dimensions (for demostration purposes, the boundary condition for map size is (50,50) : 20 20 
  ```
2) Number of Obstacles 
  The user is prompted to enter the number of obstacles.  
  Example:  
  ```
  Enter the number of obstacles : 5
  ```  
3) Obstacle Coordinates  
  The user is prompted to enter the obstacle coordinates in the following format : <row number> <colummn number>  
  Example:  
  ```
  Enter obstacle 1 : 2 0
  ```
4) Start Position  
  The user is prompted to enter the start position in the following format : <row number> <column number>  
  Example:  
  ```
  Enter the start position : 5 4
  ```  
5) Goal Position
  The user is prompted to enter the goal position in the following format : <row number> <column number>  
  Example  
  ```
  Enter the goal position : 2 3
  ```
6) Number of iterations to run the planner:  
  The user is prompted to enter the number of iterations the planner should run.  
  Example
  ```
  Enter the number of iterations to to compute the planner : 1000  
  ```


The program outputs the following :

A grid map with the path, obstacles, start and goal positions. The color legend for the visualization is as follows:  
a) Green : Path  
b) Red   : Start Position  
c) Blue  : End Position  
d) Black : Obstacles  
e) Brown : Boundary for the map

Limitation :  
For demonstation and visualization purposes, the map size is restricted to a grid of 50x50. However, the algorithm runs for a map of any size (with different visualization schemes).  
Also, the step size is currently fixed at 1 pixel(or one grid block) movement. This is again done for current visualization scheme. Howver, the algorithm runs for a step size for other types of visualization schemes.

When a path cannot be generated, the program prints the following on the shell command line :
```
****** path not found *******
```


### Installation and Building the code 

1) Clone the repository 
```
git clone https://github.com/ankurbodhe/simple_RRT_planner.git
```
2) Install openGL and GLUT dependancy

if you are running on an Ubuntu system, run the following command
```
sudo apt-get install freeglut3-dev
```
3) Build the code
```
make
```
4) Execute the program
```
./rrt_planner
```
