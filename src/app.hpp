#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "graph.hpp"
#include "graphics/button.hpp"

enum stan {
        dodajW, usuwanieW, 
        dodajK, usuwanieK, 
        symulacjaSily,
        algorytm,
        odczytPlik,
        zapisPlik
};

class Application{
public:
    sf::RenderWindow window;
    sf::Font font;
    Graph G;

    enum buttonsEnum {
        buttonDodajW, buttonUsuwanieW,
        buttonDodajK, buttonUsuwanieK,
        buttonSymulacjaSily,
        buttonOdczyt,
        buttonZapis,
        buttonDfs,
        buttonPokazKlik, buttonPokazPozycje,
        buttonBfs
    };//i wszystkie pozostale algorytmy tez maja button
    std::vector<Button> buttons;
    stan aktualnyStan;//wszystkie stany
    
    void Run();
    void CheckPodswietlenie(sf::Vector2i);
    void Render();
    Application();

    void HandleEvent(sf::Event &event);
    void HandleMouseButtonPressed(sf::Event &event);
};





#endif