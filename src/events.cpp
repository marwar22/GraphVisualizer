#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include <climits>
#include <algorithm>

#include "app.hpp"
#include "graph.hpp"
#include "graphics/button.hpp"
#include "utils.hpp"
#include "filehandle.hpp"

extern void *sG;
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
        case chooseVertex:
            for (Button &button : buttonsChooseVertex) {
                if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
                    button.OnClick(*this,button,event);           
                }
            }
            break;
        default:
            for (Button &button : buttons) {
                if (button.rectangle.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) ) {//czy myszka jest w prostokacie przycisku
                    button.OnClick(*this,button,event);
                    ClearSelected();      
                    holdingVertexId = -1;
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
                    //v.SetColor(sf::Color::Yellow);
                    holdingVertexId = v.id;
                    v.isBeingChosen = true;
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
        case chooseVertex:
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    chosenVertices.push_back( v.id );
                    aktualnyStan = algorithmR;
                    algorithms[algorithmId](&G,&stepLista,chosenVertices);
                    break;
                }
            }
            break;
        case addE:
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    if( firstVertexId == -1 ) {
                        firstVertexId = v.id;
                        v.isBeingChosen = true;
                    }else if( secondVertexId == -1 ) {
                        secondVertexId = v.id;
                        //tu był if isWeighted
                        G.AddEdge( firstVertexId, secondVertexId, 0, 0 );                    
                        G.vertices [ firstVertexId ].isBeingChosen = false;
                        firstVertexId = -1;
                        secondVertexId = -1;
                        
                    }
                    break;
                }
            }
            break;
        
        case editE:
        {
            if (selectedEdgeId == -1){ /// jeszcze nie wybrano 2 krawędzi
                for (Vertex &v: G.vertices) {
                    int dx = v.position.x - event.mouseButton.x;
                    int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                    if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                        if( firstVertexId == -1 ) {
                            firstVertexId = v.id;
                            v.isBeingChosen = true;
                        }else if( secondVertexId == -1) {
                            // jeżeli istnieje krawędź między firstVertexId a secondVertexId, czekaj na wpr wagi
                            secondVertexId = v.id;
                            for(Edge &e: G.allEdges ) {
                                if( (e.idVertexFrom == firstVertexId && e.idVertexTo == secondVertexId) 
                                    || ( e.idVertexFrom == secondVertexId && e.idVertexTo == firstVertexId )){
                                        v.isBeingChosen = true;
                                        selectedEdgeId = e.id; 
                                        //e.weight1=1;
                                        }
                            }
                            if (selectedEdgeId == -1)
                                secondVertexId = -1;
                        }
                    }
                }
            }
                /// część po wybraniu 2 wierzchołków w innej części programu            
        }
            break; //???
        case removeE:
            for (Vertex &v: G.vertices) {            
                int dx = v.position.x - event.mouseButton.x;
                int dy = v.position.y - (event.mouseButton.y - TOOLBAR_HEIGHT);
                if (sqrt(dx*dx+dy*dy) <= V_RADIUS) {
                    if( firstVertexId == -1 ) {
                        firstVertexId = v.id;
                        v.isBeingChosen = true;
                    }else if( secondVertexId == -1) {
                        secondVertexId = v.id;
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
                        G.vertices [ firstVertexId ].isBeingChosen = false;
                        
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
                //G.vertices[holdingVertexId].SetColor(sf::Color::Red);
                G.vertices[holdingVertexId].isBeingChosen = false;
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

char Application::getCharFromInput(sf::Event &event){
    return static_cast<char>(event.text.unicode);
}

void Application::HandleTextEntered(sf::Event &event) {//j
    char letter = getCharFromInput(event);//SPRAWDZIC DZIALANIE ENTER'A NA WINDOWSIE, JEZELI CHCEMY WIDNOWSA TEZ
    if(aktualnyStan == saveFile || aktualnyStan == readFile) {
        if(letter == 8) textEntered.pop_back();
        else if(letter == 13) {
            if(aktualnyStan == saveFile)
                WriteFile( textEntered.c_str(), &(G) );
            if(aktualnyStan == readFile)
                ReadFile( textEntered.c_str(), &(G) ); 
        }
        else textEntered.push_back(letter);
    }

    if (aktualnyStan == editE && selectedEdgeId != -1) {
        if     ((int)letter == 45) {G.allEdges[selectedEdgeId].weight1 *= (-1);} // zmiana znaku
        else if((int)letter == 13) {
            selectedEdgeId = -1; 
            G.vertices[firstVertexId].isBeingChosen = false;
            G.vertices[secondVertexId].isBeingChosen = false;

            firstVertexId = -1; 
            secondVertexId = -1;
        } //enter
        else if((int)letter == 8) {G.allEdges[selectedEdgeId].weight1 /= 10;} //backspace
        else if(G.allEdges[selectedEdgeId].weight1 <= (INT_MAX - 100) / 10 && int(letter) - 48 >= 0 && int(letter) - 48 <= 9){
                G.allEdges[selectedEdgeId].weight1 = G.allEdges[selectedEdgeId].weight1 * 10 + (int(letter) - 48);
        }
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
    if(event.type == sf::Event::TextEntered)          HandleTextEntered(event);       
}