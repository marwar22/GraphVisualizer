#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include "graph.hpp"
#include "utils.hpp"
#define pb push_back
#define rep(i,a,b) for(int i = (int)a; i <= (int)b; i++)
#define M_RAD 57.2957

float GetAngleByCoordinates(float x, float y)//zwraca kat miedzy osia y+ zgodnie z ruchem wskazowek zegara do punku (x,y)
{
    float angle = atan2(-y,-x);
    if (angle < 0) angle += 2*M_PI;
    return angle;
}

float GetAngleByPoints(sf::Vector2f v,sf::Vector2f w) {
    float x = v.x - w.x;
    float y = v.y - w.y;
    return GetAngleByCoordinates(x,y);
}

float getLength(sf::Vector2f p1, sf::Vector2f p2) {//odleglosc miedzy dwoma punktami w przestrzeni
	return sqrtf(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Graph::Graph(sf::Font * f) {
    font = f;
    isDirected = false;
    isWeighted = false;
}

Graph::Graph(Graph* g){
    vertices = std::vector<Vertex>(g->vertices);
    allEdges = std::vector<Edge>(g->allEdges);

    font = g->font;
    isDirected = g->isDirected;
    isWeighted = g->isWeighted;
}


Graph::Graph(){}

void Graph::CalculateForces(const int width,const int height) {
	//rep(i, 0, vertices.size()-1)
    for (Vertex &v:vertices) v.force = sf::Vector2f(0.f,0.f);
	//przyciaganie do srodka 800 400
	rep(i, 0, vertices.size()-1) {
		float distance   = getLength(sf::Vector2f(width/2, height/2), vertices[i].position);
		float forceValue = CenterGravityForce(distance);
		float angle      = GetAngleByCoordinates(vertices[i].position.x - 800, vertices[i].position.y - 400);
		sf::Vector2f forces(cos(angle) * forceValue, sin(angle) * forceValue);
        vertices[i].force += forces;
	}

	//odpychanie sie wierzcholkow
	for (int i = 0; i < vertices.size(); ++i) {
		for (int j = i+1; j < vertices.size(); ++j) {
		float distance   = getLength(vertices[i].position, vertices[j].position);
		float forceValue = VertexRepulsionForce(distance);
		float angle      = GetAngleByCoordinates(vertices[i].position.x - vertices[j].position.x, vertices[i].position.y - vertices[j].position.y);
        sf::Vector2f forces(cos(angle) * forceValue, sin(angle) * forceValue);
		vertices[i].force += forces;
        vertices[j].force -= forces;
        }
	}

	//przyciaganie sie na krawedziach
	for (auto edge : allEdges) {
        int v = edge.idVertexFrom;
        int w = edge.idVertexTo;

		float distance   = getLength(vertices[v].position, vertices[w].position);
		float forceValue = EdgeAttractionForce(distance);
		float angle      = GetAngleByCoordinates(vertices[v].position.x - vertices[w].position.x, vertices[v].position.y - vertices[w].position.y);
        
        //std::cerr<<v<<" "<<w<<" "<<angle*180/(M_PI)<<std::endl;
        //std::cerr<< cos(angle) * forceValue<<" "<< sin(angle) * forceValue<<std::endl;

        sf::Vector2f forces(cos(angle) * forceValue, sin(angle) * forceValue);
        vertices[v].force += forces;
        vertices[w].force -= forces;
	
    }
}

void Graph::ApplyForces(int width,int height) {
//	rep(i, 0, vertices.size()-1) {
    for (Vertex &v :vertices) {
        if (v.isBeingChosen) {
            v.KeepInGraphArea(width, height);
            continue;
        }
		sf::Vector2f delta = sf::Vector2f(v.force.x , v.force.y );
        //std::cerr<<"F "<< i <<" "<<delta.x<<" "<<delta.y<<std::endl;

        if (delta.x > 10) delta.x  = 10;
        if (delta.x < -10) delta.x = -10;
        if (delta.y > 10) delta.y  = 10;
        if (delta.y < -10) delta.y = -10;

		v.position += delta;
        v.KeepInGraphArea(width, height);
		v.text1.setPosition( v.text1.getPosition()  + delta);
	}
}

float Graph::VertexRepulsionForce(float distance) {
    if (distance >= OPT_V_DST) return 0;
    //if (distance >= 270) return 1/(distance-250);

    float force = distance - OPT_V_DST;
    force *= force;
    force /= -3000.f;
    //if (distance > OPT_V_DST) force /= -100.f;
    //std::cerr<<"VGF"<<distance / 1000.f<<" "<<force<<std::endl;
    //return std::min(0.05f,force);
    return force;
}

float Graph::EdgeAttractionForce(float distance) {
    float force = distance - OPT_E_DST;
    force *= force;
    force /= 5000.f;
    if (distance < OPT_E_DST) force *= -1.f; 
    //std::cerr<<"EAF"<<distance / 400.f<<" "<<force<<std::endl;
    return std::min(distance / 100.f, force);
}

float Graph::CenterGravityForce(float distance) {
	float force = distance;
    force *= force;
    force /= 5000000.f;
    return force;
}

void Graph::Draw(sf::RenderTarget& window,bool editLook){


    for (Edge edge: allEdges) {        
        float distance = getLength(vertices[edge.idVertexFrom].position,vertices[edge.idVertexTo].position);
        float angle = GetAngleByPoints(vertices[edge.idVertexFrom].position,vertices[edge.idVertexTo].position);       
        sf::RectangleShape line(sf::Vector2f(distance, LINE_WIDTH));
        
        line.setOrigin(sf::Vector2f(0, LINE_WIDTH/2));
        if (editLook) edge.color = sf::Color::Black;
        line.setFillColor(edge.color);
        line.setPosition(vertices[edge.idVertexFrom].position);
        line.setRotation(angle*(180/M_PI));
        window.draw(line);

        
        if (isDirected) {
            sf::RectangleShape arrowLine1(sf::Vector2f(ARR_H, ARR_W));
            sf::RectangleShape arrowLine2(sf::Vector2f(ARR_H, ARR_W));
            arrowLine1.setOrigin(sf::Vector2f(0, ARR_W));
            arrowLine2.setOrigin(sf::Vector2f(0, 0));
            arrowLine1.setFillColor(edge.color);
            arrowLine2.setFillColor(edge.color);
            arrowLine1.setPosition(vertices[edge.idVertexFrom].position + sf::Vector2f(cos(angle)*V_RADIUS, sin(angle)*V_RADIUS)); // jaka konwencja from/to
            arrowLine2.setPosition(vertices[edge.idVertexFrom].position + sf::Vector2f(cos(angle)*V_RADIUS, sin(angle)*V_RADIUS)); // jaka konwencja from/to

            arrowLine1.setRotation(angle*(180/M_PI) + 45);
            arrowLine2.setRotation(angle*(180/M_PI) - 45);
            window.draw(arrowLine1);
            window.draw(arrowLine2);
        }

        edge.t1.setString(std::to_string(edge.id));//TA LINIJKA DO USUNIECIA
        edge.t1.setPosition((vertices[edge.idVertexFrom].position.x + vertices[edge.idVertexTo].position.x)/2,(vertices[edge.idVertexFrom].position.y + vertices[edge.idVertexTo].position.y)/2);
        edge.t2.setPosition((vertices[edge.idVertexFrom].position.x + vertices[edge.idVertexTo].position.x)/2,(vertices[edge.idVertexFrom].position.y + vertices[edge.idVertexTo].position.y)/2+20);
        window.draw(edge.t1);
        //window.draw(edge.t2);
    }

    sf::CircleShape shape(V_RADIUS,100);
    shape.setOrigin(sf::Vector2f(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2));
    //shape.setFillColor(sf::Color::Blue);
    
    for (Vertex v: vertices) {
        v.text1.setString(std::to_string(v.id));
        shape.setPosition(sf::Vector2f(v.position.x, v.position.y));
        if (editLook) {
            v.color = sf::Color::Red;            
            if (v.isBeingChosen) {
                shape.setFillColor(sf::Color::Yellow);
            } else {
                shape.setFillColor(sf::Color::Red);
            }
        }else {
            shape.setFillColor(v.color);
        }
        window.draw(shape);
        if(v.id < 10) v.text1.setPosition(sf::Vector2f(v.position.x, v.position.y- 3));
        else if(v.id < 100) v.text1.setPosition(sf::Vector2f(v.position.x + 3, v.position.y - 3));
        else v.text1.setPosition(sf::Vector2f(v.position.x + 6, v.position.y - 3));
        window.draw(v.text1);
    }
}
