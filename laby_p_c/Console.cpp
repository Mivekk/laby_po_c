#include "Console.h"

Console::Console()
    : h(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

Console::~Console()
{
}

void Console::textColor(int textColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

void Console::backgroundColor(int backgroundColor)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);

    int textColor = csbiInfo.wAttributes % 16;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor * 16 + textColor);
}

void Console::gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void Console::write(int x, int y)
{
    gotoxy(x, y);
    textColor(WHITE);
    backgroundColor(BLACK);
}
