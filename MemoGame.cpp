#include "MemoGame.h"

#define fflush FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

void MemoGame::Play()
{
	system("mode con: cols=130 lines=30");

	//커서숨김
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &Cursor);

	printf("게임설명 + 카운트다운 추가예정 (엔터누르면 시작)");
	getchar();
	system("cls");

	_mutex.lock();
	PrintBackground();
	_mutex.unlock();

	thread time([&]() {Display_Countdown(13, 2, TIME_LIMIT); });
	int check=0;
	char key;
	int num = 4;
	do
	{
		if (!check)
		{
			cur = 0;
			Display_Score(40, 2);
			Display_Combo(70, 2);
			SetList(num + (combo / 3));
			ansreset();
			DisplayList();
			fflush;
			check = 1;
		}
		if (_kbhit())
		{
			
			key = _getch();
			check = Scoring(key);
			Display_Score(40, 2);
			Display_Combo(70, 2);
		}
		if (cur == num)
		{
			cur = 0;
			check = 0;
			combo++;
		}
	} while (!gameover_check);

	Display_Timeover(30, 5);
	time.join();
	
}

void MemoGame::ansreset()
{
	int size = ans.size();
	for (int i = 0; i < size; i++)
	{
		_mutex.lock();
		ans[i].PrintKey();
		_mutex.unlock();
	}
	ans.clear();
}

int MemoGame::Scoring(char key)
{
	int ret = 0;
	key = toupper(key);
	gotoxy(3, 25);
	printf("%c", key);
	if (list[cur].GetChar() == key)
	{
		score += 1000 + (combo * 200);
		SKY;
		_mutex.lock();
		list[cur].PrintKey();
		Orgn;
		_mutex.unlock();
		ans.push_back(list[cur]);
		ret = 1;
		cur++;
	}
	else
		combo = 0;

	return ret;
}

void MemoGame::SetList(int size)
{
	srand((unsigned int)time(NULL));
	list.clear();
	int check[KEY_SIZE] = { 0 };
	for (int i = 0; i < size; i++)
	{
		int index;
		do
		{
			int random = rand();
			index = random % 33;
		} while (check[index]);

		check[index] = 1;
		list.push_back(key[index]);
	}
}

void MemoGame::DisplayList()
{
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		_mutex.lock();
		RED;
		list[i].PrintKey();
		Orgn;
		_mutex.unlock();
		Sleep(1000);		
		_mutex.lock();
		list[i].PrintKey();
		_mutex.unlock();
	}
}

void MemoGame::PrintAllKey()
{
	char first[13] = { 'Q','W','E','R','T','Y','U','I','O','P','[',']' };
	char second[12] = { 'A','S','D','F','G','H','J','K','L',';','\'' };
	char third[11] = { 'Z','X','C','V','B','N','M',',','.','/' };
	int x = 5, y = 6;
	for (int i = 0; i < FIRST_LINE_SIZE; i++)
	{
		key[i].Setchar(first[i]);
		key[i].SetXy(x, y);
		key[i].PrintKey();
		x += 10;
	}

	x = 7, y = 11;
	for (int i = 12; i < 12 + SECOND_LINE_SIZE; i++)
	{
		key[i].Setchar(second[i-12]);
		key[i].SetXy(x, y);
		key[i].PrintKey();
		x += 10;
	}

	x = 10, y = 16;
	for (int i = 23; i < 23 + THIRD_LINE_SIZE; i++)
	{
		key[i].Setchar(third[i-23]);
		key[i].SetXy(x, y);
		key[i].PrintKey();
		x += 10;
	}

}

void MemoGame::Key::PrintKey()
{
	gotoxy(x, y);
	printf("┏━━━━━━┓");
	gotoxy(x, y + 1);
	printf("┃      ┃");
	gotoxy(x, y + 2);
	printf("┃      ┃");
	gotoxy(x, y + 3);
	printf("┃  %c   ┃",this->ch);
	gotoxy(x, y + 4);
	printf("┗━━━━━━┛");
}
void MemoGame::PrintBackground()
{
	PrintTime(3, 1);
	PrintScore(30, 1);
	PrintCombo(60, 1);
	Printedge();
	PrintAllKey();
	Display_Score(40, 2);
	Display_Combo(70, 2);
}

void MemoGame::Printedge()
{
	gotoxy(0, 5);
	printf("┏");
	for (int i = 1; i < 128; i++)
		printf("━");
	printf("┓");
	for (int y = 6; y < 22; y++)
	{
		gotoxy(0, y);
		printf("┃");
		gotoxy(128, y);
		printf("┃");
	}
	gotoxy(0, 22);
	printf("┗");
	for (int i = 1; i < 128; i++)
		printf("━");
	printf("┛");
}