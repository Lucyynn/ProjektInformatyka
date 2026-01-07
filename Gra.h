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
	sf::RectangleShape gracz;
	
    // Title screen
    bool inTitleScreen;
    int selectedOption;
    sf::Font font;
    sf::Text title;
    sf::Text option[2];
    bool keyUpPressed;
    bool keyDownPressed;
    bool enterPressed;

	//Funkcje Private
    void initVariables();
    void initWindow();
    void initPrzeszkody();
    void initGracza();
    void initTitleScreen();
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
    void updateMousePositions();
    void updateGracza();
    void updatePrzeszkoda();
    void update();

    void renderGracza();
    void renderPrzeszkoda();
    void renderTitleScreen();
    void render();
};