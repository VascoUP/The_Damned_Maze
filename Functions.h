#ifndef Functions
	#define Functions

#include <string>

class Func{
public:
	static void clrscr();
	static void gotoxy(int x, int y);
	static void setcolor(unsigned int color, unsigned int background_color);
	static int Convert_color(std::string cor_ins);

	static bool MakeBoard(char name, unsigned int color, std::string FileName);

	static unsigned int chooseColor();
	static void beggining();
	static void playerInfo();
	static void menu();
};
#endif 