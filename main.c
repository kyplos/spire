#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define CHUNK_SIZE 32
#define MAP_WIDTH 32
#define MAP_HEIGHT 32

typedef enum {
    TILE_EMPTY,
    TILE_PATH,
    TILE_TOWER_SPOT,
    TILE_CASTLE,
    TILE_SPAWN
} TileType;

typedef struct {
    int x, y;
    int pathIndex;
    int active;
} Enemy;

#define ENEMY_SPEED 2
#define MAX_ENEMIES 10
#define SPAWN_INTERVAL 30
Enemy enemies[MAX_ENEMIES];
int spawnTimer = 0;

TileType map[MAP_WIDTH][MAP_HEIGHT];

void GenerateMap() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            map[x][y] = TILE_EMPTY;
        }
    }

    int x = 0, y = 0;
    while (x < 31) {
        map[x][y] = TILE_PATH;
        x++;
    }
    while (y < 31) {
        map[x][y] = TILE_PATH;
        y++;
    }

    map[31][31] = TILE_CASTLE;
    map[0][0] = TILE_SPAWN;
}

void DrawMap() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            Color color = LIGHTGRAY;
            if (map[x][y] == TILE_PATH) color = DARKGRAY;
            else if (map[x][y] == TILE_TOWER_SPOT) color = GREEN;
            else if (map[x][y] == TILE_CASTLE) color = RED;
            else if (map[x][y] == TILE_SPAWN) color = BLUE;

            DrawRectangle(x * CHUNK_SIZE, y * CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE, color);
            DrawRectangleLines(x * CHUNK_SIZE, y * CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE, BLACK);
        }
    }
}

void SpawnEnemy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].x = 0;
            enemies[i].y = 0;
            enemies[i].pathIndex = 0;
            enemies[i].active = 1;
            break;
        }
    }
}

void UpdateEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            int x = enemies[i].x / CHUNK_SIZE;
            int y = enemies[i].y / CHUNK_SIZE;

            if (map[x][y] == TILE_CASTLE) {
                enemies[i].active = 0;
                continue;
            }

            int newX = enemies[i].x;
            int newY = enemies[i].y;
            if (x < 31) newX += ENEMY_SPEED;
            else if (y < 31) newY += ENEMY_SPEED;

            enemies[i].x = newX;
            enemies[i].y = newY;
        }
    }
}

void DrawEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            DrawCircle(enemies[i].x + CHUNK_SIZE / 2, enemies[i].y + CHUNK_SIZE / 2, CHUNK_SIZE / 3, BLACK);
        }
    }
}

int main() {
    InitWindow(1024, 1024, "Spire");
    SetTargetFPS(60);

    GenerateMap();
    for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].active = 0;
    }

    while (!WindowShouldClose()) {
        spawnTimer++;
        if (spawnTimer >= SPAWN_INTERVAL) {
            SpawnEnemy();
            spawnTimer = 0;
        }
        UpdateEnemies();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawMap();
        DrawEnemies();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
