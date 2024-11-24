#include "crow.h"
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <string>

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
    orm::make_table("scores",
        orm::make_column("id", &Score::id, orm::primary_key()),
        orm::make_column("player_name", &Score::player_name),
        orm::make_column("score", &Score::score)
    )
);

int main() {
    // Sincronizează schema bazei de date
    storage.sync_schema();

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

    return 0;
}
