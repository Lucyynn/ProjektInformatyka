
#include "Gra.h"


int main()
{

    srand(time(NULL));

    //init game engine
    Gra Gra;

    //Nasluchiwanie akcji i podtrzymywanie okna
    while(Gra.running())
    {
        
        //Wyczyszczenie poprzedniej klatki
        Gra.update();


        //Wyœwietlanie stworzonego okna
        Gra.render();
    
    }

    

    return 0;
}