#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "button.hpp"


Button::Button() {}
Button::Button(int x, int y, int width, int height, std::string napis, sf::Font* font,std::function<void(Button&,sf::Event&)> __OnClick){
    rectangle.setPosition(x,y);
    rectangle.setSize(sf::Vector2f(width,height));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    text.setFont(*font);
    text.setString(napis);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    //text.setOutlineColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2));
    text.setPosition(x + width / 2, y + height / 2 - 2);    
    OnClick = __OnClick;
}

void Button::SetColor(sf::Color color) {
    rectangle.setOutlineColor(color);
    text.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) {
      window.draw(rectangle);
      window.draw(text);
}