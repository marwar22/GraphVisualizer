
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "graph.hpp"
#include "app.hpp"
#include <math.h>
#include <iostream>
#include <string>


void Test(Button &thisButton,sf::Event &event) {
    std::cout<<"test\n"<<std::endl;
    return;
}

void SetTextToMousePosition(Button &thisButton,sf::Event &event) {   
    thisButton.text.setString(std::to_string(event.mouseButton.x) + "x "+ std::to_string(event.mouseButton.y)+ "y");
}

Application::Application()
{
    if (!font.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    G = Graph(&font);
    aktualnyStan = dodajW;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    buttons.push_back(Button(50,700,195,45,"Dodaj wierzcholek",  &font,Test));
    buttons.push_back(Button(250,700,195,45,"Usun wierzcholek",  &font,Test));
    buttons.push_back(Button(500,700,145,45,"Dodaj krawedz",     &font,Test));
    buttons.push_back(Button(700,700,145,45,"Usun krawedz",      &font,Test));
    buttons.push_back(Button(900,700,145,45,"Symulacja sil",     &font,Test));
    buttons.push_back(Button(1100,700,145,45,"Odczyt z pliku",   &font,Test));
    buttons.push_back(Button(1300,700,145,45,"Zapis do pliku",   &font,Test));

    buttons.push_back(Button(500,400,150,50,"Koordy",            &font,SetTextToMousePosition));

    window.create(sf::VideoMode(1600, 800), "Projekt PWI",sf::Style::Default,settings);
    window.setFramerateLimit(100);
}

void Application::CheckPodswietlenie(sf::Vector2i mousePosition) {
    for (Button &button : buttons) {
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {//czy myszka jest w prostokacie przycisku
            button.SetColor(sf::Color::Blue);
        }
        else {
            button.SetColor(sf::Color::Black);
        }
    }

}

void Application::Run() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {HandleEvent(event);}

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // if(aktualnyStan == ...)
        G.CalculateForces();//to wtedy i tlyko wtedy gdy aktualny stan na symulacje sily
        G.ApplyForces();
        CheckPodswietlenie(mousePosition);
        Render();
    }
}

void Application::Render() {
    window.clear(sf::Color::White);        
    G.Draw(window);
    for (int i=0; i<buttons.size(); ++i) {
        window.draw(buttons[i].rectangle);
        window.draw(buttons[i].text);
    }
    window.display();
}
