#include "ArrowGame.h"

void ArrowGame::PrintBackground()
{
	PrintTime(3, 1);
	PrintScore(30, 1);
	PrintCombo(60, 1);
	Printedge();

}

void ArrowGame::Printedge()
{
	gotoxy(0, 8);
	printf("┏");
	for (int i = 1; i < 128; i++)
		printf("━");
	printf("┓");
	for (int y = 9; y < 24; y++)
	{
		gotoxy(0, y);
		printf("┃");
		gotoxy(128, y);
		printf("┃");
	}
	gotoxy(0, 24);
	printf("┗");
	for (int i = 1; i < 128; i++)
		printf("━");
	printf("┛");
}

void ArrowGame::SetArrowList()
{
	srand((unsigned)time(0));
	list.clear();
	int x = 2, y = 13;
	for (int i = 0; i < ARROW_SIZE; i++)
	{
		int dir = rand() % 4 + 1;
		Arrow ar;
		if (dir == 1) dir = UP;
		else if (dir == 2) dir = DOWN;
		else if (dir == 3) dir = LEFT;
		else if (dir == 4) dir = RIGHT;

		ar.SetDir(dir);
		ar.Setxy(x, y);
		list.push_back(ar);
		x+=14;
	}
}

void ArrowGame::PrintArrowList()
{
	for (int i = 0; i < ARROW_SIZE; i++)
	{
		list[i].PrintArrow();
	}
}

void ArrowGame::Play()
{
	system("mode con: cols=130 lines=30");

	//커서숨김
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &Cursor);
	printf("Press the enter\n");
	getchar();
	system("cls");

	thread time([&]() {Display_Countdown(13, 2); });	
	int check = 0;
	char key;
	this->cur = 0;
	
	do
	{
		if (!check)
		{
			_mutex.lock();
			PrintBackground();
			ClearBoard();	
			SetArrowList();
			PrintArrowList();
			Display_Score(40,2);
			Display_Combo(70, 2);
			_mutex.unlock();
			check = 1;
		}

		if (_kbhit())
		{
			key = _getch();
			if (key == -32)
				key = _getch();
			Scoring(key);
			Display_Score(40, 2);
			Display_Combo(70, 2);
		}
		
		if (cur == ARROW_SIZE)
		{
			cur = 0;
			check = 0;
		}
	} while (!gameover_check);

	system("cls");
	Display_Timeover();
	time.join();
}

void ArrowGame::Scoring(int key)
{	
	if (list[cur].isCorrect(key)) //정답
	{
		SKY;
		_mutex.lock();
		list[cur].PrintArrow();
		_mutex.unlock();
		Orgn;
		cur++;
		score += 1000 + (combo * 200);
		combo++;
	}
	else //오답
	{
		combo = 0;
	}
}

void ArrowGame::ClearBoard()
{
	for (int i = 9; i <= 23; i++)
	{
		gotoxy(2, i);
		for (int j = 1; j < 127; j++)
			printf(" ");
	}
}

int ArrowGame::Arrow::isCorrect(int key)
{
	if (this->dir == key) return 1;
	else return 0;
}

void ArrowGame::Arrow::PrintArrow()
{
	switch (dir)
	{
	case UP:
	{
		gotoxy(x + 4, y);
		printf("■\n");
		gotoxy(x + 2, y+1);
		printf("■■■\n");
		gotoxy(x, y+2);
		printf("■■■■■\n");
		gotoxy(x + 2, y+3);
		printf("■■■\n");
		gotoxy(x + 2, y+4);
		printf("■■■\n");
		gotoxy(x + 2, y+5);
		printf("■■■\n");
		break;
	}
	case DOWN:
	{
		gotoxy(x + 2, y);
		printf("■■■\n");
		gotoxy(x + 2, y+1);
		printf("■■■\n");
		gotoxy(x + 2, y+2);
		printf("■■■\n");
		gotoxy(x, y+3);
		printf("■■■■■\n");
		gotoxy(x + 2, y+4);
		printf("■■■\n");
		gotoxy(x + 4, y+5);
		printf("■\n");
		break;
	}
	case LEFT:
	{
		gotoxy(x+4, y+1);
		printf("■");
		gotoxy(x + 2, y+2);
		printf("■■■■■");
		gotoxy(x, y+3);
		printf("■■■■■■");
		gotoxy(x+2, y+4);
		printf("■■■■■");
		gotoxy(x + 4, y+5);
		printf("■");
		break;
	}
	case RIGHT:
	{
		gotoxy(x + 6, y+1);
		printf("■");
		gotoxy(x, y+2);
		printf("■■■■■");
		gotoxy(x, y+3);
		printf("■■■■■■");
		gotoxy(x , y+4);
		printf("■■■■■");
		gotoxy(x + 6, y+5);
		printf("■");
		break;
	}
	}
   
}
