#pragma once

#include "object/pad.h"
#include "object/ball.h"
#include "sl.h"

// setea el largo de la pantalla
void SetScreenWidth(int& screenWidth);

// setea el alto de la pantalla
void SetScreenHeight(int& screenHeight);

// devuelve el largo de la pantalla
int GetScreenWidth(int screenWidth);

// devuelve el alto de la pantalla
int GetScreenHeight(int screenHeight);

// dibuja
void DrawFigures(Pad pad1, Pad pad2, Ball ball, int screenWidth, int screenHeight);

// contiene el bucle de juego
void GameLoop();

// mov. de los pads
void PadMovement(Pad& pad, int screenHeight);

// chequea si la pelota colisiona con un pad
void PadBallCollision(Ball& ball, Pad pad);

// mov. de la pelota
void BallMovement(Ball& ball, Pad& pad1, Pad& pad2, int screenWidth, int screenHeight, int& ballInicialSpeedX, int& ballInicialSpeedY, bool ballCollidingWithWalls, bool& isBallInicialSpeedRandomized);
