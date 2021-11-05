#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "funkcje.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char* argv[])
{	
	if (argc < 3)
	{
		printf("Za malo argumentow");
		obslugaArgumentow();
		return 0;
	}
	if (argc > 4)
	{
		printf("Za duzo argumentow");
		obslugaArgumentow();
		return 0;
	}
	bool wykonaj = false;
	char nazwaPliku[64];
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-h"))
		{
			strcpy(nazwaPliku, argv[i+1]);
			i++;
			wykonaj = true;
		}
		if (!strcmp(argv[i], "-z"))
		{
			wypiszZasady();
		}
	}
	if (wykonaj == false)
	{
		printf("Niepoprawne argumenty");
		printf("Argumenty: %s %s %s", argv[1], argv[2], argv[3]);
		obslugaArgumentow();
	}

	if (wykonaj)
	{
		srand((unsigned int)time(NULL));

		int stanKonta = 0;										//aktualny stan konta
		char graj = 'y';
		while (graj == 'y' || graj == 'Y')
		{
			char* haslo = czytajZPliku(nazwaPliku);				//wzor hasla
			char* aktualnyStanTablicy = zakryjHaslo(haslo);		//aktualny stan odkrytych i nieodkrytych liter
			char wprowadzonyZnak = '\0';						//ostatni wprowadzony znak
			bool hasloOdgadniete = false;						//zmienna pomocnicza do kontroli czy haslo zostalo poprawnie odgadniete i gre mozna zakonczyc

			wypiszAktualnyStanTablicy(wprowadzonyZnak, aktualnyStanTablicy, haslo);
			while (hasloOdgadniete == false)																//glowna petla programu
			{
				wprowadzonyZnak = wprowadzanieZnaku(wprowadzonyZnak);										//input
				hasloOdgadniete = obslugaZnaku(wprowadzonyZnak, haslo, aktualnyStanTablicy, &stanKonta);	//processing
			}
			wygrana(&stanKonta);																			//output

			free(aktualnyStanTablicy);
			free(haslo);
			do
			{
				printf("\nChcesz grac dalej?\n (y\\Y) - tak\n (n\\N) - nie\n");
				if (!scanf(" %c", &graj))printf("\nBlad odczytu");
				char ch;
				while ((ch = getchar()) != '\n');
			} while (graj != 'y' && graj != 'n' && graj != 'N' && graj != 'Y');
		}
		_CrtDumpMemoryLeaks();
	}
	return 0;
}
