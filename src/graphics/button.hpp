#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>



class Button{
public:
    sf::RectangleShape rectangle;
    sf::Text text;
    void (*OnClick)();
    void draw(sf::RenderWindow&);
    Button(int, int, int, int, std::string, sf::Font *);
    Button();
};

#endif