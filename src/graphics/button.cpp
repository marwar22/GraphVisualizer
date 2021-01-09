#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "button.hpp"


Button::Button() {}
Button::Button(int _x, int _y, int _width, int _height, std::string napis,sf::Font* font,
               std::function<void(Application &app,Button&,sf::Event&)> _OnClick) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    OnClick = _OnClick;
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
      window.draw(rectangle);
      window.draw(text);
}