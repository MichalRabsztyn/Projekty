/** @file */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "funkcje.h"



void wypiszZasady()
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\
	\n$\t\tWITAJ W KOLE FORTUNY\t\t   $\
	\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\
	\nPRZEBIEG GRY:\
	\n1. Na poczatku haslo bedzie zakryte\
	\n2. Twoim zadaniem jest podanie litery (bez polskich znakow)\
	\n\t2a. jezeli podasz spolgloske, Kolo Fortuny wylosuje dla ciebie ilosc ECTSow, ktora zostanie dodana do Twojego indeksu\
	\n\t2b. jezeli podasz samogloske, z twojego konta odjete zostana 3 ECTSy\
	\n3. Mozesz podac cale haslo wpisujac \"?\", enter i wpisujac haslo");
}

void obslugaArgumentow()
{
	printf("\nObsluga:\
	\n -h\t\tplik z haslami\
	\n -z\t\tpokaz zasady (argument nieobowiazkowy)");
}

char* czytajZPliku(char nazwaPliku[])
{
	char kategoria[32];						//bufor na odczyt kategorii
	char buffer[64];						//bufor na odczyt hasla
	for (int i = 0; i < 64; i++)
	{
		buffer[i] = '\0';
	}
	int losowanie = rand() % 50 + 1;		//losowanie numeru hasla w pliku - "% * +" gdzie "*" to liczba hasel w pliku  
	FILE* file = fopen(nazwaPliku, "r");
	if (file != NULL)
	{
		for (int i = 0; i < losowanie; i++)
		{
			if (fscanf(file, "%s  %[^\n]", kategoria, buffer) == 0) printf("\nBlad odczytu");				//odczyt "kategoria" "reszta linii"
		}
		fclose(file);
		printf("\n\nHaslo nalezy do kategorii: %s\n", kategoria);
	}
	else
	{
		printf("\nWystapil problem ze znalezieniem hasel, sprobuj ponownie\n");
	}
	char* haslo = (char*)malloc((strlen(buffer) + 1)*sizeof(char));		//alokacja pamieci dla wzoru hasla
	if(haslo)strcpy(haslo, buffer);
	return haslo;														//zwracany wskaznik na wzor hasla
}

char* zakryjHaslo(char* haslo)
{
	char* ukryteLitery = NULL;
	ukryteLitery = (char*)malloc((strlen(haslo) + 1) * sizeof(char));	//alokacja pamieci na przetrzymywanie aktualnego stanu tablicy
	if (ukryteLitery)
	{
		strcpy(ukryteLitery, haslo);
		for (size_t i = 0; i < strlen(ukryteLitery); i++)				//podmiana liter z hasla na prostokaty
		{
			if (ukryteLitery[i] != ' ')
			{
				ukryteLitery[i] = 170;									//znak ascii 170 " ¬ "			
			}
		}
	}
	return ukryteLitery;												//zwracany wskaznik na stan tablicy
}

void wypiszAktualnyStanTablicy(char litera, char aktualnyStanTablicy[], char haslo[])
{
	if (litera != '\0')
	{
		for (size_t i = 0; i < strlen(haslo); i++)						//dopisanie nowej litery do aktualnego stanu tablicy
		{
			if (haslo[i] != ' ' && haslo[i] == litera)
			{
				aktualnyStanTablicy[i] = litera;
			}
		}
	}
	printf("\n%s\n\n", aktualnyStanTablicy);							//wypisanie aktualnego stanu tablicy na ekran
}

char wprowadzanieZnaku(char wprowadzonyZnak)
{
	if(!scanf(" %c", &wprowadzonyZnak)) printf("\nBlad odczytu");										//odczyt pierwszego wprowadzonego znaku
	char ch;															//zmienna pomocnicza
	while ((ch = getchar()) != '\n');									//zapewnienie ze uzytkownik poda tylko jeden znak
	return wprowadzonyZnak;												//zwracany wprowadzony znak
}

void wygrana(int* stanKonta)
{
	printf("\nW Y G R A N A\n");
	printf("\nTwoj koncowy wynik to %d ECTS", *stanKonta);
	if (*stanKonta == 0 || *stanKonta >= 5)								//rozroznienie koncowek fleksyjnych 
	{
		printf("ow\n");
	}
	else if (*stanKonta != 1)
	{
		printf("y\n");
	}
}

int liczWystapieniaLiteryWHasle(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[])
{
	int wystapieniaLiteryWHasle = 0;
	for (size_t i = 0; i < strlen(haslo); i++)							//liczenie wystapien litery pod warunkiem ze jest w hasle i nie zostala wprowadzona wczesniej
	{
		if (wprowadzonaLitera == haslo[i] && wprowadzonaLitera != aktualnyStanTablicy[i])
		{
			wystapieniaLiteryWHasle++;
		}
	}
	return wystapieniaLiteryWHasle;										//zwracana liczba wystapien litery w hasle
}

