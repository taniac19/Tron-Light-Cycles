#include "Global.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <ctime>


using namespace std;

std::chrono::time_point<chrono::system_clock> m_StartTime;
std::chrono::time_point<chrono::system_clock> m_EndTime;

bool gameOver;
//bool start;
int fruitX, fruitY, score;
double potSeg;
int niveles;
int scores[10];
int width      = 80;
int height     = 30;
bool  m_bRunning     = false;
bool _jugador2Activo = true;
bool _jugador3Activo = false;
bool _jugagor4Activo = false;
int  _jugadorActual  = 1;
int contScores = 0;
bool esMultijugador = true;
bool wantToExit     = false;

double nextAutoPilotMove = 0;
bool   makeAutoPilotMove = true;
double nextAutoPilotMoveDelay = 2;


double elapsedMilliseconds()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;

	if (m_bRunning)
	{
		endTime = std::chrono::system_clock::now();
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}
double elapsedSeconds()
{
	return elapsedMilliseconds() / 1000.0;
}
void gotoxy(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}
void Start()
{
	m_StartTime = chrono::system_clock::now();
	m_bRunning = true;
	nextAutoPilotMove = elapsedSeconds();
}
