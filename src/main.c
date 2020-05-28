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

    //Charge main character image and declare its position
    Image docDi = LoadImage("DOC_WALKING11.png");
    ImageResize(&docDi, 192*PLAYER_RAD/25, 64*PLAYER_RAD/25);
    Texture2D docD = LoadTextureFromImage(docDi); // walking right
    Rectangle frameRecD = { 0.0f, 0.0f, (float)docD.width/3, (float)docD.height };
    Vector2 positionD = {800/2-(PLAYER_RAD*1.25), 600/2-(PLAYER_RAD*1.25)};

    Image docAi = LoadImage("DOC_WALKINGA11.png");
    ImageResize(&docAi, 192*PLAYER_RAD/25, 64*PLAYER_RAD/25);
    Texture2D docA = LoadTextureFromImage(docAi); // walking left
    Rectangle frameRecA = { 0.0f, 0.0f, (float)docA.width/3, (float)docA.height };
    Vector2 positionA = {800/2-(PLAYER_RAD*1.25), 600/2-(PLAYER_RAD*1.25)};

    // Charge bullet
    Image bulleti = LoadImage("BULLET.png");
    ImageResize(&bulleti, 36*BULLET_RAD/10, 22*BULLET_RAD/10);
    Texture2D bullet = LoadTextureFromImage(bulleti);

    // Charge bad dudes
    Image covidi = LoadImage("COVID_S.png");
    ImageResize(&covidi, 4*BRUTE_RAD*2, BRUTE_RAD*2);
    Texture2D covid = LoadTextureFromImage(covidi);
    Rectangle frameRecC = { 0.0f, 0.0f, (float)covid.width/4, (float)covid.height };

    Image baci = LoadImage("BACTERIA_S.png");
    ImageResize(&baci, 20*MINION_RAD/5, 11*MINION_RAD/5);
    Texture2D bac = LoadTextureFromImage(baci);
    Rectangle frameRecB = { 0.0f, 0.0f, (float)bac.width/5, (float)bac.height };

    // Initialize frames of main character
    int currentFrame = 0;
    int framesCounter = 0;

    // Initialize frames of bad dudes
    int currentFrameC = 0;
    int framesCounterC = 0;
    int currentFrameB = 0;
    int framesCounterB = 0;

    // A flag that will tell if the main character goes left or right
    bool flag = 0; 

    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

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

        // Moving to the left (main character)
        if (IsKeyDown(KEY_D)||(IsKeyDown(KEY_W)&&flag)||(IsKeyDown(KEY_S)&&flag)){
        
            framesCounter++;

            if (framesCounter >= 7.5)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 3) currentFrame = 0;

                frameRecD.x = (float)currentFrame*(float)docD.width/3; // dividir fotograma
            }
        }

        // Moving to the right (main character)
        if (IsKeyDown(KEY_A)||(IsKeyDown(KEY_W)&&!flag)||(IsKeyDown(KEY_S)&&!flag)){
        
            framesCounter++;

            if (framesCounter >= 7.5)
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 3) currentFrame = 0;

                frameRecA.x = (float)currentFrame*(float)docA.width/3; 
            }
        } 


        // Spining and squishing of bad dudes
        framesCounterC++;

        if (framesCounterC >= 7.5)
        {
            framesCounterC = 0;
            currentFrameC++;

            if (currentFrameC > 3) currentFrameC = 0;

            frameRecC.x = (float)currentFrameC*(float)covid.width/4;
        }

        framesCounterB++;

        if (framesCounterB >= 7.5)
        {
            framesCounterB = 0;
            currentFrameB++;

            if (currentFrameB > 3) currentFrameB = 0;

            frameRecB.x = (float)currentFrameB*(float)bac.width/5;
        }


        // Update the state
        state_update(lvl,sta);

        // Drawing
        BeginDrawing();

            ClearBackground(CLITERAL(Color){ 200, 203, 0, 255 });

            draw_state(lvl, sta, covid, bac, frameRecC, frameRecB, bullet);

            // Main character movement
            if (IsKeyDown(KEY_D)){
                DrawTextureRec(docD, frameRecD, positionD, WHITE);
                flag = 1;
            }

            if (IsKeyDown(KEY_A)){
                DrawTextureRec(docA, frameRecA, positionA, WHITE);
                flag = 0;
            }

            if((IsKeyDown(KEY_W)&&flag)||(IsKeyDown(KEY_S)&&flag)){
                DrawTextureRec(docD, frameRecD, positionD, WHITE);
            }

            if((IsKeyDown(KEY_W)&&!flag)||(IsKeyDown(KEY_S)&&!flag)){
                DrawTextureRec(docA, frameRecA, positionA, WHITE);
            }

            if (flag){
                DrawTextureRec(docD, frameRecD, positionD, WHITE);
            }

            else{
                DrawTextureRec(docA, frameRecA, positionA, WHITE);
            }


            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

        EndDrawing();

    }

    //Unload images
    UnloadTexture(docD);
    UnloadTexture(docA);
    UnloadTexture(covid);
    UnloadTexture(bac);

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
