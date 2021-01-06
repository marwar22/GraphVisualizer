
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include "graph.hpp"
#include "app.hpp"
#include "utils.cpp"

void Test(Application &app,Button &thisButton,sf::Event &event) {
    std::cout<<"test\n"<<std::endl;
    return;
}

void SetTextToMousePosition(Application &app,Button &thisButton,sf::Event &event) {   
    thisButton.text.setString(std::to_string(event.mouseButton.x) + "x "+ std::to_string(event.mouseButton.y)+ "y");
}
void SetMovingV(Application &app,Button &thisButton,sf::Event &event) {
    app.aktualnyStan = movingV;
}
Application::Application()
{
    if (!font.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    G = Graph(&font);
    aktualnyStan    = addV;
    holdingVertexId = -1;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;


    buttons.push_back(Button(50,24,195,45,"Dodaj wierzcholek",  &font,Test));
    buttons.push_back(Button(250,24,195,45,"Usun wierzcholek",  &font,Test));
    buttons.push_back(Button(450,24,145,45,"Dodaj krawedz",     &font,Test));
    buttons.push_back(Button(800,24,145,45,"Usun krawedz",      &font,Test));
    buttons.push_back(Button(900,24,145,45,"Symulacja sil",     &font,Test));
    buttons.push_back(Button(1050,24,145,45,"Odczyt z pliku",   &font,Test));
    buttons.push_back(Button(1200,24,145,45,"Zapis do pliku",   &font,Test));

    buttons.push_back(Button(1350,24,150,45,"Koordy",           &font,SetTextToMousePosition));
    buttons.push_back(Button(1350,24,150,45,"Przesun\nwierzcholek",&font,SetMovingV));

    for (int i = 1; i< buttons.size();++i) {
        buttons[i].x = buttons[i-1].x + buttons[i-1].width + BUTTON_SPACING;
        buttons[i].Relocate();
    }
    window.create(sf::VideoMode(1920, 1080), "Projekt PWI",sf::Style::Default,settings);
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
        G.CalculateForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);//to wtedy i tlyko wtedy gdy aktualny stan na symulacje sily
        G.ApplyForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);
        CheckPodswietlenie(mousePosition);
        Render();
    }
}

void Application::Render() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    buttons[0].text.setString(std::to_string(mousePosition.x) + " " + std::to_string(mousePosition.y));
    buttons[1].text.setString(std::to_string(window.getSize().x));
    buttons[2].text.setString(std::to_string(aktualnyStan));
    //buttons[3].text.setString(std::to_string(GraphArea.getMaximumAntialiasingLevel()));
    window.clear(sf::Color::White);        
    RenderGraphArea();
    RenderToolBar();    

    window.display();
}
void Application::RenderGraphArea(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    sf::RenderTexture GraphArea;
    GraphArea.create(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT,settings);
    GraphArea.clear(sf::Color::Blue);

    G.Draw(GraphArea);
     
    GraphArea.display();
    sf::Sprite GraphAreaSprite;
    GraphAreaSprite.setTexture(GraphArea.getTexture());
    GraphAreaSprite.setPosition(0,TOOLBAR_HEIGHT);
    window.draw(GraphAreaSprite);    
}
void Application::RenderToolBar() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    sf::RenderTexture toolBar;
    toolBar.create(window.getSize().x,TOOLBAR_HEIGHT,settings);
    toolBar.clear(sf::Color::Green);

    sf::RectangleShape shape(sf::Vector2f(toolBar.getSize().x,TOOLBAR_HEIGHT));
    shape.setFillColor(sf::Color::Green);
    toolBar.draw(shape);
    for (int i=0; i<buttons.size(); ++i) {
        buttons[i].draw(toolBar);
    }
    toolBar.display();
    sf::Sprite toolBarSprite;
    toolBarSprite.setTexture(toolBar.getTexture());
    toolBarSprite.setPosition(0,0);
    window.draw(toolBarSprite);

}