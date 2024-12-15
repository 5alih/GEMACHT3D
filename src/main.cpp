#include "engine_core.h"

int main() 
{
	CoreEngine engine;
	engine.Initialize();
	engine.Run();
	engine.Shutdown();
	return 0;
}