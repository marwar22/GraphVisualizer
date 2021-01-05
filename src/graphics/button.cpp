#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "button.hpp"
#include <string>
#include <iostream> //tmp
void Add() {
    std::cerr<<"123"<<std::endl;
    return;
}

Button::Button(int x, int y, int width, int height, std::string napis, sf::Font* font){
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
    
    OnClick = &Add;
}

Button::Button() {}

void Button::draw(sf::RenderWindow& window) {
      window.draw(rectangle);
      window.draw(text);
}