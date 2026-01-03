#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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
	int punkty;
	float przeszkodaSpawnTimer;
	float przeszkodaSpawnTimerMax;
	int maxPrzeszkody;

	//Obiekty
	std::vector<sf::RectangleShape> przeszkody;
	sf::RectangleShape przeszkoda;
	

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
	
	void render();
	void renderPrzeszkoda();
};
