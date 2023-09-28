#include "game.h"
#include "sl.h"
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

enum Screen
{
	PauseSinglePlayer,
	PauseMultiPlayer,
	MainMenu,
	SinglePalyer,
	MultiPlayer,
	Rules,
	Credits,
	Exit,
};

void InitFont()
{
	slSetFont(slLoadFont("res/fonts/VCR_OSD_MONO_1.001.ttf"), NULL);
}

void SetScreenWidth(int& screenWidth)
{
	screenWidth = 800;
}

void SetScreenHeight(int& screenHeight)
{
	screenHeight = 450;
}

int GetScreenWidth(int screenWidth)
{
	return screenWidth;
}

int GetScreenHeight(int screenHeight)
{
	return screenHeight;
}

// inicializa todo
void InitAll(Ball& ball, Pad& pad1, Pad& pad2, Pad& ia, int& screenWidth, int& screenHeight)
{
	SetScreenWidth(screenWidth);
	SetScreenHeight(screenHeight);

	slWindow(screenWidth, screenHeight, "Pong", false);

	InitFont();

	InitBall(ball, screenWidth, screenHeight);

	InitPads(pad1, GetScreenWidth(screenWidth) / 10, GetScreenHeight(screenHeight) / 2, screenHeight, 87, 83);
	InitPads(pad2, (GetScreenWidth(screenWidth) - 100), GetScreenHeight(screenHeight) / 2, screenHeight, SL_KEY_UP, SL_KEY_DOWN);
	InitIaPad(ia, GetScreenWidth(screenWidth) - 100, GetScreenHeight(screenHeight) / 2, screenHeight);
}

void DrawFigures(Pad pad1, Pad pad2, Ball ball, int screenWidth, int screenHeight)
{
	string points1 = to_string(pad1.points);
	string points2 = to_string(pad2.points);

	slSetForeColor(1, 1, 1, 1);
	slText(200, 420, points1.c_str());
	slText(600, 420, points2.c_str());

	slRectangleFill(400, 225, 5, 450);

	slSetForeColor(4, 0, 4, 1);
	slRectangleFill(pad1.positionX, pad1.positionY, pad1.width, pad1.height);

	slSetForeColor(1, 0, 0, 1);
	slCircleFill(ball.positionX, ball.positionY, ball.radius, 10);

	slSetForeColor(0, 1, 1, 1);
	slRectangleFill(pad2.positionX, pad2.positionY, pad2.width, pad2.height);
}

// dibuja el menú
void DrawMenu(Screen& screen, int counter, int screenWidth, int screenHeight)
{
	slSetTextAlign(SL_ALIGN_CENTER);
	slSetForeColor(1, 1, 1, 1);
	slSetFontSize(200);
	slText(400, 250, "Pong");

	slSetFontSize(20);
	slText(400, 230, "Use arrow keys to navigate the menu");
	slText(400, 210, "Press \"backspace\" to return to the menu while not in-game");

	slSetFontSize(40);
	slText(400, 180, "SinglePalyer");
	slText(400, 140, "MultiPlayer");
	slText(400, 100, "Rules");
	slText(400, 60, "Credits");
	slText(400, 20, "Exit");

	switch (counter)
	{
	case SinglePalyer:
		slSetForeColor(1, 0, 0, 1);
		slText(400, 180, "SinglePalyer");
		if (slGetKey(SL_KEY_ENTER))
		{
			screen = SinglePalyer;
		}
		break;

	case MultiPlayer:
		slSetForeColor(1, 0, 0, 1);
		slText(400, 140, "MultiPlayer");
		if (slGetKey(SL_KEY_ENTER))
		{
			screen = MultiPlayer;
		}
		break;

	case Rules:
		slSetForeColor(1, 0, 0, 1);
		slText(400, 100, "Rules");
		if (slGetKey(SL_KEY_ENTER))
		{
			screen = Rules;
		}
		break;

	case Credits:
		slSetForeColor(1, 0, 0, 1);
		slText(400, 60, "Credits");
		if (slGetKey(SL_KEY_ENTER))
		{
			screen = Credits;
		}
		break;

	case Exit:
		slSetForeColor(1, 0, 0, 1);
		slText(400, 20, "Exit");
		if (slGetKey(SL_KEY_ENTER))
		{
			screen = Exit;
		}
		break;
	}
}

void PointsReset(Pad& pad)
{
	pad.points = pad.minPoints;
}

