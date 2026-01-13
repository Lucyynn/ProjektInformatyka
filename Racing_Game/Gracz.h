#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Gracz
{
private:
	//Obiekty
	
	
	//Funkcje prywatne
	void initVariables();
	void initKsztalt();

	//Zmienne prywatne
	float predkosc_gracza;
public:
	
	//Konstruktory / Destruktory
	
	Gracz(float x = 385.f, float y = 700.f);
	virtual ~Gracz();
	
	
	//Zmienne publiczne
	bool niewrazliwosc_na_przeszkody = false;

	//Funkcje publiczne
	sf::RectangleShape ksztalt;
	sf::Texture pixelAuto;
	void updateInput(sf::RenderTarget* target, float przeszkoda_size);
	void update(sf::RenderTarget* target, float przeszkoda_size);
	void render(sf::RenderTarget *target);
};

