#include "GridMap.h"
#include <cmath>

GridMap::GridMap(){
    ready = quad_init(quad);
    IsoGridMapArray.resize(mapW*mapH);
    // Optional: load your tile textures here (update paths)
    // gltex_from_file("Assets/IsoPlains.png", PlainsTexture);
    // gltex_from_file("Assets/IsoWater.png",  WaterTexture);
    // gltex_from_file("Assets/IsoMountain.png", MountainTexture);
    // gltex_from_file("Assets/IsoSnow.png", SnowTexture);
}

GridMap::~GridMap(){
    quad_shutdown(quad);
    gltex_destroy(PlainsTexture);
    gltex_destroy(WaterTexture);
    gltex_destroy(MountainTexture);
    gltex_destroy(SnowTexture);
    for(int i=0;i<4;++i) gltex_destroy(IsoMapTexture[i]);
}

void GridMap::ResetIsoGridMapArray(){
    for(auto& c: IsoGridMapArray){ c.tileType=0; c.height=0; }
}

void GridMap::InitializeIsoView(){
    // Placeholder: fill with some pattern
    for(int y=0;y<mapH;++y){
        for(int x=0;x<mapW;++x){
            auto& c = IsoGridMapArray[y*mapW+x];
            c.tileType = (x+y)%4;
            c.height = (x+y)%3;
        }
    }
}

void GridMap::IsometricExportMap(int view){
    (void)view;
    // For now, do nothing. In your project, render to an FBO and save/read it.
}

void GridMap::drawTile(int gx, int gy, const GLTexture& tex, float sx, float sy){
    if(tex.id==0) return;
    // Simple iso placement (tweak to your formula)
    float tileW = 64, tileH = 32;
    float screenX = sx + (gx - gy) * (tileW * 0.5f);
    float screenY = sy + (gx + gy) * (tileH * 0.5f);
    quad_draw(quad, tex.id, screenX, screenY, (float)tex.width, (float)tex.height);
}

void GridMap::IsometricDrawMap(int index){
    (void)index;
    if(!ready) return;
    // Demo draw using one texture if available
    for(int y=0;y<mapH;++y){
        for(int x=0;x<mapW;++x){
            const GLTexture* t = &PlainsTexture;
            switch(IsoGridMapArray[y*mapW+x].tileType){
                case 1: t = &WaterTexture; break;
                case 2: t = &MountainTexture; break;
                case 3: t = &SnowTexture; break;
                default: t = &PlainsTexture; break;
            }
            drawTile(x,y,*t, 600.0f, 50.0f);
        }
    }
}

void GridMap::ResetPerlinTexture(){
    // Optional: generate noise into an Image then gltex_from_image(...) if you need it.
}
