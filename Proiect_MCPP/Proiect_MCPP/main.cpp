#include "map.h"
#include "player.h"
#include <conio.h>
#include <windows.h>

int main()
{
	/*Map map(10, 10);
	map.printMap();*/
    Player player("user1",5, 5);  
    int maxX = 10, maxY = 10; 

    std::cout << "Utilizeaza tastele WASD pentru a muta playerul. Apasa Q pentru a iesi.\n";

    while (true) {
        if (_kbhit()) {
            char key = _getch();

            if (key == 'q') break;  

            player.movePlayer(player, key, maxX, maxY);  
            system("cls");  
            player.displayPosition(); 
        }
        Sleep(100); 
    }
}