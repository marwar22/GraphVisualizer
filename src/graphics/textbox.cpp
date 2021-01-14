#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "textbox.hpp"

TextBox::TextBox() {}
TextBox::TextBox(int _x, int _y, int _width, int _height, std::string napis,sf::Font* font) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2);
    text.setFont(*font);
    text.setString(napis);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    Relocate();
}
void TextBox::Relocate() {
    rectangle.setPosition(x,y);
    rectangle.setSize(sf::Vector2f(width,height));
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2));
    text.setPosition(x + width / 2, y + height / 2 - 2);   
}
void TextBox::SetColor(sf::Color color) {
    rectangle.setOutlineColor(color);
    text.setFillColor(color);
}

void TextBox::Draw(sf::RenderTarget& window) {
      window.draw(rectangle);
      window.draw(text);
}