// SnakeGame.cpp: define el punto de entrada de la aplicación de consola.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <ctime>
#include "Jugador.h"
#include "Global.h"


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
extern int scores[10];

extern void Start();
extern double elapsedMilliseconds();
extern double elapsedSeconds();
extern void gotoxy(int x, int y);

Jugador jugador1(true, false, width / 2 , height / 2, 'w', 's', 'a','d');
Jugador jugador2(true, true ,    10     ,     10, 'w', 's', 'a', 'd');
Jugador jugador3(true, true,    40     ,     40, 'w', 's', 'a', 'd');
Jugador jugador4(true, true,   100     ,     100, 'w', 's', 'a', 'd');
Jugador jugador5(true, false, 50, 50, 'i', 'k', 'j', 'l');

void Setup() {
	gameOver = false;
	/*start = false;*/
	potSeg = 10;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}
void UltimasPartidas() {
	cout << "-------------------------------------------------------------" << endl;
	cout << "SINGLE PLAYER" << endl;

	for (int i = 0; i < contScores; i++) {
		
		cout << "Partida " << i + 1 << " el puntaje del jugador fue de: " << scores[i] << endl;
	}

	
}
void LevelLogic() {

	//NIVELES
	if (!esMultijugador && elapsedSeconds() >= 0.0 && elapsedSeconds() < 80.0) {
		Sleep(8);
		niveles = 1;
		jugador2.activo = true;
		jugador3.activo = false;
		jugador4.activo = false;
		jugador5.activo = false;
		score = 20;
	}
	if (!esMultijugador && elapsedSeconds() >= 80.0 && elapsedSeconds() < 160.0) {
		Sleep(70);
		niveles = 2;
		jugador2.activo = true;
		jugador3.activo = false;
		jugador4.activo = false;
		jugador5.activo = false;
		score = 40;

	}
	if (!esMultijugador && elapsedSeconds() >= 160.0 && elapsedSeconds() < 240.0) {
		Sleep(50);
		niveles = 3;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = false;
		jugador5.activo = false;
		score = 60;
	}
	if (!esMultijugador && elapsedSeconds() >= 240.0 && elapsedSeconds() < 320.0) {
		Sleep(30);
		niveles = 4;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = false;
		jugador5.activo = false;
		score = 80;

	}
	if (!esMultijugador && elapsedSeconds() >= 320.0 && elapsedSeconds() < 400.0) {
		Sleep(25);
		niveles = 5;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = false;
		jugador5.activo = false;
		score = 100;
	}

	if (!esMultijugador && elapsedSeconds() >= 400.0 && elapsedSeconds() < 480.0) {
		Sleep(20);
		niveles = 6;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = true;
		jugador5.activo = false;
		score = 130;
	}
	if (!esMultijugador && elapsedSeconds() >= 480.0 && elapsedSeconds() < 560.0) {
		Sleep(15);
		niveles = 7;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = true;
		jugador5.activo = false;
		score = 170;
	}
	if (!esMultijugador && elapsedSeconds() >= 560.0 && elapsedSeconds() < 640.0) {
		Sleep(10);
		niveles = 8;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = true;
		jugador5.activo = false;
		score = 220;
	}
	if (!esMultijugador && elapsedSeconds() >= 640.0 && elapsedSeconds() < 720.0) {
		Sleep(5);
		niveles = 9;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = true;
		jugador5.activo = false;
		score = 280;
	}
	if (!esMultijugador && elapsedSeconds() >= 720.0 && !gameOver) {
		Sleep(0);
		niveles = 10;
		jugador2.activo = true;
		jugador3.activo = true;
		jugador4.activo = true;
		jugador5.activo = false;
		score = 350;
	}

	if ((elapsedSeconds() - nextAutoPilotMove) > nextAutoPilotMoveDelay && !makeAutoPilotMove) {
		nextAutoPilotMove = elapsedSeconds();
		makeAutoPilotMove = true;
	}
}
void seleccionarActivos() {
	if (!esMultijugador) {
		jugador2.activo =true;
		jugador3.activo = false;
		jugador4.activo = false;
		jugador5.activo = false;
	}
	else {
		jugador5.activo = true;
		jugador2.activo = false;
		jugador3.activo = false;
		jugador4.activo = false;
	}
}



