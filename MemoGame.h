#pragma once
#include "Game.h"

#define TIME_LIMIT 30
#define FIRST_LINE_SIZE 12
#define SECOND_LINE_SIZE 11
#define THIRD_LINE_SIZE 10
#define KEY_SIZE FIRST_LINE_SIZE+SECOND_LINE_SIZE+THIRD_LINE_SIZE

#define START_SIZE 4
class MemoGame : public Game
{

	class Key
	{

	private:
		char ch;
		int x, y;


	public:
		Key() : ch(0), x(0), y(0) {}
		void Setchar(char ch) { this->ch = ch; }
		char GetChar() { return ch; }
		void SetXy(int x, int y) { this->x = x, this->y = y; }
		void PrintKey();


	};


private:
	vector <Key> list;
	vector <Key> ans;
	Key key[KEY_SIZE];
	int cur;

public:
	MemoGame() :cur(0) {}
	void Play();
	void PrintBackground();
	void Printedge();
	void PrintAllKey();
	void SetList(int);
	void DisplayList();
	int Scoring(char key);
	void ansreset();
};