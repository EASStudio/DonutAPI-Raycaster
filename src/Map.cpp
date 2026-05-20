#include "DonutMath.h"
#include "Globals.h"

int map[Window::MAP_HEIGHT][Window::MAP_WIDTH] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,4,0,3,0,4,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,4,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,4,0,3,0,4,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,7,2,4,2,4,2,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,4,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,4,2,2,4,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,7,2,2,2,2,4,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

SectorDef sectors[Window::SECTORS] =
{
    { 0.00f, 1.00f,  0.00f, 0.00f,  0.00f, 0.00f,  5, 0 },
    { 0.20f, 1.00f,  0.00f, 0.00f,  0.00f, 0.00f,  5, 0 },
    { 0.40f, 1.00f,  0.00f, 0.00f,  0.00f, 0.00f,  6, 0 },
    { 0.00f, 1.00f,  0.40f, 0.00f,  0.00f, 0.00f,  6, 0 },
    { 0.00f, 1.00f,  0.00f, 0.40f,  0.00f, 0.00f,  6, 0 },
    { 0.00f, 0.55f,  0.00f, 0.00f,  0.00f, 0.00f,  6, 7 },
    { 0.00f, 1.00f,  0.20f, 0.20f,  0.00f, 0.00f,  5, 0 },
    { 0.50f, 1.00f,  0.00f, 0.00f,  0.00f, 0.00f,  1, 0 },
};

/*
Sector:
0 = No sector
1 = Slope sector
2 = Mini block sector 
3 = Stair sector
4 = Small stair floor sector
5 = Top wall Sector
7 = Tall stair sector
*/

int sectorMap[Window::MAP_HEIGHT][Window::MAP_WIDTH] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,3,3,3,3,3,3,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,5,5,1,1,3,3,3,3,3,3,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,1,1,5,5,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

struct Player
{
    float x;
    float y;
    float lookY;
    float angle;
};
Player player = { 172.0f, 182.0f, 0.0f, 80.0f }; 

int getSectorAt(int cellX, int cellY)
{
    if (cellX < 0 || cellX >= Window::MAP_WIDTH || cellY < 0 || cellY >= Window::MAP_HEIGHT) return 0;
    return sectorMap[cellY][cellX];
}

int getPlayerSector()
{
    return getSectorAt((int)(player.x / Window::CELL_SIZE), (int)(player.y / Window::CELL_SIZE));
}

float getFloorH(int secId, float wx, float wy)
{
    if (secId < 0 || secId >= Window::SECTORS) return 0.0f;
    const SectorDef& s = sectors[secId];
    float cx = fmodf(wx, (float)Window::CELL_SIZE) / Window::CELL_SIZE; if (cx < 0.f) cx += 1.f;
    float cy = fmodf(wy, (float)Window::CELL_SIZE) / Window::CELL_SIZE; if (cy < 0.f) cy += 1.f;
    return s.floorH + s.floorSlopeX * cx + s.floorSlopeY * cy;
}

float getCeilH(int secId, float wx, float wy)
{
    if (secId < 0 || secId >= Window::SECTORS) return 1.0f;
    const SectorDef& s = sectors[secId];
    float cx = fmodf(wx, (float)Window::CELL_SIZE) / Window::CELL_SIZE; if (cx < 0.f) cx += 1.f;
    float cy = fmodf(wy, (float)Window::CELL_SIZE) / Window::CELL_SIZE; if (cy < 0.f) cy += 1.f;
    return s.ceilH + s.ceilSlopeX * cx + s.ceilSlopeY * cy;
}

static float getFloorHCentre(int sec, int cx, int cy)
{
    return getFloorH(sec, (cx + 0.5f) * Window::CELL_SIZE, (cy + 0.5f) * Window::CELL_SIZE);
}

static float getCeilHCentre(int sec, int cx, int cy)
{
    return getCeilH(sec, (cx + 0.5f) * Window::CELL_SIZE, (cy + 0.5f) * Window::CELL_SIZE);
}

inline int projectY(float worldH, double dist, float eyeH)
{
    if (dist <= 0.0) return 0;
    return (int)(Window::HEIGHT / 2.0 + player.lookY + (eyeH - worldH) * ((double)Window::VERTICAL_SCALE / dist));
}

