

#define MAX_BALLS 20

typedef struct ball{
    Vector2 position;
    bool health;
    int direction;
    int radius;
} Ball;

typedef struct {
    Ball ball[MAX_BALLS];  // an array to store all the enemies
    int numBalls;  // the current number of enemies
} BallManager;


void spawnBall(Ball *ball, int screenWidth, int screenHeight) {
    ball-> position.x = (float)GetRandomValue(0, screenWidth);
    ball-> position.y = 10;
    ball-> health = true;
    ball-> direction = 1;
    ball-> radius = 10;
}

void updateBall(BallManager *ballManager, float speed){
    
    Ball *ball = &ballManager->ball[0];
    
    ball-> position.y = ball-> position.y + 2.0f * ball-> direction * speed;
    


}


void ballCollision(BallManager *ballManager){
    
    Ball *ball = &ballManager->ball[0];
    if(ball-> position.y >= GetScreenHeight() - ball-> radius) ball-> direction *= -1;
    if(ball-> position.y <= ball-> radius) ball-> direction *= -1;
    
    
}