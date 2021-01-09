#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <functional>
#include <string>

class Application;
class TextBox{
public:
    sf::RectangleShape rectangle;
    sf::Text text;
    int x, y;
    int width, height;
    void draw(sf::RenderTarget&);
    void SetColor(sf::Color);
    
    TextBox(int, int, int, int, std::string,sf::Font *);

    TextBox();
    void SetPosition();
    void Relocate();
};

#endif