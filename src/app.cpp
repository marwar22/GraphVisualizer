#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "graph.hpp"
#include "app.hpp"
#include "utils.hpp"
#include "algorithms/algorithms.hpp"


void ChooseVertexInit(Application &app)
{
    app.aktualnyStan = chooseVertex;
    app.chosenVertices.clear();
}
void Application::ClearSelected() {
    if (firstVertexId != -1) {
        G.vertices[firstVertexId].isBeingChosen = false;
        firstVertexId = -1;
    }

    if (secondVertexId != -1) {
        G.vertices[secondVertexId].isBeingChosen = false;
        secondVertexId = -1;
    }

    if (selectedEdgeId != -1) {
        G.allEdges[selectedEdgeId].isHighlighted = false;
        selectedEdgeId = -1;
    }
}
void ButtonRemoveVertex(Application &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = removeV;}
void ButtonAddVertex(Application    &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = addV;}
void ButtonAddEdge(Application      &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = addE;}
void ButtonEditEdge(Application     &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = editE;}
void ButtonRemoveEdge(Application   &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = removeE;}
void ButtonMoveVertex(Application   &app,Button &thisButton,sf::Event &event) {app.aktualnyStan = movingV;}
void ButtonSimulate(Application     &app,Button &thisButton,sf::Event &event) {app.simulateForces = !app.simulateForces;}
void ButtonAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.simulateForces = false;
    app.runningForward = false;
    app.aktualnyStan = algorithmC; 
    app.G.befAlgIsDirected = app.G.isDirected;
   }
void PlayAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = true;
    app.runningBack = false;
    app.lastStep = clock();
    app.lastStep /= CLOCKS_PER_SEC; 
   }
void PlayBackAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningBack = true;
    app.runningForward = false;
    app.lastStep = clock();
    app.lastStep /= CLOCKS_PER_SEC; 
   }
void StopPlayingAlgorithm(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = false;
    app.runningBack = false; 
   }
void ButtonReadFile(Application     &app,Button &thisButton,sf::Event &event) {
    app.textEntered.clear();
    app.aktualnyStan = readFile;
    app.textEntered.clear(); 
    }
void ButtonSaveFile(Application     &app,Button &thisButton,sf::Event &event) {
    app.textEntered.clear();
    app.aktualnyStan = saveFile;
    app.textEntered.clear(); 
    }
void ButtonReturnToGraphEdit(Application       &app,Button &thisButton,sf::Event &event) {
    app.aktualnyStan = nothing;
    app.holdingVertexId = -1;
    app.firstVertexId = -1;    
    app.secondVertexId = -1; 
   }
void ButtonReturnToAlgChoose(Application    &app,Button &thisButton,sf::Event &event) {
    app.runningForward = false;
    app.runningBack = false;
    app.aktualnyStan = algorithmC;
    app.G.isDirected = app.G.befAlgIsDirected;
    for (Vertex &v: app.G.vertices)
        v.color = sf::Color::Red;
    for (Edge &e: app.G.allEdges){
        e.color = sf::Color::Black;
        e.isHighlighted = false;
    }
} 
void ButtonStepRight(Application    &app,Button &thisButton,sf::Event &event) {
    app.stepLista.GoRight();
    app.runningForward = false;
    app.runningBack = false;}
void ButtonStepLeft(Application     &app,Button &thisButton,sf::Event &event) {
    app.stepLista.GoLeft();
    app.runningForward = false;
    app.runningBack = false;}
void ButtonRunDFS(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 0;
}
void ButtonRunBFS(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 1;
}
void ButtonRunDIJKSTRA(Application  &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 2;
}
void ButtonRunSCC(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    app.aktualnyStan = algorithmR;
    app.algorithmId = 3;
    app.algorithms[app.algorithmId](&(app.G),&(app.stepLista),app.chosenVertices);
}

void ButtonRunPostorder(Application &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 4;
}

void ButtonRunMST(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 5;
}

void ButtonRunIsBipartial(Application       &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    ChooseVertexInit(app);
    app.algorithmId = 6;
}

void ButtonRunColors(Application    &app,Button &thisButton,sf::Event &event) {
    app.stepLista.ClearStates();
    app.aktualnyStan = algorithmR;
    app.algorithmId = 7;
    app.algorithms[app.algorithmId](&(app.G),&(app.stepLista),app.chosenVertices);
}

void ButtonGraphDirected(Application    &app,Button &thisButton,sf::Event &event) {
    app.G.isDirected = !app.G.isDirected;
}

