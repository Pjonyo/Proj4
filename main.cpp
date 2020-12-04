#include "Game.h"
#include "ArrowGame.h"
#include "RainGame.h"
#include "MemoGame.h"

int main()
{
	Game* gm = new MemoGame;
	gm->Play();
}
