#pragma once
#include <vector>
#include "GridCell.h"
#include "gl_image.h"
#include "gl_texture.h"
#include "gl_fbo.h"
#include "quad.h"

class GridMap {
public:
    GridMap();
    ~GridMap();
    void ResetIsoGridMapArray();
    void InitializeIsoView();
    void IsometricExportMap(int view);
    void IsometricDrawMap(int index);
    void ResetPerlinTexture();

private:
    std::vector<GridCell> IsoGridMapArray;
    GLTexture PlainsTexture, WaterTexture, MountainTexture, SnowTexture;
    GLTexture IsoMapTexture[4];
    Quad quad{};
    bool ready=false;
    int mapW=31, mapH=31;

    void drawTile(int x, int y, const GLTexture& tex, float sx, float sy);
};
