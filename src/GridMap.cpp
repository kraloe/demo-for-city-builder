#include "GridMap.h"
#include "FastNoiseLite.h"
#include <cmath>
#include <cstdlib>
#include <cstdio>

static inline int clampi(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }
static const int WATER_T = 75;
static const int PLAINS_T = 150;
static const int MOUN_T = 205;
static const float elevationScale = 0.25f;

GridMap::GridMap() {
    ready = quad_init(quad);
    IsoGridMapArray.resize(mapW * mapH);

    if (!gltex_from_file("Assets/IsoPlains.png", PlainsTexture))    std::printf("[WARN] IsoPlains.png not found\n");
    if (!gltex_from_file("Assets/IsoWater.png", WaterTexture))      std::printf("[WARN] IsoWater.png not found\n");
    if (!gltex_from_file("Assets/IsoMountains.png", MountainTexture))  std::printf("[WARN] IsoMountains.png not found\n");
    if (!gltex_from_file("Assets/IsoPeak.png", SnowTexture))        std::printf("[WARN] IsoPeak.png not found\n");

    int seed = 1337;
    GenerateHeightMapWithFastNoise(seed, 0.04f, 5, 0.5f, 2.0f);
    BakeTileTypesFromHeight();
}

GridMap::~GridMap() {
    quad_shutdown(quad);
    gltex_destroy(PlainsTexture);
    gltex_destroy(WaterTexture);
    gltex_destroy(MountainTexture);
    gltex_destroy(SnowTexture);
    for (int i = 0; i < 4; ++i) gltex_destroy(IsoMapTexture[i]);
}

void GridMap::GenerateHeightMapWithFastNoise(int seed, float frequency, int octaves, float gain, float lacunarity) {
    FastNoiseLite noise(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalGain(gain);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFrequency(frequency);

    IsoGridMapArray.resize(mapW * mapH);

    const float ox = 1000.0f, oy = 2000.0f;
    for (int y = 0; y < mapH; ++y) {
        for (int x = 0; x < mapW; ++x) {
            float n = noise.GetNoise(ox + (float)x, oy + (float)y);
            float h01 = (n + 1.0f) * 0.5f;
            unsigned char H = (unsigned char)std::round(h01 * 255.0f);
            int idx = y * mapW + x;
            IsoGridMapArray[idx].height = (int)H;
        }
    }
}

void GridMap::BakeTileTypesFromHeight() {
    for (int y = 0; y < mapH; ++y) {
        for (int x = 0; x < mapW; ++x) {
            auto& c = IsoGridMapArray[y * mapW + x];
            const int h = c.height;
            if (h < WATER_T)           c.tileType = 1;
            else if (h < PLAINS_T)     c.tileType = 0;
            else if (h < MOUN_T)       c.tileType = 2;
            else                       c.tileType = 3;
        }
    }
}

void GridMap::ResetIsoGridMapArray() {
    for (auto& c : IsoGridMapArray) { c.tileType = 0; c.height = 0; }
}

void GridMap::InitializeIsoView() {
}

void GridMap::IsometricExportMap(int view) {
    (void)view;
}

void GridMap::IsometricDrawMap(int) {
    if (!ready) return;
    float startX = 600.0f, startY = 80.0f;

    for (int y = 0; y < mapH; ++y) {
        for (int x = 0; x < mapW; ++x) {
            const auto& c = IsoGridMapArray[y * mapW + x];
            const GLTexture* t = &PlainsTexture;
            switch (c.tileType) {
            case 1: t = &WaterTexture;     break;
            case 2: t = &MountainTexture;  break;
            case 3: t = &SnowTexture;      break;
            default: t = &PlainsTexture;   break;
            }
            drawTile(x, y, *t, startX, startY, c.height);
        }
    }
}

void GridMap::ResetPerlinTexture() {
    int seed = std::rand();
    GenerateHeightMapWithFastNoise(seed, 0.04f, 5, 0.5f, 2.0f);
    BakeTileTypesFromHeight();
}

void GridMap::drawTile(int gx, int gy, const GLTexture& tex, float sx, float sy, int height) {
    if (tex.id == 0) return;

    const float tileW = float(tex.width);
    const float tileH = float(tex.height);

    float screenX = sx + (gx - gy) * (tileW * 0.5f);
    float screenY = sy + (gx + gy) * (tileH * 0.5f);

    float elevPx = float(height);  
    screenY -= elevPx;

    quad_draw(quad, tex.id, screenX, screenY, tileW, tileH);
}
