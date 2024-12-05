#include "server.h"
#include "crow.h"  // Include crow pentru serverul web
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <string>

#include <queue>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>


// Structura pentru stocarea scorurilor
struct Score {
    int id;
    std::string player_name;
    int score;
};

namespace orm = sqlite_orm;

// Definirea schemei bazei de date
auto storage = orm::make_storage(
    "battle_city.db",
    orm::make_table(
        "scores",
        orm::make_column("id", &Score::id, orm::primary_key()),
        orm::make_column("player_name", &Score::player_name),
        orm::make_column("score", &Score::score)
    ),
    orm::make_table(
        "games",
        orm::make_column("id", &GameSession::gameId, orm::primary_key()),
        orm::make_column("players", &GameSession::serializedPlayers),
        orm::make_column("maxPlayers", &GameSession::maxPlayers)
    )
);


// Funcția pentru inițializarea serverului
void initServer() {
    // Sincronizează schema bazei de date
    storage.sync_schema();

    // Creează o nouă tabelă pentru jocuri
    storage.sync_schema(orm::make_table(
        "games",
        orm::make_column("id", &GameSession::gameId, orm::primary_key()),
        orm::make_column("players", &GameSession::serializedPlayers),
        orm::make_column("maxPlayers", &GameSession::maxPlayers)
    ));




}

// Funcția pentru a configura rutele și a porni serverul
void startServer() {
    crow::SimpleApp app;

    int scor = 0;  // Scorul jocului, stocat temporar în memorie

    // Endpoint pentru a primi și actualiza poziția tancului
    CROW_ROUTE(app, "/update").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "JSON invalid");
        }

        int tancX = body["tancX"].i();
        int tancY = body["tancY"].i();

        std::cout << "Poziția tancului primită: X=" << tancX << " Y=" << tancY << std::endl;

        // Exemplu de calcul al scorului
        scor += 10;

        // Salvează scorul în baza de date
        Score new_score = { 0, "Player1", scor };  // Folosim un nume generic pentru jucător
        storage.insert(new_score);

        return crow::response(200, "Poziție primită și scor actualizat");
        });

    // Endpoint pentru a returna scorurile
    CROW_ROUTE(app, "/score")([&]() {
        auto scores = storage.get_all<Score>();  // Obține toate scorurile din baza de date
        crow::json::wvalue result;
        for (size_t i = 0; i < scores.size(); ++i) {
            result["scores"][i] = crow::json::wvalue{
                {"id", scores[i].id},
                {"player_name", scores[i].player_name},
                {"score", scores[i].score}
            };
        }
        return result;
        });

    // Endpoint pentru a returna poziția tancului
    CROW_ROUTE(app, "/position")([&]() {
        crow::json::wvalue result;
        result["tancX"] = 10;  // Exemplu de poziție X
        result["tancY"] = 20;  // Exemplu de poziție Y
        return result;
        });

    // Rulează serverul pe portul 18080
    app.port(18080).multithreaded().run();
}





// Structura pentru stocarea jocurilor active
struct GameSession {
    int gameId;
    std::vector<std::string> players;
    int maxPlayers;
    std::string serializedPlayers;  // Adăugat pentru compatibilitate cu SQLite

    // Serializare vector în șir
    void serialize() {
        serializedPlayers.clear();
        for (const auto& player : players) {
            if (!serializedPlayers.empty()) {
                serializedPlayers += ","; // Separator
            }
            serializedPlayers += player;
        }
    }

    // Deserializare șir în vector
    void deserialize() {
        players.clear();
        std::istringstream stream(serializedPlayers);
        std::string player;
        while (std::getline(stream, player, ',')) {
            players.push_back(player);
        }
    }
};



std::queue<std::string> playerQueue;  // Coada de așteptare pentru jucători
std::unordered_map<int, GameSession> activeGames;  // Jocurile active
std::mutex queueMutex;
std::mutex gameMutex;

// Funcția pentru gestionarea jucătorilor și distribuirea lor în jocuri
void matchPlayers() {
    int gameIdCounter = 1;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Interval de verificare

        std::vector<std::string> playersToMatch;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            while (!playerQueue.empty() && playersToMatch.size() < 4) {
                playersToMatch.push_back(playerQueue.front());
                playerQueue.pop();
            }
        }

        if (!playersToMatch.empty()) {
            std::lock_guard<std::mutex> lock(gameMutex);
            activeGames[gameIdCounter] = { gameIdCounter, playersToMatch, 4 };

            // Salvează jocul în baza de date
            GameSession newGame;
            newGame.gameId = gameIdCounter;
            newGame.players = playersToMatch;
            newGame.maxPlayers = 4;
            newGame.serialize();  // Pregătește datele pentru stocare


            // Salvează jocul în baza de date
            storage.insert(newGame);



            std::cout << "Joc creat cu ID " << gameIdCounter << " pentru jucătorii: ";
            for (const auto& player : playersToMatch) {
                std::cout << player << " ";
            }
            std::cout << std::endl;
            gameIdCounter++;
        }
    }
}

// Funcția pentru a configura serverul
void startServerWithMultigaming() {
    crow::SimpleApp app;

    // Endpoint pentru a adăuga un jucător în coada de așteptare
    CROW_ROUTE(app, "/join").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "JSON invalid");
        }

        std::string playerName = body["player_name"].s();

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            playerQueue.push(playerName);
        }

        std::cout << "Jucătorul " << playerName << " a fost adăugat în coadă." << std::endl;
        return crow::response(200, "Jucător adăugat în coadă");
        });

    // Endpoint pentru a verifica starea jocurilor active
    CROW_ROUTE(app, "/games")([]() {
        crow::json::wvalue result;

        {
            std::lock_guard<std::mutex> lock(gameMutex);
            for (const auto& [gameId, game] : activeGames) {
                crow::json::wvalue gameInfo;
                gameInfo["gameId"] = game.gameId;
                gameInfo["players"] = crow::json::wvalue();
                for (size_t i = 0; i < game.players.size(); ++i) {
                    gameInfo["players"][i] = game.players[i];
                }
                crow::json::wvalue gameEntry;
                gameEntry["gameId"] = game.gameId;
                for (size_t i = 0; i < game.players.size(); ++i) {
                    gameEntry["players"][i] = game.players[i];
                }
                result["games"][std::to_string(gameId)] = std::move(gameEntry);

            }
        }

        return result;
        });

    // Rulează serverul și thread-ul pentru matchmaking
    std::thread matchmakingThread(matchPlayers);
    matchmakingThread.detach();

    app.port(18080).multithreaded().run();
}
