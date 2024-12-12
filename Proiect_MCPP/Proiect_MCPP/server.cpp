#include "Server.h"
#include "crow.h"
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

namespace orm = sqlite_orm;

auto storage = orm::make_storage(
    "battle_city.db",
    orm::make_table(
        "users",
        orm::make_column("id", &User::id, orm::primary_key().autoincrement()),
        orm::make_column("username", &User::username, orm::unique()),
        orm::make_column("email", &User::email),   
        orm::make_column("password", &User::password) 
    ),
    orm::make_table(
        "scores",
        orm::make_column("id", &Score::id, orm::primary_key()),
        orm::make_column("player_name", &Score::playerName),  
        orm::make_column("score", &Score::score)
    ),
    orm::make_table(
        "games",
        orm::make_column("id", &GameSession::gameId, orm::primary_key()),  
        orm::make_column("players", &GameSession::serializedPlayers),       
        orm::make_column("maxPlayers", &GameSession::maxPlayers)            
    )
);

std::queue<std::string> playerQueue;
std::unordered_map<int, GameSession> activeGames;
std::mutex queueMutex;
std::mutex gameMutex;
void GameSession::serialize() {
    serializedPlayers.clear();  
    for (const auto& player : players) {
        if (!serializedPlayers.empty()) {  
            serializedPlayers += ",";  
        }
        serializedPlayers += player;  
    }
}

void GameSession::deserialize() {
    players.clear();
    std::istringstream stream(serializedPlayers); 
    std::string player;
    while (std::getline(stream, player, ',')) {
        players.push_back(player);
    }
}

void initServer() {
    storage.sync_schema();
}

void matchPlayers() {
    int gameIdCounter = 1;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
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

            GameSession newGame;
            newGame.gameId = gameIdCounter;  
            newGame.players = playersToMatch; 
            newGame.maxPlayers = 4;  
            newGame.serialize();
            storage.insert(newGame);

            std::cout << "Game created with ID " << gameIdCounter << " for players: ";
            for (const auto& player : playersToMatch) {
                std::cout << player << " ";
            }
            std::cout << std::endl;
            gameIdCounter++;
        }
    }
}
void startServer() {
    crow::SimpleApp app;

    int score = 0;

    CROW_ROUTE(app, "/update").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        int tankX = body["tankX"].i();
        int tankY = body["tankY"].i();

        std::cout << "Tank position received: X=" << tankX << ", Y=" << tankY << std::endl;

        score += 10;
        Score newScore = { 0, "Player1", score };
        storage.insert(newScore);

        return crow::response(200, "Position received, score updated");
        });

    CROW_ROUTE(app, "/score")([&]() {
        auto scores = storage.get_all<Score>();
        crow::json::wvalue result;

        for (size_t i = 0; i < scores.size(); ++i) {
            result["scores"][i] = crow::json::wvalue{
                {"id", scores[i].id},
                {"player_name", scores[i].playerName},  
                {"score", scores[i].score}
            };
        }
        return result;
        });

    CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body["username"].s().size() == 0) {
            return crow::response(400, "Invalid request");
        }
        std::string username = body["username"].s();
        std::string email = body["email"].s(); // Opțional
        std::string password = body["password"].s(); // Opțional

        // Verifică dacă utilizatorul există deja
        auto existingUser = storage.get_all<User>(orm::where(orm::c(&User::username) == username));
        if (!existingUser.empty()) {
            return crow::response(409, "Username already exists");
        }

        // Creează un utilizator nou
        User newUser = { 0, username, email, password };
        storage.insert(newUser);
        return crow::response(200, "User registered successfully");
        });


    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body["username"].s().size() == 0) {
            return crow::response(400, "Invalid request");
        }
        std::string username = body["username"].s();
        std::string password = body["password"].s(); // Opțional

        // Găsește utilizatorul în baza de date
        auto user = storage.get_all<User>(orm::where(orm::c(&User::username) == username));
        if (user.empty()) {
            return crow::response(404, "User not found");
        }

        // Verifică parola (opțional)
        if (!password.empty() && user[0].password != password) {
            return crow::response(401, "Invalid password");
        }

        return crow::response(200, "Login successful");
        });



    app.port(18080).multithreaded().run();
}

void startServerWithMultigaming() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/join").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        std::string playerName = body["player_name"].s();

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            playerQueue.push(playerName);
        }

        std::cout << "Player " << playerName << " added to queue." << std::endl;
        return crow::response(200, "Player added to queue");
        });

    CROW_ROUTE(app, "/games")([]() {
        crow::json::wvalue result;

        {
            std::lock_guard<std::mutex> lock(gameMutex);
            for (const auto& [gameId, game] : activeGames) {
                crow::json::wvalue gameInfo;
                gameInfo["gameId"] = game.gameId;  
                for (size_t i = 0; i < game.players.size(); ++i) {  
                    gameInfo["players"][i] = game.players[i];  
                }
                result["games"][std::to_string(gameId)] = std::move(gameInfo);
            }
        }

        return result;
        });

    std::thread matchmakingThread(matchPlayers);
    matchmakingThread.detach();

    app.port(18080).multithreaded().run();
}

void stopServer() {
   
}
