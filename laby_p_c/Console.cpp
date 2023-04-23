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

void Console::setup(int x, int y)
{
    gotoxy(x, y);
    textColor(WHITE);
    backgroundColor(BLACK);
}

void Console::addLog(const std::string& text)
{
    logs.push_back(text);
}

void Console::displayLogs()
{
    int elementsToDelete = logs.size() - MAX_LOGS;
    if (elementsToDelete > 0) {
        logs.erase(logs.begin(), logs.begin() + elementsToDelete - 1);
    }

    int startX = 70, startY = 2;
    setup(startX, startY);
    for (int i = 0; i < MAX_LOGS && i < logs.size(); i++) {
        gotoxy(startX, startY + i);
        std::cout << "                                                    ";
        gotoxy(startX, startY + i);
        std::cout << logs[i];
    }
}
