#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "app.hpp"
#include "graph.hpp"
#include "graphics/button.hpp"
#include "utils.cpp"

void Application::HandleMouseButtonPressed(sf::Event &event) {
    for (Button &button : buttons) {
        if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
            button.OnClick(*this,button,event);                        
        }
    }
    if (aktualnyStan == movingV) {        
        for (Vertex &v: G.vertices) {            
            int dx = v.position.x - event.mouseButton.x;
            int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
            if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                v.SetColor(sf::Color::Yellow);
                holdingVertexId = v.id;
                v.isBeingMoved = true;
                break;
            }
        }
    }
}
void Application::HandleMouseButtonReleased(sf::Event &event) {
    if (holdingVertexId != -1) {        
        G.vertices[holdingVertexId].SetColor(sf::Color::Red);
        G.vertices[holdingVertexId].isBeingMoved = false;
        holdingVertexId = -1;
    }
}
void Application::HandleMouseMoved(sf::Event &event) {
    if (holdingVertexId != -1) {
        G.vertices[holdingVertexId].position.x = event.mouseMove.x;
        G.vertices[holdingVertexId].position.y = event.mouseMove.y - TOOLBAR_HEIGHT;
    }
}
void Application::HandleEvent(sf::Event &event) {
    if (event.type == sf::Event::Closed)              window.close();        
    if (event.type == sf::Event::MouseButtonPressed)  HandleMouseButtonPressed(event);                
    if (event.type == sf::Event::MouseButtonReleased) HandleMouseButtonReleased(event);
    if (event.type == sf::Event::MouseMoved)          HandleMouseMoved(event);
    if (event.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
}