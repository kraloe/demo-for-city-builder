#pragma once
#include "Vec2.h"
#include <GLFW/glfw3.h>

class MouseInput
{
private:
    Math::vec2 pan {0.0f, 0.0f};
    Math::vec2 lastMousePos {0.0f, 0.0f};
    bool dragging = false;
    float zoom = 1.0f;
    GLFWwindow* window = nullptr;
    double scrollDelta = 0.0;

    static void ScrollCallback(GLFWwindow* win, double xoff, double yoff){
        (void)xoff;
        auto* self = reinterpret_cast<MouseInput*>(glfwGetWindowUserPointer(win));
        if(self) self->scrollDelta += yoff;
    }

public:
    explicit MouseInput(GLFWwindow* win): window(win){
        glfwSetWindowUserPointer(window, this);
        glfwSetScrollCallback(window, ScrollCallback);
    }

    Math::vec2 GetPan() const { return pan; }
    float GetZoom() const { return zoom; }

    void MouseDrag(){
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
            double mx, my; glfwGetCursorPos(window, &mx, &my);
            Math::vec2 mousePos{ float(mx), float(my) };
            if(!dragging) lastMousePos = mousePos;
            Math::vec2 delta = mousePos - lastMousePos;
            pan += delta;
            lastMousePos = mousePos;
            dragging = true;
        }else{
            dragging = false;
        }
    }

    void MouseScroll(){
        if(scrollDelta != 0.0){
            float oldZoom = zoom;
            zoom += float(scrollDelta) * 0.1f;
            if(zoom < 0.1f) zoom = 0.1f;
            if(zoom > 5.0f) zoom = 5.0f;
            double mx, my; glfwGetCursorPos(window, &mx, &my);
            float zoomFactor = zoom / oldZoom;
            pan = pan * zoomFactor + Math::vec2{ float(mx), float(my) } * (1.f - zoomFactor);
            scrollDelta = 0.0;
        }
    }
};
