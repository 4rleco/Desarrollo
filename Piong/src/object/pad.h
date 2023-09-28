#pragma once

#include "sl.h"

struct Pad
{
	float positionX;
	float positionY;

	int keyUp;
	int keyDown;

	float width;
	float height;

	int minPosition;
	int maxPosition;

	float speed;

	int points;
	int minPoints;
	int maxPoints;
};

// inicializa los pads
void InitPads(Pad& pad, int positionX, int positionY, int screenHeight, int keyUp, int keyDown);

void InitIaPad(Pad& pad, int positionX, int positionY, int screenHeight);