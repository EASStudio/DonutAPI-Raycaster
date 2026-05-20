#include "Game.h"
#include "Globals.h"

#include <fstream>

void Game::Shutdown()
{
    appIsRunning = false;
    exit(0);           
}

void Game::Run()
{
    appIsRunning = true;
    Init();
}

void Game::DrawSlopeDir(int screenX, int screenY, int sec, int cellW, int cellH)
{
    if (sec <= 0) return;

    float sx = editor.editCeil ? sectors[sec].ceilSlopeX : sectors[sec].floorSlopeX;
    float sy = editor.editCeil ? sectors[sec].ceilSlopeY : sectors[sec].floorSlopeY;

    if (abs(sx) < 0.01f && abs(sy) < 0.01f) return;

    int cx = screenX + cellW / 2;
    int cy = screenY + cellH / 2;

    DrawLine(cx, cy, cx + (int)(sx * 20), cy + (int)(sy * 20), PIXEL_SOLID, editor.editCeil ? RED : CYAN);
}

void Game::DrawEditor()
{
    const int BASE_CELL = 4;
    int cellW = std::max(2, (int)(BASE_CELL * editor.zoom));
    int cellH = cellW;  // Square cells look better in the editor

    // How many cells fit on screen at current zoom
    int visX = Window::WIDTH / cellW + 1;
    int visY = Window::HEIGHT / cellH + 1;
   
    // Clamp scroll so we don't go past the map
    editor.viewOffsetX = std::clamp(editor.viewOffsetX, 0, std::max(0, Window::MAP_WIDTH - visX));
    editor.viewOffsetY = std::clamp(editor.viewOffsetY, 0, std::max(0, Window::MAP_HEIGHT - visY));

    for (int y = editor.viewOffsetY; y < Window::MAP_HEIGHT && y < editor.viewOffsetY + visY; y++)
    {
        for (int x = editor.viewOffsetX; x < Window::MAP_WIDTH && x < editor.viewOffsetX + visX; x++)
        {
            int sx = (x - editor.viewOffsetX) * cellW;
            int sy = (y - editor.viewOffsetY) * cellH;

            int tile = map[y][x];
            int sec = sectorMap[y][x];
            unsigned short color = DARK_GRAY;

            if (tile > 0) color = (tile % 2 == 0) ? RED : DARK_RED;
            if (sec > 0) color += (sec * 2);

            DrawRectangle(sx, sy, cellW - 1, PIXEL_SOLID, color);

            if (sec > 0) DrawSlopeDir(sx, sy, sec, cellW, cellH);
        }
    }

    // Cursor — only draw if on screen
    bool cursorVisible =
        editor.postionX >= editor.viewOffsetX && editor.postionX < editor.viewOffsetX + visX &&
        editor.postionY >= editor.viewOffsetY && editor.postionY < editor.viewOffsetY + visY;

    if (cursorVisible)
    {
        int sx = (editor.postionX - editor.viewOffsetX) * cellW;
        int sy = (editor.postionY - editor.viewOffsetY) * cellH;
        DrawRectangle(sx, sy, cellW, PIXEL_SOLID, WHITE);
    }

    // UI
    std::wstring modeNames[] = { L"TILE", L"SECTOR", L"SLOPE", L"HEIGHT", L"PORTAL" };
    DrawString(2, 2, L"MODE: " + modeNames[editor.state], CYAN);
    DrawString(2, 12, L"EDITING: " + std::wstring(editor.editCeil ? L"CEILING" : L"FLOOR"), editor.editCeil ? RED : GREEN);
    DrawString(2, 22, L"Tile: " + std::to_wstring(editor.selectedTile), WHITE);
    DrawString(2, 32, L"Sec: " + std::to_wstring(editor.selectedSector), WHITE);
    DrawString(2, 42, L"Zoom: " + std::to_wstring((int)(editor.zoom * 100)) + L"%", WHITE);
    DrawString(2, 52, L"View: (" + std::to_wstring(editor.viewOffsetX) + L"," + std::to_wstring(editor.viewOffsetY) + L")", GRAY);

    int curSec = sectorMap[editor.postionY][editor.postionX];
    if (curSec > 0)
    {
        DrawString(2, 65, L"H: " + std::to_wstring(editor.editCeil ? sectors[curSec].ceilH : sectors[curSec].floorH), YELLOW);
        DrawString(2, 75, L"SX: " + std::to_wstring(editor.editCeil ? sectors[curSec].ceilSlopeX : sectors[curSec].floorSlopeX), YELLOW);
        DrawString(2, 85, L"SY: " + std::to_wstring(editor.editCeil ? sectors[curSec].ceilSlopeY : sectors[curSec].floorSlopeY), YELLOW);
    }

    DrawString(2, Window::HEIGHT / 2, L"[WASD] Move  [+/-] Zoom  [TAB] Game  [P] Pick current tile  [F] Ceil/Floor  [E] Tile cycle  [Q] Sector  [Space] Apply  [V] Save", GRAY);
}

