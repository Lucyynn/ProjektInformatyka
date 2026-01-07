#include "Gra.h"

//Prywatne funkcje


void Gra::initVariables()
{
	this->okno = nullptr;


    
    this->przeszkodaSpawnTimerMax = 50.f;
    this->przeszkodaSpawnTimer = this->przeszkodaSpawnTimerMax;
    this->maxPrzeszkody = 100;

}

void Gra::initWindow()
{
	//W³aœciwoœci okna
	this->Ustawienia_okna.height = 800;
	this->Ustawienia_okna.width = 800;
    this->okno = new sf::RenderWindow(this->Ustawienia_okna, "Racing Game", sf::Style::Titlebar | sf::Style::Close);
    this->okno->setFramerateLimit(60);
}

void Gra::initPrzeszkody()
{
    //W³aœciwoœci przeszkody
    
    //this->przeszkoda.move(10.f, 10.f);
    this->przeszkoda.setSize(sf::Vector2f(120.f, 30.f));
    this->przeszkoda.setFillColor(sf::Color::Red);
    
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
    int miejsce_przeszkody = rand() % 3;
    
    if (miejsce_przeszkody == 0)
    {
        this->przeszkoda.setPosition(
            static_cast<float>(static_cast<int>( this->okno->getSize().x / 4 - this->przeszkoda.getSize().x / 2)),
            0.f
        );
    }
    if (miejsce_przeszkody == 1)
    {
        this->przeszkoda.setPosition(static_cast<int>(this->okno->getSize().x / 4 * 2 - this->przeszkoda.getSize().x / 2),
            0.f
        );
	}
    if (miejsce_przeszkody == 2)
    {
        this->przeszkoda.setPosition(static_cast<int>(this->okno->getSize().x / 4 * 3 - this->przeszkoda.getSize().x / 2),
            0.f
        );
    }
    
	 
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

	//Ruch przeszkody w dó³ ekranu

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
    gracz.update(this->okno, this->przeszkoda.getSize().x);
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
	this->gracz.render(this->okno);
	
    
    
    //Wyœwietlenie okna
    this->okno->display();
}


