/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H

/** Dla uproszczenia utworzony zosta³ typ bool.*/
typedef enum { false, true } bool;

/** Wyœwietlanie w oknie konsoli instrukcji obs³ugi parametrów.*/
void obslugaArgumentow();
/** Wyœwietlanie zasad gry, je¿eli jako parametr podano '-z'.*/
void wypiszZasady(); 
/** Losowanie i odczytywanie z pliku has³a.
@param nazwaPliku[] nazwa pliku z has³ami*/
char* czytajZPliku(char nazwaPliku[]);
/** Zakrywanie hasla w oknie konsoli u¿ytkownik bêdzie widzieæ znaki w iloœci i konfiguracji odpowiadaj¹cej tej we wzorze has³a.
@param haslo wzór has³a*/
char* zakryjHaslo(char* haslo); 
/** Wypisywanie w oknie konsolii aktualnego stanu odkrytych i nieodkrytych liter has³a.
@param litera wprowadzona przez u¿ytkownika litera
@param aktualnyStanTablicy[] tablica z ci¹giem odkrytych i nieodkrytych liter
@param haslo wzór has³a*/
void wypiszAktualnyStanTablicy(char litera, char aktualnyStanTablicy[], char haslo[]); 
/** Obs³uga wprowadzania pojedynczej litery.
@param wprowadzonyZnak wprowadzony przez u¿ytkownika znak jeszcze niezdefiniowany jako litera, b¹dŸ "?"*/
char wprowadzanieZnaku(char wprowadzonyZnak); 
/** Powiadomienie u¿ytkownika o wygranej rundzie i wyœwietlenie stanu konta.
@param stanKonta aktualny stan konta*/
void wygrana(int* stanKonta); 
/** Zliczanie wyst¹pieñ litery w haœle mno¿nika punktów w wypadku wprowadzenia spó³g³oski.
@param wprowadzonaLitera wprowadzony przez u¿ytkownika znak rozpoznany jako litera
@param haslo wzór has³a
@param aktualnyStanTablicy[] tablica z ci¹giem odkrytych i nieodkrytych liter*/
int liczWystapieniaLiteryWHasle(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[]); 
/** Losowanie wartoœci od 0 do 10 bêd¹cych iloœci¹ punktów za wprowadzon¹ spó³g³oskê. Wylosowanie 0 oznacza wyzerowanie konta.
@param wystapieniaLiteryWHasle liczba wyst¹pieñ litery we wzorze has³a
@param stanKonta aktualny stan konta*/
int koloFortuny(int wystapieniaLiteryWHasle, int* stanKonta);
/** Sprawdzenie czy aktualny stan tablicy jest taki sam jak wzor hasla.
@param haslo wzór has³a
@param aktualnyStanTablicy[] tablica z ci¹giem odkrytych i nieodkrytych liter*/
bool sprawdzCzyWygrana(char haslo[], char aktualnyStanTablicy[]); 
/** Decyzja co zrobiæ dalej, gdy ju¿ wiadomio, ¿e wprowadzony znak jest liter¹.
@param wprowadzonaLitera wprowadzony przez u¿ytkownika znak rozpoznany jako litera
@param haslo wzór has³a
@param aktualnyStanTablicy[] tablica z ci¹giem odkrytych i nieodkrytych liter
@param stanKonta aktualny stan konta*/
bool znakJestLitera(char wprowadzonaLitera, char haslo[], char aktualnyStanTablicy[], int* stanKonta);
/** Sprawdzenie czy ci¹g znaków podanych po wprowadzeniu przez u¿ytkowanika "?" jest zgodny ze wzorem has³a.
@param haslo wzór has³a*/
bool zgadywanieHasla(char haslo[]); 
/** Definiowanie czy u¿ytkownik wprowadzi³ poprawny znak bêd¹cy liter¹ lub czy chce podaæ pe³ne has³o.
@param wprowadzonyZnak wprowadzony przez u¿ytkownika znak jeszcze niezdefiniowany jako litera, b¹dŸ "?"
@param haslo wzór has³a
@param aktualnyStanTablicy[] tablica z ci¹giem odkrytych i nieodkrytych liter
@param stanKonta aktualny stan konta*/
bool obslugaZnaku(char wprowadzonyZnak, char haslo[], char aktualnyStanTablicy[], int* stanKonta); 

#endif
