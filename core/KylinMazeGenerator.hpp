#ifndef KYLINMAZEGENERATOR_HPP
#define KYLINMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>


class KylinMazeGenerator: public MazeGenerator{
	private:
		std::vector<std::vector<bool>> visited;//a vector to record whether the cells of maze being visited
		Direction direct = Direction::up;//a default direction

	public:
		void generateMaze(Maze& maze) override;//generate a maze
		void initvisit(int startW, int startH, Maze& maze);//initialize a vector contain all false that represent whether the cells in maze are visited or not
		int randomMove();//generate random number from 1-4 to represent up down left right
		int randomStartW(Maze& maze);//generate random number within the range of maze width to indicate x coordinate of the starting point
		int randomStartH(Maze& maze);//generate random number within the range of maze width to indicate y coordinate of the starting point
		Direction moveNext(int& x, int& y, int move);//next move based on direction
		bool checkAllVisit(Maze& maze);//check if all cells in maze being visited
		bool checkAround(int x, int y, Maze& maze);//check if the genePath has no way to go
		bool checkDirect(int x, int y, Maze& maze, Direction d);//check if there is a direction is vaild to break the wall and avoid out of bound
		void recusiveGen(int x, int y, Maze& maze);//recusive function that generate the path
};

#endif