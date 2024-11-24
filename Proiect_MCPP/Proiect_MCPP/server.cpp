#include "crow.h"
#include <iostream>

int main() {
    crow::SimpleApp app;

    int scor = 0;

    // Endpoint pentru a primi poziția tancului
    CROW_ROUTE(app, "/update").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "JSON invalid");
        }
        int tancX = body["tancX"].i();
        int tancY = body["tancY"].i();

        std::cout << "Poziția tancului primită: X=" << tancX << " Y=" << tancY << std::endl;

        // Exemplu: Actualizare scor
        scor += 10;

        return crow::response(200, "Poziție primită");
        });

    // Endpoint pentru scor
    CROW_ROUTE(app, "/score")([&]() {
        return crow::json::wvalue{ {"scor", scor} };
        });

    app.port(18080).multithreaded().run();
}
