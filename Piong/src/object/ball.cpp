#include "ball.h"
#include "gameData/game.h"

void InitBall(Ball& ball, int screenWidth, int screenHeight)
{
	ball.inicialPosX = GetScreenWidth(screenWidth) / 2.0f;
	ball.inicialPosY = GetScreenHeight(screenHeight) / 2.0f;
	ball.positionX = ball.inicialPosX;
	ball.positionY = ball.inicialPosY;
	ball.radius = 10.5f;
	ball.normalSpeed = { 250.0f, 220.0f };
	ball.speed = { ball.normalSpeed.x, ball.normalSpeed.y };
}