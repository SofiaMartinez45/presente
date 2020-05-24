#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells, iterate, including borders outside the level
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            // If the cell is a wall, paint it
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
        }
    }
}

void draw_state(const level *lvl, const state *sta, Texture2D sprite_bullet, Texture2D Sprite, Texture2D sprite_BRUTE, Texture2D sprite_MINION, Rectangle frameRec, Rectangle *frameRec_B, Rectangle *frameRec_M, int *currentFrame_E, int *framesCounter_E){

    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player is in the middle of the screen
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    // set the camera rotation to 0
    cam.rotation = 0.0;
    // set the camera zoom to 1
    cam.zoom = 1.0;

    // Draw everything relative to the camera from now on
    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);
    
    for(int i=0;i<sta->n_enemies;i++){
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};  
        //Draw enemies depending on the type
        if(sta->enemies[i].kind == MINION){
         
            if (*framesCounter_E >= (60/FRAME_SPEED))
            {
                
                (*framesCounter_E) = 0;
                (*currentFrame_E)++;
                
                if (*currentFrame_E > 5) *currentFrame_E = 0;

                frameRec_M->x = (float)*currentFrame_E*(float)sprite_MINION.width/4;
            }
            DrawTextureRec(sprite_MINION, *frameRec_M, vec, WHITE); 
        }
        else{
            if (*currentFrame_E > 5) *currentFrame_E = 0;

            frameRec_B->x = (float)*currentFrame_E*(float)sprite_BRUTE.width/4;
            DrawTextureRec(sprite_BRUTE, *frameRec_B, vec, WHITE); 
        }
    }

    // Draw player
    {
        // Get a copy of the player's entity
        entity ent = sta->pla.ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        //Draws the player texture according to the frames according to the player's speed
        DrawTextureRec(Sprite, frameRec, vec, WHITE); 
    }

    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw the sprite that represents the bullets
        DrawTextureV(sprite_bullet, vec, WHITE);   
    }

    // Stop drawing relative to the camera
    EndMode2D();
}
