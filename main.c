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

TileType map[MAP_WIDTH][MAP_HEIGHT];


int main() {
    InitWindow(1024, 1024, "Spire");
    SetTargetFPS(60);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
}
