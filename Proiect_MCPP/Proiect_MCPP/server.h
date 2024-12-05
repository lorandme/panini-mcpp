#pragma once

#include <string>

// Funcția pentru inițializarea serverului
void initServer();

// Funcția pentru a începe rularea serverului
void startServer();

// Funcția pentru a închide serverul
void stopServer();

// Funcția pentru a actualiza poziția tancului
void updateTankPosition(int x, int y);

// Funcția pentru a obține scorul de pe server
int getScore();

// Funcția pentru a trimite un răspuns către client
void sendResponse(const std::string& message);

// Funcția pentru a gestiona conexiunile de la clienți
void handleClientConnections();

// Funcția pentru a trata cererile HTTP
void handleHttpRequests();

void startServerWithMultigaming();

