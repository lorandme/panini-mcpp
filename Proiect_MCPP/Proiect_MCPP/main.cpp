#include "GameManager.h"
#include <iostream>

int main() {
    // Inițializare GameManager
    GameManager gameManager;

    // Inițializare joc
    gameManager.initializeGame();

    // Start joc
    std::cout << "Jocul a inceput! \n";
    gameManager.startGame();

    return 0;
}
