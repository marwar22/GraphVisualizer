#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <functional>
#include <string>

class Application;
class Button{
public:
    sf::RectangleShape rectangle;
    sf::Text text;
    std::function<void(Application &app,Button&,sf::Event&)> OnClick;
    int x, y;
    int width, height;
    void draw(sf::RenderTarget&);
    void SetColor(sf::Color);
    
    Button(int, int, int, int, std::string,sf::Font *,
           std::function<void(Application &app,Button&,sf::Event&)>);

    Button();
    void SetPosition();
    void Relocate();
};

#endif