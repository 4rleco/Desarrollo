#pragma once

#include "sl.h"

struct Pad
{
	double positionX;
	double positionY;

	int keyUp;
	int keyDown;

	int width;
	int height;

	int minPosition;
	int maxPosition;

	int speed;

	int points;
	int minPoints;
	int maxPoints;
};

// inicializa los pads
void InitPads(Pad& pad, int positionX, int positionY, int screenHeight, int keyUp, int keyDown);

void InitIaPad(Pad& pad, int positionX, int positionY, int screenHeight);