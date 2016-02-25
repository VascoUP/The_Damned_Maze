#include "TheMaze.h"
#include "Functions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

Maze::Maze(char name, unsigned int color, std::vector <std::vector <unsigned int>> m, Position PosPlayer, bool sword, bool dragon, int numLines, int numColumns) :player(name, color, PosPlayer, numLines, numColumns)
{
	maze = m;

	Sword = sword;
	Dragon = dragon;
}

//-----------------------------------------------------------------------------------------------------

bool Maze::hitWall(unsigned int move)
{
	Position playerPosition = player.ReturnPosition();

	switch (move)
	{
	case 1:
		if (playerPosition.column > 0 && maze[playerPosition.line][playerPosition.column - 1] == 0)// || (maze[playerPosition.line][playerPosition.column - 1] == 3 && Dragon && !killedDragon)))
			return true;
		return false;
	case 2:
		if (playerPosition.line > 0 && maze[playerPosition.line - 1][playerPosition.column] == 0)// || (maze[playerPosition.line - 1][playerPosition.column] == 3 && Dragon && !killedDragon)))
			return true;
		return false;
	case 3:
		if (playerPosition.column < maze[playerPosition.line].size() - 1 && maze[playerPosition.line][playerPosition.column + 1] == 0)// || (maze[playerPosition.line][playerPosition.column + 1] == 0 && Dragon && !killedDragon)))
			return true;
		return false;
	case 4:
		if (playerPosition.line < maze.size() - 1 && maze[playerPosition.line + 1][playerPosition.column] == 0)
			return true;
		return false;
	}

	return true;
}

bool Maze::finishMaze() const
{
	Position playerPosition = player.ReturnPosition();
	
	if (maze[playerPosition.line][playerPosition.column] == 3)
	{
		if (Dragon)
		{
			if (killedDragon)
				return true;
			else
			{
				Func::gotoxy(50, 10);
				Func::setcolor(RED, BLACK);
				std::cout << "YOU HAVE TO KILL THE DRAGON!";
				return false;
			}
		}
		else
			return true;
	}

	return false;
}

bool Maze::killed()
{
	Position playerPosition = player.ReturnPosition();

	if (maze[playerPosition.line][playerPosition.column] == 5)
	{
		if (hasSword)
		{
			killedDragon = true;
			maze[playerPosition.line][playerPosition.column] == 1;
			return false;
		}
		else
			return true;
	}
	return false;
}

void Maze::getSword()
{
	Position playerPosition = player.ReturnPosition();

	if (maze[playerPosition.line][playerPosition.column] == 4)
	{
		hasSword = true;
		maze[playerPosition.line][playerPosition.column] = 1;
	}
}

//-----------------------------------------------------------------------------------------------------

void Maze::displaySquare(unsigned int info, bool Occupied) const
{
	switch (info)
	{
	case 0:
		Func::setcolor(player.ReturnColor(), DARKGRAY);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << "/";
		break;
	case 1:
		Func::setcolor(player.ReturnColor(), GREEN);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << " ";
		break;
	case 2:
		Func::setcolor(player.ReturnColor(), RED);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << " ";
		break;
	case 3:
		Func::setcolor(player.ReturnColor(), RED);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << " ";
		break;
	case 4:
		Func::setcolor(player.ReturnColor(), LIGHTCYAN);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << " ";
		break;
	case 5:
		Func::setcolor(player.ReturnColor(), BROWN);
		if (Occupied)
			std::cout << player.ReturnName();
		else
			std::cout << " ";
		break;
	}
}

void Maze::displayInfo() const
{
	Func::setcolor(RED, BLACK);

	for (size_t i = 0; i < 25; i++)
	{
		Func::gotoxy(45, i);
		std::cout << "|";
	}

	if (Sword)
	{
		Func::gotoxy(50, 2);
		Func::setcolor(WHITE, BLACK);
		std::cout << "Sword: ";

		if (hasSword)
			std::cout << "equiped    ";
		else
			std::cout << "not equiped";
	}

	if (Dragon)
	{
		Func::gotoxy(50, 4);
		std::cout << "Dragon: ";

		if (killedDragon)
			std::cout << "killed    ";
		else
			std::cout << "not killed";
	}
}

void Maze::movePlayer()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;

	INPUT_RECORD irInput;

	ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

	switch (irInput.Event.KeyEvent.wVirtualKeyCode)
	{
	case VK_LEFT:
	case VK_NUMPAD4:
		if (!hitWall(1) && player.movePerson(1))
		{
			getSword();
			Position position = player.ReturnPosition();
			Func::gotoxy(position.column, position.line + 2);
			displaySquare(maze[position.line][position.column], true);
			Func::gotoxy(position.column + 1, position.line + 2);
			displaySquare(maze[position.line][position.column + 1], false);
		}
		break;
	case VK_UP:
	case VK_NUMPAD8:
		if (!hitWall(2) && player.movePerson(2))
		{
			getSword();
			Position position = player.ReturnPosition();
			Func::gotoxy(position.column, position.line + 2);
			displaySquare(maze[position.line][position.column], true);
			Func::gotoxy(position.column, position.line + 3);
			displaySquare(maze[position.line + 1][position.column], false);
		}
		break;
	case VK_RIGHT:
	case VK_NUMPAD6:
		if (!hitWall(3) && player.movePerson(3))
		{
			getSword();
			Position position = player.ReturnPosition();
			Func::gotoxy(position.column, position.line + 2);
			displaySquare(maze[position.line][position.column], true);
			Func::gotoxy(position.column - 1, position.line + 2);
			displaySquare(maze[position.line][position.column - 1], false);
		}
		break;
	case VK_DOWN:
	case VK_NUMPAD2:
		if (!hitWall(4) && player.movePerson(4))
		{
			getSword();
			Position position = player.ReturnPosition();
			Func::gotoxy(position.column, position.line + 2);
			displaySquare(maze[position.line][position.column], true);
			Func::gotoxy(position.column, position.line + 1);
			displaySquare(maze[position.line - 1][position.column], false);

		}
		break;
	}

	displayInfo();

	Func::setcolor(WHITE, BLACK);
}

void Maze::displayMaze() const
{
	Position PosPlayer = player.ReturnPosition();
	Func::setcolor(LIGHTRED, BLACK);
	std::cout << "-- THE DAMNED MAZE --\n\n";

	for (size_t l = 0; l < maze.size(); l++)
	{
		for (size_t c = 0; c < maze[l].size(); c++)
		{
			if (l == PosPlayer.line && c == PosPlayer.column)
				displaySquare(maze[l][c], true);
			else
				displaySquare(maze[l][c], false);
		}

		std::cout << std::endl;
	}

	displayInfo();

	Func::setcolor(WHITE, BLACK);
}

//-----------------------------------------------------------------------------------------------------

void Maze::Game()
{
	bool end = false;
	displayMaze();

	while (!end)
	{
		movePlayer();
		if (finishMaze())
		{
			Func::clrscr();

			Sleep(100);
			
			end = true;
		}
		else if (killed())
		{
			Func::clrscr();

			std::cout << "-- THE DAMNED MAZE --\n\n"
				<< "YOU WERE KILLED BY THE DRAGON WHILE\nTRYING TO EXIT THE MAZE";

			Sleep(1500);

			end = true;
		}
	}
}