
# Visual Studio Setup

Open `opengl_port.sln` in VS 2022.

## Provide Dependencies
- **GLFW**: Install via vcpkg (`vcpkg install glfw3:x64-windows`) and ensure `vcpkg integrate install` is done.
  - Or set `GlfwIncludeDir`/`GlfwLibDir` in `user-config.props` to your GLFW paths.
- **GLAD**: Generate a loader for OpenGL 3.3+ Core Profile at https://glad.dav1d.de/ (API: OpenGL, Profile: Core).
  - Replace `third_party\glad\src\glad.c` and put headers into `third_party\glad\include\glad\`.
- **stb**: Put `stb_image.h` and `stb_image_write.h` under `third_party\stb\`.

## Build
- Choose `x64-Debug` or `x64-Release`, build, and run.
- If link errors for `glfw3.lib` appear, confirm `GlfwLibDir` is correct or vcpkg integration is active.
