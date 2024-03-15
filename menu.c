


Vector2 mousePoint = {};
Color buttonColor = (Color){0, 0, 0, 50};
Color noColor = (Color){0, 0, 0, 0};


Rectangle playButton = {1024/2 - 100, 800/2, 200, 50};


int menuScene(){
    
    mousePoint = GetMousePosition();
    
    
    Color bgColor = (Color){20, 20, 20, 255};
    ClearBackground(bgColor);
    
    
    if (CheckCollisionPointRec(mousePoint, playButton)) DrawRectangleRec(playButton, buttonColor);
    else DrawRectangleRec(playButton, noColor);
    


    DrawText("CATCH-CATCH", GetScreenWidth()/2 - 150, GetScreenHeight()/2 - 300, 40, WHITE);
    DrawText("PLAY", GetScreenWidth()/2 - 40, GetScreenHeight()/2 + 12, 30, BLUE);
    
    if (CheckCollisionPointRec(mousePoint, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;  
    
    
    return 0;
}