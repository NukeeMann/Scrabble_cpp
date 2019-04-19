#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define MAP_SIZE 15	// Wielkosc mapy

#define BEGINX 60	// Wspolrzedna x-owa mapy
#define BEGINY 6	// Wspolrzedna y-owa mapy

#define Lx 1	// Wspolrzedna x-owa legendy
#define Ly 1	// Wspolrzedna y-owa legendy

#define ILOSC_LITER 100		// Ilosc liter w woreczku

#define PKT_1 1			// Mno¿niki punktów za litere
#define PKT_2 2
#define PKT_3 3
#define PKT_4 4
#define PKT_5 5
#define PKT_8 8
#define PKT_10 10

#define LSx2 2	// Mniejszy mnoznik za litere
#define LSx3 3	// Wiekszy mnoznik za litere
#define WSx2 2	// Mniejszy mnoznik za slowo
#define WSx3 3	// Wiekszy mnoznik za slowo


void create_map(char field[][MAP_SIZE]);	// Tworzy pusta mape

int pola_specjalne(int i, int j);		// Wypisuje wszystkie pola specjalne i sprawdza czy na punkcie I i J jest pole specjalne

void print_map(char field[][MAP_SIZE]);		// Wyswietla mape

void kursor_position(int x, int y);			// Wyswietla pozycje kursora

bool Alfabet_Pusty(char ALFABET[ILOSC_LITER]);		// Sprawdza czy wszystkie litery nie zostaly juz zuzyte

char losuj_kafelek(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *liczba_losowan);		// Losuje kafelki graczowi

void lista_kafelkow(char player_tales[]);	// Wyswietla liste kafelkow gracza

void nowa_gra(char ALFABET[ILOSC_LITER], char player1_tales[7], char field[][MAP_SIZE], char Alfabet_Copy[ILOSC_LITER], int* player_points, int *liczba_losowan);	// Restart do nowej gry

int check_player_tales(char player1_copied_tales[], char w_litera);			// Czy gracz ma kafelek ktory wpisuje

void wpisywanie_slowa(char player1_tales[], char word[], int x, int y, char field[][MAP_SIZE], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan);		// Wyswietlanie slowa

void ustaw_slowo(char field[][MAP_SIZE], char word[], int x, int y, char player1_tales[], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan);		// Demonstruje umieszczenie slowa

void ruch_poziome_slowo(char field[][MAP_SIZE], char copy_player1_tales[], char player1_tales[], char word[], int n, int x, int y);		// Kolory tla na mapie wzgledem pasowania danego kafelka w orientacji poziomej

void ruch_pionowe_slowo(char field[][MAP_SIZE], char copy_player1_tales[], char player1_tales[], char word[], int n, int x, int y);		// Kolory tla na mapie wzgledem pasowania danego kafelka w orientacji pionowej

bool czy_litera_pasuje(char field[][MAP_SIZE], char player1_tales[], char word[], char ALFABET[], char Alfabet_Copy[], int x, int y, int n, int orientacja, int *player_points); 		// Sprawdza czy slowo mozna wstawic

void wstawianie_slowa(int orientacja, char field[][MAP_SIZE], char word[], char player1_tales[], int n, int x, int y, char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan);	// Wstawianie kafelka i sprawdzenie czy jest to mozliwe

void wymiana_kafelkow(char player1_tales[], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *liczba_losowan);		// Wymiana zaznaczonych kafelkow POCZATEK

void wybor_kafelka(char player1_tales[], char kopia_kafelkow[], int n, bool wywolanie[]); // Zaznaczenie kafelkow do wymiany

void wymien_kafelek(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], char player1_tales[], int pozycja, int *liczba_losowan);		// Wymienia zaznaczone kafelki

void wyswietl_punkty(int player_points);		// Wyswietla liczbe punktow gracza

void bonusy(char field[][MAP_SIZE], int a, int b, int * points, int * WS, char word[], int n);		// Doliczanie pól specjalnych do punktacji

void losuj_wszystkie_kafelki(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], char player1_tales[], int *liczba_losowan);		// Pierwsze losowanie wszystkich kafelkow

bool nazwa_pliku(char name[]); // Wczytywanie nazwy do zapisu/odczytu

bool zapisywanie(char field[][MAP_SIZE], int player_points, char ALFABET[ILOSC_LITER], char player1_tales[], int liczba_losowan, int czas);		// Zapisywanie stanu gry

bool wczytywanie(char field[][MAP_SIZE], int* player_points, char ALFABET[ILOSC_LITER], char player1_tales[], int* liczba_losowan, int* czas);		// Wczytywanie gry

int punkty_litera(char field[][MAP_SIZE], int a, int b);		// Przydziela punkty za litery bedace na planszy i stykajace sie ze slowem gracza

int punkty_litry_slowa(char word[], int i);		// Przydziela punkty za litery postawione przez gracza
	

