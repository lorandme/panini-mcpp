#include "GameManager.h"
#include <iostream>

int main() {
    // Inițializare GameManager
    GameManager gameManager;

    // Inițializare joc
    gameManager.initializeGame();

    // Start joc
    std::cout << "Jocul a început! \n";
    gameManager.startGame();

    return 0;
}
