#pragma once
#include "Game.h"

#define ARROW_SIZE 9
#define TIME_LIMIT 20

class ArrowGame : public Game
{

	class Arrow
	{
	private:
		int x;
		int y;
		int dir;

	public:
		Arrow() : dir(0) {}
		Arrow(int dir) { dir = dir; }
		void SetDir(int dir) { this->dir = dir; }
		int GetDir() { return dir; }
		void PrintArrow();
		int isCorrect(int ans);
		void Setxy(int x, int y) { this->x = x, this->y = y; }
	};

private:
	vector <Arrow> list;
	int cur;

public:
	ArrowGame() : cur(-1) {}
	void Play();
	void SetArrowList();
	void PrintArrowList();
	void PrintBackground();
	void Printedge();
	void ClearBoard();
	void Scoring(int key);
};