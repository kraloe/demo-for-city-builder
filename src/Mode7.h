#pragma once
#include "gl_image.h"
#include "gl_texture.h"
#include "quad.h"
#include "Vec2.h"

class Mode7 {
public:
    bool Load(const char* mapPath, const char* skyPath);
    void Update(double dt, void* glfwWindow);
    void Draw();
    void Unload();

    void SetViewport(int x, int y, int w, int h){ vpX=x; vpY=y; vpW=w; vpH=h; }
    void SetBlowup(int s){ blowup_scale = s<1?1:s; }

private:
    struct Frustum {
        float Far1x=0, Far1y=0;
        float Far2x=0, Far2y=0;
        float Near1x=0, Near1y=0;
        float Near2x=0, Near2y=0;
    };

    float fWorldX=0.0f, fWorldY=0.0f, fWorldA=0.0f;
    float fNear=-171.0f, fFar=28.0f, fFoVHalf=1.3f;
    float fSpeed=100.0f; 
    float skyOffset=0.0f;

    int vpX=0, vpY=0, vpW=800, vpH=450;
    int blowup_scale=1;

    Image imgMap;
    GLTexture texMap{};
    GLTexture texSky{};

    GLTexture texOutput{};
    std::vector<unsigned char> frameBuffer;

    Frustum frustum{};
    Quad quad{};
    bool quadReady=false;

    void rebuildFrameTextureIfNeeded();
    void buildGroundScanlines();
    void updateFrustum();
};
