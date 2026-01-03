#include "Gra.h"

//Prywatne funkcje
void Gra::initVariables()
{
	this->okno = nullptr;


    this->punkty = 0;
    this->przeszkodaSpawnTimerMax = 10.f;
    this->przeszkodaSpawnTimer = this->przeszkodaSpawnTimerMax;
    this->maxPrzeszkody = 10;

}

void Gra::initWindow()
{
	this->Ustawienia_okna.height = 600;
	this->Ustawienia_okna.width = 800;
    this->okno = new sf::RenderWindow(this->Ustawienia_okna, "Racing Game", sf::Style::Titlebar | sf::Style::Close);
    this->okno->setFramerateLimit(60);
}

void Gra::initPrzeszkody()
{
    //W³aœciwoœci przeszkody
    
    this->przeszkoda.move(10.f, 10.f);
    this->przeszkoda.setSize(sf::Vector2f(15.f, 15.f));
    this->przeszkoda.setFillColor(sf::Color::Red);
    this->przeszkoda.setOutlineColor(sf::Color::Black);
    this->przeszkoda.setOutlineThickness(1.f);
}

//Konstruktory / Destruktory
Gra::Gra()
{
	this->initVariables();
	this->initWindow();
    this->initPrzeszkody();
}

Gra::~Gra()
{
	delete this->okno;
}

//Accessors
const bool Gra::running() const
{
	return this->okno->isOpen();
}



//Definicje funkcji


void Gra::stworzPrzeszkode()
{
    //Tworzenie przeszkód, losowanie ich wspolrzednych na ekranie, ustawianie ich koloru

    this->przeszkoda.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->okno->getSize().x - this->przeszkoda.getSize().x)),
        0.f
    );

    this->przeszkoda.setFillColor(sf::Color::Red);
    this->przeszkody.push_back(this->przeszkoda);
}

void Gra::pollEvents()
{
    //Sprawdzanie akcji
    while (this->okno->pollEvent(this->akcja))
    {
        if (akcja.type == sf::Event::Closed)
        {
            this->okno->close();
        }

        if (akcja.type == sf::Event::KeyPressed)
        {
            if (akcja.key.code == sf::Keyboard::Escape)
            {
                this->okno->close();
            }
        }
    }
}

void Gra::updateMousePositions()
{
    //Aktualizuje pozycje kursora wzglêdem okna s³u¿y do tego (Vector2i)
    this->poz_wzgledem_okna = sf::Mouse::getPosition(*this->okno);
    
    
}

void Gra::updatePrzeszkoda()
{
    if (this->przeszkody.size() < this->maxPrzeszkody)
    {
        if (this->przeszkodaSpawnTimer >= this->przeszkodaSpawnTimerMax)
        {
            //Tworzymy przeszkode i resetujemy timer jej powstawania
            this->stworzPrzeszkode();
            this->przeszkodaSpawnTimer = 0.f;
        }
        else
        {
            this->przeszkodaSpawnTimer += 1.f;
        }
    }

    for (auto& e : this->przeszkody)
    {
        e.move(0.f, 5.f);
    }
}

void Gra::update()
{

    this->pollEvents();
    
    this->updateMousePositions();

    this->updatePrzeszkoda();
}




void Gra::renderPrzeszkoda()
{
    for (auto& e : this->przeszkody)
    {
        this->okno->draw(e);
    }
}


void Gra::render()
{
    this->okno->clear();

    //Tu bêdzie rysowana gra
    this->renderPrzeszkoda();

    this->okno->display();
}


