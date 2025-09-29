#include "gl_platform.h"
#include "Mode7.h"
#include "GridMap.h"
#include "MouseInput.h"
#include "input.h"

#include <cstdio>

int main(){
    GLApp app;
    if(!glapp_init(app, 1280, 720, "OpenGL Port")) return 1;

    // Input helpers
    CS230::Input input(app.window);
    MouseInput mouse(app.window);

    Mode7 mode7;
    mode7.SetViewport(0,0,1280,720);
    mode7.SetBlowup(1);
    // Update these paths to your assets
    mode7.Load("Assets/map.png", "Assets/Sky.png");

    GridMap grid;
    grid.InitializeIsoView();

    double prev = glfwGetTime();
    while(!glfwWindowShouldClose(app.window)){
        double now = glfwGetTime();
        double dt = now - prev; prev = now;

        glapp_begin_frame();

        input.Update();
        mouse.MouseDrag();
        mouse.MouseScroll();
        mode7.Update(dt, app.window);

        // Draw order example
        mode7.Draw();
        grid.IsometricDrawMap(1);

        glapp_end_frame(app);
    }

    mode7.Unload();
    glapp_shutdown(app);
    return 0;
}
