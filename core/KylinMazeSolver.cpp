#include "KylinMazeSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <vector>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver,KylinMazeSolver,"Kylin's Solver (Required)");

void KylinMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){      //solve a maze
    mazeSolution.restart();
    currentPos = mazeSolution.getStartingCell();
    initvisit(maze);
    recursiveSol(currentPos.first, currentPos.second, maze, mazeSolution);
}
		
void KylinMazeSolver::initvisit(const Maze& maze){      //initialize a vector contain all false that represent whether the cells in maze are visited or not
    visited.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); ++i){
        visited[i].resize(maze.getHeight());
    }
    for (int a = 0; a < maze.getWidth(); a++){
        for (int b = 0; b < maze.getWidth(); b++){
            visited[a][b] = false;
        }
    }
    visited[currentPos.first][currentPos.second] = true;
}
		
Direction KylinMazeSolver::moveNext(int& x, int& y, int move){      //use int to generate direction to move
    Direction d;
    switch(move){
        case 1:     //if move is 1 means direction goes down
            d = Direction::down;
            y++;
            break;
        case 2:     //if move is 2 means direction goes right
            d = Direction::right;
            x++;
            break;
        case 3:     //if move is 3 means direction goes up
            d = Direction::up;
            y--;
            break;
        case 4:     //if move is 4 means direction goes left
            d = Direction::left;
            x--;
            break;
    }
    return d;
}

bool KylinMazeSolver::wayToGo(int x, int y, const Maze& maze){      //check if there is a path to go, the path require no wall and the next cell not being visited
    int tempx = x;
	int tempy = y;
	for(int move = 1; move < 5; move++){
		direct = moveNext(x, y, move);
		if(!(maze.wallExists(tempx, tempy, direct)) && visited[x][y] == false){     //when there is no wall and the next cell not being visited means there is way to go
            nextMove = move;
			x = tempx;
			y = tempy;
			return true;
		}
        x = tempx;
        y = tempy;
	}
    return false;
}

void KylinMazeSolver::recursiveSol(int x, int y, const Maze& maze, MazeSolution& mazeSolution){     //the recusive function that used to solve the maze and get the solution
    currentPos = mazeSolution.getCurrentCell();
    if(mazeSolution.isComplete())
		return;
    if(wayToGo(x, y, maze)){        //if there is a way go, just go deep to find out if this is the solution
        direct = moveNext(x, y, nextMove);
        mazeSolution.extend(direct);
        currentPos = mazeSolution.getCurrentCell();
        visited[currentPos.first][currentPos.second] = true;
        recursiveSol(currentPos.first, currentPos.second, maze, mazeSolution);
    }else{      //if there is no way to go, means this path is no the solution of maze, then backup to previous cell to check if there is another way to go
        mazeSolution.backUp();
		currentPos = mazeSolution.getCurrentCell();
		recursiveSol(currentPos.first, currentPos.second, maze, mazeSolution);
    }
}