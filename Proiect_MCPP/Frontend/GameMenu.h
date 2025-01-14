#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class GameMode {
    SOLO_4PLAYERS,
    TEAM_2V2,
    EXIT
};

class MenuRenderer {
private:
    sf::RenderWindow& m_window;
    sf::Font m_font;

    sf::Color m_backgroundColor;
    sf::Color m_textColor;
    sf::Color m_buttonColor;
    sf::Color m_highlightColor;

    struct MenuItem {
        sf::RectangleShape button;
        sf::Text text;
    };

    std::vector<MenuItem> m_menuItems;
    size_t m_selectedIndex;
    bool m_selectionMade;
    GameMode m_selectedMode;

    void createMenuItems();
    void setupMenuItem(MenuItem& item, const std::string& label, float yPosition);
    void handleEvents();
    void render();

public:
    MenuRenderer(sf::RenderWindow& window);
    GameMode run();
    bool isSelectionMade() const { return m_selectionMade; }
};