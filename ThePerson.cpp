#include "ThePerson.h"

Person::Person(char Name, unsigned int Color, Position Ppos, int numLines, int numColumns)
{
	name = Name;
	color = Color;
	position.column = Ppos.column;
	position.line = Ppos.line;
	Lines = numLines;
	Columns = numColumns;
}

Position Person::ReturnPosition() const
{
	Position PersonPosition;
	return PersonPosition = position;
}

char Person::ReturnName() const
{
	char playerName;
	return playerName = name;
}

unsigned int Person::ReturnColor() const
{
	unsigned int playerColor;
	return playerColor = color;
}

//---------------------------------

bool Person::movePerson(unsigned int move)
{
	switch (move)
	{
	case 1:
		if (position.column > 0)
		{
			position.column--;
			return true;
		}
		return false;		
	case 2:
		if (position.line > 0)
		{
			position.line--;
			return true;
		}
		return false;
		break;
	case 3:
		if (position.column < Columns - 1)
		{
			position.column++;
			return true;
		}
		return false;
		break;
	case 4: 
		if (position.line < Lines - 1)
		{
			position.line++;
			return true;
		}
		return false;
		break;
	}

	return false;
}