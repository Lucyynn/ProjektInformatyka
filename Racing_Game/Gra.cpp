#include "Gra.h"
#include <Windows.h>
//Prywatne funkcje


void Gra::initVariables()
{
	this->okno = nullptr;
    
    inTitleScreen = true;
    this->wynik = 0.f;
    selectedOption = 0;
    keyUpPressed = keyDownPressed = enterPressed = false;
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
    this->przeszkoda.setSize(sf::Vector2f(60.f, 120.f));
    this->przeszkoda.setFillColor(sf::Color::Red);
    this->predkosc_przeszkody = 2.f;
    
    
    
    this->maxPrzeszkody = 10;
    this->przeszkodaSpawnTimerMax = 100.f;
    this->przeszkodaSpawnTimer = this->przeszkodaSpawnTimerMax;
}

void Gra::initMoneta()
{
	this->moneta.setSize(sf::Vector2f(30.f, 30.f));
	this->moneta.setFillColor(sf::Color::Yellow);
	this->moneta.setPosition(this->okno->getSize().x / 2 - this->moneta.getSize().x / 2, 400.f);
	this->predkosc_monety = 5.f;
}

// funkcja init title screen
void Gra::initTitleScreen()
{
    if (!font.loadFromFile("font.ttf"))
    {
        std::cerr << "Nie mozna wczytac fontu" << std::endl;
    }

    title.setFont(font);
    title.setString("RACING GAME");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    title.setPosition(this->okno->getSize().x / 2.f, 100.f);

    option[0].setFont(font);
    option[0].setString("NOWA GRA");
    option[0].setCharacterSize(30);
    option[0].setFillColor(sf::Color::Red);
    sf::FloatRect opt0Bounds = option[0].getLocalBounds();
    option[0].setOrigin(opt0Bounds.width / 2.f, opt0Bounds.height / 2.f);
    option[0].setPosition(this->okno->getSize().x / 2.f, 300.f);

    option[1].setFont(font);
    option[1].setString("WYJSCIE");
    option[1].setCharacterSize(30);
    option[1].setFillColor(sf::Color::White);
    sf::FloatRect opt1Bounds = option[1].getLocalBounds();
    option[1].setOrigin(opt1Bounds.width / 2.f, opt1Bounds.height / 2.f);
    option[1].setPosition(this->okno->getSize().x / 2.f, 400.f);
}

void Gra::initFonts()
{
    if (!this->font_wyniku.loadFromFile("Dosis_font.ttf"))
    {
		std::cout << "ERROR::GRA::INITFONTS:: Nie mozna wczytac fontu wyniku" << std::endl;
    }
}

void Gra::initWynikText()
{
	this->wyswietlanie_wyniku.setFont(this->font_wyniku);
    this->wyswietlanie_wyniku.setCharacterSize(16);
	this->wyswietlanie_wyniku.setFillColor(sf::Color::White);
	this->wyswietlanie_wyniku.setPosition(10.f, 10.f);
}

// funkcja handle title screen
void Gra::handleTitleScreenInput()
{
    if (akcja.type == sf::Event::KeyPressed)
    {
        if (akcja.key.code == sf::Keyboard::Up && !keyUpPressed)
        {
            selectedOption--;
            if (selectedOption < 0) selectedOption = 1;
            keyUpPressed = true;
        }
        else if (akcja.key.code == sf::Keyboard::Down && !keyDownPressed)
        {
            selectedOption++;
            if (selectedOption > 1) selectedOption = 0;
            keyDownPressed = true;
        }
        else if (akcja.key.code == sf::Keyboard::Enter && !enterPressed)
        {
            enterPressed = true;
            if (selectedOption == 0) { inTitleScreen = false; zegar.restart(); } // NOWA GRA
            else if (selectedOption == 1) okno->close();    // WYJSCIE
        }
    }
    else if (akcja.type == sf::Event::KeyReleased)
    {
        if (akcja.key.code == sf::Keyboard::Up) keyUpPressed = false;
        if (akcja.key.code == sf::Keyboard::Down) keyDownPressed = false;
        if (akcja.key.code == sf::Keyboard::Enter) enterPressed = false;
    }
}

//Konstruktory / Destruktory

Gra::Gra()
{
    
    this->initVariables();
    this->initWindow();
    this->initFonts();
	
    
	
    this->initWynikText();
    this->initTitleScreen();
    this->initPrzeszkody();
    this->initMoneta();
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
    
	losowanie_drogi(&this->przeszkoda);
	 
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
    

    if (inTitleScreen) 
        handleTitleScreenInput();
    }
}




