#include "Tools.h"

Tools::Tools()
{
}

Tools::~Tools()
{
}

CHAR* Tools::Color(int color, const char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	char buff[MAXCHAR];
	sprintf(buff, "%s", Message);
	return buff;
}