#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <unistd.h>
#endif

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <string>
#include <cstring>  // Pentru memset

#include "Team.h"
#include "Player.h"
#include "Tile.h"
#include "Weapon.h"
#include <nlohmann/json.hpp>  // Include header-ul JSON

using json = nlohmann::json;

class Server {
private:
    int m_serverSocket;
    int m_port;
    std::mutex m_mutex;
    std::unordered_map<int, std::thread> m_clientThreads;
    std::vector<Team> m_teams;

public:
    Server(int port) : m_port(port), m_serverSocket(-1) {}

    ~Server() {
#ifdef _WIN32
        WSACleanup();
#endif
        for (auto& [_, clientThread] : m_clientThreads) {
            if (clientThread.joinable()) {
                clientThread.join();
            }
        }
        if (m_serverSocket != -1) {
            closesocket(m_serverSocket);
        }
    }

    void init() {
        // Creare socket
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Eroare la initializarea WinSock.");
        }
#endif

        m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_serverSocket == -1) {
            throw std::runtime_error("Eroare la crearea socket-ului serverului.");
        }

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(m_port);

        // Asociere socket cu port
        if (bind(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            throw std::runtime_error("Eroare la asocierea socket-ului serverului.");
        }

        // Ascultare conexiuni
        if (listen(m_serverSocket, 5) < 0) {
            throw std::runtime_error("Eroare la ascultarea conexiunilor.");
        }

        std::cout << "Serverul ruleaza pe portul " << m_port << std::endl;
    }

    void start() {
        while (true) {
            sockaddr_in clientAddr{};
            socklen_t clientLen = sizeof(clientAddr);
            int clientSocket = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

            if (clientSocket >= 0) {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_clientThreads[clientSocket] = std::thread(&Server::handleClient, this, clientSocket);
                std::cout << "Un nou client s-a conectat." << std::endl;
            }
        }
    }

private:
    void handleClient(int clientSocket) {
        try {
            char buffer[1024];
            while (true) {
                memset(buffer, 0, sizeof(buffer));
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

                if (bytesReceived <= 0) {
                    std::cout << "Clientul s-a deconectat." << std::endl;
                    closesocket(clientSocket);
                    break;
                }

                std::string message(buffer);

                // Protejează parsing-ul JSON cu try-catch
                json request;
                try {
                    request = json::parse(message);  // Încearcă să parsezi mesajul
                }
                catch (const std::exception& e) {
                    std::cerr << "Eroare la parsing-ul JSON: " << e.what() << std::endl;
                    json response;
                    response["status"] = "error";
                    response["message"] = "Mesajul trimis nu este un JSON valid.";
                    std::string responseStr = response.dump();
                    send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
                    continue;  // Mergi mai departe fără a continua procesarea pentru acest mesaj
                }

                json response = processRequest(request);

                std::string responseStr = response.dump();
                send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare la gestionarea clientului: " << e.what() << std::endl;
            closesocket(clientSocket);
        }
    }

    json processRequest(const json& request) {
        std::string command = request["command"];
        json response;

        try {
            if (command == "join_team") {
                std::string teamName = request["team_name"];
                std::string playerName = request["player_name"];
                Team* team = findOrCreateTeam(teamName);
                Player newPlayer(playerName, 0, 0);
                team->addPlayer(newPlayer);
                response["status"] = "ok";
                response["message"] = "Player added to team.";
            }
            else if (command == "get_score") {
                std::string teamName = request["team_name"];
                Team* team = findTeam(teamName);
                if (team) {
                    response["status"] = "ok";
                    response["score"] = team->getScore();
                }
                else {
                    response["status"] = "error";
                    response["message"] = "Team not found.";
                }
            }
            else if (command == "update_score") {
                std::string teamName = request["team_name"];
                int points = request["points"];
                Team* team = findTeam(teamName);
                if (team) {
                    team->updateScore(points);
                    response["status"] = "ok";
                    response["message"] = "Team score updated.";
                }
                else {
                    response["status"] = "error";
                    response["message"] = "Team not found.";
                }
            }
            else {
                response["status"] = "error";
                response["message"] = "Unknown command.";
            }
        }
        catch (const std::exception& e) {
            response["status"] = "error";
            response["message"] = "Internal server error: " + std::string(e.what());
        }

        return response;
    }

    Team* findOrCreateTeam(const std::string& teamName) {
        for (auto& team : m_teams) {
            if (team.getName() == teamName) {
                return &team;
            }
        }

        m_teams.emplace_back(teamName);
        return &m_teams.back();
    }

    Team* findTeam(const std::string& teamName) {
        for (auto& team : m_teams) {
            if (team.getName() == teamName) {
                return &team;
            }
        }
        return nullptr;
    }
};
