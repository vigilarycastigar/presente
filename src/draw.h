#ifndef DRAW_H
#define DRAW_H

#include "level.h"
#include "state.h"
#include <raylib.h>

// Draws the cells of the level in the screen
void draw_level(const level *lvl);

// Draws the whole state and the level in the screen
void draw_state(const level *lvl, const state *sta, const Texture2D covid, Texture2D bac, Rectangle frameRecC, Rectangle frameRecB, Texture2D bullet);

#endif


/*Image covidSi = LoadImage("COVID.png");
    ImageResize(&covidSi, 128*PLAYER_RAD/17, 36*PLAYER_RAD/17);
    Texture2D covidS = LoadTextureFromImage(covidSi); // walking right
    Rectangle frameRecD = { 0.0f, 0.0f, (float)covidS.width/4, (float)covidS.height };*/