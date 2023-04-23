#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

#define BLACK		0
#define BLUE		1
#define GREEN		2
#define CYAN		3
#define RED			4
#define MAGENTA		5
#define BROWN		6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA	13
#define YELLOW		14
#define WHITE		15

#define MAX_LOGS 16

class Console
{
public:
	Console();
	~Console();

	void textColor(int textColor);
	void backgroundColor(int backgroundColor);
	void gotoxy(int x, int y);
	void setup(int x, int y);

	void addLog(const std::string& text);
	void displayLogs();

private:
	HANDLE h;

	std::vector<std::string> logs;
};

