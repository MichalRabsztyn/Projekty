/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H

/** Dla uproszczenia utworzony zosta� typ bool.*/
typedef enum { false, true } bool;

/** Wy�wietlanie w oknie konsoli instrukcji obs�ugi parametr�w.*/
void obslugaArgumentow();
/** Wy�wietlanie zasad gry, je�eli jako parametr podano '-z'.*/
void wypiszZasady(); 
/** Losowanie i odczytywanie z pliku has�a.
@param nazwaPliku[] nazwa pliku z has�ami*/
char* czytajZPliku(char nazwaPliku[]);
/** Zakrywanie hasla w oknie konsoli u�ytkownik b�dzie widzie� znaki w ilo�ci i konfiguracji odpowiadaj�cej tej we wzorze has�a.
@param haslo wz�r has�a*/
char* zakryjHaslo(char* haslo); 
/** Wypisywanie w oknie konsolii aktualnego stanu odkrytych i nieodkrytych liter has�a.
@param litera wprowadzona przez u�ytkownika litera
@param aktualnyStanTablicy[] tablica z ci�giem odkrytych i nieodkrytych liter
@param haslo wz�r has�a*/
void wypiszAktualnyStanTablicy(char litera, char aktualnyStanTablicy[], char haslo[]); 
/** Obs�uga wprowadzania pojedynczej litery.
@param wprowadzonyZnak wprowadzony przez u�ytkownika znak jeszcze niezdefiniowany jako litera, b�d� "?"*/
char wprowadzanieZnaku(char wprowadzonyZnak); 
/** Powiadomienie u�ytkownika o wygranej rundzie i wy�wietlenie stanu konta.
@param stanKonta aktualny stan konta*/
void wygrana(int* stanKonta); 
/** Zliczanie wyst�pie� litery w ha�le mno�nika punkt�w w wypadku wprowadzenia sp�g�oski.
@param wprowadzonaLitera wprowadzony przez u�ytkownika znak rozpoznany jako litera
@param haslo wz�r has�a
@param aktualnyStanTablicy[] tablica z ci�giem odkrytych i nieodkrytych liter*/
int liczWystapieniaLiteryWHasle(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[]); 
/** Losowanie warto�ci od 0 do 10 b�d�cych ilo�ci� punkt�w za wprowadzon� sp�g�osk�. Wylosowanie 0 oznacza wyzerowanie konta.
@param wystapieniaLiteryWHasle liczba wyst�pie� litery we wzorze has�a
@param stanKonta aktualny stan konta*/
int koloFortuny(int wystapieniaLiteryWHasle, int* stanKonta);
/** Sprawdzenie czy aktualny stan tablicy jest taki sam jak wzor hasla.
@param haslo wz�r has�a
@param aktualnyStanTablicy[] tablica z ci�giem odkrytych i nieodkrytych liter*/
bool sprawdzCzyWygrana(char haslo[], char aktualnyStanTablicy[]); 
/** Decyzja co zrobi� dalej, gdy ju� wiadomio, �e wprowadzony znak jest liter�.
@param wprowadzonaLitera wprowadzony przez u�ytkownika znak rozpoznany jako litera
@param haslo wz�r has�a
@param aktualnyStanTablicy[] tablica z ci�giem odkrytych i nieodkrytych liter
@param stanKonta aktualny stan konta*/
bool znakJestLitera(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[], int* stanKonta);
/** Sprawdzenie czy ci�g znak�w podanych po wprowadzeniu przez u�ytkowanika "?" jest zgodny ze wzorem has�a.
@param haslo wz�r has�a*/
bool zgadywanieHasla(char haslo[]); 
/** Definiowanie czy u�ytkownik wprowadzi� poprawny znak b�d�cy liter� lub czy chce poda� pe�ne has�o.
@param wprowadzonyZnak wprowadzony przez u�ytkownika znak jeszcze niezdefiniowany jako litera, b�d� "?"
@param haslo wz�r has�a
@param aktualnyStanTablicy[] tablica z ci�giem odkrytych i nieodkrytych liter
@param stanKonta aktualny stan konta*/
bool obslugaZnaku(char wprowadzonyZnak, char haslo[], char aktualnyStanTablicy[], int* stanKonta); 

#endif
