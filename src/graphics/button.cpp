#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "button.hpp"
#include "../utils.hpp"


Button::Button() {
    scale = 1;
    ifThisIsTextBox = false;
}
Button::Button(int _x, int _y, int _width, int _height, std::string napis,sf::Font* font,
               std::function<void(Application &app,Button&,sf::Event&)> _OnClick) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    OnClick = _OnClick;
    scale = 1;
    ifThisIsTextBox = false;
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    text.setFont(*font);
    text.setString(napis);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    Relocate();
    
}

Button::Button(int _x, int _y, int _width, int _height, sf::Text _text,sf::Font* font,
               std::function<void(Application &app,Button&,sf::Event&)> _OnClick) {
    scale = 1;
    ifThisIsTextBox = false;
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    OnClick = _OnClick;
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    text = _text;
    Relocate();
 
    
}

void Button::Relocate() {
    rectangle.setPosition(x,y);
    rectangle.setSize(sf::Vector2f(width,height));
    //text.setOutlineColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2));
    text.setPosition(x + width / 2, y + height / 2 - 2);   
}
void Button::SetColor(sf::Color color) {
    rectangle.setOutlineColor(color);
    text.setFillColor(color);
}

void Button::draw(sf::RenderTarget& window) {
    long double widthdb, heightdb, chrsize;
    widthdb = width;
    widthdb *= scale;
    heightdb = height;
    heightdb *= scale;
    rectangle.setPosition(x,y);
    rectangle.setSize(sf::Vector2f(widthdb,heightdb));
    chrsize = 20;
    chrsize *= scale;
    chrsize *= BUTTON_FONT_SCALE;
    text.setCharacterSize(chrsize);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2));
    text.setPosition(x + widthdb / 2, y + heightdb / 2 - 2);   
    window.draw(rectangle);
    window.draw(text);
}