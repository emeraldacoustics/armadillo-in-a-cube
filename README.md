# Armadillo in a Cube

Rotating cube with a texture of a rotating armadillo

## Overview

This project implements a 3D rendering of an armadillo model inside a rotating cube. The solution demonstrates platform-specific windowing backends, mesh data loading, framebuffer setup, texture rendering, and scene management using OpenGL.

The code is designed to be cross-platform, supporting Windows, Linux, and macOS. The armadillo model is rendered offscreen and used as a texture for the rotating cube, showcasing dynamic texture mapping and shader programming.

## Features

- **Platform Detection:** Automatically configures the environment based on the operating system (Windows, Linux, macOS).
- **Mesh Data Loading:** Loads vertex positions, normals, and triangle indices from the `armadillo.bin` file to define the 3D model.
- **Framebuffer Setup:** Renders the armadillo model to a texture using an offscreen framebuffer.
- **Scene Initialization:** Sets up vertex array objects (VAOs) and shaders for the cube and armadillo model.
- **Texture Mapping:** Applies the rendered armadillo texture to the rotating cube.
- **Rendering Loop:** Continuously renders the scene with both the rotating cube and armadillo model.
- **Optimization and Cleanup:** Properly manages and cleans up OpenGL resources to prevent memory leaks.

## How It Works

### Mesh Data Loading

The mesh data is loaded from the `armadillo.bin` file, containing the necessary vertex positions, normals, and triangle indices.

```c
int32_t load_mesh_data(const char* filename, MeshData* out_data);
```

This function reads the vertex and triangle data from the file, packing vertex positions and normals together.

### Framebuffer Setup and Texture Rendering

The armadillo model is rendered offscreen to a texture, which is later used to texture the rotating cube.

```c
void init_texture(SceneData* scene, MeshData* mesh);
```

This function sets up the offscreen framebuffer and attaches the texture, allowing the armadillo model to be rendered without being directly displayed.

### Scene Initialization

Vertex array objects and shaders are initialized for both the cube and armadillo model. The shaders handle lighting, material properties, normal mapping, and other rendering needs.

```c
void init_cube(SceneData* scene);
void init_model(SceneData* scene, MeshData* mesh_data);
```

These functions set up the VAOs, VBOs, and shaders for the cube and armadillo model.

### Texture Mapping

The texture created from the armadillo model is applied to the rotating cube, giving it a dynamic appearance.

### Rendering Loop

The scene is continuously rendered, updating the cube's texture as it rotates.

```c
void frame(SceneData* scene, MeshData* mesh_data);
void render_model(SceneData* scene, MeshData* mesh);
```

The `frame` function handles the rendering loop, where the cube's appearance is updated by the applied texture.

### Optimization and Cleanup

All allocated resources, such as VAOs, shaders, and dynamically allocated memory, are properly managed and cleaned up at the end of the program.

## Usage

1. **Dependencies**:
    - Ensure you have the necessary libraries installed (GLFW, GLAD, OpenGL).
   
2. **Compiling**:
    - Refer to the `README.md` of the assessment for detailed instructions on compiling the code.

    Example command:
    ```bash
    gcc -o armadillo takehome_solution.c -lglfw -lGL -lm
    ```

    To compile the project you should be able to simply use compiler directly:

    **Windows**

    On Windows, we assume you have Visual Studio (we tested Visual Studio 2022 Community Edtion), with C/C++ development. You should be able to open `x64 Native Tools Command Prompt for VS 2022` terminal, in which you will have
    access to `cl.exe`, the MSVC compiler. Then you can compile the takehome as:
    ```
    cl.exe -nologo -std:c11 takehome_solution.c -Fetakehome.exe -link gdi32.lib user32.lib shell32.lib
    ```

    **Linux**

    On Linux, you can use `clang` or `gcc`. We tested the compilation on `Ubuntu 2022.04.4 LTS` 
    ```
    gcc -Wall -std=c11 takehome.c -o takehome.exe -lm -lrt
    ```
    or

    ```
    clang -Wall -std=c11 takehome.c -o takehome.exe -lm -lrt
    ```
    If that does not work, check the [GLFW compile guide](https://www.glfw.org/docs/latest/compile_guide.html), specifically you might need 
    to install:
    ```
    sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
    ```

    **macOS**

    On macOS we tested the code on `Sonoma 14.5` and `Apple clang version 15.0.0`. We needed to silence some warnings 
    as Apple is much more agressive about deprecating code
    ```
    clang -Wall -Wno-deprecated-declarations -ObjC takehome.c -o takehome.exe -framework Cocoa -framework IOkit
    ```

3. **Running**:
    - Run the executable to view the rotating cube with the armadillo texture.
    ```bash
    ./armadillo
    ```

## Documentation

For a detailed explanation of the implementation, including design decisions and technical details, refer to the accompanying PDF document.

## Conclusion

This project demonstrates a robust implementation of cross-platform 3D rendering using OpenGL, showcasing advanced techniques in texture mapping, shader programming, and resource management.
