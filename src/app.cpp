#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "graph.hpp"
#include "app.hpp"
#include "utils.hpp"
#include "algorithms/algorithms.hpp"


#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))


void *sG;
//assert(zeroV || G->vertices.size() > 0);

std::mt19937 rnd2(1234);
int los0(int mi,int mx) {return rnd2()%(mx-mi+1)+mi;}

void Test(Application &app,Button &thisButton,sf::Event &event) {
    std::cout<<"test\n"<<std::endl;
    return;
}
void ChooseVertexInit(Application &app)
{
    app.aktualnyStan = chooseVertex;
    app.chosenVertices.clear();
}
void ButtonRemoveVertex(Application &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = removeV;}
void ButtonAddVertex(Application    &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = addV;}
void ButtonRemoveEdge(Application   &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = removeE;}
void ButtonAddEdge(Application      &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = addE;}
void ButtonMoveVertex(Application   &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = movingV;}
void ButtonSimulate(Application     &app,Button &thisButton,sf::Event &event) {app.simulateForces = !app.simulateForces;}
void ButtonAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.simulateForces = false;
    app.runningForward = false;
    app.aktualnyStan = algorithmC;}
void PlayAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = true;
    app.runningBack = false;
    app.lastStep= clock();
    app.lastStep /= CLOCKS_PER_SEC;}
void PlayBackAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningBack = true;
    app.runningForward = false;
    app.lastStep= clock();
    app.lastStep /= CLOCKS_PER_SEC;}
void StopPlayingAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = false;
    app.runningBack = false;}
void ButtonReadFile(Application     &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = readFile;}
void ButtonSaveFile(Application     &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = saveFile;}
void ButtonReturnToGraphEdit(Application       &app,Button &thisButton,sf::Event &event) {
    app.aktualnyStan = nothing;
    app.holdingVertexId = -1;
    app.firstVertexId = -1;    
    app.secondVertexId = -1;}
void ButtonReturnToAlgChoose(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = false;
    app.runningBack = false;
    app.aktualnyStan = algorithmC;
    for (Vertex &v: app.G.vertices)
        v.color = sf::Color::Red;
    for (Edge &e: app.G.allEdges)
        e.color = sf::Color::Black;
    }
void ButtonStepRight(Application    &app,Button &thisButton,sf::Event &event) {
    app.stepLista.GoRight();}
void ButtonStepLeft(Application     &app,Button &thisButton,sf::Event &event) {
    app.stepLista.GoLeft();}
void ButtonRunDFS(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 0;
    app.stepLista.GoRight();
    //app.algorithms[0](&(app.G),&app.stepLista);
    //app.aktualnyStan = algorithmR;
}
void ButtonRunBFS(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 1;
    app.stepLista.GoRight();
    //app.algorithms[1](&(app.G),&app.stepLista);
    //app.aktualnyStan = algorithmR;
}
void ButtonRunColors(Application    &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 2;
    app.stepLista.GoRight();
    //app.algorithms[2](&(app.G),&app.stepLista);
    //app.aktualnyStan = algorithmR;
}
void SetTextToMousePosition(Application &app,Button &thisButton,sf::Event &event) {   
    thisButton.text.setString(std::to_string(event.mouseButton.x) + "x "+ std::to_string(event.mouseButton.y)+ "y");}


