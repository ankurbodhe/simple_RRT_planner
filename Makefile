# Makefile for compliling the project
# Author : Ankur Bodhe
# Date : 18 Sept 2020

CPP = g++
SDLFLAGS = sdl-config --cflags --libs
LIBS = -lGL -lGLU -lglut
SOURCES = src/rrt.cpp src/map.cpp src/main.cpp
DEST = rrt_planner

default:
	${CPP} -o ${DEST} ${SOURCES} ${LIBS} 

clean:
	rm -f ${DEST} core *.o
