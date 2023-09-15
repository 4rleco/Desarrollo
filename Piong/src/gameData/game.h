#pragma once

#include "object/pad.h"
#include "object/ball.h"
#include "sl.h"

void SetScreenWidth(int screenWidth);

void SetScreenHeight(int screenHeight);

int GetScreenWidth(int screenWidth);

int GetScreenHeight(int screenHeight);

// dibuja
void DrawFigures(Pad pad1, Pad pad2, Ball ball);

// contiene el bucle de juego
void GameLoop();

// mov. de los pads
void PadMovement(Pad& pad);

// chequea si la pelota colisiona con un pad
void PadBallCollision(Ball& ball, Pad pad);

// mov. de la pelota
void BallMovement(Ball& ball, Pad& pad1, Pad& pad2, int& ballInicialSpeedX, int& ballInicialSpeedY, bool ballCollidingWithWalls, bool& isBallInicialSpeedRandomized);