void ButtonNothing(Application &app,Button &thisButton,sf::Event &event){}

void ButtonIncreaseAlgSpeed(Application    &app,Button &thisButton,sf::Event &event) {
    if (app.timeStep < 1.f/2047.f) return;
    app.timeStep /= 2; 
}
void ButtonDecreaseAlgSpeed(Application    &app,Button &thisButton,sf::Event &event) {
    if (app.timeStep > 4.1f) return;
    app.timeStep *= 2; 
}
Application::Application()
{
    if (!font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    
    G = Graph(&font);
    stepLista = StepList(&G);
    aktualnyStan    = addV;
    firstVertexId   = -1;
    secondVertexId  = -1;    
    holdingVertexId = -1;
    simulateForces = true;
    settings.antialiasingLevel = 8;
    
    sf::RenderTexture fejktekstura;
    
    #if (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR == 5 && SFML_VERSION_PATCH == 1)
        while(!fejktekstura.create(1,1,settings)) {
        	settings.antialiasingLevel/=2;
    	}
    #else
        settings.antialiasingLevel = 0;
    #endif
    



    runningForward = false;
    runningBack = false;
    timeStep = (1.f/16.f); 
    lastStep = 0;
    
    selectedEdgeId = -1;
    
    
    #ifdef _WIN32
        sf::Text textAddVertex( "Dodaj wierzcholek", font , 20);
        sf::Text textRemoveVertex( "Usun wierzcholek", font , 20);
        sf::Text textAddEdge( "Dodaj krawedz", font , 20);
        sf::Text textEdgeEdit( "Edycja krawedzi", font , 20);
        sf::Text textDeleteEdge( "Usun krawedz", font , 20);
        sf::Text textForceSimulation( "Symulacja sil", font , 20);
        sf::Text textMoveVertex( "Przesun\nwierzcholek", font , 20);
        sf::Text textReturn( "Powrot", font , 20);
    #else
        sf::Text textAddVertex( L"Dodaj wierzchołek", font , 20);
        sf::Text textRemoveVertex( L"Usuń wierzchołek", font , 20);
        sf::Text textAddEdge( L"Dodaj krawędź", font , 20);
        sf::Text textEdgeEdit( L"Edycja krawędzi", font , 20);
        sf::Text textDeleteEdge( L"Usuń krawędź", font , 20);
        sf::Text textForceSimulation( L"Symulacja sił", font , 20);
        sf::Text textMoveVertex( L"Przesuń\nwierzchołek", font , 20);
        sf::Text textReturn( L"Powrót", font , 20);
    #endif
    buttons.push_back(Button(50,24,195,45,textAddVertex,         &font,ButtonAddVertex));
    buttons.push_back(Button(250,24,195,45,textRemoveVertex,     &font,ButtonRemoveVertex));
    buttons.push_back(Button(450,24,145,45,textAddEdge,          &font,ButtonAddEdge));
    buttons.push_back(Button(900,24,145,45,textEdgeEdit,         &font,ButtonEditEdge));
    buttons.push_back(Button(800,24,145,45,textDeleteEdge,       &font,ButtonRemoveEdge));
    buttons.push_back(Button(900,24,145,45,textForceSimulation,  &font,ButtonSimulate));
    buttons.push_back(Button(1050,24,145,45,"Odczyt z pliku",    &font,ButtonReadFile));
    buttons.push_back(Button(1200,24,145,45,"Zapis do pliku",    &font,ButtonSaveFile));
    buttons.push_back(Button(1350,24,150,45,textMoveVertex,      &font,ButtonMoveVertex));
    buttons.push_back(Button(1350,24,150,45,"Graf skierowany",      &font,ButtonGraphDirected));
    buttons.push_back(Button(1350,24,150,45,"Wybierz\nAlgorytm", &font,ButtonAlgorithm));

    algorithms.push_back(DFS);   
    buttonsAlg.push_back(Button(50,24,50,45,"DFS", &font,ButtonRunDFS));

    algorithms.push_back(BFS);   
    buttonsAlg.push_back(Button(50,24,50,45,"BFS", &font,ButtonRunBFS));
    
    algorithms.push_back(DIJKSTRA);   
    buttonsAlg.push_back(Button(50,24,85,45,"Dijkstra", &font,ButtonRunDIJKSTRA));

    algorithms.push_back(SCC);   
    buttonsAlg.push_back(Button(50,24,50,45,"SCC", &font,ButtonRunSCC));

    algorithms.push_back(POSTORDER);   
    buttonsAlg.push_back(Button(50,24,120,45,"POSTORDER", &font,ButtonRunPostorder));

    algorithms.push_back(MST);   
    buttonsAlg.push_back(Button(50,24,50,45,"MST", &font,ButtonRunMST));

    algorithms.push_back(BIPARTIAL_CHECK);
    buttonsAlg.push_back(Button(50,24,120,45,"Dwudzielny?", &font,ButtonRunIsBipartial));

    algorithms.push_back(ColorsAlgorithm);
    buttonsAlg.push_back(Button(190,24,100,45,"Kolory",&font,ButtonRunColors));

    buttonsAlg.push_back(Button(190,24,85,45, textReturn, &font,ButtonReturnToGraphEdit));
    
    buttonsAlgR.push_back(Button(30,24,50,45,"<",                &font,PlayBackAlgorithm));
    buttonsAlgR.push_back(Button(100,24,50,45,"||",              &font,StopPlayingAlgorithm));
    buttonsAlgR.push_back(Button(170,24,50,45,">",               &font,PlayAlgorithm));
    buttonsAlgR.push_back(Button(310,24,50,45,"<-",              &font,ButtonStepLeft));
    buttonsAlgR.push_back(Button(240,24,50,45,"->",              &font,ButtonStepRight));
    buttonsAlgR.push_back(Button(380,24,85,45, textReturn,      &font,ButtonReturnToAlgChoose));
    buttonsAlgR.push_back(Button(550,24,50,45,"-",               &font,ButtonDecreaseAlgSpeed));
    buttonsAlgR.push_back(Button(690,24,50,45,"+",               &font,ButtonIncreaseAlgSpeed));
    buttonsAlgR.push_back(Button(690,24,60,45,"",                &font,ButtonNothing));
    buttonsAlgR[8].ifThisIsTextBox = true;

    buttonsChooseVertex.push_back(Button(190,24,85,45, textReturn, &font,ButtonReturnToAlgChoose));

    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Projekt PWI",sf::Style::Default,settings);
    window.setFramerateLimit(100);
}

void Application::CheckPodswietlenie(sf::Vector2i mousePosition) {
    for (Button &button : buttons) {
        if(button.ifThisIsTextBox) continue;
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {button.SetColor(sf::Color::Blue);}
        else {button.SetColor(sf::Color::Black);}
    }
    for (Button &button : buttonsAlg) {
        if(button.ifThisIsTextBox) continue;
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {button.SetColor(sf::Color::Blue);}
        else {button.SetColor(sf::Color::Black);}
    }
    for (Button &button : buttonsAlgR) {
        if(button.ifThisIsTextBox) continue;
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {button.SetColor(sf::Color::Blue);}
        else {button.SetColor(sf::Color::Black);}
    }
    for (Button &button : buttonsChooseVertex) {
        if(button.ifThisIsTextBox) continue;
        if (button.rectangle.getGlobalBounds().contains(mousePosition.x,mousePosition.y) ) {button.SetColor(sf::Color::Blue);}
        else {button.SetColor(sf::Color::Black);}
    }
}

void Application::Run() {    
    #ifdef DEBUG
        for(Vertex v2: G.vertices) {std::cerr<<"V: "<<v2.id<<std::endl;}    
        std::cerr<<"edges:"<<std::endl;
        for(Edge e2:G.allEdges) {std::cerr<<"E: "<<e2.id<<" "<<e2.idVertexFrom<<", "<<e2.idVertexTo<<std::endl;}
    #endif

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {HandleEvent(event);}

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        G.CalculateForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT,simulateForces);
        G.ApplyForces(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);
        
        if(runningForward && aktualnyStan == algorithmR){
            long double tt= clock();
            tt /= CLOCKS_PER_SEC;
            if(tt >= lastStep + timeStep){
                lastStep = tt;
                stepLista.GoRight();
            }
        }
        if(runningBack && aktualnyStan == algorithmR){
            long double tt= clock();
            tt /= CLOCKS_PER_SEC;
            if(tt >= lastStep + timeStep){
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
    
    window.clear(sf::Color::White);        
    RenderGraphArea();
    RenderToolBar();
    if( aktualnyStan == readFile || aktualnyStan == saveFile )
        RenderTextTyping();
    window.display();
}

void Application::RenderGraphArea(){
    
    sf::RenderTexture GraphArea;
    
    #if (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR == 5 && SFML_VERSION_PATCH == 1)
    	GraphArea.create(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT,settings);
    #else
        GraphArea.create(window.getSize().x,window.getSize().y-TOOLBAR_HEIGHT);
    #endif
    

    GraphArea.clear(sf::Color::Blue);

    G.Draw(GraphArea,aktualnyStan != algorithmR, (aktualnyStan == editE || aktualnyStan == removeE));
     
    GraphArea.display();
    sf::Sprite GraphAreaSprite;
    GraphAreaSprite.setTexture(GraphArea.getTexture());
    GraphAreaSprite.setPosition(0,TOOLBAR_HEIGHT);
    window.draw(GraphAreaSprite);    
}

int TotalLength( std::vector<Button>* buttonsv )
{
    int totalLength = 0;
    for (int i=0; i<buttonsv->size(); ++i) {totalLength += (*buttonsv)[i].width + BUTTON_SPACING;}
    if(buttonsv->size() > 0) totalLength += BUTTON_SPACING;
    return totalLength;
}

void SetPositionsForButtons( std::vector<Button>* buttonsv, Application* app )
{
    long double scale, xdb, ydb, btspdb, hdb, ldb, scalenxt;
    int l;
    scale = 1;
    for( ; scale >= 0.85; scale -= BUTTON_SCALE_DELTA ){
        l = TotalLength(buttonsv);
        ldb = l;
        ldb *= scale;
        l = ldb;
        if( l <= app->window.getSize().x ){
            btspdb = BUTTON_SPACING;
            btspdb *= scale;
            l = btspdb;
            (*buttonsv)[0].x = l;
            (*buttonsv)[0].scale = scale;
            (*buttonsv)[0].y = 25;
            xdb = (*buttonsv)[0].width;
            xdb *= scale;
            l += xdb + btspdb;
            for (int i = 1; i< buttonsv->size();++i) {
                (*buttonsv)[i].x = l;
                (*buttonsv)[i].y = 25;
                (*buttonsv)[i].scale = scale;
                xdb = (*buttonsv)[i].width;
                xdb *= scale;
                l += xdb + btspdb;
            }
            return;
        }
    }
    int i;
    scale = 0.85;
    for( ; scale >= 0.64; scale -= BUTTON_SCALE_DELTA ){
        i = 0;
        btspdb = BUTTON_SPACING;
        btspdb *= scale;
        l = btspdb;
        for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
            xdb = (*buttonsv)[i].width;
            xdb *= scale;
            l += xdb + btspdb;
            i++;
        }
        if( l > app->window.getSize().x ){
            i--;
            xdb = (*buttonsv)[i].width;
            xdb *= scale;
            l -= xdb + btspdb;
        }
        l = btspdb;
        for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
            xdb = (*buttonsv)[i].width;
            xdb *= scale;
            l += xdb + btspdb;
            i++;
        }
        if( l <= app->window.getSize().x ){
            i = 0, l = btspdb;
            for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
                (*buttonsv)[i].x = l;
                (*buttonsv)[i].y = 4;
                (*buttonsv)[i].scale = scale;
                xdb = (*buttonsv)[i].width;
                xdb *= scale;
                l += xdb + btspdb;
                i++;
            }
            if( l > app->window.getSize().x ){
                i--;
            }
            l = btspdb;
            for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
                (*buttonsv)[i].x = l;
                (*buttonsv)[i].y = 52;
                (*buttonsv)[i].scale = scale;
                xdb = (*buttonsv)[i].width;
                xdb *= scale;
                l += xdb + btspdb;
                i++;
            }
            return;
        }
    }
    for( int k = 3; k < 100; k++ ){
        scale = 1.8;
        scale /= k;
        scale *= 0.9;
        scalenxt = 1.8;
        scalenxt /= k + 1;
        scalenxt *= 0.9;
        for( int l = 3; l < k; l++ ){
            scale *= 0.9;
            scalenxt *= 0.9;
        }
        for( ; scale >= scalenxt; scale -= BUTTON_SCALE_DELTA ){
            i = 0;
            hdb = BUTTON_HEIGHT;
            hdb *= scale;
            btspdb = BUTTON_SPACING;
            btspdb *= scale;
            for( int j = 0; j < k; j++ )
            {
                l = btspdb;
                for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
                    xdb = (*buttonsv)[i].width;
                    xdb *= scale;
                    l += xdb + btspdb;
                    i++;
                }
                if( l > app->window.getSize().x ){
                    i--;
                    xdb = (*buttonsv)[i].width;
                    xdb *= scale;
                    l -= xdb + btspdb;
                }
            }
            if( i == buttonsv->size() ){
                i = 0;
                for( int j = 0; j < k; j++ )
                {
                    l = btspdb;
                    ydb = 6 + ( hdb + 6 ) * j;
                    //TOOLBAR_HEIGHT = ydb + hdb + 10;
                    for( ; l <= app->window.getSize().x && i < buttonsv->size(); ){
                        (*buttonsv)[i].x = l;
                        (*buttonsv)[i].y = ydb;
                        (*buttonsv)[i].scale = scale;
                        xdb = (*buttonsv)[i].width;
                        xdb *= scale;
                        l += xdb + btspdb;
                        i++;
                    }
                    if( l > app->window.getSize().x ){
                        i--;
                        xdb = (*buttonsv)[i].width;
                        xdb *= scale;
                        l -= xdb + btspdb;
                    }
                }
                return;
            }
        }
    }
}

