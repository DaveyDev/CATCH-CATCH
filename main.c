#include "raylib.h"
#include "playerMovement.c"
#include "enemy.c"
#include "ball.c"
#include "menu.c"

int isMenuOn = 0;

int main(void){

    const int screenWidth = 1024;
    const int screenHeight = 800;
    
    bool collision = false;
    int score = 0;
    int bestScore = 0;

    InitAudioDevice();     
    Sound collectPoint  = LoadSound("resources/sound/collect.wav");
    Sound death = LoadSound("resources/sound/death.wav");
    
    


    Enemy enemy;
    EnemyManager manager = {0};
    
    Ball ball;
    BallManager ballManager = {0};
    
    
    InitWindow(screenWidth, screenHeight, "game");
    float speed = 1;
    SetTargetFPS(60); 
    
    Texture2D collectBall = LoadTexture("resources/sprite/redBall.png");
    Texture2D playerSprite = LoadTexture("resources/sprite/rectPlayer.png");

    //Vector2 player2 = {(float)screenWidth/4, (float)screenHeight/4 };
    Vector2 playerSize = {(float)128, (float)32};
    Vector2 player = {(float)screenWidth/2 - playerSize.x/2 , (float)screenHeight - 100 };
    
    
    //Vector2 enemy =
    

    float timer = 0.0f;
    
    spawnBall(&ballManager.ball[0], screenWidth, screenHeight);
    
    while (!WindowShouldClose()){
        
        
        if(isMenuOn == 1){
            timer += GetFrameTime();
             
        }        
        
        
        if(timer >= 2.0f){
            
            if(manager.numEnemies < MAX_ENEMIES){
                spawnEnemy(&manager.enemies[manager.numEnemies], screenWidth, screenHeight);
                
                manager.numEnemies++;
                speed = speed + 0.01;
                
            }
            timer -= 2.0f;
        }
        
       /* if (IsKeyPressed(KEY_SPACE)) {
        // kill a random enemy
            if (manager.numEnemies > 0) {
                int index = GetRandomValue(0, manager.numEnemies - 1);
                manager.enemies[index].health = 0;
            }
        } */
        
        
        player = newPosition(player, playerSize, speed);
        //player2 = newPosition(player2, playerSize);
        
        updateEnemies(&manager, speed);
        
        
        updateBall(&ballManager, speed); 
        ballCollision(&ballManager);
       
        
        for(int i = 0; i < manager.numEnemies; i++){
            Vector2 checkCircle = {manager.enemies[i].position.x, manager.enemies[i].position.y};
            Rectangle playerRect = { player.x, player.y, playerSize.x, playerSize.y};
            
            collision = CheckCollisionCircleRec(checkCircle, 10, playerRect);
            if(collision){
                manager.enemies[i].health = 0;
                PlaySound(collectPoint);
                score++;
                
            }
            if(manager.enemies[i].position.y >= screenHeight){ 
                if(score > bestScore) bestScore = score;
                PlaySound(death);
                score = 0;
                manager.enemies[i].health = 0;
                speed = 1;
                isMenuOn = 2;
            }
        
        }
        
        
        if(isMenuOn == 2){
                
             
              
        }
          
        BeginDrawing();


            if (isMenuOn == 0){
                isMenuOn = menuScene();

                
            }
            
            else if (isMenuOn == 1){
            Color bgColor = (Color){20, 20, 20, 255};
            
            ClearBackground(bgColor);



            int countFPS = GetFPS();
            DrawText(TextFormat("FPS: %i", countFPS), screenWidth - 100, 15, 20, BLUE);
            //DrawText(TextFormat("x: %f", player.x), 200, 15, 20, BLUE);
            //DrawText(TextFormat("y: %f", player.y), 200, 35, 20, BLUE);
            DrawText(TextFormat("SCORE: %i", score), 20, 15, 20, BLUE);
            DrawText(TextFormat("BEST: %i", bestScore), 32, 35, 20, BLUE);
            DrawText(TextFormat("ver: 04-04-23", bestScore), screenWidth - 200, screenHeight - 50, 20, BLUE);
            //DrawCircle(enemy.position.x, enemy.position.y, 10, MAROON);
            
            for (int i = 0; i < manager.numEnemies; i++) {
                DrawTexture(collectBall, manager.enemies[i].position.x - 16 , manager.enemies[i].position.y - 16, WHITE);
                //DrawCircle(manager.enemies[i].position.x, manager.enemies[i].position.y, manager.enemies[i].size, RED);
            }
            
           // DrawCircle(ballManager.ball[0].position.x, ballManager.ball[0].position.y, ballManager.ball[0].radius, WHITE);

            DrawTextureV(playerSprite, player, WHITE);
            //DrawRectangleV(player, playerSize, RED);
            //DrawRectangleV(player2, playerSize, BLUE);
            //DrawRectangleV()
            }
            else if(isMenuOn == 2){
                
                for(int i = 0; i < manager.numEnemies; i++){
       
                    manager.enemies[i].health = 0;
                    updateEnemies(&manager, speed);                                       
                }

                Color bgColor = (Color){20, 20, 20, 255};
                ClearBackground(bgColor);
                
                Color buttonColor = (Color){255, 255, 255, 50};
                Color noColor = (Color){0, 0, 0, 0};
                
                DrawText(TextFormat("BEST SCORE:", bestScore), screenWidth/2 - 150, 300, 50, BLUE);
                
                int scoreX = screenWidth/2 - 10;
                if(bestScore > 9) scoreX - 25;
                if(bestScore > 99) scoreX - 25;
                
                DrawText(TextFormat("%i", bestScore), scoreX, 350, 50, BLUE);
                DrawText(TextFormat("AGAIN"), screenWidth/2 - 50, 500, 35, BLUE);
                Rectangle playButton = {1024/2 - 100, 800/2 + 90, 200, 50};
                mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
                if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) isMenuOn = 1;
 
            }
        EndDrawing();
        
        
    }
    
    UnloadTexture(collectBall);

    CloseWindow();



    return 0;
}