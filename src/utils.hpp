#ifndef UTILS_HPP
#define UTILS_HPP
#include "graph.hpp"

const float OPT_V_DST        = 200.f;
const float OPT_E_DST        = 100.f;
const float OPT_ME_V_DST     = 30.f;
const float OPT_ME_OME_DST   = 50.f;
const float OPT_ME_ME_DST    = 30.f;

const float V_RADIUS         = 15.f;
const float V_DATA_RADIUS    = 8.f;

const float ARR_W            = 5.5;
const float ARR_H            = 15.f;
const float EDGE_WIDTH       = 3.f;
const int EDGE_POINTS        = 50;  //dokładność rysowana krzywej (niewidoczne punkty środkowe na krawędziach)

const int GRAPH_AREA_WIDTH   = 1920;
const int GRAPH_AREA_HEIGHT  = 980;
const int GRAPH_AREA_BORDER  = 20;

const int TOOLBAR_HEIGHT     = 110;
const int BUTTON_SPACING     = 20;
const int BUTTON_HEIGHT      = 45;
const long double BUTTON_FONT_SCALE = 0.85;
const long double BUTTON_SCALE_DELTA = 0.002;
const int INPUT_HEIGHT     = 40;
const int INPUT_WIDTH     = 400;

void PrintGraphLog(Graph &G);

#endif