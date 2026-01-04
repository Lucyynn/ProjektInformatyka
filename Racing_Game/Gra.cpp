#include "Gra.h"

//Prywatne funkcje
void Gra::initVariables()
{
	this->okno = nullptr;


    this->punkty = 0;
    this->przeszkodaSpawnTimerMax = 10.f;
    this->przeszkodaSpawnTimer = this->przeszkodaSpawnTimerMax;
    this->maxPrzeszkody = 100;

}

void Gra::initWindow()
{
	this->Ustawienia_okna.height = 800;
	this->Ustawienia_okna.width = 600;
    this->okno = new sf::RenderWindow(this->Ustawienia_okna, "Racing Game", sf::Style::Titlebar | sf::Style::Close);
    this->okno->setFramerateLimit(60);
}

void Gra::initPrzeszkody()
{
    //W³aœciwoœci przeszkody
    
    //this->przeszkoda.move(10.f, 10.f);
    this->przeszkoda.setSize(sf::Vector2f(15.f, 15.f));
    this->przeszkoda.setFillColor(sf::Color::Red);
    this->przeszkoda.setOutlineColor(sf::Color::White);
    this->przeszkoda.setOutlineThickness(5.f);
}

void Gra::initGracza()
{
    //W³aœciwoœci gracza
    this->gracz.setSize(sf::Vector2f(20.f, 50.f));
    this->gracz.setFillColor(sf::Color::Green);
    this->gracz.setOutlineColor(sf::Color::White);
    this->gracz.setOutlineThickness(5.f);
    this->gracz.setPosition(
        static_cast<float>(this->okno->getSize().x / 2.f - this->gracz.getSize().x / 2.f),
        static_cast<float>(this->okno->getSize().y - this->gracz.getSize().y - 10.f)
	);
    
}


//Konstruktory / Destruktory
Gra::Gra()
{
	this->initVariables();
	this->initWindow();
    this->initPrzeszkody();
    this->initGracza();

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

	//this->przeszkoda.setFillColor(sf::Color::Red); //Kolor ju¿ zosta³ wczeœniej ustawiony w initPrzeszkody() zbêdne? 
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

void Gra::updateGracza()
{
    if (akcja.type == sf::Event::KeyPressed)
    {
		//Podstawowy ruch gracza
        if (akcja.key.code == sf::Keyboard::Right)
        {
            this->gracz.move(10.f, 0.f);
        }
        if (akcja.key.code == sf::Keyboard::Left)
        {
            this->gracz.move(-10.f, 0.f);
        }
        if (akcja.key.code == sf::Keyboard::Up)
        {
            this->gracz.move(0.f, -10.f);
        }
        if (akcja.key.code == sf::Keyboard::Down)
        {
            this->gracz.move(0.f, 10.f);
        }
        
		//Ograniczenie ruchu gracza w osi X
        if (this->gracz.getPosition().x >= this->okno->getSize().x - this->gracz.getSize().x)
        {
            this->gracz.move(-10.f, 0.f);
        }
        
        if (this->gracz.getPosition().x <= 0)
        {
            this->gracz.move(10.f, 0.f);
        }
        
		//Ograniczenie ruchu gracza w osi Y
        if (this->gracz.getPosition().y >= this->okno->getSize().y - this->gracz.getSize().y - 5.f)
        {
            this->gracz.move(0.f, -10.f);
        }

        if (this->gracz.getPosition().y < 5)
        {
            this->gracz.move(0.f, 10.f);
        }
    }
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
    this->updateGracza();
}




void Gra::renderGracza()
{
	//Rysowanie gracza
	this->okno->draw(this->gracz);
}

void Gra::renderPrzeszkoda()
{
	//Rysowanie przeszkód
    for (auto& e : this->przeszkody)
    {
        this->okno->draw(e);
    }
}


void Gra::render()
{
	//Wyczyszczenie okna przed rysowaniem
    this->okno->clear();

    //Tu bêdzie rysowana gra
    this->renderPrzeszkoda();
    this->renderGracza();

	//Wyœwietlenie okna
    this->okno->display();
}


