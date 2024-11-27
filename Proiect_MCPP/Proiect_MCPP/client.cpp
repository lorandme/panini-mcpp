#include <iostream>
#include <string>
#include <cpr/cpr.h>
//#include <nlohmann/json.hpp>
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING


/*int main() {
    // Clientul trimite poziția tancului la server
    nlohmann::json json_data;
    json_data["tancX"] = 10;  // Exemplu de poziție X
    json_data["tancY"] = 20;  // Exemplu de poziție Y

    // Trimiterea cererii POST către server pentru actualizarea poziției
    cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:18080/update" },
        cpr::Body{ json_data.dump() },
        cpr::Header{ {"Content-Type", "application/json"} });

    if (r.status_code == 200) {
        std::cout << "Poziția a fost actualizată cu succes!" << std::endl;
    }
    else {
        std::cerr << "Eroare la actualizarea poziției: " << r.status_code << std::endl;
    }

    // Obținerea scorului de la server
    r = cpr::Get(cpr::Url{ "http://localhost:18080/score" });

    if (r.status_code == 200) {
        std::cout << "Scor curent: " << r.text << std::endl;
    }
    else {
        std::cerr << "Eroare la obținerea scorului: " << r.status_code << std::endl;
    }

    // Obținerea poziției curente a tancului de la server
    r = cpr::Get(cpr::Url{ "http://localhost:18080/position" });

    if (r.status_code == 200) {
        auto response_json = nlohmann::json::parse(r.text);
        std::cout << "Poziția tancului: X=" << response_json["tancX"] << " Y=" << response_json["tancY"] << std::endl;
    }
    else {
        std::cerr << "Eroare la obținerea poziției: " << r.status_code << std::endl;
    }

    return 0;
}
*/