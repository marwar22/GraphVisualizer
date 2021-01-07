#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "app.hpp"
#include "graph.hpp"
#include "graphics/button.hpp"
#include "utils.hpp"

void Application::HandleMouseButtonPressed(sf::Event &event) {
    switch( aktualnyStan )
    {
        case algorithmC:
            for (Button &button : buttonsAlg) {
                if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
                    button.OnClick(*this,button,event);           
                }
            }
            break;
        case algorithmR:
            for (Button &button : buttonsAlgR) {
                if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
                    button.OnClick(*this,button,event);           
                }
            }
            break;
        default:
            for (Button &button : buttons) {
                if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
                    button.OnClick(*this,button,event);      
                    holdingVertexId = -1;
                    firstVertexId = -1;    
                    secondVertexId = -1;                
                }
            }
            break;
    }
    switch( aktualnyStan )
    {
        case movingV:       
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
            break;
        case removeV:       
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    G.RemoveVertex( v.id );
                    break;
                }
            }
            break;
        case addV:
            if( event.mouseButton.y > TOOLBAR_HEIGHT + V_RADIUS && event.mouseButton.y < window.getSize().y - V_RADIUS
                && event.mouseButton.x > V_RADIUS && event.mouseButton.x < window.getSize().x - V_RADIUS )
            {
                sf::Vector2f cords;
                cords.x = event.mouseButton.x;
                cords.y = event.mouseButton.y - TOOLBAR_HEIGHT;
                G.AddVertex( cords );
            }
            break;
        case addE:
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    if( firstVertexId == -1 ) {
                        firstVertexId = v.id;
                        v.SetColor(sf::Color::Yellow);
                    }else if( secondVertexId == -1 && firstVertexId != v.id ) {
                        secondVertexId = v.id;
                        v.SetColor(sf::Color::Yellow);
                        if( !G.isWeighted ) {
                            if( G.allEdges.empty() )
                                G.AddEdge( firstVertexId, secondVertexId, 0, 0 );
                            else for(Edge &e: G.allEdges ) {
                                if( e.idVertexFrom == firstVertexId && e.idVertexTo == secondVertexId )
                                    break;
                                if( e.idVertexFrom == secondVertexId && e.idVertexTo == firstVertexId )
                                    break;
                                if( e.id == G.allEdges.size() - 1 )
                                    G.AddEdge( firstVertexId, secondVertexId, 0, 0 );
                            }
                            G.vertices [ firstVertexId ].SetColor( sf::Color::Red );
                            G.vertices [ secondVertexId ].SetColor( sf::Color::Red );
                            firstVertexId = -1;
                            secondVertexId = -1;
                        }
                    }
                    break;
                }
            }
            break;
        case removeE:
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    if( firstVertexId == -1 ) {
                        firstVertexId = v.id;
                        v.SetColor(sf::Color::Yellow);
                    }else if( secondVertexId == -1 && firstVertexId != v.id ) {
                        secondVertexId = v.id;
                        v.SetColor(sf::Color::Yellow);
                        for(Edge &e: G.allEdges ) {
                            if( e.idVertexFrom == firstVertexId && e.idVertexTo == secondVertexId ) {
                                G.RemoveEdge( e.id );
                                break;
                            }
                            if( e.idVertexFrom == secondVertexId && e.idVertexTo == firstVertexId ) {
                                G.RemoveEdge( e.id );
                                break;
                            }
                        }
                        G.vertices [ firstVertexId ].SetColor( sf::Color::Red );
                        G.vertices [ secondVertexId ].SetColor( sf::Color::Red );
                        firstVertexId = -1;
                        secondVertexId = -1;
                    }
                    break;
                }
            }
            break;
    }

    std::cerr<<"\n\n\nlog po wykonaniu Pressed:"<<std::endl;
    PrintGraphLog(G);
}
void Application::HandleMouseButtonReleased(sf::Event &event) {
    
    switch( aktualnyStan )
    {
        case movingV:      
            if (holdingVertexId != -1) {        
                G.vertices[holdingVertexId].SetColor(sf::Color::Red);
                G.vertices[holdingVertexId].isBeingMoved = false;
                holdingVertexId = -1;
            }
            break;
    }
}
void Application::HandleMouseMoved(sf::Event &event) {
    switch( aktualnyStan )
    {
        case movingV:      
            if (holdingVertexId != -1) {
                G.vertices[holdingVertexId].position.x = event.mouseMove.x;
                G.vertices[holdingVertexId].position.y = event.mouseMove.y - TOOLBAR_HEIGHT;
            }
            break;
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