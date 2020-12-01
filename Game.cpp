#include "Game.h"

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;


void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Game::Display_Timeover()
{
    RED;
    PrintTimeover(30,5);
    Sleep(700);
    system("cls");
    Sleep(500);
    PrintTimeover(30, 5);
    Sleep(700);
    system("cls");
    Sleep(500);
    PrintTimeover(30, 5);
    Sleep(700);
    system("cls");
    Orgn;
}

void Game::PrintTimeover(int xx,int yy)
{
    int x = xx, y=yy;
    gotoxy(x, y);
    printf("■■■■■■■");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    gotoxy(x, ++y);
    printf("      ■      ");
    
    x = xx + 16, y = yy + 2;
    gotoxy(x, y);
    printf("■");
    gotoxy(x, ++y);
    printf("");
    gotoxy(x, ++y);
    printf("■");
    gotoxy(x, ++y);
    printf("■");
    gotoxy(x, ++y);
    printf("■");
    gotoxy(x, ++y);
    printf("■");
    
    x = xx + 24, y = yy + 2;
    gotoxy(x, y);
    printf("  ■■  ■■");
    gotoxy(x, ++y);
    printf("■    ■    ■");
    gotoxy(x, ++y);
    printf("■    ■    ■");
    gotoxy(x, ++y);
    printf("■    ■    ■");
    gotoxy(x, ++y);
    printf("■    ■    ■");
    gotoxy(x, ++y);
    printf("■    ■    ■");
    
    x = xx + 43, y = yy + 2;
    gotoxy(x, y);
    printf("  ■■■■");
    gotoxy(x, ++y);
    printf("■        ■");
    gotoxy(x, ++y);
    printf("■        ■");
    gotoxy(x, ++y);
    printf("■■■■■■");
    gotoxy(x, ++y);
    printf("■");
    gotoxy(x, ++y);
    printf("  ■■■■");
    
    x = xx - 4, y = yy + 12;
    gotoxy(x, y);
    printf("        ■■■■");
    gotoxy(x, ++y);
    printf("       ■      ■");
    gotoxy(x, ++y);
    printf("      ■        ■");
    gotoxy(x, ++y);
    printf("     ■          ■");
    gotoxy(x, ++y);
    printf("      ■        ■");
    gotoxy(x, ++y);
    printf("       ■      ■");
    gotoxy(x, ++y);
    printf("        ■    ■");
    gotoxy(x, y);
    printf("        ■■■■");
    
    x = xx + 18, y = yy + 14;
    gotoxy(x, y);
    printf("■      ■");
    gotoxy(x, ++y);
    printf(" ■    ■");
    gotoxy(x, ++y);
    printf("  ■  ■");
    gotoxy(x, ++y);
    printf("   ■■");
    gotoxy(x, ++y);
    printf("    ■");
    
    x = xx + 31, y = yy + 14;
    gotoxy(x, y);
    printf("  ■■■");
    gotoxy(x, ++y);
    printf("■      ■");
    gotoxy(x, ++y);
    printf("■■■■■");
    gotoxy(x, ++y);
    printf("■");
    gotoxy(x, ++y);
    printf("  ■■■");
    
    x = xx + 46, y = yy + 13;
    gotoxy(x, ++y);
    printf("■   ■");
    gotoxy(x, ++y);
    printf(" ■■");
    gotoxy(x, ++y);
    printf(" ■");
    gotoxy(x, ++y);
    printf(" ■");
    gotoxy(x, ++y);
    printf(" ■");
}

void Game::PrintTime(int x, int y)
{
	gotoxy(x, y);
	printf("┏━━━━━━━━━━━━┓");
	gotoxy(x, y + 1);
	printf("┃ TIME  :");
	gotoxy(x + 13, y + 1);
	printf("┃");
	gotoxy(x, y + 2);
	printf("┗━━━━━━━━━━━━┛");
}

void Game::PrintScore(int x, int y)
{
	gotoxy(x, y);
	printf("┏━━━━━━━━━━━━━━━━━┓");
	gotoxy(x, y + 1);
	printf("┃ SCORE  :        ┃");
	gotoxy(x, y + 2);
	printf("┗━━━━━━━━━━━━━━━━━┛");
}

void Game::PrintCombo(int x, int y)
{
	gotoxy(x, y);
	printf("┏━━━━━━━━━━━━┓");
	gotoxy(x, y + 1);
	printf("┃ Combo  :");
	gotoxy(x + 13, y + 1);
	printf("┃");
	gotoxy(x, y + 2);
	printf("┗━━━━━━━━━━━━┛");
}

void Game::Display_Combo(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
	gotoxy(x, y);
	printf("%3d", combo);
}

void Game::Display_Score(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
	gotoxy(x, y);
	printf("%7d", score);
}

void Game::Display_Countdown(int x, int y)
{
	int start = clock(), end;
	int pst;
	double prev = -1;
	while (1)
	{
		end = clock();
		pst = (int)(end - start) / CLK_TCK;
		
		if (prev != pst)
		{
			_mutex.lock();
			gotoxy(x, y);
			printf("  ");
			gotoxy(x, y);
			printf("%d", TIME_LIMIT - pst);	
			_mutex.unlock();
		}
		prev = pst;
		if (TIME_LIMIT <= pst) //시간이 지나면 반복문 종료
		{
			gameover_check = 1;
			break;
		}
	}
}

void Game::Play()
{
	system("mode con: cols=100 lines=50");
	
	//커서숨김
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &Cursor);


}