void Game::EditorInput()
{
    // Zoom
    if (GetKey(KEY_EQUAL).k_Pressed) editor.zoom = std::clamp(editor.zoom + 0.25f, 0.5f, 4.0f);
    if (GetKey(KEY_MINUS).k_Pressed)  editor.zoom = std::clamp(editor.zoom - 0.25f, 0.5f, 4.0f);

    if (GetKey(KEY_W).k_Pressed) editor.postionY--;
    if (GetKey(KEY_S).k_Pressed) editor.postionY++;
    if (GetKey(KEY_A).k_Pressed) editor.postionX--;
    if (GetKey(KEY_D).k_Pressed) editor.postionX++;

    editor.postionX = std::clamp(editor.postionX, 0, Window::MAP_WIDTH - 1);
    editor.postionY = std::clamp(editor.postionY, 0, Window::MAP_HEIGHT - 1);

    // Auto-scroll: keep cursor inside visible area 
    const int BASE_CELL = 8;
    int cellW = std::max(2, (int)(BASE_CELL * editor.zoom));
    int visX = Window::WIDTH / cellW;
    int visY = Window::HEIGHT / cellW;

    if (editor.postionX < editor.viewOffsetX)              editor.viewOffsetX = editor.postionX;
    if (editor.postionX >= editor.viewOffsetX + visX - 1)  editor.viewOffsetX = editor.postionX - visX + 2;
    if (editor.postionY < editor.viewOffsetY)              editor.viewOffsetY = editor.postionY;
    if (editor.postionY >= editor.viewOffsetY + visY - 1)  editor.viewOffsetY = editor.postionY - visY + 2;
    // Title under cursor
    if (GetKey(KEY_P).k_Pressed) 
    {
        editor.selectedTile = map[editor.postionY][editor.postionX];
        int s = sectorMap[editor.postionY][editor.postionX];
        if (s > 0) editor.selectedSector = s;
    }

    // Quick Save
    if (GetKey(KEY_V).k_Pressed) SaveMap();

    // State Selection
    if (GetKey(KEY_1).k_Pressed) editor.state = TILE;
    if (GetKey(KEY_2).k_Pressed) editor.state = SECTOR;
    if (GetKey(KEY_3).k_Pressed) editor.state = SLOPE;
    if (GetKey(KEY_4).k_Pressed) editor.state = WALL_HEIGHT;

    if (GetKey(KEY_F).k_Pressed) editor.editCeil = !editor.editCeil;

    // Cycle selection
    if (GetKey(KEY_E).k_Pressed) editor.selectedTile = (editor.selectedTile + 1) % Window::MAX_TEX;
    if (GetKey(KEY_Q).k_Pressed) editor.selectedSector = (editor.selectedSector + 1) % Window::SECTORS;

    int sec = sectorMap[editor.postionY][editor.postionX];
    float delta = 0.05f;

    // Apply / Adjust (Space for +, X for -)
    bool up = GetKey(KEY_SPACE).k_Held || GetKey(KEY_SPACE).k_Pressed;
    bool down = GetKey(KEY_X).k_Held || GetKey(KEY_X).k_Pressed;

    if (up || down)
    {
        float mod = up ? delta : -delta;

        switch (editor.state)
        {
        case TILE:
            if (up) map[editor.postionY][editor.postionX] = editor.selectedTile;
            if (down) map[editor.postionY][editor.postionX] = 0;
            break;

        case SECTOR:
            if (up) sectorMap[editor.postionY][editor.postionX] = editor.selectedSector;
            if (down) sectorMap[editor.postionY][editor.postionX] = 0;
            break;

        case WALL_HEIGHT:
            if (sec > 0) 
            {
                if (editor.editCeil) sectors[sec].ceilH += mod;
                else sectors[sec].floorH += mod;
            }
            break;

        case SLOPE:
            if (sec > 0) 
            {
                // Use Arrow Keys for Slope Direction while holding Space/X
                if (GetKey(KEY_LEFT).k_Held || GetKey(KEY_RIGHT).k_Held) {
                    float sMod = GetKey(KEY_RIGHT).k_Held ? delta : -delta;
                    if (editor.editCeil) sectors[sec].ceilSlopeX += sMod;
                    else sectors[sec].floorSlopeX += sMod;
                }
                if (GetKey(KEY_UP).k_Held || GetKey(KEY_DOWN).k_Held) {
                    float sMod = GetKey(KEY_UP).k_Held ? -delta : delta;
                    if (editor.editCeil) sectors[sec].ceilSlopeY += sMod;
                    else sectors[sec].floorSlopeY += sMod;
                }
            }
            break;
        }
    }

    if (GetKey(KEY_TAB).k_Pressed) editor.enabled = false;
}

