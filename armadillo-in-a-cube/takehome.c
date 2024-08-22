// Request implementations
#define _GLAD_IMPLEMENTATION_
#define _GLFW_IMPLEMENTATION_
#define _GL_HELPERS_IMPLEMENTATION_
#define _VEC_MATH_IMPLEMENTATION_

// Detect OS
#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX   0
#define PLATFORM_MACOS   0

#if defined(_WIN32) || defined(_WIN64)
#undef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#undef PLATFORM_LINUX
#define PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#undef PLATFORM_MACOS
#define PLATFORM_MACOS 1
#else
#error "Platform not recognized!"
#endif

// Specify windowing backend based on the OS
#if PLATFORM_LINUX
#define PLATFORM_NAME "Linux"
#define _GLFW_X11
#define _POSIX_C_SOURCE 199309L
#define GLFW_INCLUDE_NONE
#elif PLATFORM_MACOS
#define PLATFORM_NAME "OSX"
#define _GLFW_COCOA
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#elif PLATFORM_WINDOWS
#define PLATFORM_NAME "Windows"
#define _GLFW_WIN32
#define GLFW_INCLUDE_NONE
#else
#error "Unknown platform!"
#endif

// Clib includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// Include libraries
#include "libs/glfw.h"
#include "libs/glad.h"
#include "libs/gl_helpers.h"
#include "libs/vec_math.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Basic datastructures
typedef struct SceneData {
    GLuint triangle_vao;
    GLuint basic_program;
} SceneData;


typedef struct MeshData {
    int32_t vertex_count;
    int32_t triangle_count;
    float* vertex_data; // position (3 floats), normals (3 floats)
    uint32_t* triangles; // 3 x triangle_count

    // Vertex Layout info
    int32_t vertex_size;
    int32_t positions_size;
    int32_t positions_offset;
    int32_t normals_size;
    int32_t normals_offset;
} MeshData;

// Forward declare loading code
int32_t load_mesh_data(const char* filename, MeshData* out_data); 


// Shaders
const char* basic_vrtx_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;

    out vec3 v_color;

    void main()
    {
        gl_Position = vec4(position, 1.0);
        v_color = color;
    }
);

const char* basic_frag_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(

    in vec3 v_color;

    out vec4 out_color;

    void main()
    {
        out_color = vec4(v_color, 1.0);
    }
);


// Initialize function - called once, sets up data for rendering
void init(SceneData* scene){

    // Initialize triangle VAO
    GLfloat vertices[] = {
        /* Position */      /* Color */
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    GLuint triangle_vbo;
    glGenVertexArrays(1, &scene->triangle_vao);
    glBindVertexArray(scene->triangle_vao);

    glGenBuffers(1, &triangle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &triangle_vbo);

    // Create the program
    GLuint vrtx_shdr = glh_compile_shader_src(GL_VERTEX_SHADER, basic_vrtx_shdr_src);
    GLuint frag_shdr = glh_compile_shader_src(GL_FRAGMENT_SHADER, basic_frag_shdr_src);
    scene->basic_program = glh_link_program(vrtx_shdr, 0, frag_shdr);
}

// Frame function - called on every frame, performs the rendering
void frame(SceneData *scene) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3f, 0.3f, 0.45f, 1.0f);

    // Render the triangle
    glBindVertexArray(scene->triangle_vao);
    glUseProgram(scene->basic_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

int32_t main(int32_t argc, char** argv) {

    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW! Terminating\n");
        exit(EXIT_FAILURE);
    }

    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Yembo Takehome", NULL, NULL);
    if (!window) {
        glfwTerminate();
        printf("Failed to create window! Terminating!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize OpenGL
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "[ERROR] Failed to initialize OpenGL context!\n");
        return 1;
    }

    // Read mesh data 
    MeshData mesh = {0};
    if (!load_mesh_data("data/armadillo.bin", &mesh)){
        printf("Loaded the mesh with %d vertices and %d triangles!\n", mesh.vertex_count, mesh.triangle_count);
        printf("Vertex Layout: %d bytes per vertex\n", mesh.vertex_size);
        printf("  Position Size: %d bytes | Offset: %d bytes\n", mesh.positions_size, mesh.positions_offset);
        printf("  Normal Size:   %d bytes | Offset: %d bytes\n", mesh.normals_size, mesh.normals_offset);
    }

    // Initialize scene
    SceneData scene = {0};
    init(&scene);

    // Run the rendering loop
    while (!glfwWindowShouldClose(window))
    {
        frame(&scene);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 1;
}

// Implementation of data loading, out of the way
int32_t load_mesh_data(const char* filename, MeshData* out_data) {
    FILE *file = fopen(filename, "rb");
    
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    if (fread(&out_data->vertex_count, sizeof(uint32_t), 1, file) != 1) {
        perror("Failed to read vertex count");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read triangle count (1 byte)
    if (fread(&out_data->triangle_count, sizeof(uint32_t), 1, file) != 1) {
        perror("Failed to read triangle count");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Allocate memory for vertex data 
    out_data->vertex_size = 6 * sizeof(float);
    size_t vertex_data_size = out_data->vertex_count * out_data->vertex_size;
    out_data->vertex_data = (float *)malloc(vertex_data_size);
    if (!out_data->vertex_data) {
        perror("Failed to allocate memory for vertices");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read vertex data
    if (fread(out_data->vertex_data, 1, vertex_data_size, file) != vertex_data_size) {
        perror("Failed to read vertex data");
        free(out_data->vertex_data);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Allocate memory for triangle data 
    size_t triangle_data_size = out_data->triangle_count * 3 * sizeof(uint32_t);
    out_data->triangles = (uint32_t *)malloc(triangle_data_size);
    if (!out_data->triangles) {
        perror("Failed to allocate memory for triangles");
        free(out_data->vertex_data);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read triangle data
    if (fread(out_data->triangles, 1, triangle_data_size, file) != triangle_data_size) {
        perror("Failed to read triangle data");
        free(out_data->vertex_data);
        free(out_data->triangles);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);
    out_data->positions_size = 3 * sizeof(float);
    out_data->positions_offset = 0;
    out_data->normals_size = 3 * sizeof(float);
    out_data->normals_offset = 3 * sizeof(float);
    return 0;
}