int koloFortuny(int wystapieniaLiteryWHasle, int* stanKonta)
{
	int kolo = rand() % 10;				//losowanie wartosci na kole fortuny z zakresu 0-9
	if (kolo == 0)
	{
		printf("\nB A N K R U T");										//wylosowanie 0 oznacza wyzerowanie konta
		*stanKonta = 0;
		return 0;														//zwracana informacja o wyzerowaniu
	}
	else
	{
		*stanKonta += wystapieniaLiteryWHasle * kolo;					//dodanie do konta wartosci wskazanej przez kolo pomnozonej przez ilosc wystapien litery w hasle
		printf("\nDO TWOJEGO KONTA DODANO %d ECTS-OW (%d * %d)\n", wystapieniaLiteryWHasle * kolo, wystapieniaLiteryWHasle, kolo);
		return 1;														//zwracana informacja o tym ze kolo wskazalo wartosc rozna od zera
	}
}

bool sprawdzCzyWygrana(char haslo[], char aktualnyStanTablicy[])
{
	for (size_t i = 0; i < strlen(haslo); i++)							//sprawdzanie czy znaki w hasle i na tablicy sa identyczne
	{
		if (haslo[i] != aktualnyStanTablicy[i])							
		{
			return false;												//zwracana informacja o roznicy w hasle i na tablicy
		}
	}
	return true;														//zwracana informacja o odgadnietym hasle
}

bool znakJestLitera(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[], int* stanKonta)
{
	if (wprowadzonaLitera >= 'A' && wprowadzonaLitera <= 'Z')			//zabezpieczenie przed wprowadzeniem liter roznej wielkosci
	{
		wprowadzonaLitera = wprowadzonaLitera + 32;
	}
	int wystapieniaLiteryWHasle = liczWystapieniaLiteryWHasle(wprowadzonaLitera, haslo, aktualnyStanTablicy);
	if (wystapieniaLiteryWHasle != 0)
	{
		if (wprowadzonaLitera == 'a' || wprowadzonaLitera == 'e' || wprowadzonaLitera == 'i' || wprowadzonaLitera == 'o' || wprowadzonaLitera == 'u' || wprowadzonaLitera == 'y')
		{																//obsluga samogloski
			if (*stanKonta >= 3)
			{
				*stanKonta -= 3;
				printf("\nZAKUPIONO SAMOGLOSKE ZA 3 ECTS-Y\n");
			}
			else														
			{
				wprowadzonaLitera = '\0';
				printf("\nBRAK WYSTARCZAJACYCH SRODKOW NA KONCIE\n");
			}
		}
		else															//obsluga spolgloski
		{
			if (koloFortuny(wystapieniaLiteryWHasle, stanKonta) == 0)
			{
				wprowadzonaLitera = '\0';
			}
		}
	}
	else
	{
		printf("\nZA TE LITERE NIE MA PUNKTOW\n");
	}
	printf("\nStan konta: %d\n", *stanKonta);
	wypiszAktualnyStanTablicy(wprowadzonaLitera, aktualnyStanTablicy, haslo);

	return sprawdzCzyWygrana(haslo, aktualnyStanTablicy);				//zwracana informacja o wygranej
}

bool zgadywanieHasla(char haslo[])
{
	char odgadywaneHaslo[128];			//bufor na odgadywane haslo
	fgets(odgadywaneHaslo, sizeof odgadywaneHaslo, stdin);
	if (strlen(haslo) != (strlen(odgadywaneHaslo) - 1))					//sprawdzenie prawidlowosci na podstawie dlugosci podanego hasla i wzoru
	{
		printf("\nNieprawidlowe haslo\n");
		return false;													//zwracana informacja o nieprawidlowosci hasla
	}
	else
	{
		int i = 0;
		bool identyczne = true;
		while (identyczne && odgadywaneHaslo[i + 1] != '\0')			//porownywanie hasel litera po literze
		{
			if (haslo[i] != odgadywaneHaslo[i])
			{
				identyczne = false;
			}
			else i++;
		}
		if (identyczne)
		{
			return true;												//zwracana informacja o prawidlowosci hasla
		}
		else
		{
			printf("\nNieprawidlowe haslo\n");
			return false;												//zwracana informacja o nieprawidlowosci hasla
		}
	}
}

bool obslugaZnaku(char wprowadzonyZnak, char haslo[], char aktualnyStanTablicy[], int* stanKonta)
{
	if ((wprowadzonyZnak >= 'a' && wprowadzonyZnak <= 'z') || (wprowadzonyZnak >= 'A' && wprowadzonyZnak <= 'Z'))	//sprawdzenie czy wprowadzony znak jest litera
	{
		return znakJestLitera(wprowadzonyZnak, haslo, aktualnyStanTablicy, stanKonta);								//zwracana informacja czy haslo zostalo zgadniete
	}
	else if (wprowadzonyZnak == '?')																				//wprowadzenie "?" pozwala na wpisanie calego hasla
	{
		return zgadywanieHasla(haslo);																				//zwracana informacja czy haslo zostalo zgadniete
	}
	else
	{
		printf("\nNiepoprawny znak\n");
		return false;																								//zwracana informacja o nieprawidlowosci znaku
	}
}
