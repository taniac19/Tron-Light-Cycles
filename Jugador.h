#include<iostream>
#ifndef PERSONA_H
#define PERSONA_H
#include <string>
#include <windows.h>
using namespace std;


class Jugador {
public:
	int tailX[4000];
	int tailY[4000];
	bool acceleracion = false;
	int x, y;
	int vidas = 4;
	int nTail;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
	int valorPot;
	int dirAnterior = 1;

	bool activo = false;
	bool autoPilot = false;
	bool start;

	char upkey, downKey, leftKey, rightKey;

	Jugador(bool _esActivo, bool _autoPilot, int firstX, int firstY, char _upkey, char _downKey, char _leftKey, char _rightKey);
	void Logic();
	void Input(char getch);
	bool imprimirCola(int altura, int largo, HANDLE h, int color);
	bool imprimirMoto(int altura, int largo, HANDLE h);
	bool choco();
	void chocoOtraCola(int tailX2[], int tailY2[], int nTail2);

};
#endif