Application::Application()
{
    if (!font.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    G = Graph(&font);
    stepLista = StepList(&G);
    sG = &G;
    aktualnyStan    = addV;
    holdingVertexId = -1;
    simulateForces = false;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    
    runningForward = false;
    runningBack = false;
    timeStep = 0.01; //czas
    lastStep = 0;

    buttons.push_back(Button(50,24,195,45,"Dodaj wierzcholek",   &font,ButtonAddVertex));
    buttons.push_back(Button(250,24,195,45,"Usun wierzcholek",   &font,ButtonRemoveVertex));
    buttons.push_back(Button(450,24,145,45,"Dodaj krawedz",      &font,ButtonAddEdge));
    buttons.push_back(Button(800,24,145,45,"Usun krawedz",       &font,ButtonRemoveEdge));
    buttons.push_back(Button(900,24,145,45,"Symulacja sil",      &font,ButtonSimulate));
    buttons.push_back(Button(1050,24,145,45,"Odczyt z pliku",    &font,ButtonReadFile));
    buttons.push_back(Button(1200,24,145,45,"Zapis do pliku",    &font,ButtonSaveFile));

    buttons.push_back(Button(1350,24,150,45,"Koordy",            &font,SetTextToMousePosition));
    buttons.push_back(Button(1350,24,150,45,"Przesun\nwierzcholek",&font,ButtonMoveVertex));
    buttons.push_back(Button(1350,24,150,45,"Wybierz\nAlgorytm", &font,ButtonAlgorithm));

    algorithms.push_back(DFS);   
    algorithms.push_back(BFS);   
    buttonsAlg.push_back(Button(50,24,50,45,"DFS",     &font,ButtonRunDFS));
    buttonsAlg.push_back(Button(50,24,50,45,"BFS",     &font,ButtonRunBFS));
    
    algorithms.push_back(ColorsAlgorithm);
    buttonsAlg.push_back(Button(190,24,80,45,"Kolory",          &font,ButtonRunColors));
    buttonsAlg.push_back(Button(190,24,150,45,"Powrot",          &font,ButtonReturnToGraphEdit));
    


    buttonsAlgR.push_back(Button(50,24,50,45,"<",                &font,PlayBackAlgorithm));
    buttonsAlgR.push_back(Button(50,24,50,45,"||",               &font,StopPlayingAlgorithm));
    buttonsAlgR.push_back(Button(50,24,50,45,">",                &font,PlayAlgorithm));
    buttonsAlgR.push_back(Button(50,24,50,45,"->",               &font,ButtonStepRight));
    buttonsAlgR.push_back(Button(120,24,50,45,"<-",              &font,ButtonStepLeft));
    buttonsAlgR.push_back(Button(190,24,150,45,"Powrot",         &font,ButtonReturnToAlgChoose));
    buttonsChooseVertex.push_back(Button(190,24,150,45,"Powrot", &font,ButtonReturnToAlgChoose));

    for (int i = 1; i< buttons.size();++i) {
        buttons[i].x = buttons[i-1].x + buttons[i-1].width + BUTTON_SPACING;
        buttons[i].Relocate();
    }
    for (int i = 1; i< buttonsAlg.size();++i) {
        buttonsAlg[i].x = buttonsAlg[i-1].x + buttonsAlg[i-1].width + BUTTON_SPACING;
        buttonsAlg[i].Relocate();
    }
    for (int i = 1; i< buttonsAlgR.size();++i) {
        buttonsAlgR[i].x = buttonsAlgR[i-1].x + buttonsAlgR[i-1].width + BUTTON_SPACING;
        buttonsAlgR[i].Relocate();
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
    for (Button &button : buttonsAlg) {
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {//czy myszka jest w prostokacie przycisku
            button.SetColor(sf::Color::Blue);
        }
        else {
            button.SetColor(sf::Color::Black);
        }
    }
    for (Button &button : buttonsAlgR) {
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {//czy myszka jest w prostokacie przycisku
            button.SetColor(sf::Color::Blue);
        }
        else {
            button.SetColor(sf::Color::Black);
        }
    }
    for (Button &button : buttonsChooseVertex) {
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {//czy myszka jest w prostokacie przycisku
            button.SetColor(sf::Color::Blue);
        }
        else {
            button.SetColor(sf::Color::Black);
        }
    }

}

void Application::Run() {
    for(Vertex v2: G.vertices) {
        std::cerr<<"V: "<<v2.id<<std::endl;
    }    
    std::cerr<<"edges:"<<std::endl;
    for(Edge e2:G.allEdges) {
        std::cerr<<"E: "<<e2.id<<" "<<e2.idVertexFrom<<", "<<e2.idVertexTo<<std::endl;}

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {HandleEvent(event);}

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //stepLista.currentStep                
        //std::cerr<<"steplista: "<<stepLista.G->vertices.size()<<" <-> "<< stepLista.G <<"\n";
        //std::cerr<<(stepLista.G == sG);
        //assert((zeroV) || (    (stepLista.G->vertices[0].id >= 0 && stepLista.G->vertices[0].id <= 2) && stepLista.currentStep >= -1   ));
        
        if(simulateForces)
        {
            G.CalculateForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);//to wtedy i tlyko wtedy gdy aktualny stan na symulacje sily
            G.ApplyForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);
        } else {
            for (Vertex &v: G.vertices) {
                v.KeepInGraphArea(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);
            }
        }
        if( runningForward && aktualnyStan == algorithmR ){
            long double tt= clock();
            tt /= CLOCKS_PER_SEC;
            if( tt >= lastStep + timeStep ){
                lastStep = tt;
                stepLista.GoRight();
            }
        }
        if( runningBack && aktualnyStan == algorithmR ){
            long double tt= clock();
            tt /= CLOCKS_PER_SEC;
            if( tt >= lastStep + timeStep ){
                lastStep = tt;
                stepLista.GoLeft();
            }
        }
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

    G.Draw(GraphArea,aktualnyStan != algorithmR);
     
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
    switch( aktualnyStan )
    {
        case algorithmC:
            for (int i=0; i<buttonsAlg.size(); ++i) {
                buttonsAlg[i].draw(toolBar);
            }
            break;
        case algorithmR:
            for (int i=0; i<buttonsAlgR.size(); ++i) {
                buttonsAlgR[i].draw(toolBar);
            }
            break;
        case chooseVertex:
            for (int i=0; i<buttonsChooseVertex.size(); ++i) {
                buttonsChooseVertex[i].draw(toolBar);
            }
            break;
        default:
            for (int i=0; i<buttons.size(); ++i) {
                buttons[i].draw(toolBar);
            }
            break;
    }
    toolBar.display();
    sf::Sprite toolBarSprite;
    toolBarSprite.setTexture(toolBar.getTexture());
    toolBarSprite.setPosition(0,0);
    window.draw(toolBarSprite);

}