// colision de las palteas con los bordes
void PadColision(Pad& pad, int screenHeight)
{
	int maxScreenHeight = GetScreenHeight(screenHeight);
	int minScreenHeight = (GetScreenHeight(screenHeight - GetScreenHeight(screenHeight)));

	if (pad.positionY <= minScreenHeight)
	{
		//std::cout << "Colison Up" << std::endl;		
		pad.positionY = pad.minPosition;
	}

	else if ((pad.positionY + pad.height) >= maxScreenHeight)
	{
		//std::cout << "Colison Down" << std::endl;		
		pad.positionY = pad.maxPosition;
	}
}

void PadMovement(Pad& pad, int screenHeight)
{
	if (slGetKey(pad.keyUp))
	{
		pad.positionY += pad.speed * slGetDeltaTime();
	}

	if (slGetKey(pad.keyDown))
	{
		pad.positionY -= pad.speed * slGetDeltaTime();
	}

	PadColision(pad, screenHeight);
}

void IaPadMovement(Pad& pad, Ball ball, int screenHeight)
{
	if (pad.positionY + (pad.height / 2) > ball.positionY)
	{
		pad.positionY -= 180.0f * slGetDeltaTime();
	}
	else if (pad.positionY + (pad.width / 2) <= ball.positionY)
	{
		pad.positionY += 180.0f * slGetDeltaTime();
	}

	PadColision(pad, screenHeight);
}

// chequea si la pelota colisiona con las paredes
void BallCollision(Ball& ball, Pad& pad1, Pad& pad2, int screenWidth, bool& ballCollidingWithWalls, int& ballInicialSpeedX, int& ballInicialSpeedY)
{
	int minScreenPosX = 0;

	if (ball.positionX >= (screenWidth - ball.radius))
	{
		//std::cout << "Colison Right" << std::endl;
		pad1.points++;

		ball.speed.x = ball.normalSpeed.x;
		ball.speed.y = ball.normalSpeed.y;

		ballCollidingWithWalls = true;
	}

	else if (ball.positionX <= (minScreenPosX + ball.radius))
	{
		//std::cout << "Colison Left" << std::endl;
		pad2.points++;

		ball.speed.x = ball.normalSpeed.x;
		ball.speed.y = ball.normalSpeed.y;

		ballCollidingWithWalls = true;
	}
}

void PadBallCollision(Ball& ball, Pad pad)
{
	float ballWith = ball.radius * 2;
	float ballHeight = ball.radius * 2;

	if ((pad.positionX + pad.width >= ball.positionX) &&
		(pad.positionX <= (ball.positionX - ball.radius) + ballWith) &&
		(pad.positionY + pad.height >= ball.positionY) &&
		(pad.positionY <= (ball.positionY - ball.radius) + ballHeight))
	{

		if (ball.positionX > pad.positionX)
		{
			ball.positionX = (pad.positionX + pad.width) + ball.radius;
		}

		else
		{
			ball.positionX = pad.positionX - ball.radius;
		}

		ball.speed.x *= -1.1f;
	}
}

void BallMovement(Ball& ball, Pad& pad1, Pad& pad2, int screenWidth, int screenHeight, int& ballInicialSpeedX, int& ballInicialSpeedY, bool ballCollidingWithWalls, bool& isBallInicialSpeedRandomized)
{
	if (isBallInicialSpeedRandomized == false)
	{
		ballInicialSpeedX = rand() % 2;
		ballInicialSpeedY = rand() % 2;

		if (ballInicialSpeedX == 0)
		{
			ballInicialSpeedX = -1;
		}

		if (ballInicialSpeedY == 0)
		{
			ballInicialSpeedY = -1;
		}

		isBallInicialSpeedRandomized = true;
	}

	ball.positionX += ball.speed.x * ballInicialSpeedX * slGetDeltaTime();
	ball.positionY += ball.speed.y * ballInicialSpeedY * slGetDeltaTime();

	if ((ball.positionX >= (GetScreenWidth(screenWidth) - ball.radius)) || (ball.positionX <= ball.radius))
		ball.speed.x *= -1.0f;

	if ((ball.positionY >= (GetScreenHeight(screenHeight) - ball.radius)) || (ball.positionY <= ball.radius))
		ball.speed.y *= -1.0f;

	BallCollision(ball, pad1, pad2, screenWidth, ballCollidingWithWalls, ballInicialSpeedX, ballInicialSpeedY);

	if (ballCollidingWithWalls)
	{
		ball.positionX = ball.inicialPosX;
		ball.positionY = ball.inicialPosY;
		isBallInicialSpeedRandomized = false;
	}

	//slRender();
}

