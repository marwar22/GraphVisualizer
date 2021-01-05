#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <functional>
#include <string>

class Button{
public:
    sf::RectangleShape rectangle;
    sf::Text text;
    std::function<void(Button&,sf::Event&)> OnClick;
    void draw(sf::RenderWindow&);
    void SetColor(sf::Color);
    Button(int, int, int, int, std::string, sf::Font *,std::function<void(Button&,sf::Event&)>);
    Button();
};

#endif