Ray castRay(double angle)
{
    double rad = angle * DEG2RAD;
    double rayX = player.x;
    double rayY = player.y;
    int lastOpenCX = (int)(player.x / Window::CELL_SIZE);
    int lastOpenCY = (int)(player.y / Window::CELL_SIZE);

    while (true)
    {
        rayX += cos(rad) * Window::RAY_STEP; rayY += sin(rad) * Window::RAY_STEP;
        double dist = sqrt((rayX - player.x) * (rayX - player.x) + (rayY - player.y) * (rayY - player.y));

        if (dist > Window::RENDER_DISTANCE)
            return { (double)Window::RENDER_DISTANCE, 0, 0.f, (float)rayX, (float)rayY, 0, 0, getSectorAt(lastOpenCX, lastOpenCY) };

        int cellX = (int)rayX / Window::CELL_SIZE, cellY = (int)rayY / Window::CELL_SIZE;

        if (cellX < 0 || cellX >= Window::MAP_WIDTH || cellY < 0 || cellY >= Window::MAP_HEIGHT)
            return { (double)Window::RENDER_DISTANCE, 0, 0.f, (float)rayX, (float)rayY, cellX, cellY, getSectorAt(lastOpenCX, lastOpenCY) };

        int cell = map[cellY][cellX];

        if (cell == 0) 
        { 
            lastOpenCX = cellX; 
            lastOpenCY = cellY;
        }

        else
        {
            float fx = fmod((float)rayX, (float)Window::CELL_SIZE) / Window::CELL_SIZE;
            float fy = fmod((float)rayY, (float)Window::CELL_SIZE) / Window::CELL_SIZE;
            float wallX = (fabs(fx - 0.5f) > fabs(fy - 0.5f)) ? fy : fx;
            return { dist, cell, wallX, (float)rayX, (float)rayY, cellX, cellY, getSectorAt(lastOpenCX, lastOpenCY) };
        }
    }
    return { (double)Window::RENDER_DISTANCE, 0, 0.f, 0.f, 0.f, 0, 0, 0 };
}

bool isWall(float x, float y)
{
    int cx = (int)x / Window::CELL_SIZE, cy = (int)y / Window::CELL_SIZE;
    if (cx < 0 || cx >= Window::MAP_WIDTH || cy < 0 || cy >= Window::MAP_HEIGHT) return true;
    return map[cy][cx] != 0;
}

static void drawVStrip(int screenX, int yTop, int yBottom, float texU, const Texture& tex)
{
    int totalPx = yBottom - yTop;

    if (totalPx <= 0) return;

    int dt = (yTop < 0) ? 0 : yTop;
    int db = (yBottom >= Window::HEIGHT) ? Window::HEIGHT - 1 : yBottom;

    for (int y = dt; y <= db; y++)
    {
        float v = (float)(y - yTop) / (float)totalPx;
        unsigned short col = SampleTexture(tex, texU, v);
        if (col != 0) DrawPixel(screenX, y, PIXEL_SOLID, col);
    }
}

void drawBackground(const TextureSet& texSet, int floorID)
{
    int pSec = getPlayerSector();
    float eyeH = getFloorH(pSec, player.x, player.y) + 0.5f;

    float leftAngle = (player.angle - Window::FOV / 2.0f) * (float)DEG2RAD;
    float rightAngle = (player.angle + Window::FOV / 2.0f) * (float)DEG2RAD;
    float rdX0 = cosf(leftAngle), rdY0 = sinf(leftAngle);
    float rdX1 = cosf(rightAngle), rdY1 = sinf(rightAngle);

    for (int y = 0; y < Window::HEIGHT; y++)
    {
        float dy = (float)y - (Window::HEIGHT / 2.0f + player.lookY);
        if (fabsf(dy) < 0.5f) continue;

        bool  isFloor = (dy > 0.0f);
        float eyeOffset = isFloor ? eyeH : (1.0f - eyeH);
        if (eyeOffset <= 0.0f) continue;

        float rowDist = eyeOffset * (float)Window::VERTICAL_SCALE / fabsf(dy);

        float wx = player.x + rowDist * rdX0;
        float wy = player.y + rowDist * rdY0;
        float sx = rowDist * (rdX1 - rdX0) / (float)Window::WIDTH;
        float sy = rowDist * (rdY1 - rdY0) / (float)Window::WIDTH;

        for (int x = 0; x < Window::WIDTH; x++, wx += sx, wy += sy)
        {
            int sec = getSectorAt((int)(wx / Window::CELL_SIZE), (int)(wy / Window::CELL_SIZE));

            float fh = isFloor ? getFloorH(sec, wx, wy) : getCeilH(sec, wx, wy);
            float actualOffset = isFloor ? (eyeH - fh) : (fh - eyeH);
            if (actualOffset <= 0.0f) continue;

            float corrDist = actualOffset * (float)Window::VERTICAL_SCALE / fabsf(dy);
            float scale = corrDist / rowDist;  

            float wxS = player.x + (wx - player.x) * scale;
            float wyS = player.y + (wy - player.y) * scale;

            int secS = getSectorAt((int)(wxS / Window::CELL_SIZE), (int)(wyS / Window::CELL_SIZE));
            float u = fmodf(wxS / Window::CELL_SIZE, 1.0f); if (u < 0.f) u += 1.f;
            float v = fmodf(wyS / Window::CELL_SIZE, 1.0f); if (v < 0.f) v += 1.f;

            int texId = isFloor ? sectors[secS].floorTexId : sectors[secS].ceilTexId;
            if (texId > 0 && texId < Window::MAX_TEX && texSet.tex[texId])
                DrawPixel(x, y, PIXEL_SOLID, SampleTexture(*texSet.tex[floorID], u, v));  // texID
            else
                DrawPixel(x, y, isFloor ? PIXEL_QUARTER : PIXEL_SOLID, isFloor ? DARK_GREEN : DARK_BLUE);
        }
    }
}