//updatea el modo un jugador
void UpdateSinglePlayer(Ball& ball, Pad& pad1, Pad& ia, Screen& screen, int screenWidth, int screenHeight, int& ballInicialSpeedX, int& ballInicialSpeedY, bool ballCollidingWithWalls, bool& hasWon, bool& isBallInicialSpeedRandomized)
{
	bool pause = false;

	if (!hasWon && !pause)
	{
		// mov. primer rectangulo restringido a la pantalla
		PadMovement(pad1, screenHeight);

		// mov. segundo rectangulo restringido a la pantalla
		IaPadMovement(ia, ball, screenHeight);

		// mov. pelota
		BallMovement(ball, pad1, ia, screenWidth, screenHeight, ballInicialSpeedX, ballInicialSpeedY, ballCollidingWithWalls, isBallInicialSpeedRandomized);

		PadBallCollision(ball, pad1);
		PadBallCollision(ball, ia);

		if(slGetKey(SL_KEY_ESCAPE))
		{
			pause = true;
		}

		if (pad1.points >= pad1.maxPoints
			|| ia.points >= ia.maxPoints)
		{
			hasWon = true;
		}
	}

	if (pause)
	{
		screen = Screen::PauseSinglePlayer;
	}

	if (pad1.points >= pad1.maxPoints)
	{
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1, 0, 0, 1);
		slSetFontSize(30);
		slText(400, 420, "Player 1 wins!");
		slText(400, 120, "Press \"enter\" to return to the main menu");
		if (slGetKey(SL_KEY_ENTER))
		{
			PointsReset(pad1);
			PointsReset(ia);
			hasWon = false;
			screen = Screen::MainMenu;
		}
	}

	else if (ia.points >= ia.maxPoints)
	{
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1, 0, 0, 1);
		slSetFontSize(30);
		slText(400, 420, "The computer wins!");
		slText(400, 120, "Press \"enter\" to return to the main menu");
		if (slGetKey(SL_KEY_ENTER))
		{
			PointsReset(pad1);
			PointsReset(ia);
			hasWon = false;
			screen = Screen::MainMenu;
		}
	}
}

//updatea el modo dos jugadores
void UpdateMultiplayer(Ball& ball, Pad& pad1, Pad& pad2, Screen& screen, int screenWidth, int screenHeight, int& ballInicialSpeedX, int& ballInicialSpeedY, bool ballCollidingWithWalls, bool& hasWon, bool& isBallInicialSpeedRandomized)
{
	bool pause = false;

	if (!hasWon && !pause)
	{
		// mov. primer rectangulo restringido a la pantalla
		PadMovement(pad1, screenHeight);

		// mov. segundo rectangulo restringido a la pantalla
		PadMovement(pad2, screenHeight);

		// mov. pelota
		BallMovement(ball, pad1, pad2, screenWidth, screenHeight, ballInicialSpeedX, ballInicialSpeedY, ballCollidingWithWalls, isBallInicialSpeedRandomized);

		PadBallCollision(ball, pad1);
		PadBallCollision(ball, pad2);

		if (slGetKey(SL_KEY_ESCAPE))
		{
			pause = true;
		}

		if (pad1.points >= pad1.maxPoints
			|| pad2.points >= pad2.maxPoints)
		{
			hasWon = true;
		}
	}

	if (pause)
	{
		screen = Screen::PauseMultiPlayer;
	}

	if (pad1.points >= pad1.maxPoints)
	{
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1, 0, 0, 1);
		slSetFontSize(30);
		slText(400, 420, "Player 1 wins!");
		slText(400, 120, "Press \"enter\" to return to the main menu");
		if (slGetKey(SL_KEY_ENTER))
		{
			PointsReset(pad1);
			PointsReset(pad2);
			hasWon = false;
			screen = Screen::MainMenu;
		}
	}

	else if (pad2.points >= pad2.maxPoints)
	{
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1, 0, 0, 1);
		slSetFontSize(30);
		slText(400, 420, "Player 2 wins!");
		slText(400, 120, "Press \"enter\" to return to the main menu");
		if (slGetKey(SL_KEY_ENTER))
		{
			PointsReset(pad1);
			PointsReset(pad2);
			hasWon = false;
			screen = Screen::MainMenu;
		}
	}
}

