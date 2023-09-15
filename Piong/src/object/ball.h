#pragma once

#include "sl.h"

struct Vector2 
{
	float x;
	float y;
};

struct Ball
{
	double inicialPosX;
	double inicialPosY;
	double positionX;
	double positionY;
	double radius;
	Vector2 normalSpeed;
	Vector2 speed;
};

// inicializa la pelota
void InitBall(Ball& ball, int screenWidth, int screenHeight);