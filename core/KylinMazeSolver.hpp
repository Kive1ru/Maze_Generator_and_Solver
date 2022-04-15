#ifndef KYLINMAZESOLVER_HPP
#define KYLINMAZESOLVER_HPP

#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include <vector>


class KylinMazeSolver: public MazeSolver{
	private:
		std::vector<std::vector<bool>> visited;//a vector to record whether the cells of maze being visited
		Direction direct = Direction::up;//a default direction
		int nextMove = 0;//indicate the direction to move
		std::pair<int,int> currentPos;//a pair that get the current cell position
		
	public:
		void solveMaze(const Maze& maze, MazeSolution& mazeSolution);//solve a maze
		void initvisit(const Maze& maze);//initialize a vector contain all false that represent whether the cells in maze are visited or not
		Direction moveNext(int& x, int& y, int move);//next move based on direction
		bool wayToGo(int x, int y, const Maze& maze);//Check if there is any direction that can go
		void recursiveSol(int x, int y, const Maze& maze, MazeSolution& mazeSolution);//the recusive function that used to solve the maze and get the solution                                                  
};

#endif