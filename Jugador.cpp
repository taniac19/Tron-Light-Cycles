#include "Jugador.h"
#include "Global.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <ctime>

using namespace std;

extern std::chrono::time_point<chrono::system_clock> m_StartTime;
extern std::chrono::time_point<chrono::system_clock> m_EndTime;

extern bool gameOver;
//extern bool start;
extern int fruitX, fruitY, score;
extern double potSeg;
extern int niveles;
extern 	int contScores;
extern int width;
extern int height;
extern bool  m_bRunning;
extern bool _jugador2Activo;
extern bool _jugador3Activo;
extern bool _jugagor4Activo;
extern int  _jugadorActual;

extern bool esMultijugador;
extern bool wantToExit;
extern double nextAutoPilotMove;
extern  bool   makeAutoPilotMove;
extern double nextAutoPilotMoveDelay;

extern void Start();
extern double elapsedMilliseconds();
extern double elapsedSeconds();
extern void gotoxy(int x, int y);
extern int scores[10];



Jugador::Jugador(bool _esActivo, bool _autoPilot, int firstX, int firstY, char _upkey, char _downKey, char _leftKey, char _rightKey) {
	valorPot = 0;
	dir = STOP;
	start = false;

	upkey = _upkey;
	downKey = _downKey; 
	leftKey = _leftKey;
	rightKey = _rightKey;

	x = firstX;
	y = firstY;

	activo = _esActivo;
	autoPilot = _autoPilot;
}

void Jugador::chocoOtraCola(int tailX2[], int tailY2[], int nTail2) {

	for (int i = 0; i < nTail2; i++) {
		if (tailX2[i] == x && tailY2[i] == y) {
			vidas--;
			nTail = 0;

			x = rand() % width;
			y = rand() % height;
		}
	}

}

bool Jugador::choco() {

	if (x < 1 ||  x >= width - 1 || y < 1 || y >= height - 1 ) {
		//Input();
		return true;
	}
	return false;
}

void Jugador::Input( char getch) {
	if (!activo)
		return;
	if (autoPilot){
		if (makeAutoPilotMove  || choco() ) {
			int randDir = rand() % 2 + 1;
			makeAutoPilotMove = false;

			
				switch (dirAnterior) {
				case 1:             //UP
					switch (randDir) {
					case 1:
						dir = LEFT;
						dirAnterior = 3;
						start = true;
						break;
					case 2:
						dir = RIGHT;
						dirAnterior = 4;
						start = true;
						break;
					}

					break;
				case 2:            //DOWN
					switch (randDir) {
					case 1:
						dir = LEFT;
						dirAnterior = 3;
						start = true;
						break;
					case 2:
						dir = RIGHT;
						dirAnterior = 4;
						start = true;
						break;
					}

					break;
				case 3:           //LEFT
					switch (randDir) {
					case 1:
						dir = UP;
						dirAnterior = 1;
						start = true;
						break;
					case 2:
						dir = DOWN;
						dirAnterior = 2;
						start = true;
						break;
					}


					break;
				case 4:          //RIGHT
					switch (randDir) {
					case 1:
						dir = UP;
						dirAnterior = 1;
						start = true;
						break;
					case 2:
						dir = DOWN;
						dirAnterior = 2;
						start = true;
						break;
					}

					break;
				}
			
			gotoxy(x, y);
		}
	}
	else
	{
		if (_kbhit()) {
			//char currentKey = _getch();
			char currentKey = getch;
			if (currentKey == leftKey ) {
				dir = LEFT;
				start = true;
				acceleracion = false;
				_jugadorActual = 1;
			}
			else if ( currentKey == rightKey) {
				dir = RIGHT;
				start = true;
				acceleracion = false;
				_jugadorActual = 1;
			}
			else if ( currentKey == upkey ) {
				dir = UP;
				start = true;
				acceleracion = false;
				_jugadorActual = 1;
			}
			else if (currentKey == downKey) {
				dir = DOWN;
				start = true;
				acceleracion = false;
				_jugadorActual = 1;
			}

			switch (currentKey) {
			case'x':
				gameOver = true;
				wantToExit = true;
				acceleracion = false;
				start = false;
				break;
			case 'p':
				system("pause");
				acceleracion = false;
				break;

			case 'q':
				acceleracion = true;
				break;
			case't':
				break;
			}
			gotoxy(x, y);
		}
	}


	if (start == true) {
		nTail++;
	}
}

void Jugador::Logic() {

	if (!activo)
		return;

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;

		break;
	case RIGHT:
		x++;

		break;
	case UP:
		y--;
	
		break;
	case DOWN:
		y++;
	
		break;
	default:
		break;
	}
	if (y < 0 || x < 0) {
		vidas--;
		nTail = 0;
		x = rand() % width;
		y = rand() % height;

	}
	if (x == width || y == height) {
		vidas--;
		nTail = 0;
		x = rand() % width;
		y = rand() % height;
	}

	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			vidas--;
			nTail = 0;
			x = rand() % width;
			y = rand() % height;
		}
	}
	/*if (vidas == 0 && !autoPilot) {
		gameOver = true;
	}*/
	// POTENCIADORES
	if (x == fruitX && y == fruitY)
	{
		fruitX = rand() % width;
		fruitY = rand() % height;
		potSeg = elapsedSeconds() + 10;
		valorPot += 30;
	}

}

bool Jugador::imprimirCola(int altura, int largo, HANDLE h, int color) {
	if (!activo)
		return false;

	for (int k = 0; k < nTail; k++)
	{
		if (tailX[k] == largo && tailY[k] == altura)
		{
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | color | color);
			cout << char(219);
			return true;
		}
	}
	return false;
}
bool Jugador::imprimirMoto(int altura, int largo, HANDLE h) {
	if (!activo)
		return false;

	if (altura == y && largo == x) {
		return true;
	}
	return false;
}
