#include "GameMenu.h"
#include <iostream>

MenuRenderer::MenuRenderer(sf::RenderWindow& window) :
    m_window(window),
    m_selectedIndex(0),
    m_selectionMade(false),
    m_backgroundColor{ 50, 50, 50 },
    m_textColor{ 255, 255, 255 },
    m_buttonColor{ 57, 7, 115 },
    m_highlightColor{ 94, 13, 189 }
{
    if (!m_font.loadFromFile("../assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    createMenuItems();
}

void MenuRenderer::createMenuItems() {
    std::vector<std::string> labels = {
        "1v1v1v1",
        "2v2",
        "Exit"
    };

    for (size_t i = 0; i < labels.size(); ++i) {
        MenuItem item;
        setupMenuItem(item, labels[i], 100.f + i * 80.f);
        m_menuItems.push_back(item);
    }
}

void MenuRenderer::setupMenuItem(MenuItem& item, const std::string& label, float yPosition) {
    item.button.setSize({ 300.f, 50.f });
    item.button.setPosition(
        m_window.getSize().x / 2.f - item.button.getSize().x / 2.f,
        yPosition
    );
    item.button.setFillColor(m_buttonColor);

    item.text.setFont(m_font);
    item.text.setString(label);
    item.text.setCharacterSize(20);
    item.text.setFillColor(m_textColor);

    sf::FloatRect textBounds = item.text.getLocalBounds();
    item.text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    item.text.setPosition(
        item.button.getPosition().x + item.button.getSize().x / 2.f,
        item.button.getPosition().y + item.button.getSize().y / 2.f
    );
}

void MenuRenderer::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
                m_selectedIndex = (m_selectedIndex - 1 + m_menuItems.size()) % m_menuItems.size();
                break;
            case sf::Keyboard::Down:
                m_selectedIndex = (m_selectedIndex + 1) % m_menuItems.size();
                break;
            case sf::Keyboard::Enter:
                // Logică selectare
                m_selectionMade = true;
                m_selectedMode = static_cast<GameMode>(m_selectedIndex);

                switch (m_selectedMode) {
                case GameMode::SOLO_4PLAYERS:
                    std::cout << "Selected: 1v1v1v1" << std::endl;
                    break;
                case GameMode::TEAM_2V2:
                    std::cout << "Selected: 2v2" << std::endl;
                    break;
                case GameMode::EXIT:
                    m_window.close();
                    break;
                }
                return;
            default:
                break;
            }
        }
    }
}

void MenuRenderer::render() {
    m_window.clear(m_backgroundColor);

    sf::Text titleText;
    titleText.setFont(m_font);
    titleText.setString("Select Game Mode");
    titleText.setCharacterSize(40);
    titleText.setFillColor(m_textColor);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top);
    titleText.setPosition(m_window.getSize().x / 2.f, 20.f);
    m_window.draw(titleText);

    for (size_t i = 0; i < m_menuItems.size(); ++i) {
        auto& item = m_menuItems[i];

        if (i == m_selectedIndex) {
            item.button.setFillColor(m_highlightColor);
            item.text.setFillColor(m_backgroundColor);
        }
        else {
            item.button.setFillColor(m_buttonColor);
            item.text.setFillColor(m_textColor);
        }

        m_window.draw(item.button);
        m_window.draw(item.text);
    }

    m_window.display();
}

GameMode MenuRenderer::run() {
    while (m_window.isOpen()) {
        handleEvents();
        render();

        if (m_selectionMade) {
            return m_selectedMode;
        }
    }

    return GameMode::EXIT;
}