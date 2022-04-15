#include <memory>
#include "KylinMazeGenerator.hpp"
#include "Maze.hpp"
#include "MazeFactory.hpp"


int main()
{
    std::unique_ptr<Maze> maze = MazeFactory{}.createMaze(10, 10);
    KylinMazeGenerator generator;
    generator.generateMaze(*maze);
    return 0;
    
}