//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <string>
//#include <nlohmann/json.hpp>
//#include <cstring>  // Pentru memset
//#include <codecvt>
//#include <locale>
//#include <iostream>
//
//using json = nlohmann::json;
//
//class Client {
//private:
//    SOCKET m_socket;
//    std::string m_serverIP;
//    int m_serverPort;
//
//public:
//    Client(const std::string& serverIP, int serverPort)
//        : m_serverIP(serverIP), m_serverPort(serverPort), m_socket(INVALID_SOCKET) {}
//
//    ~Client() {
//        if (m_socket != INVALID_SOCKET) {
//            closesocket(m_socket);
//        }
//        WSACleanup();
//    }
//
//    // Inițializarea clientului
//    void init() {
//        WSADATA wsaData;
//        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//            throw std::runtime_error("Eroare la initializarea WinSock.");
//        }
//
//        m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//        if (m_socket == INVALID_SOCKET) {
//            throw std::runtime_error("Eroare la crearea socket-ului.");
//        }
//
//        sockaddr_in serverAddr{};
//        serverAddr.sin_family = AF_INET;
//        serverAddr.sin_port = htons(m_serverPort);
//        inet_pton(AF_INET, m_serverIP.c_str(), &serverAddr.sin_addr);
//
//        if (connect(m_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
//            throw std::runtime_error("Eroare la conectarea la server.");
//        }
//    }
//
//    std::string wstringToUtf8(const std::wstring& wstr) {
//        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//        return converter.to_bytes(wstr);
//    }
//
//    void sendMessage(const json& request) {
//        std::string requestStr = request.dump();
//
//        std::string utf8Message = wstringToUtf8(std::wstring(requestStr.begin(), requestStr.end()));
//
//        send(m_socket, utf8Message.c_str(), utf8Message.size(), 0);
//    }
//
//    json receiveMessage() {
//        char buffer[1024];
//        memset(buffer, 0, sizeof(buffer));
//
//        int bytesReceived = recv(m_socket, buffer, sizeof(buffer) - 1, 0);
//        if (bytesReceived <= 0) {
//            throw std::runtime_error("Eroare la primirea mesajului sau serverul s-a deconectat.");
//        }
//
//        std::string message(buffer);  
//        if (message.empty()) {
//            throw std::runtime_error("Mesajul primit este gol.");
//        }
//        std::cerr << "Mesaj primit de la server: " << message << std::endl;  
//
//        try {
//            json response = json::parse(message);
//            return response;
//        }
//        catch (const json::exception& e) {
//            std::cerr << "Eroare la parsarea JSON: " << e.what() << std::endl;
//            throw std::runtime_error("Eroare la parsarea JSON.");
//        }
//    }
//
//    void startGame() {
//        nlohmann::json message = { {"action", "start_game"} };
//        sendMessage(message);
//    }
//
//    void updateScore(const std::string& player, int score) {
//        nlohmann::json message = { {"action", "update_score"}, {"player", player}, {"score", score} };
//        sendMessage(message);
//    }
//
//    void endGame() {
//        nlohmann::json message = { {"action", "end_game"} };
//        sendMessage(message);
//    }
//
//    void processResponse(const nlohmann::json& response) {
//        if (response.contains("action")) {
//            std::string action = response["action"];
//            if (action == "start_game") {
//                std::cout << "Jocul a fost pornit!" << std::endl;
//            }
//            else if (action == "update_score") {
//                std::string player = response["player"];
//                int score = response["score"];
//                std::cout << "Scor actualizat: " << player << " are acum " << score << " puncte!" << std::endl;
//            }
//            else if (action == "end_game") {
//                std::cout << "Jocul s-a terminat!" << std::endl;
//            }
//        }
//
//        if (response.contains("status")) {
//            std::cout << "Status: " << response["status"] << std::endl;
//        }
//    }
//
// 
//
//    void handleServerResponse(const json& response) {
//        if (response.contains("status") && response["status"] == "error") {
//            std::cerr << "Error: " << response["message"] << std::endl;
//            if (response["message"] == "Connection lost") {
//                reconnectToServer();  // Metodă de reconectare
//            }
//        }
//        else {
//            std::cout << "Success: " << response["message"] << std::endl;
//        }
//    }
//
//    void reconnectToServer() {
//        std::cout << "Trying to reconnect to the server..." << std::endl;
//        init(); 
//    }
//
//
//};
#include "Client.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>// Folosim biblioteca CPR pentru cereri HTTP

Client::Client(const std::string& serverUrl) : serverUrl(serverUrl) {}

bool Client::registerUser(const std::string& username, const std::string& password) {
    // Creăm un obiect JSON pentru a trimite datele
    nlohmann::json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    // Trimiterea cererii POST către serverul care se află pe localhost
    cpr::Response response = cpr::Post(
        cpr::Url{ "http://localhost:8080/register" },  // URL-ul serverului
        cpr::Header{ {"Content-Type", "application/json"} },  // Setează tipul de conținut la JSON
        cpr::Body{ json_data.dump() }  // Datele trimise în corpul cererii (convertite la string JSON)
    );

    if (response.status_code == 200) {
        std::cout << "Utilizatorul a fost înregistrat cu succes!" << std::endl;
        return true;
    }
    else {
        std::cerr << "Eroare la înregistrare: " << response.text << std::endl;
        return false;
    }
}

bool Client::login(const std::string& username, const std::string& password) {
    // URL-ul pentru ruta de autentificare
    std::string url = serverUrl + "/login";  // Asigură-te că serverul are această rută configurată

    // Crearea payload-ului cu datele pentru autentificare
    cpr::Payload payload = { {"username", username}, {"password", password} };

    // Trimiterea cererii POST către server
    cpr::Response response = cpr::Post(cpr::Url{ url }, payload);

    // Verificarea răspunsului de la server
    if (response.status_code == 200) {
        std::cout << "Autentificare reușită!" << std::endl;
        return true;
    }
    else {
        std::cout << "Autentificare eșuată: " << response.text << std::endl;
        return false;
    }
}
