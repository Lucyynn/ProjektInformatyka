#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Gracz.h"

class Gra
{

private:
	
	//Zmienne okna
	
	sf::RenderWindow* okno;
	sf::VideoMode Ustawienia_okna;
	sf::Event akcja;
	
	//Pozycje kursora
	sf::Vector2i poz_wzgledem_okna;

	//Logika gry
	
	float przeszkodaSpawnTimer;
	float przeszkodaSpawnTimerMax;
	int maxPrzeszkody;

	//Obiekty
	std::vector<sf::RectangleShape> przeszkody;
	sf::RectangleShape przeszkoda;
	
	
	Gracz gracz;

	//Funkcje Private
	void initVariables();
	void initWindow();
	void initPrzeszkody();

public:
	
	//Konstruktury i destruktory
	Gra();
	virtual ~Gra();
	
	//Accessors
	const bool running() const;

	//Funkcje
	void stworzPrzeszkode();
	void pollEvents();
	
	void updateMousePositions();
	void updatePrzeszkoda();
	void update();
	
	void renderPrzeszkoda();
	void render();
	
	//Zmienne
	
};
