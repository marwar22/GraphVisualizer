#ifndef UTILS_HPP
#define UTILS_HPP
#include "graph.hpp"

const float OPT_V_DST  = 200.f;
const float OPT_E_DST  = 100.f;
const float OPT_ME_DST = 20.f;
const float OPT_MED_DST = 50.f;

const float V_RADIUS = 15.f;
const float LINE_WIDTH = 3.f;

const int GRAPH_AREA_WIDTH   = 1920;
const int GRAPH_AREA_HEIGHT  = 980;
const int GRAPH_AREA_BORDER  = 20;
const int TOOLBAR_HEIGHT     = 100;
const int BUTTON_SPACING     = 20;
const int BUTTON_HEIGHT      = 45;

const float ARR_W = 5.5;
const float ARR_H = 15.f;

void PrintGraphLog(Graph &G);

#endif