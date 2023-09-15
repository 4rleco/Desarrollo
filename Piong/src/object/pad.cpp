#include "pad.h"
#include "gameData/game.h"

void InitPads(Pad& pad, int positionX, int positionY, int screenHeight, int keyUp, int keyDown)
{
	pad.positionX = positionX;
	pad.positionY = positionY;

	pad.keyUp = keyUp;
	pad.keyDown = keyDown;

	pad.width = 15;
	pad.height = 50;

	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight(screenHeight) - pad.height;

	pad.speed = 350;	

	pad.points = 0;
	pad.minPoints = 0;
	pad.maxPoints = 7;
}

void InitIaPad(Pad& pad, int positionX, int positionY, int screenHeight)
{
	pad.positionX = positionX;
	pad.positionY = positionY;

	pad.width = 15;
	pad.height = 50;

	pad.minPosition = 0;
	pad.maxPosition = GetScreenHeight(screenHeight) - pad.height;

	pad.speed = 350;

	pad.points = 0;
	pad.minPoints = 0;
	pad.maxPoints = 7;
}