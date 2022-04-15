#include <ics46/factory/DynamicFactory.hpp>
#include "KylinMazeGenerator.hpp"
#include <random>
#include <vector>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,KylinMazeGenerator,"Kylin's Algorithm (Required)");

void KylinMazeGenerator::generateMaze(Maze& maze){      //generate a maze
	maze.addAllWalls();
    int startW = randomStartW(maze);
    int startH = randomStartH(maze);
    initvisit(startW, startH, maze);
    recusiveGen(startW, startH, maze);
}

void KylinMazeGenerator::initvisit(int startW, int startH, Maze& maze){     //initialize a vector contain all false that represent whether the cells in maze are visited or not
    visited.resize(maze.getWidth());
    for (int i = 0; i < maze.getWidth(); ++i){
        visited[i].resize(maze.getHeight());
    }
    for (int a = 0; a < maze.getWidth(); a++){
        for (int b = 0; b < maze.getWidth(); b++){
            visited[a][startH] = false;
        }
    }
    visited[startW][startH] = true;
}

int KylinMazeGenerator::randomMove(){       //generate random number from 1-4 that use for moveNext function to represent up down left right
    std::random_device d;
    std::default_random_engine gen{d()};
    std::uniform_int_distribution<int> dist{1,4};
    return dist(gen);
}

int KylinMazeGenerator::randomStartW(Maze& maze){       //generate random number within the range of maze width to indicate x coordinate of the starting point
    int width = maze.getWidth()-1;
    std::random_device d;
    std::default_random_engine gen{d()};
    std::uniform_int_distribution<int> dist{0, width};
    return dist(gen);
}

int KylinMazeGenerator::randomStartH(Maze& maze){       //generate random number within the range of maze width to indicate y coordinate of the starting point
    int height = maze.getHeight()-1;
    std::random_device d;
    std::default_random_engine gen{d()};
    std::uniform_int_distribution<int> dist{0, height};
    return dist(gen);
}

Direction KylinMazeGenerator::moveNext(int& x, int& y, int move){       //use random number from randomMove() to generate direction to move
    Direction d;
    switch(move){
        case 1:     //if move is 1 means direction goes up
            d = Direction::up;
            y--;
            break;
        case 2:     //if move is 2 means direction goes down
            d = Direction::down;
            y++;
            break;
        case 3:     //if move is 3 means direction goes left
            d = Direction::left;
            x--;
            break;
        case 4:     //if move is 4 means direction goes right
            d = Direction::right;
            x++;
            break;
    }
    return d;
}

bool KylinMazeGenerator::checkAllVisit(Maze& maze){     //check if all cells in maze being visited, if there is one not being visited, return false
    for (int a = 0; a < maze.getWidth(); a++){
        for (int b = 0; b < maze.getHeight(); b++){
            if(visited[a][b] == false){
                return false;
            }
        }
    }
    return true;
}

bool KylinMazeGenerator::checkAround(int x, int y, Maze& maze){     //check for current cell see if surround cells being visited or not.
    int height = maze.getHeight()-1;                                //If there is a cell not being visited, return false
    int width = maze.getWidth()-1;
    if(x == 0){
		if(y == 0){
			if(!visited[x][y+1] || !visited[x+1][y]){
                return false;
            }
		}else if(y == height){
            if(!visited[x][y-1] || !visited[x+1][y]){
                return false;
            }
		}else{
			if(!visited[x][y+1] || !visited[x][y-1] || !visited[x+1][y]){
				return false;
            }
		}
	}else if(y==0){
		if(x == width){
			if(!visited[x][y+1] || !visited[x-1][y])
				return false;
		}else{
			if(!visited[x][y+1] || !visited[x+1][y] || !visited[x-1][y])
				return false;
		}
	}else if(x == width){
		if(y == height){
			if(!visited[x][y-1] || !visited[x-1][y])
				return false;
		}else{
			if(!visited[x][y+1] || !visited[x][y-1] || !visited[x-1][y])
				return false;
		}
	}else if(y == height){
		if(!visited[x][y-1] || !visited[x+1][y] || !visited[x-1][y])
			return false;
	}else{
		if(!visited[x][y+1] || !visited[x][y-1] || !visited[x+1][y] || !visited[x-1][y]){
			return false;
		}	
	}
	return true;
}

bool KylinMazeGenerator::checkDirect(int x, int y, Maze& maze, Direction d){        //check if there is a direction is vaild to break the wall and avoid out of bound
    int height = maze.getHeight()-1;
    int width = maze.getWidth()-1;
    if(x != 0 && d == Direction::left){
		return true;
    }else if(x != width && d == Direction::right){ 
		return true;
	}else if(y != 0 && d == Direction::up){
		return true;
	}else if(y != height && d == Direction::down){
		return true;
	}else{
        return false;
    }
}

void KylinMazeGenerator::recusiveGen(int x, int y, Maze& maze){     //recusive function that generate the path
    while(!checkAround(x,y,maze)){
        int step = randomMove();
        int tempx = x;
	    int tempy = y;
        direct = moveNext(x, y, step);
        if(checkDirect(tempx, tempy, maze, direct) && !visited[x][y]){      //if the next break is in bound and the cell is not visited, then remove the wall
            maze.removeWall(tempx, tempy, direct);
            visited[x][y] = true;
            recusiveGen(x, y, maze);
        }else{
            x = tempx;
            y = tempy;
            recusiveGen(x, y, maze);
        }
    }
}