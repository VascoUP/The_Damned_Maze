#ifndef ThePerson
	#define ThePerson

#include "Utility.h"

class Person {
public:
	Person(char Name, unsigned int Color, Position Ppos, int numLines, int numColumns);
	Position ReturnPosition() const;
	char ReturnName() const;
	unsigned int ReturnColor() const;

	bool movePerson(unsigned int move);
private:
	char name;
	unsigned int color, Lines, Columns;
	Position position;
};
#endif