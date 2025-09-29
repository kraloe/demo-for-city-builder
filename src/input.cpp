#include "input.h"
using namespace CS230;

Input::Input(GLFWwindow* win):window(win){
    keys_down.resize((int)Keys::Count, false);
    previous_keys_down.resize((int)Keys::Count, false);
}
bool Input::KeyDown(Keys k){ return keys_down[(int)k]; }
bool Input::KeyJustPressed(Keys k){ return keys_down[(int)k] && !previous_keys_down[(int)k]; }
bool Input::KeyJustReleased(Keys k){ return !keys_down[(int)k] && previous_keys_down[(int)k]; }
void Input::Update(){
    previous_keys_down = keys_down;
    for(int i=0;i<(int)Keys::Count;++i){
        int gk = cs230_to_glfw((Keys)i);
        if(gk<0){ keys_down[i]=false; continue; }
        keys_down[i] = glfwGetKey(window, gk) == GLFW_PRESS;
    }
}
int CS230::cs230_to_glfw(Input::Keys k){
    switch(k){
        case Input::Keys::A: return GLFW_KEY_A; case Input::Keys::B: return GLFW_KEY_B;
        case Input::Keys::C: return GLFW_KEY_C; case Input::Keys::D: return GLFW_KEY_D;
        case Input::Keys::E: return GLFW_KEY_E; case Input::Keys::F: return GLFW_KEY_F;
        case Input::Keys::G: return GLFW_KEY_G; case Input::Keys::H: return GLFW_KEY_H;
        case Input::Keys::I: return GLFW_KEY_I; case Input::Keys::J: return GLFW_KEY_J;
        case Input::Keys::K: return GLFW_KEY_K; case Input::Keys::L: return GLFW_KEY_L;
        case Input::Keys::M: return GLFW_KEY_M; case Input::Keys::N: return GLFW_KEY_N;
        case Input::Keys::O: return GLFW_KEY_O; case Input::Keys::P: return GLFW_KEY_P;
        case Input::Keys::Q: return GLFW_KEY_Q; case Input::Keys::R: return GLFW_KEY_R;
        case Input::Keys::S: return GLFW_KEY_S; case Input::Keys::T: return GLFW_KEY_T;
        case Input::Keys::U: return GLFW_KEY_U; case Input::Keys::V: return GLFW_KEY_V;
        case Input::Keys::W: return GLFW_KEY_W; case Input::Keys::X: return GLFW_KEY_X;
        case Input::Keys::Y: return GLFW_KEY_Y; case Input::Keys::Z: return GLFW_KEY_Z;
        case Input::Keys::Space: return GLFW_KEY_SPACE;
        case Input::Keys::Enter: return GLFW_KEY_ENTER;
        case Input::Keys::Left: return GLFW_KEY_LEFT;
        case Input::Keys::Right:return GLFW_KEY_RIGHT;
        case Input::Keys::Up:   return GLFW_KEY_UP;
        case Input::Keys::Down: return GLFW_KEY_DOWN;
        case Input::Keys::Escape:return GLFW_KEY_ESCAPE;
        case Input::Keys::Tab:  return GLFW_KEY_TAB;
        default: return -1;
    }
}
