#include "Modules/CoreModule/GameEngine.h"

int main(int argc, char **argv)
{
	GameEngine gameEngine(960, 720);

	gameEngine.PreInit();

	gameEngine.Init();

	gameEngine.Tick();

	gameEngine.End();
	
	return 0;
}