int main() {
	char Alfabet_Copy[ILOSC_LITER];
	char ALFABET[ILOSC_LITER] = { 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'a', 'a', 'a', 'a', 'a', 'a', 'a',
								  'a', 'a', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
								  'n', 'n', 'n', 'n', 'n', 'n', 'r', 'r', 'r', 'r', 'r', 'r', 't', 't', 't', 't', 't', 't', 'l',
								  'l', 'l', 'l', 's', 's', 's', 's', 'u', 'u', 'u', 'u', 'd', 'd', 'd', 'd', 'g', 'g', 'g', 'b',
								  'b', 'c', 'c', 'm', 'm', 'p', 'p', 'f', 'f', 'h', 'h', 'v', 'v', 'w', 'w', 'y', 'y', 'k', 'j', 'x', 'q', 'z', 'X', 'X' };

	int zn = 0, x = BEGINX + (MAP_SIZE/2), y = BEGINY + (MAP_SIZE/2), attr = 4, back = 0, zero = 0;
	char txt[32], player1_tales[7], word[MAP_SIZE + 1];
	int player_points = 0;
	int liczba_losowan = 0;
	int czas = time(NULL);
	srand(czas);
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
	char field[MAP_SIZE][MAP_SIZE];

	create_map(field);
	
	losuj_wszystkie_kafelki(ALFABET, Alfabet_Copy, player1_tales, &liczba_losowan);

#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Michal Wnuczynski, 175739");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	do {
		// we set black to be the background color
		// check conio2.h for available colors
		textbackground(BLACK);
		// clear the screen: we fill it out with spaces with
		// the specified background color
		clrscr();
		// we set the text color (7 == LIGHTGRAY)
		textcolor(WHITE);
		// we move the coursor to column 48 and row 1
		// rows and column are numbered starting with 1
		gotoxy(Lx, Ly);
		cputs("Sterowanie: ");
		gotoxy(Lx, Ly + 1);
		cputs("STRZALKI - Poruszanie slowem");
		gotoxy(Lx, Ly + 2);
		cputs("ENTER - Zatwierdzenie ruchu");
		gotoxy(Lx, Ly + 3);
		cputs("ESC - Rezygnacja z ruchu");
		gotoxy(Lx, Ly + 4);
		cputs("n - Nowa gra");
		gotoxy(Lx, Ly + 5);
		cputs("q - Wyjscie z gry");
		gotoxy(Lx, Ly + 6);
		cputs("i - Wstawianie slowa");
		gotoxy(Lx, Ly + 7);
		cputs("BACKSPACE - Kasowanie litery");
		gotoxy(Lx, Ly + 8);
		cputs("o - Zamiana orientacji slowa");
		gotoxy(Lx, Ly + 9);
		cputs("w - Wymiana kafelkow");
		gotoxy(Lx, Ly + 10);
		cputs("1,2,3,4,5,6,7 - Zaznaczenie kafelkow");
		gotoxy(Lx, Ly + 11);
		cputs("s - Zapisywanie");
		gotoxy(Lx, Ly + 12);
		cputs("l - Wczytywanie");
		gotoxy(Lx, Ly + 13);
		cputs("n - Nowa gra");
		gotoxy(Lx, Ly + 14);
		cputs("q - Wyjscie z gry");

		/*gotoxy(Lx, Ly);
		// we print out a text at a given cursor position
		// the cursor will move by the length of the text
		cputs("q       = exit");
		gotoxy(Lx, Ly + 1);
		cputs("cursors = moving");
		gotoxy(Lx, Ly + 2);
		cputs("space   = change color");
		gotoxy(Lx, Ly + 3);
		cputs("enter   = change background color");
		// print out the code of the last key pressed
		if (zero) sprintf_s(txt, "key code: 0x00 0x%02x", zn);*
		else sprintf_s(txt, "key code: 0x%02x", zn);
		gotoxy(Lx, Ly + 4);
		cputs(txt);*/
		gotoxy(Lx, Ly + 16);
		cputs("Michal Wnuczynski, 175739");
		gotoxy(Lx, Ly + 17);
		cputs("Zaimplementowane punkty:");
		gotoxy(Lx, Ly + 18);
		cputs("a,b,g,d,f,h,i");
		gotoxy(Lx, Ly + 21);
		cputs("Twoje kafelki: ");
		gotoxy(Lx, Ly + 22);
		lista_kafelkow(player1_tales);		// Wypisywanie kafelkow gracza
		kursor_position(x, y);
		print_map(field);		// Wypisywanie mapy
		wyswietl_punkty(player_points);
		// we draw a star
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		// putch prints one character and moves the cursor to the right
		
		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if(zn == 0) 
		{
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == 0x48)	// will be a special key
			{
				if(y != BEGINY)
					y--;
			}
			else if (zn == 0x50)
			{
				if (y != BEGINY + MAP_SIZE - 1)
					y++;
			}
			else if (zn == 0x4b)
			{
				if (x != BEGINX)
					x--;
			}
			else if (zn == 0x4d)
			{
				if (x != BEGINX + MAP_SIZE - 1)
					x++;
			}
		}else if (zn == 0x6e)
		{
			gotoxy(BEGINX + MAP_SIZE + 4, BEGINY + 4);
			textbackground(YELLOW);
			textcolor(RED);
			cputs(" Rozpoczac gre od nowa? ");
			gotoxy(BEGINX + MAP_SIZE + 4, BEGINY + 5);
			cputs("          [T/N]         ");
			textbackground(BLACK);
			char question_new_game = getch();
			if(question_new_game == 't' || question_new_game == 'T')
				nowa_gra(ALFABET, player1_tales, field, Alfabet_Copy, &player_points, &liczba_losowan);
		}
		else if (zn == 0x69)
		{

			wpisywanie_slowa(player1_tales, word, x, y, field, ALFABET, Alfabet_Copy, &player_points, &liczba_losowan);
				
		}
		else if (zn == 0x77) {
			wymiana_kafelkow(player1_tales, ALFABET, Alfabet_Copy, &liczba_losowan);
		}
		else if (zn == 0x73) {
			
			zapisywanie(field, player_points, ALFABET, player1_tales, liczba_losowan, czas);
		}
		else if (zn == 0x6c) {

			wczytywanie(field, &player_points, ALFABET, player1_tales, &liczba_losowan, &czas);
		}
		else if(zn == ' ') attr = (attr + 1) % 16;
		else if(zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends

	return 0;
	}



	void create_map(char field[][MAP_SIZE])		// Tworzy poczatkowa pusta mape
	{
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
					field[i][j] = '.';
			}
		}
		return;
	}


	int pola_specjalne(int i, int j) {		// Zwraca wartosc koloru kafelka na pozycji (i, j)

		if (i == MAP_SIZE / 2 || j == MAP_SIZE / 2) {		// Linie srodkowe
			if (i == MAP_SIZE / 2 && j == MAP_SIZE / 2)
				return 7;
			else if (i == j)
				return 13;
			else if (i == 0 || j == 0 || j == MAP_SIZE - 1 || i == MAP_SIZE - 1)
				return 12;
			else if (i == MAP_SIZE / 4 || i == MAP_SIZE - 1 - MAP_SIZE / 4 || j == MAP_SIZE / 4 || j == MAP_SIZE - 1 - MAP_SIZE / 4)
				return 9;
			else
				return 7;
		}
		else {		// Prawy gorny rog - wszystkie rogi
			if ((i == 0 || i == MAP_SIZE - 1) && (j == 0 || j == MAP_SIZE - 1))	// Czerwone pola 3xWS
				return 12;
			else if (((i == MAP_SIZE / 2 - 1 || i == MAP_SIZE / 2 + 1) && (j == MAP_SIZE / 2 - 1 || j == MAP_SIZE / 2 + 1)))	// JasnoNiebieskie pola 2xLS przy srodku
				return 9;
			else if (((i == 3 || i == MAP_SIZE - 4) && (j == 0 || j == MAP_SIZE - 1)) || ((i == 0 || i == MAP_SIZE - 1) && (j == 3 || j == MAP_SIZE - 4)))	//  JasnoNiebieskie pola 2xLS przy granicahc planszy
				return 9;
			else if (((i == 2 || i == MAP_SIZE - 3) && (j == MAP_SIZE / 2 - 1 || j == MAP_SIZE / 2 + 1)) || ((i == MAP_SIZE / 2 - 1 || i == MAP_SIZE / 2 + 1) && (j == 2 || j == MAP_SIZE - 3)))		// JasnoNiebieskie pola 2xLS przy wewnetrznych scianakch 
				return 9;
			else if ((j == i || j == MAP_SIZE - i - 1) && (i < MAP_SIZE / 2 - 2 || i > MAP_SIZE / 2 + 2))		// Rozwoe pola 2xWS za slowo na skos
				return 13;
			else if ((i == 1 || i == MAP_SIZE / 2 - 2 || i == MAP_SIZE / 2 + 2 || i == MAP_SIZE - 2) && (j == 1 || j == MAP_SIZE / 2 - 2 || j == MAP_SIZE - 2 || j == MAP_SIZE / 2 + 2)) // Pole 3x LS za litere
				return 1;
			else
				return 7;
		}

	}


	void print_map(char field[][MAP_SIZE]) {		// Wypisuje mape

		int k = 1;

		gotoxy(BEGINX, BEGINY - 2);
		for (int i = 0; i < MAP_SIZE; i++) {		// Gorna pozycja ABCDE
			putch(65 + i);
		}


		gotoxy(BEGINX, BEGINY + MAP_SIZE + 1);
		for (int i = 0; i < MAP_SIZE; i++) {		// Dolna pozycja ABCDE
			putch(65 + i);
		}


		for (int i = 1; i < MAP_SIZE + 1; i++) {		// Lewe pozycje 12345
			k = i / 10;
			if (i > 9) {
				int j = i % 10;

				gotoxy(BEGINX - 3, BEGINY - 1 + i);
				putch(48 + k);

				gotoxy(BEGINX - 2, BEGINY - 1 + i);
				putch(48 + j);
			}
			else
			{
				gotoxy(BEGINX - 2, BEGINY - 1 + i);
				putch(48 + i);
			}
		}


		for (int i = 1; i < MAP_SIZE + 1; i++) {		// Prawe pozycje 12345
			k = i / 10;
			if (i > 9) {
				int j = i % 10;

				gotoxy(BEGINX + MAP_SIZE + 1, BEGINY - 1 + i);
				putch(48 + k);

				gotoxy(BEGINX + MAP_SIZE + 2, BEGINY - 1 + i);
				putch(48 + j);
			}
			else
			{
				gotoxy(BEGINX + MAP_SIZE + 1, BEGINY - 1 + i);
				putch(48 + i);
			}
		}

		for (int i = 0; i <= MAP_SIZE + 1; i++) {
			gotoxy(BEGINX - 1 + i, BEGINY - 1);		// Gorne poziome linie ramki
			textbackground(CYAN);
			putch(' ');

			gotoxy(BEGINX - 1 + i, BEGINY + MAP_SIZE);		// Dolne poziome linie ramki
			putch(' ');
			textbackground(BLACK);
		}

		for (int i = 0; i <= MAP_SIZE; i++) {
			gotoxy(BEGINX - 1, BEGINY + i);		// Lewe pionowe linie ramki
			textbackground(CYAN);
			putch(' ');

			gotoxy(BEGINX + MAP_SIZE, BEGINY + i);		// Prawe pionowe linie ramki
			putch(' ');
			textbackground(BLACK);
		}

		for (int i = 0; i < MAP_SIZE; i++) {		// Wypelnienie mapy plansza z tablicy
			for (int j = 0; j < MAP_SIZE; j++) {

				if (i == MAP_SIZE / 2 && j == MAP_SIZE / 2)
					textbackground(13);
				else
					textbackground(pola_specjalne(i, j));


				if (field[i][j] != '.') {
					if ((i == 0 && (j == 0 || j == MAP_SIZE)) || (j == 0 && (i == 0 || i == MAP_SIZE))) {
						textcolor(BLACK);
						gotoxy(BEGINX + j, BEGINY + i);
						putch(field[i][j]);
					}
					else {
						textcolor(BLACK);
						gotoxy(BEGINX + j, BEGINY + i);
						putch(field[i][j]);
					}
				}
				else {
					textcolor(LIGHTCYAN);
					gotoxy(BEGINX + j, BEGINY + i);
					putch(' ');
				}

			}
		}
		textcolor(WHITE);

		return;
	}


	void kursor_position(int x, int y)		// Wypisuje pozycje kursora
	{
		int kursor_x = x - BEGINX + 65, kursor_y = y - BEGINY + 49; 
		gotoxy(Lx, Ly + 20);
		cputs("Pozycja kursora: ");
		putch(kursor_x);
		if (kursor_y >= 58)
		{
			int k = (kursor_y + 2) / 10 - 6;	// Gdy kursor przekroczy 9, wrzuca odpowiednio ile razy to zrobil
			int k2 = 48 + kursor_y - 58 - 10 * k; // Wypisuje cyfre jednosci po przekroczeniu 9
			putch(49 + k); // Cyfra dziesietnych
			putch(k2);	// Cyfra jednostek
		}
		else
			putch(kursor_y);
			putch(' ');

		return;
	}


	bool Alfabet_Pusty(char ALFABET[ILOSC_LITER]) {		// Sprawdza czy alfabet nie jest juz pusty
		for (int i = 0; i < ILOSC_LITER; i++) {
			if (ALFABET[i] != ' ') {
				return true;
			}
		}

		return false;
	}


	char losuj_kafelek(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *liczba_losowan) {		// Losuje nowy kafelek

		int LOS = NULL;
		int i = 0;
		bool warunek = Alfabet_Pusty(ALFABET);

		if (warunek == true) {
			(*liczba_losowan)++;
			LOS = rand() % ILOSC_LITER;
			while ((ALFABET[LOS] < 97 || ALFABET[LOS] > 122 ) && ALFABET[LOS] != 88) {
				(*liczba_losowan)++;
				LOS = rand() % ILOSC_LITER;
				if ( ( ALFABET[LOS] > 97 && ALFABET[LOS] < 122 ) || ALFABET[LOS] == 88)
					break;
				i++;
			}
			char kafelek = ALFABET[LOS];
			Alfabet_Copy[LOS] = ALFABET[LOS];
			ALFABET[LOS] = ' ';
			return kafelek;
		}

		if (warunek == false) {
			ALFABET[LOS] = ' ';
		}
		return ' ';
	}


	void lista_kafelkow(char player_tales[]) {		//Wyswietlenie kafelkow gracza

		for (int i = 0; i < 7; i++)
		{
			if ( ( 96 < player_tales[i] && player_tales[i] < 123 ) || player_tales[i] == 88)
			{
				putch(player_tales[i]);
				cputs(", ");
			}
			else {
				
			}
		}

		return;
	}


	void nowa_gra(char ALFABET[ILOSC_LITER], char player1_tales[7], char field[][MAP_SIZE], char Alfabet_Copy[ILOSC_LITER], int* player_points, int *liczba_losowan) {

		*player_points = 0;

		for (int i = 0; i < ILOSC_LITER; i++) {		// Przypisuje od nowa zmienne do tablicy
			if ( ( ALFABET[i] < 97 || ALFABET[i] > 122 ) && ALFABET[i] != 88) {
				ALFABET[i] = Alfabet_Copy[i];
			}
		}

		for (int i = 0; i < 7; i++) {	// Na nowo losuje kafelki graczowi
			player1_tales[i] = losuj_kafelek(ALFABET, Alfabet_Copy, liczba_losowan);
		}

		create_map(field);	// Czyscy cala mape poprzez przypisanie jej nowych wartosci

	}


	int check_player_tales(char player1_copied_tales[], char w_litera) {		// Kontroluje kafelki gracza podczas wstawiania slowa

		for (int n = 0; n < 7; n++) {
			if (player1_copied_tales[n] == w_litera) {
				player1_copied_tales[n] = ' ';
				return n;
			}
		}

		return -1;
	}


	void wpisywanie_slowa(char player1_tales[], char word[], int x, int y, char field[][MAP_SIZE], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan) {		// Wyswietlanie slowa
		char player1_copied_tales[7];
		int i = 0;
		int if_have[MAP_SIZE];


		gotoxy(Lx, Ly + 24);
		textcolor(9);
		textbackground(BLACK);
		cputs(" Uloz wyraz: ..........");
		char w_litera = getch();


		for (int m = 0; m < 7; m++) {		// Tworzenie zmiennej przechowujacej kopie kafelkow gracza
			player1_copied_tales[m] = player1_tales[m];
		}

		while (w_litera != 0x0d && w_litera != 0x1b)
		{
			if (w_litera == 0x08) {		// Usuwanie wprowadzonej litery
				if (i > 0)
				{
					i--;
					player1_copied_tales[if_have[i]] = player1_tales[if_have[i]];
					word[i] = NULL;
					gotoxy( 2 + Lx + i, Ly + 25);
					textcolor(0);
					textbackground(BLACK);
					putch(' ');
				}
			}
			else if (i < MAP_SIZE && w_litera != 0x20) {	// Wpisywanie nowych liter do slowa

				gotoxy( 2 + Lx + i, Ly + 25);

				if_have[i] = check_player_tales(player1_copied_tales, w_litera);
				word[i] = w_litera;

				if (if_have[i] != -1) {
					textcolor(WHITE);
					textbackground(GREEN);
					putch(w_litera);
					i++;
					textbackground(BLACK);
				}
				else
				{
					textcolor(WHITE);
					textbackground(RED);
					putch(w_litera);
					i++;
					textbackground(BLACK);
				}
			}
			w_litera = getch();
		}
		word[i] = '\0';		// Ustawienie konca slowa
		if (w_litera == 0x0d) {
			ustaw_slowo(field, word, x, y, player1_tales, ALFABET, Alfabet_Copy, player_points, liczba_losowan);		// Przeslanie slowa do informacyjnego wyswietlenia na planszy
		}

		return;
	}


	void ustaw_slowo(char field[][MAP_SIZE], char word[], int x, int y, char player1_tales[], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan) {		// Demonstruje umieszczenie slowa
		char akcja;
		int n = 0;
		int orientacja = 0;		// 0 - slowo poziomo, 1 - slowo pionowo
		char copy_player1_tales[8] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

		textcolor(WHITE);
		x = BEGINX;			// Ustawia koordynaty POKAZYWANEGO slowa
		y = BEGINY;

		kursor_position(x, y);
		print_map(field);
		textbackground(LIGHTGREEN);

		while (word[n] != '\0') {		// Wypisuje slowo pierwszy raz i zlicza jego dlugosc
			textcolor(BLACK);
			for (int o = 0; o < 7; o++) {
				if (field[y - BEGINY][n] == word[n]) {
					textbackground(LIGHTGREEN);
					gotoxy(x, y);
					putch(word[n]);
				}
				else if (player1_tales[o] == word[n]) {

					if (field[y - BEGINY][n] != word[n] && field[y - BEGINY][n] != '.') {
						textbackground(RED);
						gotoxy(x, y);
						putch(word[n]);
					}
					else {
						player1_tales[o] = ' ';
						copy_player1_tales[o] = word[n];
						textbackground(LIGHTGREEN);
						gotoxy(x, y);
						putch(word[n]);
					}
					break;
				}
				else {
					textbackground(RED);
				}
			}
			gotoxy(x, y);
			putch(word[n]);
			++n;
			x++;
			textbackground(BLACK);
			textcolor(WHITE);
			for (int o = 0; o < 7; o++) {
				if (copy_player1_tales[o] != ' ') {
					player1_tales[o] = copy_player1_tales[o];
					copy_player1_tales[o] = ' ';
				}
			}
		}

		textbackground(BLACK);
		x -= n;
		gotoxy(x, y);
		akcja = getch();
		
		while (akcja != 0x0d && akcja != 0x1b) {		// Poruszanie sie ze slowem po mapie

			if (akcja == 0x48)	// Ruch w gore
			{
				if (orientacja == 0) {
					if (y != BEGINY)
					{
						y--;
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);		// Kolorki czy litery pasuja na mapie RED i LIGHTGREN
						textcolor(WHITE);
					}
				}
				else if (orientacja == 1) {
					if (y != BEGINY)
					{
						y--;
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
				}
			}
			else if (akcja == 0x50)		// Ruch w dol
			{
				if (orientacja == 0) {
					if (y != BEGINY + MAP_SIZE - 1) {
						y++;
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);		// Kolorki czy litery pasuja na mapie RED i LIGHTGREN
						textcolor(WHITE);
					}
				}
				else if (orientacja == 1) {
					if (y + n - 1 != BEGINY + MAP_SIZE - 1) {
						y++;
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
				}
			}
			else if (akcja == 0x4b)		// Ruch w lewo
			{
				if (orientacja == 0) {
					if (x != BEGINX) {
						x--;
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);		// Kolorki czy litery pasuja na mapie RED i LIGHTGREN
						textcolor(WHITE);
					}
				}
				else if (orientacja == 1) {
					if (x != BEGINX) {
						x--;
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
				}
			}
			else if (akcja == 0x4d)		// Ruch w prawo
			{
				if (orientacja == 0) {
					if (x + n - 1 != BEGINX + MAP_SIZE - 1) {
						x++;
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);		// Kolorki czy litery pasuja na mapie RED i LIGHTGREN
						textcolor(WHITE);
					}
				}
				else if (orientacja == 1) {
					if (x != BEGINX + MAP_SIZE - 1) {
						x++;
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);

					}
				}
			}
			else if (akcja == 0x6f) {		// Zmiana orientacji slowa
				if (orientacja == 0) {
					orientacja = 1;

					if (y + n > BEGINY + MAP_SIZE) {		// Jezlei po transformacji orientacji wychodzi poza lewa ramke
						int nadmiarx = n - (BEGINY + MAP_SIZE - 1 - y) - 1;
						y = y - nadmiarx;
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
					else {									// Jezlei po transformacji orientacji NIE wychodzi poza prawa ramke
						print_map(field);
						textcolor(BLACK);
						ruch_pionowe_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
				}
				else if (orientacja == 1) {
					orientacja = 0;

					if (x + n > BEGINX + MAP_SIZE) {		// Jezlei po transformacji orientacji wychodzi poza prawa ramke
						int nadmiarx = n - (BEGINX + MAP_SIZE - 1 - x) - 1;
						x = x - nadmiarx;
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
					else {									// Jezlei po transformacji orientacji NIE wychodzi poza prawa ramke
						print_map(field);
						textcolor(BLACK);
						ruch_poziome_slowo(field, copy_player1_tales, player1_tales, word, n, x, y);
						textcolor(WHITE);
					}
				}
			}
			kursor_position(x, y);
			akcja = getch();

		}

		if (akcja == '\r') {		// Wstawianie kafelka i sprawdzanie czy mozna go tak ulozyc
			wstawianie_slowa(orientacja, field, word, player1_tales, n, x, y, ALFABET, Alfabet_Copy, player_points, liczba_losowan);
		}

		return;
	}


	void ruch_poziome_slowo(char field[][MAP_SIZE], char copy_player1_tales[], char player1_tales[], char word[], int n, int x, int y) {	// Kolorki RED i LIGHTGREEN przy poruszaniu sie po mapie poziomo
		int WspolneLitery = 0;

		if (field[y - BEGINY][x - BEGINX] == word[0]) {		// Sprawdza czy slowa w 100% nie nachodza na siebie np. SAD w [SAD]A
			for (int a = 0; a < n; a++) {
				if (field[y - BEGINY][x - BEGINX + a] == word[a])
					++WspolneLitery;
			}
		}

		if (WspolneLitery == n) {
			for (int k = 0; k < n; k++) {
				textbackground(YELLOW);
				gotoxy(x + k, y);
				putch(word[k]);
			}
		}
		else {
			for (int i = 0; i < n; i++) {

				for (int o = 0; o < 7; o++) {
					if (field[y - BEGINY][x - BEGINX + i] == word[i]) {
						textbackground(LIGHTGREEN);
					}
					else if (player1_tales[o] == word[i]) {
						if (field[y - BEGINY][x - BEGINX + i] != word[i] && field[y - BEGINY][x - BEGINX + i] != '.') {
							textbackground(RED);
						}
						else {
							player1_tales[o] = ' ';
							copy_player1_tales[o] = word[i];
							textbackground(LIGHTGREEN);
						}
						break;
					}
					else {
						textbackground(RED);
					}
				}
				gotoxy(x + i, y);
				putch(word[i]);
			}
		}
		textbackground(BLACK);
		for (int o = 0; o < 7; o++) {
			if (copy_player1_tales[o] != ' ') {
				player1_tales[o] = copy_player1_tales[o];
				copy_player1_tales[o] = ' ';
			}

		}

		return;
	}


	void ruch_pionowe_slowo(char field[][MAP_SIZE], char copy_player1_tales[], char player1_tales[], char word[], int n, int x, int y) {	// Kolorki RED i LIGHTGREEN przy poruszaniu sie po mapie pionowo
		int WspolneLitery = 0;

		if (field[y - BEGINY][x - BEGINX] == word[0]) {		// Sprawdza czy slowa w 100% nie nachodza na siebie np. SAD w [SAD]A
			for (int a = 0; a < n; a++) {
				if (field[y - BEGINY + a][x - BEGINX] == word[a])
					++WspolneLitery;
			}
		}

		if (WspolneLitery == n) {
			for (int k = 0; k < n; k++) {
				textbackground(YELLOW);
				gotoxy(x, y + k);
				putch(word[k]);
			}
		}
		else {
			for (int i = 0; i < n; i++) {

				for (int o = 0; o < 7; o++) {
					if (field[y - BEGINY + i][x - BEGINX] == word[i]) {
						textbackground(LIGHTGREEN);
					}
					else if (player1_tales[o] == word[i]) {
						if (field[y - BEGINY + i][x - BEGINX] != word[i] && field[y - BEGINY + i][x - BEGINX] != '.') {
							textbackground(RED);
							gotoxy(x, y + i);
							putch(word[i]);
						}
						else {
							player1_tales[o] = ' ';
							copy_player1_tales[o] = word[i];
							textbackground(LIGHTGREEN);
							gotoxy(x, y + i);
							putch(word[i]);
						}
						break;
					}
					else {
						textbackground(RED);
					}
				}
				gotoxy(x, y + i);
				putch(word[i]);
			}
		}
		textbackground(BLACK);
		for (int o = 0; o < 7; o++) {
			if (copy_player1_tales[o] != ' ') {
				player1_tales[o] = copy_player1_tales[o];
				copy_player1_tales[o] = ' ';
			}

		}

		return;
	}


	bool czy_litera_pasuje(char field[][MAP_SIZE], char player1_tales[], char word[], char ALFABET[], char Alfabet_Copy[], int x, int y, int n, int orientacja, int *player_points) {		// Sprawdza czy slowo mozna wstawic

		bool warunek_1 = true, warunek_2 = true, warunek_3 = true;
		int warunek_nalozenie = 0, ograniczenice_stawiania = n, points = 0, pointsMAIN = 0, WS = 1;
		bool sprawdzanie_litery[MAP_SIZE];
		char hold_player1_tales[7] = { ',', ',', ',', ',', ',', ',', ',', };

		if (orientacja == 0) {

			for (int p = 0; p < n; p++) {			// Sprawdza czy slowo laczy sie z jakims innym lub przechodzi przez srodek planszy
				if (field[y - BEGINY][x - BEGINX + p] != '.')	// Jezeli przechodzi przez jakas litere
					ograniczenice_stawiania--;
				if (y == (BEGINY + MAP_SIZE / 2) && (x + p) == (BEGINX + MAP_SIZE / 2))		// Jezeli przechodzi przez srodek planszy
					ograniczenice_stawiania--;

				if (field[y - BEGINY + 1][x - BEGINX + p] != '.' && (y - BEGINY + 1 < MAP_SIZE) )		// Sprawdza czy slowo styka sie z innym slowem
					ograniczenice_stawiania--;
				if (field[y - BEGINY - 1][x - BEGINX + p] != '.' && (y - BEGINY - 1 > 0))
					ograniczenice_stawiania--;
				if (field[y - BEGINY][x - BEGINX + p + 1] != '.' && (x - BEGINX + 1 + p < MAP_SIZE))
					ograniczenice_stawiania--;
				if (field[y - BEGINY][x - BEGINX + p - 1] != '.' && (x - BEGINX - 1 + p > 0))
					ograniczenice_stawiania--;

			}

			if (ograniczenice_stawiania == n) {
				return false;
			}

			for (int i = 0; i < n; i++) {		// Sprawdza najpierw czy litery pasuja na mapie poziomo
				if (field[y - BEGINY][x - BEGINX + i] != word[i] && field[y - BEGINY][x - BEGINX + i] != '.')
					warunek_1 = false;

				if (field[y - BEGINY][x - BEGINX + i] == word[i]) {		// Zlicza ilr liter na siebie nachodzi. Jezeli wszystkie. Ruch bedzie niedozwolony
					warunek_nalozenie++;
					points += punkty_litera(field, y - BEGINY, x - BEGINX + i);
					
				}

				if (field[y - BEGINY][x - BEGINX + i] == '.') {			// Sprawdza czy gracz posiada dana litera ktora chce postawic na pustym polu
					for (int k = 0; k < 7; k++) {
						if (player1_tales[k] == word[i]) {
							hold_player1_tales[k] = player1_tales[k];
							player1_tales[k] = ',';

							bonusy(field, y - BEGINY, x - BEGINX + i, &pointsMAIN, &WS, word, i);

							for (int p = 1; y - p >= BEGINY; p++) {
								if (field[y - BEGINY - p][x - BEGINX + i] != '.')
									points += punkty_litera(field, y - BEGINY - p, x - BEGINX + i);
								else
									break;
							}
							for (int p = 1; y + p < BEGINY + MAP_SIZE; p++) {
								if (field[y - BEGINY + p][x - BEGINX + i] != '.')
									points += punkty_litera(field, y - BEGINY + p, x - BEGINX + i);
								else
									break;
							}
							

							sprawdzanie_litery[i] = true;
							break;
						}
						else {
							sprawdzanie_litery[i] = false;
						}
					}

					for (int k = 0; k < n; k++) {
						if (sprawdzanie_litery[k] == false) {
							warunek_3 = false;
							break;
						}
					}

				}

			}

			for (int p = 0; x + n + p < BEGINX + MAP_SIZE; p++) {
				if (field[y - BEGINY][x - BEGINX + n + p] != '.')
					points += punkty_litera(field, y - BEGINY, x - BEGINX + n + p);
				else
					break;
			}
			for (int p = 1; x - p >= BEGINX ; p++) {
				if (field[y - BEGINY][x - BEGINX - p] != '.')
					points += punkty_litera(field, y - BEGINY, x - BEGINX - p);
				else
					break;
			}

		}
		else if (orientacja == 1) {

			for (int p = 0; p < n; p++) {			// Sprawdza czy slowo laczy sie z jakims innym lub przechodzi przez srodek planszy
				if (field[y - BEGINY + p][x - BEGINX] != '.')	// Jezeli przechodzi przez jakas litere
					ograniczenice_stawiania--;
				if ((y + p) == (BEGINY + MAP_SIZE / 2) && x == (BEGINX + MAP_SIZE / 2))		// Jezeli przechodzi przez srodek planszy
					ograniczenice_stawiania--;

				if (field[y - BEGINY + p + 1][x - BEGINX] != '.' && (y - BEGINY + p + 1 < MAP_SIZE))		// Sprawdza czy slowo styka sie z innym
					ograniczenice_stawiania--;
				if (field[y - BEGINY + p - 1][x - BEGINX] != '.' && (y - BEGINY + p - 1 > 0))
					ograniczenice_stawiania--;
				if (field[y - BEGINY + p][x - BEGINX + 1] != '.' && (x - BEGINX + 1 < MAP_SIZE))
					ograniczenice_stawiania--;
				if (field[y - BEGINY + p][x - BEGINX - 1] != '.' && (x - BEGINX - 1 > 0))
					ograniczenice_stawiania--;

			}

			if (ograniczenice_stawiania == n) {
				return false;
			}

			for (int i = 0; i < n; i++) {		// Sprawdza najpierw czy litery pasuja na mapie	pionowo
				if (field[y - BEGINY + i][x - BEGINX] != '.' && field[y - BEGINY + i][x - BEGINX] != word[i])
					warunek_1 = false;

				if (field[y - BEGINY + i][x - BEGINX] == word[i]){		// Zlicza ilr liter na siebie nachodzi. Jezeli wszystkie. Ruch bedzie niedozwolony
					warunek_nalozenie++;
					points += punkty_litera(field, y - BEGINY + i, x - BEGINX);
				}

				if (field[y - BEGINY + i][x - BEGINX] == '.') {			// Sprawdza czy gracz posiada dana litera ktora chce postawic na pustym polu
					for (int k = 0; k < 7; k++) {
						if (player1_tales[k] == word[i]) {
							hold_player1_tales[k] = player1_tales[k];
							player1_tales[k] = ',';

							bonusy(field, y - BEGINY + i, x - BEGINX, &pointsMAIN, &WS, word, i);

							for (int p = 1; x - p >= BEGINX; p++) {
								if (field[y - BEGINY + i][x - BEGINX - p] != '.')
									points += punkty_litera(field, y - BEGINY + i, x - BEGINX - p);
								else
									break;
							}
							for (int p = 1; x - BEGINX + p < BEGINX + MAP_SIZE - 1; p++) {
								if (field[y - BEGINY + i][x - BEGINX + p] != '.' )
									points += punkty_litera(field, y - BEGINY + i, x - BEGINX + p);
								else
									break;
							}

							sprawdzanie_litery[i] = true;
							break;
						}
						else {
							sprawdzanie_litery[i] = false;
						}
					}

					for (int k = 0; k < n; k++) {
						if (sprawdzanie_litery[k] == false) {
							warunek_3 = false;
							break;
						}
					}

				}

			}

			for (int p = 0; y + n + p < BEGINY + MAP_SIZE; p++) {
				if (field[y - BEGINY + n + p][x - BEGINX] != '.')
					points += punkty_litera(field, y - BEGINY + n + p, x - BEGINX );
				else
					break;
			}
			for (int p = 1; y - p >= BEGINY; p++) {
				if (field[y - BEGINY - p][x - BEGINX] != '.' && y - BEGINY - p > BEGINY)
					points += punkty_litera(field, y - BEGINY - p, x - BEGINX);
				else
					break;
			}

		}


		if (warunek_1 == false || warunek_2 == false || warunek_nalozenie == n || warunek_3 == false) {		// Sprawdza umieszczane slowo spelnia wszystkie wyzej podane warunki
			
			for (int m = 0; m < 7; m++) {
				if (player1_tales[m] == ',')
					player1_tales[m] = hold_player1_tales[m];
			}

			return false;
		}
		else {
			(*player_points) += points;
			(*player_points) += (pointsMAIN * WS);
			return true;
		}
	}


	void wstawianie_slowa(int orientacja, char field[][MAP_SIZE], char word[], char player1_tales[], int n, int x, int y, char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *player_points, int *liczba_losowan) {	// Wstawianie kafelka i sprawdzenie czy jest to mozliwe
		bool zezwolenie = true;
		int wykorzystane_kafelki = 0;

		if (orientacja == 0) {

			if (czy_litera_pasuje(field, player1_tales, word, ALFABET, Alfabet_Copy, x, y, n, orientacja, player_points) == true) {		// Jezlei mozna wstawic to wstawi slowo poziomo
				for (int i = 0; i < n; i++) {

					for (int k = 0; k < 7; k++) {
						if (player1_tales[k] == ',' && field[y - BEGINY][x - BEGINX + i] == '.') {
							player1_tales[k] = losuj_kafelek(ALFABET, Alfabet_Copy, liczba_losowan);
							wykorzystane_kafelki += 1;
							break;
						}
					}

					field[y - BEGINY][x - BEGINX + i] = word[i];
					gotoxy(x + i, y);
					putch(word[i]);

				}
				if (wykorzystane_kafelki == 7)
					(*player_points) += 50;
				print_map(field);
			}
			else {
				gotoxy(BEGINX + MAP_SIZE/2 - 11, BEGINY + MAP_SIZE + 3);
				textbackground(YELLOW);
				textcolor(RED);
				cputs(" Ruch jest niedozwolony ");
				textbackground(BLACK);
				getch();
			}
		}
		else if (orientacja == 1) {

			if (czy_litera_pasuje(field, player1_tales, word, ALFABET, Alfabet_Copy, x, y, n, orientacja, player_points) == true) {		// Jezlei mozna wstawic to wstawi slowo pionowo
				for (int i = 0; i < n; i++) {

					for (int k = 0; k < 7; k++) {
						if (player1_tales[k] == ',' && field[y - BEGINY + i][x - BEGINX] == '.') {
							player1_tales[k] = losuj_kafelek(ALFABET, Alfabet_Copy, liczba_losowan);
							wykorzystane_kafelki += 1;
							break;
						}
					}

					field[y - BEGINY + i][x - BEGINX] = word[i];
					gotoxy(x, y + i);
					putch(word[i]);
				}
				if (wykorzystane_kafelki == 7)
					(*player_points) += 50;
				print_map(field);
			}
			else {
				gotoxy(BEGINX + MAP_SIZE / 2 - 11, BEGINY + MAP_SIZE + 3);
				textbackground(YELLOW);
				textcolor(RED);
				cputs(" Ruch jest niedozwolony ");
				textbackground(BLACK);
				getch();
			}
		}
	}


	void wymiana_kafelkow(char player1_tales[], char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], int *liczba_losowan) {		// Zaznaczanie kafelkow do wymiany

		bool wywolanie[11] = { true, true, true, true, true, true, true, true, true, true, true };
		char kopia_kafelkow[11] = { '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' };
		gotoxy(Lx, Ly + 24);
		textcolor(LIGHTBLUE);
		textbackground(BLACK);
		cputs(" Kafelki wybrane do wymiany: ");
		textcolor(GREEN);
		char kafelek_wymiana;
		kafelek_wymiana = getch();

		while (kafelek_wymiana != 0x77 && kafelek_wymiana != 0x1b && kafelek_wymiana != 0x0d) {		// Dopki gracz nie wcisnie W, enter lub ESC. Zaznaca kafelki do wymiany

			if (kafelek_wymiana > '0' && kafelek_wymiana <= '9') {
				int n = (int)kafelek_wymiana - '1';

				if (n < 8)
					wybor_kafelka(player1_tales, kopia_kafelkow, n, wywolanie);		//	Zaznacza wybrany kafelek



				for (int i = 0; i < 7; i++) {			// Wyswietla wybrane kafelki
					if (kopia_kafelkow[i] != '.') {
						gotoxy(Lx + 2 + i, Ly + 25);
						putch(kopia_kafelkow[i]);
					}
					else {
						gotoxy(Lx + 2 + i, Ly + 25);
						putch(' ');
					}
				}

				kafelek_wymiana = getch();
			}
			else {
				kafelek_wymiana = getch();
			}

			
		}

		if (kafelek_wymiana == 0x0d || kafelek_wymiana == 0x77) {

			for (int i = 0; i < 11; i++) {
				if (kopia_kafelkow[i] != '.')
					wymien_kafelek(ALFABET, Alfabet_Copy, player1_tales, i, liczba_losowan);		// Wymienia zaznaczone kafelki
			}
		}

		return;
	}


	void wybor_kafelka(char player1_tales[], char kopia_kafelkow[], int n, bool wywolanie[]) {	// Zaznaczenie kafelkow do wymiany

		if (wywolanie[n] == true) {
			kopia_kafelkow[n] = player1_tales[n];
			wywolanie[n] = false;
		}
		else {
			kopia_kafelkow[n] = '.';
			wywolanie[n] = true;
		}

	}


	void wymien_kafelek(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], char player1_tales[], int pozycja, int *liczba_losowan) {		// Wymiana zaznaczonych kafelkow

		bool warunek = Alfabet_Pusty(ALFABET);		// Sprawdza czy alfabet posiada jeszcze kafelki 
		int LOS = NULL;

		if (warunek == true) {					// Losuje kafelek z alfabetu
			(*liczba_losowan)++;
			LOS = rand() % ILOSC_LITER;
			while ( (ALFABET[LOS] < 97 && ALFABET[LOS] != 88) || ALFABET[LOS] > 122) {
				(*liczba_losowan)++;
				LOS = rand() % ILOSC_LITER;
				if (ALFABET[LOS] != NULL)
					break;
			}
			char kafelek = ALFABET[LOS];			// Podmienia kafelek wylosowany z kafelkiem gracza
			ALFABET[LOS] = player1_tales[pozycja];
			player1_tales[pozycja] = kafelek;
		}
		else {											// Jezeli alfabet jest pusty i nie ma z czego losowac
			gotoxy(BEGINX + MAP_SIZE + 4, BEGINY);
			textbackground(YELLOW);
			textcolor(RED);
			cputs(" Brak kafelkow w woreczku ");
			textbackground(BLACK);
			getch();
		}

	}


	void wyswietl_punkty(int player_points) {		// Wyswietla liczbe punktow gracza

		char tekst[10];

		gotoxy(BEGINX + MAP_SIZE + 4, BEGINY);
		textbackground(BLACK);
		textcolor(WHITE);
		cputs("Liczba punktow:");
		textcolor(GREEN);
		sprintf_s(tekst, " %d", player_points);		// Przenosi liczbe punktow z inta do tablicy char
		cputs(tekst);
	}


	void bonusy(char field[][MAP_SIZE], int a, int b, int * points, int * WS, char word[], int i) {		// Doliczanie pól specjalnych do punktacji

		switch (pola_specjalne(a, b)) {
		case 9: {					// Pole bonus za litere - mniejszy
			(*points) += punkty_litry_slowa(word, i) * LSx2;
			break;
		}
		case 1: {					// Pole bonus za litere - wiekszy
			(*points) += punkty_litry_slowa(word, i) * LSx3;
			break;
		}
		case 12: {					// Pole bonus za slowo - wiekszy
			(*points) += punkty_litry_slowa(word, i);
			(*WS) *= WSx3;
			break;
		}
		case 13: {					// Pole bonus za slowo - mniejszy
			(*points) += punkty_litry_slowa(word, i);
			(*WS) *= WSx2;
			break;
		}
		default: {					// Zwykle pole
			(*points) += punkty_litry_slowa(word, i);
			break;
		}
		}

	}


	int punkty_litera(char field[][MAP_SIZE], int a, int b) {		// Przydziela punkty za litery bedace na planszy i stykajace sie ze slowem gracza

		switch (field[a][b])
		{
		case 'e': {
			return PKT_1;
		}
		case 'a': {
			return PKT_1;
		}
		case 'i': {
			return PKT_1;
		}
		case 'o': {
			return PKT_1;
		}
		case 'n': {
			return PKT_1;
		}
		case 'r': {
			return PKT_1;
		}
		case 't': {
			return PKT_1;
		}
		case 'l': {
			return PKT_1;
		}
		case 's': {
			return PKT_1;
		}
		case 'u': {
			return PKT_1;
		}
		case 'd': {
			return PKT_2;
		}
		case 'g': {
			return PKT_2;
		}
		case 'b': {
			return PKT_3;
		}
		case 'c': {
			return PKT_3;
		}
		case 'm': {
			return PKT_3;
		}
		case 'p': {
			return PKT_3;
		}
		case 'f': {
			return PKT_4;
		}
		case 'h': {
			return PKT_4;
		}
		case 'v': {
			return PKT_4;
		}
		case 'w': {
			return PKT_4;
		}
		case 'y': {
			return PKT_4;
		}
		case 'k': {
			return PKT_5;
		}
		case 'j': {
			return PKT_8;
		}
		case 'x': {
			return PKT_8;
		}
		case 'q': {
			return PKT_10;
		}
		case 'z': {
			return PKT_10;
		}
		}
		return 0;
	}


	int punkty_litry_slowa(char word[], int i) {		// Przydziela punkty za litery postawione przez gracza
		switch (word[i])
		{
		case 'e': {
			return PKT_1;
		}
		case 'a': {
			return PKT_1;
		}
		case 'i': {
			return PKT_1;
		}
		case 'o': {
			return PKT_1;
		}
		case 'n': {
			return PKT_1;
		}
		case 'r': {
			return PKT_1;
		}
		case 't': {
			return PKT_1;
		}
		case 'l': {
			return PKT_1;
		}
		case 's': {
			return PKT_1;
		}
		case 'u': {
			return PKT_1;
		}
		case 'd': {
			return PKT_2;
		}
		case 'g': {
			return PKT_2;
		}
		case 'b': {
			return PKT_3;
		}
		case 'c': {
			return PKT_3;
		}
		case 'm': {
			return PKT_3;
		}
		case 'p': {
			return PKT_3;
		}
		case 'f': {
			return PKT_4;
		}
		case 'h': {
			return PKT_4;
		}
		case 'v': {
			return PKT_4;
		}
		case 'w': {
			return PKT_4;
		}
		case 'y': {
			return PKT_4;
		}
		case 'k': {
			return PKT_5;
		}
		case 'j': {
			return PKT_8;
		}
		case 'x': {
			return PKT_8;
		}
		case 'q': {
			return PKT_10;
		}
		case 'z': {
			return PKT_10;
		}
		}
		return 0;
	}


	void losuj_wszystkie_kafelki(char ALFABET[ILOSC_LITER], char Alfabet_Copy[ILOSC_LITER], char player1_tales[], int *liczba_losowan) {		// Pierwsze losowanie wszystkich kafelkow

		for (int i = 0; i < 7; i++) {
			player1_tales[i] = losuj_kafelek(ALFABET, Alfabet_Copy, liczba_losowan);
		}

	}


	bool nazwa_pliku(char name[]) {		// Wczytywanie nazwy pliku do zapisu/odczytu gry

		int i = 0;
		char znak;
		znak = getch();

		while (znak != 0x0d && znak != 0x1b)
		{
			if (znak == 0x08) {		// Usuwanie wprowadzonej litery
				if (i > 0)
				{
					i--;

					name[i] = NULL;
					gotoxy(7 + Lx + i, Ly + 25);
					textcolor(0);
					textbackground(BLACK);
					putch(' ');
				}
			}
			else if (i < 14 && znak != 0x20) {	// Wpisywanie nowych liter do slowa

				gotoxy(7 + Lx + i, Ly + 25);

				name[i] = znak;

				textcolor(YELLOW);
				textbackground(BLACK);
				putch(znak);
				i++;
				textbackground(BLACK);
			}
			znak = getch();
		}
		name[i] = '\0';

		if (znak == 0x1b)		// Rezygnacja z wprowadzenia ruchu
			return false;

		return true;
	}


	bool zapisywanie(char field[][MAP_SIZE], int player_points, char ALFABET[ILOSC_LITER], char player1_tales[], int liczba_losowan, int czas) {		// Zapisywanie stanu gry

		char name[30];
		gotoxy(Lx, Ly + 24);
		textcolor(GREEN);
		textbackground(BLACK);
		cputs(" Podaj nazwe pliku do zapisu ");
		gotoxy(Lx + 1, Ly + 25);
		textcolor(WHITE);

		if (nazwa_pliku(name) == false)		// Wczytywanie nazwy pliku do zapisu
			return false;

		FILE * zapis;
		zapis = fopen(name, "w");

		for (int i = 0; i < MAP_SIZE; i++) {		// Zapisywanie mapy
			for (int n = 0; n < MAP_SIZE; n++) {
				fprintf(zapis, "%c", field[i][n]);
			}
		}

		fprintf(zapis, "%d", player_points);		// Zapisywanie punktow

		for (int i = 0; i < ILOSC_LITER; i++) {		// Zapisywanie alfabetu
			if ((ALFABET[i] < 97 || ALFABET[i] > 122) && ALFABET[i] != 88) {
				fprintf(zapis, "%c", ',');
			}
			else {
				fprintf(zapis, "%c", ALFABET[i]);
			}
		}

		fprintf(zapis, "%d", czas);		// Zapisywanie czasu do losowania

		for (int i = 0; i < 7; i++) {				// Zapisywanie kafelkow gracza	
			if ((player1_tales[i] < 97 || player1_tales[i] > 122) && player1_tales[i] != 88) {
				fprintf(zapis, "%c", ',');
			}
			else {
				fprintf(zapis, "%c", player1_tales[i]);
			}
		}

		fprintf(zapis, "%d", liczba_losowan);		// Zapisywanie liczby losowan

		fclose(zapis);

		return true;
	}


	bool wczytywanie(char field[][MAP_SIZE], int* player_points, char ALFABET[ILOSC_LITER], char player1_tales[], int* liczba_losowan, int* czas) {		// Wczytywanie gry

		char name[30];
		gotoxy(Lx, Ly + 24);
		textcolor(GREEN);
		textbackground(BLACK);
		cputs(" Podaj nazwe pliku do wczytania ");
		gotoxy(Lx + 1, Ly + 25);
		textcolor(WHITE);

		if (nazwa_pliku(name) == false)		// Wczytywanie nazwy pliku
			return false;

		FILE *zapis2;
		zapis2 = fopen(name, "r");

		if (zapis2 == NULL) {		// Jezeli plik nie istnieje
			gotoxy(Lx, Ly + 24);
			textcolor(RED);
			textbackground(BLACK);
			cputs(" Wczytywanie pliku zakonczylo sie niepowodzeniem. ");
			gotoxy(Lx + 1, Ly + 25);
			cputs("                        ");
			textcolor(WHITE);
			getch();
			return false;
		}

		for (int i = 0; i < MAP_SIZE; i++) {			// Wczytywanie mapy
			for (int n = 0; n < MAP_SIZE; n++) {
				fscanf(zapis2, "%c", &field[i][n]);

			}
		}

		fscanf(zapis2, "%d", player_points);			// Wczytywanie punktow

		for (int i = 0; i < ILOSC_LITER; i++) {			// Wczytywanie alfabetu
			fscanf(zapis2, "%c", &ALFABET[i]);
			if (ALFABET[i] == ',')
				ALFABET[i] = NULL;
		}

		fscanf(zapis2, "%d", czas);						// Wczytywanie wartosci time do odtworzenia losowania

		for (int i = 0; i < 7; i++) {					// Wczytanie listy kafelkow gracza
			fscanf(zapis2, "%c", &player1_tales[i]);
			if (player1_tales[i] == ',')
				player1_tales[i] = ' ';
		}

		fscanf(zapis2, "%d", liczba_losowan);			// Wczytyanie liczby losowan w grze

		srand(*czas);

		for (int i = 0; i < *liczba_losowan; i++) {		// Odtworzenie losowosci
			rand() % ILOSC_LITER;
		}

		fclose(zapis2);

		return true;
	}