void Gra::losowanie_drogi(sf::RectangleShape *obiekt)
{
    int wylosowane_miejsce = rand() % 3;

    if (wylosowane_miejsce == 0)
    {
        obiekt->setPosition(
            static_cast<float>(static_cast<int>(this->okno->getSize().x / 4 - obiekt->getSize().x / 2)),
            0.f
        );
    }
    if (wylosowane_miejsce == 1)
    {
        obiekt->setPosition(static_cast<int>(this->okno->getSize().x / 4 * 2 - obiekt->getSize().x / 2),
            0.f
        );
    }
    if (wylosowane_miejsce == 2)
    {
        obiekt->setPosition(static_cast<int>(this->okno->getSize().x / 4 * 3 - obiekt->getSize().x / 2),
            0.f
        );
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
        e.move(0.f, predkosc_przeszkody);
        if (e.getPosition().y > this->okno->getSize().y)
        {
            // Usuwanie przeszkody, gdy wyjdzie poza ekran
            this->przeszkody.erase(this->przeszkody.begin());
        }

        //Sprawdzanie kolizcji przeszkody z graczem
		if (e.getGlobalBounds().intersects(this->gracz.ksztalt.getGlobalBounds()))
        {
            std::cout << "Kolizja wykryta!" << std::endl;
            
            
            this->przeszkody.clear();
			this->gracz.ksztalt.setPosition(385.f, 700.f);
			inTitleScreen = true;
            keyUpPressed = keyDownPressed = enterPressed = false;
            selectedOption = 0;
            wynik = 0.f;
            this->moneta.setPosition(this->okno->getSize().x / 2 - this->moneta.getSize().x / 2, 400.f);
            
            
            
		}
    }
    
    
    
    
}

void Gra::updateMoneta()
{
    if(this->moneta.getGlobalBounds().intersects(this->gracz.ksztalt.getGlobalBounds()))
    {
        //Zbieranie monety
        this->wynik += 50.f;
		//Przeniesienie monety w losowe miejsce
        
		losowanie_drogi(&this->moneta);
	}

	moneta.move(0.f, predkosc_monety);
    
    if(moneta.getPosition().y > this->okno->getSize().y)
    {
        //Przeniesienie monety w losowe miejsce gdy wyjdzie poza ekran
        losowanie_drogi(&this->moneta);
	}
}

void Gra::updateText()
{
	this->wyswietlanie_wyniku.setString("Wynik: " + std::to_string((this->wynik)));
}

void Gra::updateWynik()
{
    
    this->czas1 = zegar.getElapsedTime();
    if (this->czas1.asSeconds() >= 1.f)
    {
        zegar.restart();
        wynik += 10.f;
    }
    
}



void Gra::update()
{
    this->pollEvents();
    this->updateMousePositions();
    

    if (!inTitleScreen)
    {
        
        
        gracz.update(this->okno, this->przeszkoda.getSize().x);
        this->updatePrzeszkoda();
        this->updateMoneta();
        updateWynik();
        updateText();
        
        return;
    }
    
    
}



void Gra::renderPrzeszkoda()
{
	//Rysowanie przeszkód
    
    for (auto& e : this->przeszkody)
    {
        this->okno->draw(e);
		std::cout << "Przeszkoda rysowana na pozycji: " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
    }
    
    
}

void Gra::renderMoneta()
{
    this->okno->draw(this->moneta);
}

void Gra::renderText()
{
    this->okno->draw(this->wyswietlanie_wyniku);

}


void Gra::render()
{
	//Wyczyszczenie okna przed rysowaniem
    // dodatki do title screen
    if (inTitleScreen)
    {
        for (int i = 0; i < 2; i++)
            option[i].setFillColor(i == selectedOption ? sf::Color::Red : sf::Color::White);

        this->okno->draw(title);
        for (int i = 0; i < 2; i++)
            this->okno->draw(option[i]);

        this->okno->display();
        return;
    }
    
    this->okno->clear();

    //Tu bêdzie rysowana gra
    
    
    this->renderPrzeszkoda();
    this->renderMoneta();
    this->gracz.render(this->okno);
    this->renderText();
    
    
    //Wyœwietlenie okna
    this->okno->display();
}


