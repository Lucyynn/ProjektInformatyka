#include "Gra.h"
#include <ctime>
//Zmiana w kodzie
//Test commit new branch
int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Gra gra;

    //Nasluchiwanie akcji i podtrzymywanie okna
    while (gra.running())
    {
        //Wyczyszczenie poprzedniej klatki
        gra.update();
        //Wyświetlanie stworzonego okna
        gra.render();
    }

    return 0;
}