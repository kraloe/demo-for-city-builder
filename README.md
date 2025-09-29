# OpenGL Port Skeleton (Raylib-free)

This project provides the minimal set of **Raylib→OpenGL** replacements discussed.
Drop these files into your solution or build with CMake.

## Dependencies

- **GLFW** (window + input)
- **GLAD** (OpenGL function loader) — either as a target or single `glad.c`
- **stb** headers: `stb_image.h`, `stb_image_write.h` (put into `third_party/stb/`)

You can fetch stb via:
- https://github.com/nothings/stb (copy `stb_image.h` and `stb_image_write.h`)

## Build (CMake)

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Files

- `src/gl_platform.*`: GLFW/GLAD bootstrap + frame helpers
- `src/gl_image.*`: Image/Color structs, load/save via stb
- `src/gl_texture.*`: Texture wrapper (`GLTexture`)
- `src/gl_fbo.*`: FBO wrapper (RenderTexture replacement)
- `src/quad.*`: Simple textured-quad draw helper
- `src/Mode7.*`: Ported Mode7 renderer (CPU→texture path)
- `src/MouseInput.h`: Ported mouse pan/zoom (GLFW)
- `src/input.*`: Ported key input shim (GLFW)
- `src/CustomCell.*`: Image→internal pixel storage example
- `src/GridCell.h`, `src/GridMap.*`: Minimal scaffolding to integrate with your iso-map logic
- `src/main.cpp`: Example loop

Replace or adapt the interfaces to match your project. The code is deliberately small and explicit, so you can copy/paste into your own solution.
