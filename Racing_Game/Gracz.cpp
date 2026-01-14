#include "Gracz.h"
#include <iostream>


void Gracz::initVariables()
{
    this->predkosc_gracza = 10.f;

}

void Gracz::initKsztalt()
{
    this->pixelAuto.loadFromFile("assets/auto2v2.png");
    
    this->ksztalt.setSize(sf::Vector2f(100.f, 100.f));
    this->ksztalt.setTexture(&this->pixelAuto);
}

    
Gracz::Gracz(float x, float y)
{
	
    initKsztalt();
    initVariables();
    ksztalt.setPosition(x, y);
}

Gracz::~Gracz()
{
    
}


void Gracz::update(sf::RenderTarget* target, float przeszkoda_size)
{
	updateInput(target, przeszkoda_size);
}



void Gracz::updateInput(sf::RenderTarget* target, float przeszkoda_size)
{
	//Ruch gracza w lewo i prawo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        //if (ksztalt.getPosition().x > target->getSize().x / 4 - przeszkoda_size / 2 - this->ksztalt.getSize().x / 2)
        //{
        //    this->ksztalt.move(-this->predkosc_gracza, 0.f);
        //}
        if (ksztalt.getPosition().x > 0.f + 25.f)
        {
            this->ksztalt.move(-this->predkosc_gracza, 0.f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        //if (ksztalt.getPosition().x < (target->getSize().x / 4 * 3) + przeszkoda_size / 2 - this->ksztalt.getSize().x / 2)
        //{
        //    this->ksztalt.move(this->predkosc_gracza, 0.f);
        //}
        if (ksztalt.getPosition().x < 800.f - 125.f)
        {
            this->ksztalt.move(this->predkosc_gracza, 0.f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (ksztalt.getPosition().y > 0.f)
        {
            this->ksztalt.move(0.f, -this->predkosc_gracza);
        }
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (ksztalt.getPosition().y < target->getSize().y - this->ksztalt.getSize().y)
        {
            this->ksztalt.move(0.f, this->predkosc_gracza);
        }
	}

}

void Gracz::render(sf::RenderTarget* target)
{
	target->draw(this->ksztalt);
}