// TODO: Add colosion to wall sectors
// TODO: Fix fisheye effect
void drawFOV(const TextureSet& texSet, int slopeID, int extWallID)
{
    int pSec = getPlayerSector();
    float eyeH = getFloorH(pSec, player.x, player.y) + 0.5f;

    const Texture* riserTex = texSet.tex[slopeID];   // slope texture

    for (int x = 0; x < Window::WIDTH; x++)
    {
        double angle = (player.angle - Window::FOV / 2.0) + ((double)x / (double)Window::WIDTH) * Window::FOV;
        double rayDirX = cos(angle * DEG2RAD);
        double rayDirY = sin(angle * DEG2RAD);

        double rayPosX = player.x / (double)Window::CELL_SIZE;
        double rayPosY = player.y / (double)Window::CELL_SIZE;
        int mapX = (int)rayPosX, mapY = (int)rayPosY;

        double deltaDistX = (fabs(rayDirX) < 1e-20) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (fabs(rayDirY) < 1e-20) ? 1e30 : fabs(1.0 / rayDirY);
        double sideDistX;
        double sideDistY;
        int stepX;
        int stepY;

        if (rayDirX < 0) 
        { 
            stepX = -1; 
            sideDistX = (rayPosX - mapX) * deltaDistX;
        }

        else 
        { 
            stepX = 1; 
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
        }

        if (rayDirY < 0) 
        { 
            stepY = -1; 
            sideDistY = (rayPosY - mapY) * deltaDistY;
        }

        else 
        { 
            stepY = 1; 
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY; 
        }

        for (int ddaStep = 0; ddaStep < 200; ddaStep++)
        {
            int side;
            if (sideDistX < sideDistY) 
            { 
                sideDistX += deltaDistX; 
                mapX += stepX;
                side = 0;
            }

            else 
            { 
                sideDistY += deltaDistY; 
                mapY += stepY;
                side = 1; 
            }

            if (mapX < 0 || mapX >= Window::MAP_WIDTH || mapY < 0 || mapY >= Window::MAP_HEIGHT) break;

            double perpDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
            double worldDist = perpDist * Window::CELL_SIZE;
            if (worldDist < 0.5) worldDist = 0.5;

            float hitX, hitY;
            if (side == 0) 
            {
                hitX = (float)((double)mapX * Window::CELL_SIZE);
                hitY = (float)((rayPosY + perpDist * rayDirY) * Window::CELL_SIZE);
            }

            else
            {
                hitX = (float)((rayPosX + perpDist * rayDirX) * Window::CELL_SIZE);
                hitY = (float)((double)mapY * Window::CELL_SIZE);
            }

            int prevCX = mapX - (side == 0 ? stepX : 0);
            int prevCY = mapY - (side == 1 ? stepY : 0);
            int prevSec = getSectorAt(prevCX, prevCY);
            int curSec = getSectorAt(mapX, mapY);

            float texU = (side == 0) ? fmodf(hitY / (float)Window::CELL_SIZE, 1.0f)
                : fmodf(hitX / (float)Window::CELL_SIZE, 1.0f);

            if (texU < 0.0f) texU += 1.0f;

            if (map[mapY][mapX] != 0)
            {
                float wallFloorH = getFloorH(prevSec, hitX, hitY);
                float wallCeilH = getCeilH(prevSec, hitX, hitY);
                int yBottom = projectY(wallFloorH, worldDist, eyeH);
                int yTop = projectY(wallCeilH, worldDist, eyeH);

                int wallTexId = map[mapY][mapX]; // texture from wall map, NOT sectorMap
                if (wallTexId > 0 && wallTexId < Window::MAX_TEX && texSet.tex[wallTexId])
                    drawVStrip(x, yTop, yBottom, texU, *texSet.tex[wallTexId]);
                else
                {
                    int dt = (yTop < 0) ? 0 : yTop;
                    int db = (yBottom >= Window::HEIGHT) ? Window::HEIGHT - 1 : yBottom;
                    for (int y = dt; y <= db; y++) DrawPixel(x, y, PIXEL_SOLID, DARK_GRAY);
                }
                break;
            }

            float oldFloorH = getFloorHCentre(prevSec, prevCX, prevCY);
            float newFloorH = getFloorHCentre(curSec, mapX, mapY);
            float oldCeilH = getCeilHCentre(prevSec, prevCX, prevCY);
            float newCeilH = getCeilHCentre(curSec, mapX, mapY);

            const float T = 0.02f;

            if (newFloorH > oldFloorH + T && riserTex)
                drawVStrip(x, projectY(newFloorH, worldDist, eyeH),
                    projectY(oldFloorH, worldDist, eyeH), texU, *riserTex);

            if (newFloorH < oldFloorH - T && riserTex)
                drawVStrip(x, projectY(oldFloorH, worldDist, eyeH),
                    projectY(newFloorH, worldDist, eyeH), texU, *riserTex);

            if (newCeilH < oldCeilH - T)
            {
                int cTexId = sectors[curSec].ceilTexId;
                const Texture* cTex = (cTexId > 0 && cTexId < Window::MAX_TEX) ? texSet.tex[cTexId]
                    : texSet.tex[7];
                if (cTex)
                    drawVStrip(x, projectY(oldCeilH, worldDist, eyeH),
                        projectY(newCeilH, worldDist, eyeH), texU, *cTex);
            }

            if (newCeilH > oldCeilH + T && texSet.tex[extWallID])         // Sets a texture to higher level walls in sectors 
                drawVStrip(x, projectY(newCeilH, worldDist, eyeH),
                    projectY(oldCeilH, worldDist, eyeH), texU, *texSet.tex[extWallID]);
        }
    }
}

