
#define MAX_ENEMIES 10  // define the maximum number of enemies

typedef struct enemy {
    Vector2 position;
    int health;
    int size;
} Enemy;
    
typedef struct {
    Enemy enemies[MAX_ENEMIES];  // an array to store all the enemies
    int numEnemies;  // the current number of enemies
} EnemyManager;

void spawnEnemy(Enemy *enemy, int screenWidth, int screenHeight) {
    enemy->position.x = (float)GetRandomValue(10, screenWidth - 10);
    enemy->position.y = 16;
    enemy->health = 100;
    enemy->size = 16;
}

void despawnEnemy(EnemyManager *manager, Enemy *enemy) {
    // Find the index of the enemy in the array
    int index = -1;
    for (int i = 0; i < manager->numEnemies; i++) {
        if (&manager->enemies[i] == enemy) {
            index = i;
            break;
        }
    }
    
    // Shift the elements after the removed enemy to fill the gap
    if (index != -1) {
        for (int i = index + 1; i < manager->numEnemies; i++) {
            manager->enemies[i - 1] = manager->enemies[i];
        }
        
        // Decrement the number of enemies
        manager->numEnemies--;
    }
}
void updateEnemies(EnemyManager *manager, float speed) {
    for (int i = 0; i < manager->numEnemies; i++) {
        Enemy *enemy = &manager->enemies[i];
        
       
        if (enemy-> health > 0){
            // Makes enemy fall
            enemy-> position.y += 2.0f * speed;
        } 

        //if(enemy-> position.y > GetScreenHeight()){
        //        enemy-> health = 0;
        //}
        
        // Check if the enemy's health has reached 0
        if (enemy-> health <= 0) {
            // Despawn the enemy
            despawnEnemy(manager, enemy);
        }
        
    }
}


