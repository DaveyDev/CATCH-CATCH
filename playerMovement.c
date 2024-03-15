

Vector2 newPosition(Vector2 player, Vector2 playerSize, float speed){
    Vector2 newPosition = { player.x, player.y };
    if (IsKeyDown(KEY_RIGHT) && player.x < GetScreenWidth() - playerSize.x) newPosition.x += 7.0f * speed;
    if (IsKeyDown(KEY_LEFT) && player.x > 0) newPosition.x -= 7.0f * speed;
    //if (IsKeyDown(KEY_UP) && player.y > 0) newPosition.y -= 2.0f;
    //if (IsKeyDown(KEY_DOWN) && player.y < GetScreenHeight() - playerSize.y) newPosition.y += 2.0f;
    return newPosition;
}
