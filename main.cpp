#include "Game.h"
#include "ArrowGame.h"
#include "RainGame.h"
#include "MemoGame.h"

int main()
{
	Game* game1 = new MemoGame;
	game1->Play();
	
	Game* game2 = new RainGame;
	game2->Play();

	Game* game3 = new ArrowGame;
	game3->Play();

	int total_score = game1->Get_Score() + game2->Get_Score() + game3->Get_Score();
	printf("%d", total_score);
}
