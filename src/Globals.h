#pragma once
#include "DonutAPI.h"

// Map and Screen varibles

namespace Window 
{
    const int WIDTH = 210;
    const int HEIGHT = 100;
    const int FONT_W = 8;
    const int FONT_H = 8;

    const int MAP_WIDTH = 24;
    const int MAP_HEIGHT = 24;
    const int CELL_SIZE = 20;

    const int FOV = 80;
    const int RENDER_DISTANCE = 250;
    const int VERTICAL_SCALE = HEIGHT * 50;
    const float LOOK_SPEED = 3.0f;
    const float MAX_LOOK = (float)(HEIGHT / 2 - 10);
    const double RAY_STEP = 0.1;
    const float ROTATION_SPEED = 1.0f;
    const float MOVEMENT_SPEED = 1.0f;
    const float MARGIN = 5.0f;
    const float STEP_HEIGHT = 0.55f;

    const int SECTORS = 8;
    const int MAX_TEX = 22;
}

struct SectorDef
{
    float floorH;
    float ceilH;
    float floorSlopeX;
    float floorSlopeY;
    float ceilSlopeX;
    float ceilSlopeY;
    int floorTexId;
    int ceilTexId;
};

struct Ray
{
    double distance;
    int wallType;
    float wallX;
    float worldX;
    float worldY;
    int cellX;
    int cellY;
    int sectorId;
};

extern SectorDef sectors[Window::SECTORS];
extern int map[24][24];
extern int sectorMap[24][24];

struct TextureSet
{
    const Texture* tex[Window::MAX_TEX];
};

// Textures
void brickTile(Texture& tex);
void blackBrickTile(Texture& tex);
void stoneTile(Texture& tex);
void blackStoneTile(Texture& tex);
void cobbleStoneTile(Texture& tex);
void woodTile(Texture& tex);
void woodenBeamTile(Texture& tex);
void glassTile(Texture& tex);
void rGlassTile(Texture& tex);
void gGlassTile(Texture& tex);
void bGlassTile(Texture& tex);
void bannerTile(Texture& tex);
void grassTile(Texture& tex);
void gravelTile(Texture& tex);
void carpetTile(Texture& tex);
void rCarpetTile(Texture& tex);
void bCarpetTile(Texture& tex);
void wSlopeTile(Texture& tex);
void bSlopeTile(Texture& tex);
void dgSlopeTile(Texture& tex);
void gSlopeTile(Texture& tex);

// Raycasting
int getSectorAt(int cellX, int cellY);
int getPlayerSector();
float getFloorH(int sectorId, float wx, float wy);
float getCeilH(int sectorId, float wx, float wy);
void input();
void drawBackground(const TextureSet& texSet, int floorID);  
void drawFOV(const TextureSet& texSet, int slopeID, int extWallID);