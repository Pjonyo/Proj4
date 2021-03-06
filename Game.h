#pragma once
#include <iostream>
#include <thread>
#include <time.h>
#include <windows.h>
#include <mutex>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y);

#define TIME_LIMIT 20
#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define SKY SetConsoleTextAttribute(COL, 0x000b);
#define Orgn SetConsoleTextAttribute(COL, 0x0007)
#define RED SetConsoleTextAttribute(COL,0x000c );

class Game
{
protected:
	int score;
	int combo;
	bool gameover_check;
	mutex _mutex;

public:
	Game() : score(0),gameover_check(0),combo(0) {}
	bool isOver() { return gameover_check; }
	int Get_Score() { return score; }
	void Display_Countdown(int x, int y);
	void Display_Score(int x, int y);
	void Display_Combo(int x, int y);
	void Display_Timeover();
	virtual void Play();
	void PrintTime(int, int);
	void PrintScore(int, int);
	void PrintCombo(int, int);
	void PrintTimeover(int, int);
};

