#pragma once
#include <vector>
#include <GLFW/glfw3.h>

namespace CS230 {
class Input {
public:
    enum class Keys { A,B,C,D,E,F,G,H,I,J,K,L,M, N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
                      Space, Enter, Left, Up, Right, Down, Escape, Tab, Count };
    explicit Input(GLFWwindow* win);
    void Update();
    bool KeyDown(Keys key);
    bool KeyJustPressed(Keys key);
    bool KeyJustReleased(Keys key);
private:
    GLFWwindow* window{};
    std::vector<bool> keys_down, previous_keys_down;
};
int cs230_to_glfw(Input::Keys k);
}
