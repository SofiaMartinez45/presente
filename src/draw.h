#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include <stdio.h>
#include "level.h"
#include "state.h"

#define FRAME_SPEED 4

// Draws the cells of the level in the screen
void draw_level(const level *lvl);

// Draws the whole state and the level in the screen
void draw_state(const level *lvl, const state *sta, Texture2D sprite_bullet, Texture2D sprite, Texture2D sprite_BRUTE, Texture2D sprite_MINION, Rectangle frameRec, Rectangle *frameRec_B, Rectangle *frameRec_M, int *currentFrame_E, int *framesCounter_E);

#endif
