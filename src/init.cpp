#include "Engine/Engine.h"

int main()
{
	TheWorld mainWorld;
	Object object(mainWorld.getList().size());
	mainWorld.addObject(object);
	Object object2(mainWorld.getList().size());
	mainWorld.addObject(object2);

	// запуск движка
	Engine myGame(&mainWorld,7);
	myGame.run();

	return 0;
}
