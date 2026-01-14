#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Gracz.h"

class Gra
{

private:
	
	//Zmienne prywatne
	float predkosc_przeszkody;
	unsigned wynik;
	float predkosc_monety;
	float predkosc_gwiazdki;
	sf::Clock zegar;
	sf::Clock zegar_niewrazliwosci;
	sf::Time czas1;
	sf::Time czas_niewrazliwosci;
	
	
	//Zmienne okna
	sf::RenderWindow* okno;
	sf::VideoMode Ustawienia_okna;
	sf::Event akcja;
	sf::Font font_wyniku;
	sf::Text wyswietlanie_wyniku;

	//Pozycje kursora
	sf::Vector2i poz_wzgledem_okna;

	//Logika gry
	float przeszkodaSpawnTimer;
	float przeszkodaSpawnTimerMax;
	int maxPrzeszkody;

	//Obiekty
	std::vector<sf::RectangleShape> przeszkody;
	sf::RectangleShape przeszkoda;
	sf::RectangleShape moneta;
	sf::RectangleShape gwiazdka;
	sf::Texture pixleTlo;
	sf::RectangleShape tlo;

	// Title screen
	bool inTitleScreen;
	int selectedOption;
	sf::Font font;
	sf::Text title;
	sf::Text option[2];
	bool keyUpPressed;
	bool keyDownPressed;
	bool enterPressed;

	Gracz gracz;

	//Funkcje Private
	void initVariables();
	void initWindow();
	void initTlo();
	void initPrzeszkody();
	void initMoneta();
	void initGwiazdka();
	void initTitleScreen();
	void initFonts();
	void initWynikText();
	void handleTitleScreenInput();

public:
	
	//Konstruktury i destruktory
	Gra();
	virtual ~Gra();
	
	//Accessors
	const bool running() const;

	//Funkcje
	void stworzPrzeszkode();
	void pollEvents();
	
	void losowanie_drogi(sf::RectangleShape *obiekt);
	void updateMousePositions();
	void losowanie_rodzaju_przeszkody(sf::RectangleShape* obiekt);
	void updatePrzeszkoda();
	void updateMoneta();
	void updateGwiazdka();
	void updateText();
	void updateWynik();
	void update();
	
	void renderPrzeszkoda();
	void renderMoneta();
	void renderGwiazdka();
	void renderText();
	void render();
	
	//Zmienne
	
};