void GameLoop()
{
	srand(time(NULL));

	Screen screen = MainMenu;

	Pad pad1;
	Pad pad2;
	Pad ia;

	Ball ball;

	int screenWidth = 0;
	int screenHeight = 0;

	int mainMenuChoice = SinglePalyer;
	int minChoice = SinglePalyer;
	int maxChoice = Exit;

	int ballInicialSpeedX = 0;
	int ballInicialSpeedY = 0;

	bool isBallInicialSpeedRandomized = false;

	bool isCollidingWithScreen = false;

	bool endGame = false;

	bool hasWon = false;

	InitAll(ball, pad1, pad2, ia, screenWidth, screenHeight);

	while (!endGame && !slShouldClose())
	{
		switch (screen)
		{
		case MainMenu:
			if (slGetKey(SL_KEY_DOWN))
			{
				mainMenuChoice++;
				if (mainMenuChoice >= maxChoice)
				{
					mainMenuChoice = maxChoice;
				}
			}

			else if (slGetKey(SL_KEY_UP))
			{
				mainMenuChoice--;
				if (mainMenuChoice <= minChoice)
				{
					mainMenuChoice = minChoice;
				}
			}

			DrawMenu(screen, mainMenuChoice, screenWidth, screenHeight);
			break;

		case SinglePalyer:
			UpdateSinglePlayer(ball, pad1, ia, screen, screenWidth, screenHeight, ballInicialSpeedX, ballInicialSpeedY, isCollidingWithScreen, hasWon, isBallInicialSpeedRandomized);
			break;

		case MultiPlayer:
			UpdateMultiplayer(ball, pad1, pad2, screen, screenWidth, screenHeight, ballInicialSpeedX, ballInicialSpeedY, isCollidingWithScreen, hasWon, isBallInicialSpeedRandomized);
			break;
		}

		switch (screen)
		{
		case MainMenu:

			break;

		case SinglePalyer:
			DrawFigures(pad1, ia, ball, screenWidth, screenHeight);
			break;

		case MultiPlayer:
			DrawFigures(pad1, pad2, ball, screenWidth, screenHeight);
			break;

		case Rules:
			slSetTextAlign(SL_ALIGN_LEFT);
			slSetForeColor(1, 1, 1, 1);
			slSetFontSize(25);
			slText(0, 250, "-Use \"w and s\" to move de left pad, only lower case!");
			slText(0, 225, "-And the up and down arrow keys for the right pad");
			slText(0, 200, "-The first one to score 7 points wins");
			slText(0, 175, "-Press \"backspace\" to return to the menu");
			slText(0, 150, "-Press \"esc\" to return pause the game");
			slText(0, 125, "-Press \"enter\" to return to the menu");
			slText(0, 100, " after the match ends");
			

			if (slGetKey(SL_KEY_BACKSPACE))
			{
				screen = Screen::MainMenu;
			}
			break;

		case PauseSinglePlayer:
			slSetTextAlign(SL_ALIGN_LEFT);
			slSetForeColor(1, 1, 1, 1);
			slSetFontSize(25);
			slText(25, screenHeight / 2, "-Press \"backspace\" to return to the menu");
			slText(25, screenHeight / 2 - 25, " or \" enter \" to continue the game");


			if (slGetKey(SL_KEY_BACKSPACE))
			{
				screen = Screen::MainMenu;
			}

			else if (slGetKey(SL_KEY_ENTER))
			{
				screen = Screen::SinglePalyer;
				std::cout << screen << std::endl;
			}

		case PauseMultiPlayer:
			slSetTextAlign(SL_ALIGN_LEFT);
			slSetForeColor(1, 1, 1, 1);
			slSetFontSize(25);
			slText(25, screenHeight / 2, "-Press \"backspace\" to return to the menu");
			slText(25, screenHeight / 2 - 25, " or \" enter \" to continue the game");


			if (slGetKey(SL_KEY_BACKSPACE))
			{
				screen = Screen::MainMenu;
			}

			else if (slGetKey(SL_KEY_ENTER))
			{
				screen = Screen::MultiPlayer;
			}

			break;

		case Credits:
			slSetTextAlign(SL_ALIGN_CENTER);
			slSetForeColor(1, 1, 1, 1);
			slSetFontSize(25);
			slText(400, 225, "Game made by Joaquin Herrero Lendner");

			if (slGetKey(SL_KEY_BACKSPACE))
			{
				screen = Screen::MainMenu;
			}
			break;

		case Exit:
			slSetTextAlign(SL_ALIGN_CENTER);
			slSetForeColor(1, 1, 1, 1);
			slSetFontSize(25);
			slText(400, 250, "Do yo want to close the game?");
			slText(400, 225, "Press \"esc\" to close the game");
			slText(400, 200, "or \"backspace\" to return to the menu");

			if (slGetKey(SL_KEY_ESCAPE))
			{
				endGame = true;
			}
			else if (slGetKey(SL_KEY_BACKSPACE))
			{
				screen = Screen::MainMenu;
			}

			break;
		}

		slSetBackColor(0, 0, 0);

		slRender();
	}

	slClose();
}