void Game::SaveMap() 
{
    std::ofstream f("map.txt");

    f << "Tiles\n";
    // Tiles
    for (int y = 0; y < Window::MAP_HEIGHT; y++)
    {
        for (int x = 0; x < Window::MAP_WIDTH; x++)
            f << map[y][x] << " ";
        f << "\n";
    }

    f << "Sectors per tile\n";

    // Sectors per tile
    for (int y = 0; y < Window::MAP_HEIGHT; y++)
    {
        for (int x = 0; x < Window::MAP_WIDTH; x++)
            f << sectorMap[y][x] << " ";
        f << "\n";
    }

    f << "Sector definitions\n";

    // Sector definitions
    for (int i = 0; i < Window::SECTORS; i++)
    {
        auto& s = sectors[i];
        f << s.floorH << " " << s.ceilH << " "
            << s.floorSlopeX << " " << s.floorSlopeY << " "
            << s.ceilSlopeX << " " << s.ceilSlopeY << "\n";
    }
}

void Game::LoadMap()
{
    std::ifstream f("map.txt");
    if (!f.is_open()) return;

    std::string line;
    // Skip header "Tiles"
    std::getline(f, line);
    for (int y = 0; y < Window::MAP_HEIGHT; y++)
        for (int x = 0; x < Window::MAP_WIDTH; x++)
            f >> map[y][x];

    // Skip header "Sectors per tile"
    std::getline(f, line); std::getline(f, line);
    for (int y = 0; y < Window::MAP_HEIGHT; y++)
        for (int x = 0; x < Window::MAP_WIDTH; x++)
            f >> sectorMap[y][x];

    // Skip header "Sector definitions"
    std::getline(f, line); std::getline(f, line);
    for (int i = 0; i < Window::SECTORS; i++) {
        f >> sectors[i].floorH >> sectors[i].ceilH
            >> sectors[i].floorSlopeX >> sectors[i].floorSlopeY
            >> sectors[i].ceilSlopeX >> sectors[i].ceilSlopeY;
    }
    f.close();
}

