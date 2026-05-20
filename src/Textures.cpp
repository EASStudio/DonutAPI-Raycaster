#include "Globals.h"

/*
Textures:

Wall textures:

Cave/Dungeon roof                  | Sky / Roof Texture
Church/Black smith hut/Castle roof | Sky / Roof Texture
House roof                         | Sky / Roof Texture
Bricks                             | 1   | Done
Black Bricks                       | 2   | Done
Stone                              | 3   | Done
Black Stone                        | 4   | Done
Cobble Stone                       | 5   | Done
Wooden Planks                      | 6   | Done
Wooden Beams                       | 7   | Done
Clear Glass                        | 8   | Done
Red Glass                          | 9   | Done
Green Glass                        | 10  | Done
Blue Glass                         | 11  | Done
Banner                             | 12  | Done

Floor Textures:
Grass                              | 13 | Done                          
Gravel                             | 14 | Done
Carpet                             | 15 | Done
Red Carpet                         | 16 | Done
Blue Carpet                        | 17 | Done

Sector/Y coord Textures:
White Slope                        | 18 | Done
Black Slope                        | 19 | Done
Dark GRAY Slope                    | 20 | Done
GRAY Slope                         | 21 | Done

*/

// Wall textures
void brickTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (y % 4 == 0) { SetTexPixel(tex, x, y, DARK_GRAY); continue; }
            int mortar = ((y / 4) % 2 == 0) ? 7 : 15;
            SetTexPixel(tex, x, y, (x == mortar % 16) ? DARK_GRAY : ((x + y) % 3 == 0 ? RED : DARK_RED));
        }
    }
}

void blackBrickTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (y % 4 == 0) { SetTexPixel(tex, x, y, DARK_GRAY); continue; }
            int mortar = ((y / 4) % 2 == 0) ? 7 : 15;
            SetTexPixel(tex, x, y, (x == mortar % 16) ? DARK_GRAY : ((x + y) % 3 == 0 ? DARK_GRAY : DARK_GRAY));
        }
    }
}

void stoneTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, GRAY);
    }
}

void blackStoneTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, DARK_GRAY);
    }
}

void cobbleStoneTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            bool h = (y % 5 == 0) || (y % 5 == 4 && x > 8);
            bool v = (x % 6 == 0) || (x % 6 == 5 && y < 8);
            SetTexPixel(tex, x, y, (h || v) ? GRAY : DARK_GRAY);
        }
    }
}

void woodTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x % 4 == 0) ? YELLOW : BROWN);
    }
}

void woodenBeamTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (y % 4 == 0) ? YELLOW : BROWN);
    }
}

void glassTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 3 == 0 ? WHITE : BLACK);  // TODO: Fix the black color | Doesnt render properly; just has an opach color
    }
}

void rGlassTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 3 == 0 ? WHITE : RED);
    }
}

void gGlassTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 3 == 0 ? WHITE : GREEN);
    }
}

void bGlassTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 3 == 0 ? WHITE : BLUE);
    }
}

void bannerTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y + y) % 4 ? BLUE : RED);
    }
}


// Floor Texture


void grassTile(Texture& tex) 
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 4 ? DARK_GREEN : GREEN);
    }
}

void gravelTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 4 ? DARK_GRAY : GRAY);
    }
}

void carpetTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 4 ? MAGENTA : DARK_MAGENTA);
    }
}

void rCarpetTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 4 ? DARK_RED : RED);
    }
}

void bCarpetTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, (x + y) % 4 ? DARK_BLUE : BLUE);
    }
}

// Sector / Y coord Textures


void wSlopeTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, WHITE);
    }
}

void bSlopeTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, BLACK);
    }
}
void dgSlopeTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, DARK_GRAY);
    }
}

void gSlopeTile(Texture& tex)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
            SetTexPixel(tex, x, y, DARK_GRAY);
    }
}