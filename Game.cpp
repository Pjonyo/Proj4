#include "Game.h"

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Game::Display_Timeover(int x,int y)
{
    system("cls");
    RED;
    PrintTimeover(x,y);
    Sleep(700);
    system("cls");
    Sleep(500);
    PrintTimeover(x, y);
    Sleep(700);
    system("cls");
    Sleep(500);
    PrintTimeover(x, y);
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
	printf("┃ SCORE  :");
    gotoxy(x + 18, y + 1);
    printf("┃");
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

void Game::Display_Countdown(int x, int y,int Time)
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
			printf("%d", Time - pst);	
			_mutex.unlock();
		}
		prev = pst;
		if (Time <= pst) //시간이 지나면 반복문 종료
		{
			gameover_check = 1;
			break;
		}
	}
}