void Game::Init()
{
    InitWindow(Window::WIDTH, Window::HEIGHT, Window::FONT_W, Window::FONT_H);
    SetWindowName(L"Quest");
    ShowConsoleCursor(false);
    SetFPS(60);

    bool gameIsRunning = false;

    Texture brickTex = CreateTexture(16, 16);
    Texture blackBrickTex = CreateTexture(16, 16);
    Texture stoneTex = CreateTexture(16, 16);
    Texture blackStoneTex = CreateTexture(16, 16);
    Texture cobbleTex = CreateTexture(16, 16);
    Texture woodTex = CreateTexture(16, 16);
    Texture beamTex = CreateTexture(16, 16);
    Texture glassTex = CreateTexture(16, 16);
    Texture rGlassTex = CreateTexture(16, 16);
    Texture gGlassTex = CreateTexture(16, 16);
    Texture bGlassTex = CreateTexture(16, 16);
    Texture bannerTex = CreateTexture(16, 16);
    Texture grassTex = CreateTexture(16, 16);
    Texture gravelTex = CreateTexture(16, 16);
    Texture carpetTex = CreateTexture(16, 16);
    Texture rCarpetTex = CreateTexture(16, 16);
    Texture bCarpetTex = CreateTexture(16, 16);
    Texture wSlopeTex = CreateTexture(16, 16);
    Texture bSlopeTex = CreateTexture(16, 16);
    Texture dgSlopeTex = CreateTexture(16, 16);
    Texture gSlopeTex = CreateTexture(16, 16);

    brickTile(brickTex);
    blackBrickTile(blackBrickTex);
    stoneTile(stoneTex);
    blackStoneTile(blackStoneTex);
    cobbleStoneTile(cobbleTex);
    woodTile(woodTex);
    woodenBeamTile(beamTex);
    glassTile(glassTex);
    rGlassTile(rGlassTex);
    gGlassTile(gGlassTex);
    bGlassTile(bGlassTex);
    bannerTile(bannerTex);
    grassTile(grassTex);
    gravelTile(gravelTex);
    carpetTile(carpetTex);
    rCarpetTile(rCarpetTex);
    bCarpetTile(bCarpetTex);
    wSlopeTile(wSlopeTex);
    bSlopeTile(bSlopeTex);
    dgSlopeTile(dgSlopeTex);
    gSlopeTile(gSlopeTex);

    TextureSet texSet = {};
    texSet.tex[0] = nullptr;       // 0: no texture / sky
    texSet.tex[1] = &brickTex;
    texSet.tex[2] = &blackBrickTex;
    texSet.tex[3] = &stoneTex;
    texSet.tex[4] = &blackStoneTex;
    texSet.tex[5] = &cobbleTex;
    texSet.tex[6] = &woodTex;
    texSet.tex[7] = &beamTex;
    texSet.tex[8] = &glassTex;
    texSet.tex[9] = &rGlassTex;
    texSet.tex[10] = &gGlassTex;
    texSet.tex[11] = &bGlassTex;
    texSet.tex[12] = &bannerTex;
    texSet.tex[13] = &grassTex;
    texSet.tex[14] = &gravelTex;
    texSet.tex[15] = &carpetTex;
    texSet.tex[16] = &rCarpetTex;
    texSet.tex[17] = &bCarpetTex;
    texSet.tex[18] = &wSlopeTex;
    texSet.tex[19] = &bSlopeTex;
    texSet.tex[20] = &dgSlopeTex;
    texSet.tex[21] = &gSlopeTex;

    LoadMap();

    while (!WindowShouldClose())
    {
        Fill(0, 0, Window::WIDTH, Window::HEIGHT, PIXEL_SOLID, BLACK);

        GetKeyState();

        if (editor.enabled) 
        {
            EditorInput();
            DrawEditor();
        }

        else if (gameIsRunning)
        {
            input();
            drawBackground(texSet, 13);
            drawFOV(texSet, 18, 7);

            if (GetKey(KEY_TAB).k_Pressed) editor.enabled = true;
        }

        else
        {
            DrawString(100, 23, L"Welcome to Quest", RED);
            DrawString(100, 24, L"1. Campaign", RED);
            DrawString(100, 25, L"2. About", RED);
            DrawString(100, 26, L"3. Quit", RED);

            if (GetKey(KEY_TAB).k_Pressed) editor.enabled = true;
            if (GetKey(KEY_1).k_Pressed) gameIsRunning = true;
            if (GetKey(KEY_2).k_Pressed) DrawString(100, 25, L"About.....", WHITE);
            if (GetKey(KEY_3).k_Pressed) Shutdown();
        }

        UpdateScreen();
    }

    appIsRunning = false;
    FlushKeys();

    DestroyTexture(brickTex);
    DestroyTexture(blackBrickTex);
    DestroyTexture(stoneTex);
    DestroyTexture(blackStoneTex);
    DestroyTexture(cobbleTex);
    DestroyTexture(woodTex);
    DestroyTexture(beamTex);
    DestroyTexture(glassTex);
    DestroyTexture(rGlassTex);
    DestroyTexture(gGlassTex);
    DestroyTexture(bGlassTex);
    DestroyTexture(bannerTex);
    DestroyTexture(grassTex);
    DestroyTexture(gravelTex);
    DestroyTexture(carpetTex);
    DestroyTexture(rCarpetTex);
    DestroyTexture(bCarpetTex);
    DestroyTexture(wSlopeTex);
    DestroyTexture(bSlopeTex);
    DestroyTexture(dgSlopeTex);
    DestroyTexture(gSlopeTex);

    DestroyWindow();
}