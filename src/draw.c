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

void draw_state(const level *lvl, const state *sta, const Texture2D covid, Texture2D bac, Rectangle frameRecC, Rectangle frameRecB, Texture2D bullet){

    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player it's in the middle of the screen
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
    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;

        // Initialize a Vector2 that represents the center of the entity Texture position
        Vector2 vecC = {ent.x-BRUTE_RAD,ent.y-BRUTE_RAD};
        Vector2 vecB = {ent.x-MINION_RAD*0.44,ent.y-MINION_RAD};

        // Draw textures
        if(sta->enemies[i].kind == MINION){
                DrawTextureRec(bac, frameRecB, vecB, WHITE);
                }

            else{
                //DrawTextureV(covid, vecC, WHITE);
                DrawTextureRec(covid, frameRecC, vecC, WHITE);
            }
        
    }

    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        //Vector2 vec = {ent.x,ent.y};
        // Initialize a Vector2 that represents the center of the entity Texture position
        Vector2 vecB = {ent.x-BULLET_RAD*1.6,ent.y-BULLET_RAD};
        // Draw a circle with the radius of the entity
        DrawTextureV(bullet, vecB, WHITE);
        //DrawCircleV(vec,ent.rad,PINK);
    }

    

    // Stop drawing relative to the camera
    EndMode2D();
}
