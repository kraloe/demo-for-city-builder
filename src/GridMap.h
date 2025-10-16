#pragma once
#include <vector>
#include "GridCell.h"
#include "gl_image.h"
#include "gl_texture.h"
#include "gl_fbo.h"
#include "quad.h"
#include "FastNoiseLite.h"

class GridMap {
public:
    GridMap();
    ~GridMap();
    void ResetIsoGridMapArray();
    void InitializeIsoView();
    void IsometricExportMap(int view);
    void IsometricDrawMap(int index);
    void ResetPerlinTexture();

    void drawTile(int gx, int gy, const GLTexture& tex, float sx, float sy, int height);

    void GenerateHeightMapWithFastNoise(int seed, float frequency, int octaves, float gain, float lacunarity);

    void BakeTileTypesFromHeight();

private:
    std::vector<GridCell> IsoGridMapArray;
    GLTexture PlainsTexture, WaterTexture, MountainTexture, SnowTexture;
    GLTexture IsoMapTexture[4];
    Quad quad{};
    bool ready=false;
    int mapW=31, mapH=31;

    void drawTile(int x, int y, const GLTexture& tex, float sx, float sy);
};
