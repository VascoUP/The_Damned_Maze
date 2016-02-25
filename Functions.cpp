#include "Functions.h"
#include "Utility.h"
#include "TheMaze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

const std::vector <std::string> Levels = { "Level1.txt", "Level2.txt", "Level3.txt" };

void Func::clrscr() //"apaga" o ecrã
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hCon, coordScreen);
}

void Func::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Func::setcolor(unsigned int color, unsigned int background_color) //muda a cor
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | background_color * 16 + color);
}

int Func::Convert_color(std::string cor_ins)
{
	unsigned int cor;
	unsigned int i = 0;
	while (i < cor_ins.length())
	{
		cor_ins[i] = toupper(cor_ins[i]);
		i++;
	}

	if (cor_ins == "PRETO" || cor_ins == "BLACK")
		cor = BLACK;
	else if (cor_ins == "AZUL_ESCURO" || cor_ins == "BLUE")
		cor = BLUE;
	else if (cor_ins == "VERDE_ESCURO" || cor_ins == "GREEN")
		cor = GREEN;
	else if (cor_ins == "CIANO_ESCURO" || cor_ins == "CYAN")
		cor = CYAN;
	else if (cor_ins == "VERMELHO_ESCURO" || cor_ins == "RED")
		cor = RED;
	else if (cor_ins == "MAGENTA_ESCURO" || cor_ins == "MAGENTA")
		cor = MAGENTA;
	else if (cor_ins == "CASTANHO" || cor_ins == "BROWN")
		cor = BROWN;
	else if (cor_ins == "CINZENTO_CLARO" || cor_ins == "LIGHTGRAY")
		cor = LIGHTGRAY;
	else if (cor_ins == "CINZENTO_ESCURO" || cor_ins == "DARKGRAY")
		cor = DARKGRAY;
	else if (cor_ins == "AZUL_CLARO" || cor_ins == "LIGHTBLUE")
		cor = LIGHTBLUE;
	else if (cor_ins == "VERDE_CLARO" || cor_ins == "LIGHTGREEN")
		cor = LIGHTGREEN;
	else if (cor_ins == "CIANO_CLARO" || cor_ins == "LIGHTCYAN")
		cor = LIGHTCYAN;
	else if (cor_ins == "VERMELHO_CLARO" || cor_ins == "LIGHTRED")
		cor = LIGHTRED;
	else if (cor_ins == "MAGENTA_CLARO" || cor_ins == "LIGHTMAGENTA")
		cor = LIGHTMAGENTA;
	else if (cor_ins == "AMARELO" || cor_ins == "YELLOW")
		cor = YELLOW;
	else if (cor_ins == "BRANCO" || cor_ins == "WHITE")
		cor = WHITE;
	else
	{
		std::cout << "Cores inseridas indisponiveis!" << std::endl;
		exit(EXIT_FAILURE); //porque falhou a cor
	}

	return cor;
}

//--------------------------------------------------------

bool Func::MakeBoard(char name, unsigned int color, std::string FileName)
{
	std::string ignore;
	int numLines, numColumns;
	bool sword = false, dragon = false;

	std::ifstream maze_file;
	maze_file.open(FileName);

	maze_file >> numLines >> numColumns;
	maze_file.ignore(1000, '\n');

	std::vector <std::vector <unsigned int>> m(numLines, std::vector <unsigned int>(numColumns));

	Position PosPlayer;

	maze_file >> PosPlayer.line >> PosPlayer.column;
	maze_file.ignore(1000, '\n');

	while (!maze_file.eof())
	{
		for (size_t l = 0; l < m.size(); l++)
		{
			for (size_t c = 0; c < m[l].size(); c++)
			{
				maze_file >> m[l][c];
				if (m[l][c] == 4)
					sword = true;
				else if (m[l][c] == 5)
					dragon = true;
			}

			maze_file.ignore(1000, '\n');
		}

		maze_file.ignore(1000, '\n');
	}

	maze_file.close();

	Maze labyrinth(name, color, m, PosPlayer, sword, dragon, numLines, numColumns);
	labyrinth.Game();

	if (labyrinth.killed())
		return false;

	clrscr();
	return true;
}

//-----------------------------------------------------------------------------

unsigned int Func::chooseColor()
{
	unsigned int option, color;

	setcolor(BLUE, BLACK);
	std::cout << "\n1 - BLUE";
	setcolor(MAGENTA, BLACK);
	std::cout << "\n2 - MAGENTA";
	setcolor(BROWN, BLACK);
	std::cout << "\n3 - BROWN";
	setcolor(LIGHTMAGENTA, BLACK);
	std::cout << "\n4 - LIGHTMAGENTA";
	setcolor(YELLOW, BLACK);
	std::cout << "\n5 - YELLOW";
	setcolor(WHITE, BLACK);
	std::cout << "\n\nOption: ";;
	std::cin >> option;

	switch (option)
	{
	case 1:
		color = BLUE;
		break;
	case 2:
		color = MAGENTA;
		break;
	case 3:
		color = BROWN;
		break;
	case 4:
		color = LIGHTMAGENTA;
		break;
	case 5:
		color = YELLOW;
		break;
	}

	return color;
}

void Func::beggining()
{
	setcolor(LIGHTRED, BLACK);
	gotoxy(28, 10);
	std::cout << "-- THE DAMNED MAZE --";
	Sleep(1000);
	clrscr();

	for (int y = 9; y >= 0; y--)
	{
		gotoxy(28, y);
		std::cout << "-- THE DAMNED MAZE --";
		Sleep(100);
		clrscr();
	}

	for (int x = 28; x >= 0; x--)
	{
		gotoxy(x, 0);
		std::cout << "-- THE DAMNED MAZE --";
		Sleep(100);
		clrscr();
		x--;
	}
}

void Func::playerInfo()
{
	char letter;
	unsigned int i = 0;
	bool killed = false;
	std::string Color;

	setcolor(LIGHTRED, BLACK);
	std::cout << "-- THE DAMNED MAZE --\n\n";
	setcolor(WHITE, BLACK);
	
	std::cout << "Choose a letter for your character: ";
	std::cin >> letter;
	std::cin.clear();
	std::cin.ignore(1000, '\n');

	unsigned int color = chooseColor();

	clrscr();

	for (size_t i = 0; i < Levels.size(); i++)
	{
		if (!MakeBoard(letter, color, Levels[i]))
		{
			std::cout << "\n\nGame Over!";
			Sleep(2000);
			killed = true;
			break;
		}
	}

	if (!killed)
	{
		std::cout << "\n Good Job!\n\n"
			<< "You exited the Maze sucessfully!\n"
			<< "You, my brave individual, deserve a cookie\n"
			<< "Go get it, it's in the kitchen!!!";
	}		
}

void Func::menu()
{
	char option;

	clrscr();

	setcolor(LIGHTRED, BLACK);
	std::cout << "-- THE DAMNED MAZE --\n\n";
	setcolor(WHITE, BLACK);

	std::cout << "1 - JOGAR\n"
		<< "2 - SAIR\n\n"
		<< "Opcao: ";

	std::cin >> option;
	std::cin.clear();
	std::cin.ignore(1000, '\n');

	switch (option)
	{
	case '1':
		clrscr();
		playerInfo();
		break;
	case '2':
		std::cout << std::endl << std::endl;
		exit(0);
	default:
		setcolor(LIGHTRED, BLACK);
		std::cout << "Atencao: ";
		setcolor(WHITE, BLACK);
		std::cout << "Selecione uma das opções acima";
		Sleep(500);
		clrscr();
		break;
	}
}