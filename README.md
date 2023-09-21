# Maze problem

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Installation](#installation)


## General info

The program needs a txt file with informations about maze:

number of line numer of column
number of block cells
a list of block cells: row column
row and column for the start position
row and column for the end position

With this file the program can make 6 operation

1. Write in a file initial maze like a matrix with 0 - free cell and -1 - block cell.

2. Write in a file the maze after prelucration with Lee's algorithm. 

3. Write in a file a list of position in maze, the shortest path from start to end.

4. Create a visual application with the initial maze.

5. Create a visual application with the shortest path from start to end.

6. Create a visual application with the process that create the shortest path.

## Technologies
Project is write in: 
* C 
* GTK library for C 
* CSS for styling the application

## Installation
1. Clone the project

2. Install GTK library

```bash
sudo apt-get install libgtk-3-dev
```

3. Add the matrix file

4. Run the `main.c` file

```bash
gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0`
```