void Draw() {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//cout << "---------->TRON: LIGHT CYCLES<----------- " << endl;

	gotoxy(jugador1.x, jugador1.y);

	if (!esMultijugador) {
		gotoxy(jugador2.x, jugador2.y);
		gotoxy(jugador3.x, jugador3.y);
		gotoxy(jugador4.x, jugador4.y);
	}
	else {
		gotoxy(jugador5.x, jugador5.y);
	}

	for (int i = 0; i < width + 2; i++) {
		gotoxy(i, 0);
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << char(219);
	}
	cout << endl;


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {

				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << char(219);
			}
			 if(jugador1.imprimirMoto(i, j, h) || jugador2.imprimirMoto(i, j, h) || jugador3.imprimirMoto(i, j, h) || jugador4.imprimirMoto(i, j, h) || jugador5.imprimirMoto(i, j, h)) {
				 SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				 cout << char(206);

			}
			else if (i == fruitY && j == fruitX && elapsedSeconds() >=potSeg) {

				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << char(169);

			}
			else
			{
				if (!esMultijugador) {
					bool print = jugador1.imprimirCola(i, j, h, FOREGROUND_BLUE);
					if (jugador1.acceleracion) {
						bool print = jugador1.imprimirCola(i, j, h, FOREGROUND_BLUE);
					}
					bool print2 = jugador2.imprimirCola(i, j, h, FOREGROUND_RED);
					bool print3 = jugador3.imprimirCola(i, j, h, FOREGROUND_GREEN);
					bool print4 = jugador4.imprimirCola(i, j, h, FOREGROUND_INTENSITY);
					if (!print && !print2 && !print3 && !print4) {
						cout << char(32);
					}
				}
				else {
					bool print = jugador1.imprimirCola(i, j, h, FOREGROUND_BLUE);
					bool print5 = jugador5.imprimirCola(i, j, h, FOREGROUND_GREEN);
					if (!print && !print5 ) {
						cout << char(32);
					}
				}
			}
				if (j == width - 1) {

					SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << char(219);
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {

		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << char(219);
	}

	cout << endl;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Score:" << score << "       ";
	cout << "Lives Jugador 1: " << jugador1.vidas - 1 << endl;
	if (esMultijugador) {
		cout << "Lives Jugador 2: " << jugador5.vidas - 1 << endl;
	}
	cout << "Tiempo: " << elapsedSeconds() << "       ";
	cout << "Nivel:" << niveles << "       ";
	cout << "Potenciador: " << jugador1.valorPot << endl;
}
void Menu() {

	bool error = false;

	do {
		error = false;
		

		int opcion;
		int opcion2;
		cout << "-------------------------------------------------------------" << endl;
		cout << "MENU \n 1. Iniciar Nueva Partida \n 2. Ultimas Partidas" << endl;
		cout << "-------------------------------------------------------------" << endl;
		cout << "Ingrese la opcion deseada: " << endl;
		cin >> opcion;

		switch (opcion) {
		case 1:

			cout << "-------------------------------------------------------------" << endl;
			cout << "1. Single Player \n 2. Multiplayer" << endl;
			cin >> opcion2;

			switch (opcion2) {
			case 1:
				esMultijugador = false;
				break;
			case 2:
				esMultijugador = true;
				break;
			default:
				break;
			}
			seleccionarActivos();
			Setup();
			gameOver = false;
			jugador1.vidas = 4;
			jugador5.vidas = 4;
			Start();
			while (!gameOver) {

				jugador1.chocoOtraCola(jugador2.tailX, jugador2.tailY, jugador2.nTail);
				jugador1.chocoOtraCola(jugador3.tailX, jugador3.tailY, jugador3.nTail);
				jugador1.chocoOtraCola(jugador4.tailX, jugador4.tailY, jugador4.nTail);
				jugador1.chocoOtraCola(jugador5.tailX, jugador5.tailY, jugador5.nTail);


				if (!esMultijugador) {
					jugador2.chocoOtraCola(jugador1.tailX, jugador1.tailY, jugador1.nTail);
					jugador2.chocoOtraCola(jugador3.tailX, jugador3.tailY, jugador3.nTail);
					jugador2.chocoOtraCola(jugador4.tailX, jugador4.tailY, jugador4.nTail);

					jugador3.chocoOtraCola(jugador1.tailX, jugador1.tailY, jugador1.nTail);
					jugador3.chocoOtraCola(jugador2.tailX, jugador2.tailY, jugador2.nTail);
					jugador3.chocoOtraCola(jugador4.tailX, jugador4.tailY, jugador4.nTail);

					jugador4.chocoOtraCola(jugador1.tailX, jugador1.tailY, jugador1.nTail);
					jugador4.chocoOtraCola(jugador2.tailX, jugador2.tailY, jugador2.nTail);
					jugador4.chocoOtraCola(jugador3.tailX, jugador3.tailY, jugador3.nTail);
				}
				else {
					jugador5.chocoOtraCola(jugador1.tailX, jugador1.tailY, jugador1.nTail);
				}

				Draw();
				

				char getch = 't';
				if (_kbhit()) {
					getch = _getch();
				}
				
				jugador1.Input(getch);
				jugador1.Logic();

				if (!esMultijugador) {
					jugador2.Input(getch);
					jugador2.Logic();

					jugador3.Input(getch);
					jugador3.Logic();

					jugador4.Input(getch);
					jugador4.Logic();
				}
				else {
					jugador5.Input(getch);
					jugador5.Logic();

				}

				LevelLogic();

				if (jugador1.vidas == 0 ) {
					std::cout << "\t\t!!!Game over! Jugador 1 Perdio" << endl;
					system("pause");
					gameOver = true;
				}
				if (jugador5.vidas == 0) {
					std::cout << "\t\t!!!Game over! Jugador 2 Perdio" << endl;
					system("pause");
					gameOver = true;
				}

			}
			//std::cout << "\t\t!!!Game over!" << endl << "\t\tYour score is: " << score << endl;
			if (!esMultijugador) {
				scores[contScores] = score;
				contScores++;
				std::cout << "\t\t!!!Game over!" << endl << "\t\tYour score is: " << score << endl;

			}
			system("cls");
			error =true;
			break;
		case 2:
			UltimasPartidas();
			error = true;
			break;
		default:
			cout << "Ingrese solamente el numero de las opciones." << endl;
			error = true;
			break;

		}
		
	} while (error);

}
int main()
{
	Menu();
	system("pause");
	return 0;
}