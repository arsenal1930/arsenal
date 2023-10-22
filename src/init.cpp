#include "Engine/Engine.h"

int main()
{
	TheWorld mainWorld;
	Denizen denizen;
	mainWorld.addDenizen(denizen);

	// запуск движка
	Engine myGame(&mainWorld);
	myGame.run();

	return 0;
}