void Application::RenderToolBar() {
    
    sf::RenderTexture toolBar;
    #if (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR == 5 && SFML_VERSION_PATCH == 1)
    	toolBar.create(window.getSize().x,TOOLBAR_HEIGHT,settings);
    #else
    	toolBar.create(window.getSize().x,TOOLBAR_HEIGHT);
    #endif

    toolBar.clear(sf::Color::Green);

    sf::RectangleShape shape(sf::Vector2f(toolBar.getSize().x,TOOLBAR_HEIGHT));
    shape.setFillColor(sf::Color::Green);
    toolBar.draw(shape);
    std::stringstream stringStream;
    std::string stringSpeed;
    switch( aktualnyStan )
    {
        case algorithmC:
            SetPositionsForButtons( &buttonsAlg, this );
            for (int i=0; i<buttonsAlg.size(); ++i) {
                buttonsAlg[i].draw(toolBar);
            }
            break;

        case algorithmR:
            stringStream << std::fixed << std::setprecision(3) << std::round(1000/timeStep)/16000;
            stringSpeed = stringStream.str();
            buttonsAlgR[8].text.setString(stringSpeed);
            SetPositionsForButtons( &buttonsAlgR, this );
            for (int i=0; i<buttonsAlgR.size(); ++i) {
                buttonsAlgR[i].draw(toolBar);
            }
            break;

        case chooseVertex:
            SetPositionsForButtons( &buttonsChooseVertex, this );
            for (int i=0; i<buttonsChooseVertex.size(); ++i) {
                buttonsChooseVertex[i].draw(toolBar);
            }
            break;

        default:
            SetPositionsForButtons( &buttons, this );
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

void Application::RenderTextTyping() {
    sf::Text inputboxtext;
    inputboxtext.setFont(font);
    inputboxtext.setString(textEntered);
    inputboxtext.setCharacterSize(20);
    
    #if (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR == 5 && SFML_VERSION_PATCH == 1)
    	inputboxtext.setFillColor(sf::Color(1,1,1));
    #else
    	inputboxtext.setColor(sf::Color(1,1,1));
    #endif

    inputboxtext.setOrigin(sf::Vector2f(inputboxtext.getGlobalBounds().width/2,0));
    inputboxtext.setPosition(INPUT_WIDTH/2,INPUT_HEIGHT/2-13);
    
    sf::RenderTexture inputbox;
    #if (SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR == 5 && SFML_VERSION_PATCH == 1)
    	inputbox.create(INPUT_WIDTH,INPUT_HEIGHT,settings);
    #else
    	inputbox.create(INPUT_WIDTH,INPUT_HEIGHT);
    #endif

    inputbox.clear(sf::Color(240, 240, 240));

    sf::RectangleShape shape(sf::Vector2f(inputbox.getSize().x,TOOLBAR_HEIGHT));
    shape.setFillColor(sf::Color(200,200,200));
    shape.setOutlineColor(sf::Color(1,1,1));
    inputbox.draw(shape);
    inputbox.draw(inputboxtext);
    
    inputbox.display();
    sf::Sprite inputboxsprite;
    inputboxsprite.setTexture(inputbox.getTexture());
    inputboxsprite.setPosition(window.getSize().x/2-INPUT_WIDTH/2,window.getSize().y/2-INPUT_HEIGHT/2);
    window.draw(inputboxsprite);
}
