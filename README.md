# Simple RRT Planner
#### Author : Ankur Bodhe

---
This is program is a simple RRT planner that takes in an input map with dimensions from the user, the number of obstacles and obstacle coordinates and the start and goal positions.

The program provides an interactive command line method for accepting inputs from the user.

The program outputs the following :

A grid map with the path, obstacles, start and goal positions. The color legend for the visualization is as follows:  
a) Green : Path  
b) Red   : Start Position  
c) Blue  : End Position  
d) Black : Obstacles  
e) Brown : Boundary for the map

Limitation :  
For demonstation and visualization purposes, the map size is restricted to a grid of 50x50. However, the algorithm runs for a map of any size (with different visualization schemes)

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
