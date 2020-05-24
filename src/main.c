
#include <raylib.h>
#include <math.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");

    //Loading imagen
    Image imagen_D = LoadImage("./resources/spritesheet_D.png");
    Image imagen_A = LoadImage("./resources/spritesheet_A.png");
    Image imagen_MINION = LoadImage("./resources/spritesheet_MINION.png");
    Image imagen_BRUTE = LoadImage("./resources/spritesheet_BRUTE.png");

    //Changing image scalar according to the entity it represents
    ImageResize(&imagen_D, imagen_D.width*1.5, imagen_D.height*1.5); 
    ImageResize(&imagen_A, imagen_A.width*1.5, imagen_A.height*1.5);
    ImageResize(&imagen_MINION, imagen_A.width*1.8, imagen_A.height*1.8);
    ImageResize(&imagen_BRUTE, imagen_A.width*2.4, imagen_A.height*2.4);


    //Transforming from image to textures
    Texture2D sprite_D = LoadTextureFromImage(imagen_D);
    Texture2D sprite_A = LoadTextureFromImage(imagen_A);
    Texture2D sprite_MINION = LoadTextureFromImage(imagen_MINION);
    Texture2D sprite_BRUTE = LoadTextureFromImage(imagen_BRUTE);
    Texture2D sprite_bullet = LoadTexture("./resources/sprite_Bullet.png");


    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    //Variables to animate the player
    Texture2D sprite_player = sprite_D; 
    Rectangle frameRec = {0.0f, 0.0f, (float)sprite_player.width/4, (float)sprite_player.height};
    int currentFrame = 0;
    int framesCounter = 0;

    //Variables to animate enemies
    Rectangle frameRec_M = {0.0f, 0.0f, (float)sprite_MINION.width/4, (float)sprite_MINION.height};
    Rectangle frameRec_B = {0.0f, 0.0f, (float)sprite_BRUTE.width/4, (float)sprite_BRUTE.height};
    int currentFrame_E = 0; 
    int framesCounter_E = 0;   

    // Main loop
    while(!WindowShouldClose()){

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta);

        //Indicates the direction in which the player entity is moving
        if(IsKeyDown(KEY_A))sprite_player = sprite_A;    
        if(IsKeyDown(KEY_D))sprite_player = sprite_D; 
    
        //Modify the animation speed according to the speed of the player
        float speed = sqrt(sta->pla.ent.vx*sta->pla.ent.vx+sta->pla.ent.vy*sta->pla.ent.vy);

        framesCounter++;
        framesCounter_E++;

        if (framesCounter >= (60/speed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;
            //Modify the animation frame 
            frameRec.x = (float)currentFrame*(float)sprite_player.width/4;
        }

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            draw_state(lvl, sta, sprite_bullet, sprite_player, sprite_BRUTE, sprite_MINION, frameRec, &frameRec_B, &frameRec_M, &currentFrame_E, &framesCounter_E);
            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

        EndDrawing();

    }
    // De-Initialization
    UnloadTexture(sprite_D);
    UnloadTexture(sprite_A);
    UnloadTexture(sprite_MINION);
    UnloadTexture(sprite_BRUTE);
    UnloadTexture(sprite_player);
    UnloadTexture(sprite_bullet);

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
