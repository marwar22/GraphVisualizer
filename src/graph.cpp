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

float GetAngleByCoordinates(float x, float y) {
    float angle = atan2(-y,-x);
    if (angle < 0) angle += 2*M_PI;
    return angle;
}

float GetAngleByPoints(sf::Vector2f v,sf::Vector2f w) {
    float x = v.x - w.x;
    float y = v.y - w.y;
    return GetAngleByCoordinates(x,y);
}

float getLength(sf::Vector2f p1, sf::Vector2f p2) {//odległość między dwoma punktami w przestrzeni
	return sqrtf(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Graph::Graph(sf::Font * f) {
    font = f;
    isDirected = true;
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
void Graph::CalculateRepulsionForceMidEdges(MidEdge &me1, MidEdge &me2){
    float distance   = getLength(me1.position,me2.position);
    float forceValue = MidEdgeOtherMidEdgeRepulsionForce(distance);
    float angle      = GetAngleByPoints(me1.position,me2.position);

    sf::Vector2f forces(cos(angle) * forceValue, sin(angle) * forceValue);
    me1.force += forces;
    me2.force -= forces;
}
void Graph::CalculateForces(const int width,const int height,bool simulateForces) {

    for (Vertex &v:vertices) v.force = sf::Vector2f(0.f,0.f); //zerowanie sił wierzchołków
    for (Edge   &e:allEdges) e.midEFrom.force = e.midETo.force = sf::Vector2f(0.f,0.f); //zerowanie sił między krawędzi
    if (simulateForces) {
        //przyciaganie do srodka 
        for (Vertex &v:vertices) {
            float distance   = getLength(sf::Vector2f(width/2, height/2), v.position);
            float forceValue = CenterGravityForce(distance);
            float angle      = GetAngleByCoordinates(v.position.x - width/2, v.position.y - height/2);
            sf::Vector2f forces(cos(angle) * forceValue, sin(angle) * forceValue);
            v.force += forces;
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
    }
	
	for (Edge &edge : allEdges) {
        int v = edge.idVertexFrom;
        int w = edge.idVertexTo;
        //przyciaganie sie na krawedziach
        float distance, forceValue, angle; 
        sf::Vector2f forces;
        if (simulateForces) {
            distance   = getLength(vertices[v].position, vertices[w].position);
            forceValue = EdgeAttractionForce(distance);
            angle      = GetAngleByCoordinates(vertices[v].position.x - vertices[w].position.x, vertices[v].position.y - vertices[w].position.y);
            
            forces = sf::Vector2f(cos(angle) * forceValue, sin(angle) * forceValue);
            vertices[v].force += forces;
            vertices[w].force -= forces;
        }

        //-----------------------------------------
        //przyciąganie się wierzchołek - midkrawędź
        float selfLoopMltp = 1;
        if(v == w) selfLoopMltp = 100.f;
        distance   = getLength(vertices[v].position, edge.midEFrom.position);
        forceValue = MidEdgeVertexAttractionForce(distance,selfLoopMltp);
        angle      = GetAngleByPoints(vertices[v].position, edge.midEFrom.position);
        forces = sf::Vector2f(cos(angle) * forceValue, sin(angle) * forceValue);
        edge.midEFrom.force -= forces;

        distance   = getLength(vertices[w].position, edge.midETo.position);
        forceValue = MidEdgeVertexAttractionForce(distance,selfLoopMltp);
        angle      = GetAngleByPoints(vertices[w].position, edge.midETo.position);
        forces = sf::Vector2f(cos(angle) * forceValue, sin(angle) * forceValue);
        edge.midETo.force -= forces;

        //----------------------------------------
        //przyciąganie się midkrawędź - midkrawędź
        distance   = getLength(edge.midEFrom.position, edge.midETo.position);
        forceValue = MidEdges1EdgeAttractionForce(distance,selfLoopMltp);
        angle      = GetAngleByPoints(edge.midEFrom.position, edge.midETo.position);
        forces = sf::Vector2f(cos(angle) * forceValue, sin(angle) * forceValue);
        edge.midEFrom.force += forces;
        edge.midETo.force   -= forces;
    }

    for (int i = 0; i < allEdges.size(); ++i) {
        for (int j = i+1; j < allEdges.size(); ++j) {
            CalculateRepulsionForceMidEdges(allEdges[i].midEFrom,allEdges[j].midEFrom);
            CalculateRepulsionForceMidEdges(allEdges[i].midETo,  allEdges[j].midETo);
            CalculateRepulsionForceMidEdges(allEdges[i].midEFrom,allEdges[j].midETo);
            CalculateRepulsionForceMidEdges(allEdges[i].midETo,  allEdges[j].midEFrom);
        }
    }
}

void Graph::ApplyForces(int width,int height) {
    for (Vertex &v :vertices) {
        if (v.isBeingChosen) {
            v.KeepInGraphArea(width, height);
            continue;
        }
		sf::Vector2f delta = sf::Vector2f(v.force.x , v.force.y );

        if (delta.x > 10)   delta.x  = 10;
        if (delta.x < -10)  delta.x = -10;
        if (delta.y > 10)   delta.y  = 10;
        if (delta.y < -10)  delta.y = -10;

		v.position += delta;
        v.KeepInGraphArea(width, height);
		v.text1.setPosition( v.text1.getPosition()  + delta);
	}
    for (Edge &e :allEdges) {
        e.midEFrom.position += e.midEFrom.force;        
        e.midETo.position   += e.midETo.force;        
    }
}

float Graph::VertexRepulsionForce(float distance) {
    if (distance >= OPT_V_DST) return 0;
    float force = distance - OPT_V_DST;
    force *= force;
    force /= -3000.f;
    return force;
}

float Graph::MidEdgeOtherMidEdgeRepulsionForce(float distance) {
    if (distance >= OPT_ME_OME_DST) return 0;
    float force = distance - OPT_ME_OME_DST;
    force *= force;
    force /= -1000.f;
    return force;
}

float Graph::MidEdges1EdgeAttractionForce(float distance, float optDst = OPT_ME_ME_DST) {
    float force = distance - optDst;
    force  *= force;
    force /= 1000.f;
    if (distance < optDst) force *= -1.f; 
    return std::min(distance / 100.f, force);
}


float Graph::EdgeAttractionForce(float distance) {
    float force = distance - OPT_E_DST;
    force *= force;
    force /= 5000.f;
    if (distance < OPT_E_DST) force *= -1.f; 
    return std::min(distance / 100.f, force);
}

float Graph::MidEdgeVertexAttractionForce(float distance,float optDst = OPT_ME_V_DST) {
    float force = distance - optDst;
    force  *= force;
    force /= 1000.f;
    if (distance < optDst) force *= -1.f; 
    return std::min(distance / 100.f, force);
}
float Graph::CenterGravityForce(float distance) {
	float force = distance;
    force *= force;
    force /= 5000000.f;
    return force;
}

float GetPtByPerc( float n1 , float n2 , float perc ) {
    float diff = n2 - n1;
    return n1 + ( diff * perc );
}    

void Graph::Draw(sf::RenderTarget& window, bool editLook, bool editEdges){
    sf::Vector2f dbg1,dbg2;
    sf::CircleShape dataShape(V_DATA_RADIUS,100);
    dataShape.setOrigin(sf::Vector2f(dataShape.getGlobalBounds().width/2,dataShape.getGlobalBounds().height/2));

    for (Edge &edge: allEdges) {   
        sf::Vector2f prvPos;
        sf::Vector2f posFrom   = vertices[edge.idVertexFrom].position;
        sf::Vector2f posMEFrom = edge.midEFrom.position;
        sf::Vector2f posMETo   = edge.midETo.position;
        sf::Vector2f posTo     = vertices[edge.idVertexTo].position;
        sf::Color color_of_elements = edge.color;

        if (editLook) {
            if (edge.isHighlighted) {
                edge.color = sf::Color::Yellow;
            } else {
                edge.color = sf::Color::Black;    
            }
        }
        
        float angleArrow = 10000;
        bool wasInside = false;
        
        for( int i = 0 ; i <= EDGE_POINTS ; i++ ) {
            float perc = (float)i / (float)EDGE_POINTS;
            sf::Vector2f aL(GetPtByPerc(posFrom.x, posMEFrom.x ,perc), GetPtByPerc(posFrom.y, posMEFrom.y ,perc));
            sf::Vector2f bL(GetPtByPerc(posMEFrom.x, posMETo.x ,perc), GetPtByPerc(posMEFrom.y, posMETo.y ,perc));
            sf::Vector2f cL(GetPtByPerc(posMETo.x, posTo.x ,perc), GetPtByPerc(posMETo.y, posTo.y ,perc));

            sf::Vector2f dL(GetPtByPerc(aL.x, bL.x ,perc), GetPtByPerc(aL.y, bL.y ,perc));
            sf::Vector2f eL(GetPtByPerc(bL.x, cL.x ,perc), GetPtByPerc(bL.y, cL.y ,perc));

            sf::Vector2f pos(GetPtByPerc(dL.x , eL.x , perc), GetPtByPerc(dL.y , eL.y , perc));
            if (i > 0) {
                int thisEdgeWidth = EDGE_WIDTH;
                if (edge.isHighlighted)
                    thisEdgeWidth *= 2;

                sf::RectangleShape edgeSeg(sf::Vector2f(getLength(prvPos,pos), thisEdgeWidth));
                edgeSeg.setFillColor(sf::Color(0,0,0,255));
                edgeSeg.setPosition(prvPos);
                edgeSeg.setOrigin(0,thisEdgeWidth/2);
                edgeSeg.setFillColor(edge.color);

                float angle = GetAngleByPoints(prvPos,pos);  
                edgeSeg.setRotation(angle*(180/M_PI));
                window.draw(edgeSeg);
                if (!wasInside) {
                    if (getLength(pos,vertices[edge.idVertexTo].position) <= V_RADIUS) {
                        dbg1 = pos;
                        dbg2 = prvPos;
                        angleArrow = GetAngleByPoints(pos,prvPos);
                        wasInside = true;
                    }                    
                }
            }            
            if (i == EDGE_POINTS/2) {
                edge.dataPoint = pos;
            }
            prvPos = pos;            
        }
        
        if (isDirected) {
            sf::RectangleShape arrowLine1(sf::Vector2f(ARR_H, ARR_W));
            sf::RectangleShape arrowLine2(sf::Vector2f(ARR_H, ARR_W));
            arrowLine1.setOrigin(sf::Vector2f(0, ARR_W));
            arrowLine2.setOrigin(sf::Vector2f(0, 0));
            arrowLine1.setFillColor(edge.color);
            arrowLine2.setFillColor(edge.color);
            arrowLine1.setPosition(vertices[edge.idVertexTo].position + sf::Vector2f(cos(angleArrow)*V_RADIUS, sin(angleArrow)*V_RADIUS)); // jaka konwencja from/to
            arrowLine2.setPosition(vertices[edge.idVertexTo].position + sf::Vector2f(cos(angleArrow)*V_RADIUS, sin(angleArrow)*V_RADIUS)); // jaka konwencja from/to

            arrowLine1.setRotation(angleArrow*(180/M_PI) + 45);
            arrowLine2.setRotation(angleArrow*(180/M_PI) - 45);
            window.draw(arrowLine1);
            window.draw(arrowLine2);
        }
        if (editEdges) {
            dataShape.setFillColor(edge.color);
            dataShape.setPosition(edge.dataPoint);
            window.draw(dataShape);
        }
        
        edge.t1.setString(std::to_string(edge.weight1));
        edge.t1.setOrigin(edge.t1.getLocalBounds().width/2,edge.t1.getLocalBounds().height/2);
        edge.t1.setPosition(edge.dataPoint.x,edge.dataPoint.y);
        edge.t2.setPosition(edge.dataPoint.x,edge.dataPoint.y+20);
        window.draw(edge.t1);
    }

    sf::CircleShape shape(V_RADIUS,100);
    shape.setOrigin(sf::Vector2f(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2));
    
    for (Vertex v: vertices) {
        v.text1.setString(std::to_string(v.id));
        v.subText.setString(std::to_string(v.data1));
        v.subText2.setString(std::to_string(v.data2));
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

        if (!editLook) {
            v.subText.setPosition(sf::Vector2f(v.text1.getPosition().x, v.text1.getPosition().y + 20));
            v.subText2.setPosition(sf::Vector2f(v.subText.getPosition().x, v.subText.getPosition().y + 20));
            v.subText.setOrigin(sf::Vector2f(v.subText.getGlobalBounds().width/2,v.subText.getGlobalBounds().height/2));
            v.subText2.setOrigin(sf::Vector2f(v.subText2.getGlobalBounds().width/2,v.subText2.getGlobalBounds().height/2));
            window.draw(v.subText);
            window.draw(v.subText2);
        }
    }
}