static bool canMoveTo(float nx, float ny)
{
    if (isWall(nx + Window::MARGIN, ny) || isWall(nx - Window::MARGIN, ny)) return false;
    if (isWall(nx, ny + Window::MARGIN) || isWall(nx, ny - Window::MARGIN)) return false;
    int curSec = getPlayerSector();
    int newSec = getSectorAt((int)(nx / Window::CELL_SIZE), (int)(ny / Window::CELL_SIZE));
    return (getFloorH(newSec, nx, ny) - getFloorH(curSec, player.x, player.y)) <= Window::STEP_HEIGHT;
}

void input()
{

    if (GetKey(KEY_UP).k_Held) player.lookY += Window::LOOK_SPEED;  // look up
    if (GetKey(KEY_DOWN).k_Held) player.lookY -= Window::LOOK_SPEED;  // look down
    player.lookY = fmaxf(-Window::MAX_LOOK, fminf(Window::MAX_LOOK, player.lookY));

    if (GetKey(KEY_A).k_Held)  player.angle -= Window::ROTATION_SPEED;
    if (GetKey(KEY_D).k_Held) player.angle += Window::ROTATION_SPEED;

    if (GetKey(KEY_W).k_Held)
    {
        float nx = player.x + cosf(player.angle * (float)DEG2RAD) * Window::MOVEMENT_SPEED;
        float ny = player.y + sinf(player.angle * (float)DEG2RAD) * Window::MOVEMENT_SPEED;
        if (canMoveTo(nx, player.y)) player.x = nx;
        if (canMoveTo(player.x, ny)) player.y = ny;
    }

    if (GetKey(KEY_S).k_Held)
    {
        float nx = player.x - cosf(player.angle * (float)DEG2RAD) * Window::MOVEMENT_SPEED;
        float ny = player.y - sinf(player.angle * (float)DEG2RAD) * Window::MOVEMENT_SPEED;
        if (canMoveTo(nx, player.y)) player.x = nx;
        if (canMoveTo(player.x, ny)) player.y = ny;
    }
}