#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <nlohmann/json.hpp>
#include <cstring>  // Pentru memset
#include <codecvt>
#include <locale>
#include <iostream>

using json = nlohmann::json;

class Client {
private:
    SOCKET m_socket;
    std::string m_serverIP;
    int m_serverPort;

public:
    Client(const std::string& serverIP, int serverPort)
        : m_serverIP(serverIP), m_serverPort(serverPort), m_socket(INVALID_SOCKET) {}

    ~Client() {
        if (m_socket != INVALID_SOCKET) {
            closesocket(m_socket);
        }
        WSACleanup();
    }

    // Inițializarea clientului
    void init() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Eroare la initializarea WinSock.");
        }

        m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_socket == INVALID_SOCKET) {
            throw std::runtime_error("Eroare la crearea socket-ului.");
        }

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(m_serverPort);
        inet_pton(AF_INET, m_serverIP.c_str(), &serverAddr.sin_addr);

        if (connect(m_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw std::runtime_error("Eroare la conectarea la server.");
        }
    }

    // Funcție pentru conversia unui șir wide char în UTF-8
    std::string wstringToUtf8(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    // Trimiterea unui mesaj către server (convertim mesajul în UTF-8)
    void sendMessage(const json& request) {
        // Converim JSON-ul într-un string
        std::string requestStr = request.dump();

        // Verificăm și converim string-ul în UTF-8 (dacă este cazul)
        std::string utf8Message = wstringToUtf8(std::wstring(requestStr.begin(), requestStr.end()));

        // Trimiterea mesajului
        send(m_socket, utf8Message.c_str(), utf8Message.size(), 0);
    }

    // Primirea unui răspuns de la server
    json receiveMessage() {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesReceived = recv(m_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            throw std::runtime_error("Eroare la primirea mesajului sau serverul s-a deconectat.");
        }

        // Verificăm dacă există date valide și dacă mesajul poate fi procesat
        std::string message(buffer);  // Păstrăm doar aceasta linie
        if (message.empty()) {
            throw std::runtime_error("Mesajul primit este gol.");
        }
        std::cerr << "Mesaj primit de la server: " << message << std::endl;  // Adaugă aceasta linie pentru debug

        try {
            json response = json::parse(message);
            return response;
        }
        catch (const json::exception& e) {
            std::cerr << "Eroare la parsarea JSON: " << e.what() << std::endl;
            throw std::runtime_error("Eroare la parsarea JSON.");
        }
    }

    void startGame() {
        nlohmann::json message = { {"action", "start_game"} };
        sendMessage(message);
    }

    void updateScore(const std::string& player, int score) {
        nlohmann::json message = { {"action", "update_score"}, {"player", player}, {"score", score} };
        sendMessage(message);
    }

    void endGame() {
        nlohmann::json message = { {"action", "end_game"} };
        sendMessage(message);
    }

    void processResponse(const nlohmann::json& response) {
        if (response.contains("action")) {
            std::string action = response["action"];
            if (action == "start_game") {
                std::cout << "Jocul a fost pornit!" << std::endl;
            }
            else if (action == "update_score") {
                std::string player = response["player"];
                int score = response["score"];
                std::cout << "Scor actualizat: " << player << " are acum " << score << " puncte!" << std::endl;
            }
            else if (action == "end_game") {
                std::cout << "Jocul s-a terminat!" << std::endl;
            }
        }

        if (response.contains("status")) {
            std::cout << "Status: " << response["status"] << std::endl;
        }
    }

    void sendGreetingToServer() {
        // Creăm un obiect JSON cu mesajul dorit
        nlohmann::json greetingMessage = { {"message", "Salut server"} };

        // Trimitem acest mesaj serverului
        sendMessage(greetingMessage);
    }


    void handleServerResponse(const json& response) {
        if (response.contains("status") && response["status"] == "error") {
            std::cerr << "Error: " << response["message"] << std::endl;
            if (response["message"] == "Connection lost") {
                reconnectToServer();  // Metodă de reconectare
            }
        }
        else {
            std::cout << "Success: " << response["message"] << std::endl;
        }
    }

    void reconnectToServer() {
        std::cout << "Trying to reconnect to the server..." << std::endl;
        init();  // Reinitializează conexiunea
    }


};
