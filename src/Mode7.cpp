#include "Mode7.h"
#include <GLFW/glfw3.h>
#include <cmath>

static inline int clampi(int v,int lo,int hi){ return v<lo?lo:(v>hi?hi:v); }

bool Mode7::Load(const char* mapPath, const char* skyPath){
    if(!image_load_rgba(mapPath, imgMap)) return false;
    gltex_from_file(skyPath, texSky);
    texOutput.id = 0; texOutput.width = 0; texOutput.height = 0;
    quadReady = quad_init(quad);
    return quadReady;
}

void Mode7::rebuildFrameTextureIfNeeded(){
    const int outW = vpW * blowup_scale;
    const int outH = (vpH/2) * blowup_scale;
    const size_t need = size_t(outW) * size_t(outH) * 4;
    if(frameBuffer.size() != need){
        frameBuffer.assign(need, 0);
        Image img; img.width=outW; img.height=outH; img.channels=4;
        img.pixels.resize(need, 0);
        gltex_from_image(img, texOutput);
    }
}

void Mode7::updateFrustum(){
    float A = fWorldA, F = fFoVHalf;
    frustum.Far1x  = fWorldX + std::cos(A - F)*fFar;
    frustum.Far1y  = fWorldY + std::sin(A - F)*fFar;
    frustum.Near1x = fWorldX + std::cos(A - F)*fNear;
    frustum.Near1y = fWorldY + std::sin(A - F)*fNear;
    frustum.Far2x  = fWorldX + std::cos(A + F)*fFar;
    frustum.Far2y  = fWorldY + std::sin(A + F)*fFar;
    frustum.Near2x = fWorldX + std::cos(A + F)*fNear;
    frustum.Near2y = fWorldY + std::sin(A + F)*fNear;
}

void Mode7::buildGroundScanlines(){
    const int outW = vpW * blowup_scale;
    const int outH = (vpH/2) * blowup_scale;

    for(int y=0; y<vpH/2; ++y){
        float fSampleDepth = float(y) / float(vpH/2);
        float fStartX = (frustum.Far1x - frustum.Near1x) / (fSampleDepth) + frustum.Near1x;
        float fStartY = (frustum.Far1y - frustum.Near1y) / (fSampleDepth) + frustum.Near1y;
        float fEndX   = (frustum.Far2x - frustum.Near2x) / (fSampleDepth) + frustum.Near2x;
        float fEndY   = (frustum.Far2y - frustum.Near2y) / (fSampleDepth) + frustum.Near2y;

        for(int x=0; x<vpW; ++x){
            float fSampleWidth = float(x)/float(vpW);
            float fx = (fEndX - fStartX)*fSampleWidth + fStartX;
            float fy = (fEndY - fStartY)*fSampleWidth + fStartY;

            int texX = int(fx);
            int texY = int(fy);

            unsigned char r=0,g=0,b=0,a=0;
            if(texX>=0 && texX<imgMap.width && texY>=0 && texY<imgMap.height){
                Color c = image_get_pixel(imgMap, texX, texY);
                r=c.r; g=c.g; b=c.b; a=c.a;
            }else{
                r=g=b=0; a=255;
            }

            for(int by=0; by<blowup_scale; ++by){
                int oy = (y*blowup_scale + by);
                for(int bx=0; bx<blowup_scale; ++bx){
                    int ox = (x*blowup_scale + bx);
                    size_t idx = (size_t(oy)*outW + ox)*4;
                    frameBuffer[idx+0]=r;
                    frameBuffer[idx+1]=g;
                    frameBuffer[idx+2]=b;
                    frameBuffer[idx+3]=a;
                }
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, texOutput.id);
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,outW,outH,GL_RGBA,GL_UNSIGNED_BYTE,frameBuffer.data());
}

void Mode7::Update(double dt, void* winPtr){
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(winPtr);
    if(glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS) fNear += 0.1f * fSpeed * float(dt);
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS) fNear -= 0.1f * fSpeed * float(dt);
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS) fFar  += 0.1f * fSpeed * float(dt);
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS) fFar  -= 0.1f * fSpeed * float(dt);
    if(glfwGetKey(window, GLFW_KEY_Z)==GLFW_PRESS) fFoVHalf += 0.1f * float(dt);
    if(glfwGetKey(window, GLFW_KEY_X)==GLFW_PRESS) fFoVHalf -= 0.1f * float(dt);

    if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        fWorldA += 1.0f * float(dt);
        skyOffset += 1.0f * fSpeed * 1.5f * float(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        fWorldA -= 1.0f * float(dt);
        skyOffset -= 1.0f * fSpeed * 1.5f * float(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        fWorldX += std::cos(fWorldA) * fSpeed * float(dt);
        fWorldY += std::sin(fWorldA) * fSpeed * float(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        fWorldX -= std::cos(fWorldA) * fSpeed * float(dt);
        fWorldY -= std::sin(fWorldA) * fSpeed * float(dt);
    }
    updateFrustum();
}

void Mode7::Draw(){
    if(!quadReady) return;
    rebuildFrameTextureIfNeeded();

    // Ground
    buildGroundScanlines();
    // Sky (simple draw; no UV offset shader here)
    if(texSky.id){
        // draw at top half
        float drawW = float(vpW*blowup_scale);
        float drawH = float((vpH/2)*blowup_scale);
        quad_draw(quad, texSky.id, float(vpX), float(vpY), drawW, drawH);
    }
    // Ground at bottom half
    quad_draw(quad, texOutput.id,
              float(vpX), float(vpY + (vpH/2)*blowup_scale),
              float(vpW*blowup_scale), float((vpH/2)*blowup_scale));
}

void Mode7::Unload(){
    gltex_destroy(texOutput);
    gltex_destroy(texSky);
    gltex_destroy(texMap);
    imgMap = Image{};
    if(quadReady){ quad_shutdown(quad); quadReady=false; }
}
