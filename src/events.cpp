#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "app.hpp"
#include "graph.hpp"
#include "graphics/button.hpp"

void Application::HandleMouseButtonPressed(sf::Event &event) {
    for (Button &button : buttons) {
        if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
            button.OnClick(button,event);
            
            
        }
    }
    
    //buttons[0].OnClick(&buttons,event);
    //buttons[0].text.setString(std::to_string(event.mouseButton.x) + "x "+ std::to_string(event.mouseButton.y)+ "y");
}

void Application::HandleEvent(sf::Event &event) {
    if (event.type == sf::Event::Closed)
        window.close();
        
    if (event.type == sf::Event::MouseButtonPressed) {
        HandleMouseButtonPressed(event);                
        
    }    
}