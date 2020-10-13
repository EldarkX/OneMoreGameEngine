#include "../inc/arcanoid.h"

int main(int argc, char **argv)
{
	Game game(960, 720);

	game.PreInit();

	game.Init();

	game.Tick();

	game.End();
	
	return 0;
}
