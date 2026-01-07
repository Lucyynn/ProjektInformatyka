#include "Gracz.h"


void Gracz::initVariables()
{
    this->predkosc_gracza = 10.f;

}

void Gracz::initKsztalt()
{
    this->ksztalt.setSize(sf::Vector2f(30.f, 30.f));
    this->ksztalt.setFillColor(sf::Color::Green);
}

    
Gracz::Gracz(float x, float y)
{
	
	ksztalt.setPosition(x, y);
    initKsztalt();
    initVariables();
    
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
        if (ksztalt.getPosition().x > target->getSize().x / 4 - przeszkoda_size / 2 - this->ksztalt.getSize().x / 2)
        {
            this->ksztalt.move(-this->predkosc_gracza, 0.f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(ksztalt.getPosition().x < (target->getSize().x / 4 * 3)  + przeszkoda_size / 2 - this->ksztalt.getSize().x / 2)
        this->ksztalt.move(this->predkosc_gracza, 0.f);
    }

}

void Gracz::render(sf::RenderTarget* target)
{
	target->draw(this->ksztalt);
}