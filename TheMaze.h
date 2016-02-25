#ifndef TheMaze
	#define TheMaze

#include "ThePerson.h"
#include "Utility.h"
#include <vector>

class Maze{
public:
	Maze(char name, unsigned int color, std::vector <std::vector <unsigned int>> m, Position PosPlayer, bool sword, bool dragon, int numLines, int numColumns);

	bool hitWall(unsigned int move);
	bool finishMaze() const;
	bool killed();
	void getSword();

	void displaySquare(unsigned int info, bool Occupied) const;
	void displayInfo() const;
	void movePlayer();
	void displayMaze() const;

	void Game();
private:
	std::vector <std::vector <unsigned int>> maze;
	bool Sword, Dragon, killedDragon = false, hasSword = false;
	Person player;
};

#endif