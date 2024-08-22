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

// Basic datastructures
typedef struct SceneData {
    GLuint cube_vao;
    GLuint basic_program;
    GLuint model_vao;
    GLuint model_program;
    GLuint framebuffer;
    GLuint texture;
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

float cube_vertices[] = {
		// positions          // normals           // texture coords
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		// Front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		// Left face
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		// Right face
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		// Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

		// Top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	};

// Shaders for cube
const char* cube_vrtx_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(
    // Vertex Shader Input Attributes
    // `aPos` is the position of the vertex.
    layout (location = 0) in vec3 aPos;
    // `aNormal` is the normal vector at the vertex.
    layout (location = 1) in vec3 aNormal;
    // `aTexCoords` are the texture coordinates for the vertex.
    layout (location = 2) in vec2 aTexCoords;

    // Output to the fragment shader
    // `FragPos` is the transformed position of the vertex in world space.
    out vec3 FragPos;
    // `Normal` is the transformed normal vector.
    out vec3 Normal;
    // `TexCoords` are the texture coordinates passed to the fragment shader.
    out vec2 TexCoords;

    // Uniforms used for transformations
    // `model` is the model matrix that transforms vertex positions from model space to world space.
    uniform mat4 model;
    // `view` is the view matrix that transforms vertices from world space to camera space.
    uniform mat4 view;
    // `projection` is the projection matrix that transforms vertices from camera space to screen space.
    uniform mat4 projection;

    void main()
    {
        // Transform vertex position from model space to world space using the model matrix.
        FragPos = vec3(model * vec4(aPos, 1.0));

        // Transform the normal vector from model space to world space using the model matrix.
        // `transpose(inverse(model))` is used to correctly transform normals.
        Normal = mat3(transpose(inverse(model))) * aNormal;

        // Pass texture coordinates to the fragment shader.
        TexCoords = aTexCoords;

        // Calculate the final position of the vertex in clip space.
        // `projection * view * vec4(FragPos, 1.0)` transforms the vertex position through view and projection matrices.
        gl_Position = projection * view * vec4(FragPos, 1.0);
    }
);

const char* cube_frag_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(

    // Output color of the fragment.
    out vec4 FragColor;

    // Inputs from the vertex shader.
    // `FragPos` is the position of the fragment in world space.
    in vec3 FragPos;
    // `Normal` is the normal vector at the fragment.
    in vec3 Normal;
    // `TexCoords` is the texture coordinate of the fragment.
    in vec2 TexCoords;

    // Uniforms for textures and lighting.
    // `simple_texture` is the texture sampler for the object's texture.
    uniform sampler2D simple_texture;

    void main()
    {
        // Normalize the normal vector for correct lighting calculations.
        vec3 norm = normalize(Normal);

        // Compute the direction of the light relative to the fragment position.
        // Here, a directional light is positioned at (1.0, 1.0, 1.0).
        vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0) - FragPos);

        // Calculate the diffuse lighting component.
        // `diff` is the dot product between the normal and light direction, clamped to zero.
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0, 1.0, 1.0); // White diffuse light

        // Ambient lighting component (constant, low-level illumination).
        vec3 ambient = vec3(1.0, 1.0, 1.0); // White ambient light
        
        // Sample the texture color at the given texture coordinates.
        vec4 texColor = texture(simple_texture, TexCoords);

        // Combine the ambient and diffuse lighting with the texture color.
        // `0.8` is the alpha value for the final color (opacity).
        vec4 result = texColor * vec4((ambient + diffuse), 0.8);

        // Set the final color of the fragment.
        FragColor = result;
    }
);

// Shaders for model
const char* model_vrtx_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(

    // Vertex Shader Input Attributes
    // `aPos` is the position of the vertex, with layout location 0.
    layout(location = 0) in vec3 aPos;   // Position attribute
    
    // `aNormal` is the normal vector at the vertex, with layout location 1.
    layout(location = 1) in vec3 aNormal; // Normal attribute

    // Outputs to the fragment shader
    // `FragPos` is the position of the fragment in world space.
    out vec3 FragPos;  // Position of the fragment in world space

    // `Normal` is the normal vector at the fragment, used for lighting calculations.
    out vec3 Normal;   // Normal of the fragment

    // Uniforms used for transformations
    // `model` matrix transforms vertex positions from model space to world space.
    // `view` matrix transforms vertices from world space to camera (view) space.
    // `projection` matrix transforms vertices from camera space to screen space.
    uniform mat4 model;       // Model matrix
    uniform mat4 view;        // View matrix
    uniform mat4 projection;  // Projection matrix

    void main()
    {
        // Transform the vertex position from model space to world space.
        FragPos = vec3(model * vec4(aPos, 1.0));

        // Transform the normal vector from model space to world space.
        // `transpose(inverse(model))` adjusts normals for correct lighting in world space.
        Normal = mat3(transpose(inverse(model))) * aNormal;  

        // Calculate the final position of the vertex in clip space.
        // Applying the projection matrix after the view matrix determines the final screen position.
        // Adjusting `vec4(FragPos, 0.4)` scales the position, affecting the zoom level.
        gl_Position = projection * view * vec4(FragPos, 0.4); // zoom
    }
);

const char* model_frag_shdr_src =
    GLH_SHADER_HEADER
    GLH_STRINGIFY(
    
    // Output color of the fragment.
    out vec4 FragColor;
    // Inputs from the vertex shader.
    // `FragPos` is the position of the fragment in world space.
    in vec3 FragPos;
    // `Normal` is the normal vector at the fragment.
    in vec3 Normal;
    // `TexCoord` is the texture coordinate of the fragment (not used in this shader).
    in vec2 TexCoord;

    // Uniforms for lighting and material properties.
    // `lightPos` is the position of the light source in world space.
    uniform vec3 lightPos;
    // `viewPos` is the position of the camera/viewer in world space.
    uniform vec3 viewPos;
    // `lightColor` is the color of the light source.
    uniform vec3 lightColor;
    // `objectColor` is the base color of the object.
    uniform vec3 objectColor;
    // `roughness` and `metalness` control the material properties for PBR.
    uniform float roughness;
    uniform float metalness;

    void main()
    {
        // Normalize the normal vector for proper lighting calculations.
        vec3 norm = normalize(Normal);
        // Calculate the direction from the fragment to the viewer (camera).
        vec3 viewDir = normalize(viewPos - FragPos);
        // Calculate the direction from the fragment to the light source.
        vec3 lightDir = normalize(lightPos - FragPos);
        // Calculate the half-vector between the view direction and the light direction.
        vec3 halfDir = normalize(viewDir + lightDir);

        // Ambient lighting contribution (constant low-level illumination).
        vec3 ambient = 0.1 * lightColor;

        // Diffuse lighting contribution based on the Lambertian reflectance model.
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Specular lighting contribution using the Blinn-Phong reflection model.
        // `pow(max(dot(norm, halfDir), 0.5), 64.0)` controls the shininess.
        float spec = pow(max(dot(norm, halfDir), 0.5), 64.0);
        vec3 specular = spec * lightColor;

        // Simple Physically Based Rendering (PBR) approximation:
        // Albedo is the base color of the object, adjusted for metalness.
        vec3 albedo = objectColor * (1.0 - metalness);
        vec3 ambientColor = ambient * albedo; // Adjust ambient color based on albedo.
        vec3 diffuseColor = diffuse * albedo; // Adjust diffuse color based on albedo.
        vec3 specularColor = specular * metalness; // Adjust specular color based on metalness.

        // Combine ambient, diffuse, and specular components to get the final color.
        vec3 result = ambientColor + diffuseColor + specularColor;
        // Set the output fragment color with full opacity.
        FragColor = vec4(result, 1.0);
    }
);

// Implementation of data loading, out of the way
int32_t load_mesh_data(const char* filename, MeshData* out_data);

// Initialize cube function - called once, sets up data for rendering
void init_cube(SceneData* scene){
    
    // Initialize cube VAO (Vertex Array Object) and VBO (Vertex Buffer Object)
    GLuint cube_vbo;

    // Generate a new VAO for the cube
    glGenVertexArrays(1, &scene->cube_vao); 
    
    // Generate a new VBO for the cube
    glGenBuffers(1, &cube_vbo); 

    // Bind the VAO to set up its configuration
    glBindVertexArray(scene->cube_vao); 

    // Upload vertex data to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

        // Set up the vertex attributes
        // Position attribute: location = 0, 3 components (x, y, z), float type, no normalization, stride = 8 floats, offset = 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        // Enable the position attribute
        glEnableVertexAttribArray(0);
        
        // Normal attribute: location = 1, 3 components (x, y, z), float type, no normalization, stride = 8 floats, offset = 3 floats
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        // Enable the normal attribute
        glEnableVertexAttribArray(1);
        
         // Texture coordinate attribute: location = 2, 2 components (u, v), float type, no normalization, stride = 8 floats, offset = 6 floats
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        // Enable the texture coordinate attribute
        glEnableVertexAttribArray(2);

    // Unbind the VBO (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // Unbind the VAO (optional)
    glBindVertexArray(0);

    // Compile shaders and link the shader program
    // Compile vertex shader
    GLuint vrtx_shdr = glh_compile_shader_src(GL_VERTEX_SHADER, cube_vrtx_shdr_src);
    // Compile fragment shader
    GLuint frag_shdr = glh_compile_shader_src(GL_FRAGMENT_SHADER, cube_frag_shdr_src);
    // Link shaders into a program
    scene->basic_program = glh_link_program(vrtx_shdr, 0, frag_shdr);
}

// Initialize model function - called once, sets up data for rendering
void init_model(SceneData* scene, MeshData* mesh_data) {
    // Initialize VAO (Vertex Array Object), VBO (Vertex Buffer Object), and EBO (Element Buffer Object)
    glGenVertexArrays(1, &scene->model_vao);  // Generate a new VAO and store its ID in `scene->model_vao`
    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);  // Generate a new VBO and store its ID in `vbo`
    glGenBuffers(1, &ebo);  // Generate a new EBO and store its ID in `ebo`

    glBindVertexArray(scene->model_vao);  // Bind the VAO to configure its vertex attributes

    // Bind and configure the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  // Bind the VBO to `GL_ARRAY_BUFFER`
    glBufferData(GL_ARRAY_BUFFER, mesh_data->vertex_count * mesh_data->vertex_size, mesh_data->vertex_data, GL_STATIC_DRAW);  
    // Upload vertex data to the VBO. `mesh_data->vertex_count` is the number of vertices,
    // `mesh_data->vertex_size` is the size of each vertex in bytes, and `mesh_data->vertex_data` is the data pointer.

    // Bind and configure the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  // Bind the EBO to `GL_ELEMENT_ARRAY_BUFFER`
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_data->triangle_count * 3 * sizeof(uint32_t), mesh_data->triangles, GL_STATIC_DRAW);  
    // Upload index data to the EBO. `mesh_data->triangle_count * 3` is the number of indices,
    // `sizeof(uint32_t)` is the size of each index, and `mesh_data->triangles` is the data pointer.

    // Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh_data->vertex_size, (void*)mesh_data->positions_offset);  
    // Position attribute: location = 0, 3 components (x, y, z), float type, no normalization,
    // stride = `mesh_data->vertex_size`, offset = `mesh_data->positions_offset`
    glEnableVertexAttribArray(0);  // Enable the position attribute

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mesh_data->vertex_size, (void*)mesh_data->normals_offset);  
    // Normal attribute: location = 1, 3 components (x, y, z), float type, no normalization,
    // stride = `mesh_data->vertex_size`, offset = `mesh_data->normals_offset`
    glEnableVertexAttribArray(1);  // Enable the normal attribute

    // Unbind the buffers
    // Unbind the VBO (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO (optional)
    glBindVertexArray(0);

    // Compile shaders and link the shader program
    // Compile vertex shader
    GLuint vrtx_shdr = glh_compile_shader_src(GL_VERTEX_SHADER, model_vrtx_shdr_src);  
    // Compile fragment shader
    GLuint frag_shdr = glh_compile_shader_src(GL_FRAGMENT_SHADER, model_frag_shdr_src);  
    // Link shaders into a program and store its ID in `scene->model_program`
    scene->model_program = glh_link_program(vrtx_shdr, 0, frag_shdr);
}

void set_texture(SceneData* scene) {
    // Define light and material properties
    vec3_t lightPos = vec3(0.0f, 1.0f, 2.0f);  // Position of the light in world space
    vec3_t lightColor = vec3(1.0f, 1.0f, 1.0f);  // Color of the light (white)
    vec3_t objectColor = vec3(0.6f, 1.0f, 0.3f);  // Color of the object/material
    float ambientStrength = 0.5f;  // Strength of the ambient light component
    float roughness = 0.5f;  // Roughness factor for the material (used in PBR)
    float metalness = 0.5f;  // Metalness factor for the material (used in PBR)

    // Pass light properties to the fragment shader
    // Get the location of the uniform variables in the fragment shader
    GLint lightPosLoc = glGetUniformLocation(scene->model_program, "lightPos");
    GLint lightColorLoc = glGetUniformLocation(scene->model_program, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(scene->model_program, "objectColor");
    GLint ambientStrengthLoc = glGetUniformLocation(scene->model_program, "ambientStrength");
    GLint roughnessLoc = glGetUniformLocation(scene->model_program, "roughness");
    GLint metalnessLoc = glGetUniformLocation(scene->model_program, "metalness");

    // Set the values of the uniform variables
    glUniform3fv(lightPosLoc, 1, (const GLfloat*)&lightPos);  // Pass the light position as a vec3
    glUniform3fv(lightColorLoc, 1, (const GLfloat*)&lightColor);  // Pass the light color as a vec3
    glUniform3fv(objectColorLoc, 1, (const GLfloat*)&objectColor);  // Pass the object color as a vec3
    glUniform1f(ambientStrengthLoc, ambientStrength);  // Pass the ambient light strength as a float
    glUniform1f(roughnessLoc, roughness);  // Pass the roughness value as a float
    glUniform1f(metalnessLoc, metalness);  // Pass the metalness value as a float
}

void init_texture(SceneData* scene, MeshData* mesh) {
    // Generate and bind the framebuffer object (FBO)
    glGenFramebuffers(1, &scene->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);

    // Generate and configure the texture for color attachment
    glGenTextures(1, &scene->texture);
    glBindTexture(GL_TEXTURE_2D, scene->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // Set texture parameters for filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

    // Attach the texture to the framebuffer's color attachment point
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene->texture, 0);

    // Create and configure the depth buffer
    GLuint depth_buffer;
    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);

    // Check if the framebuffer is complete and ready for rendering
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Framebuffer is not complete!\n");
    }

    // Set the viewport to match the size of the texture
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Clear the framebuffer (color and depth buffers)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the camera and transformation matrices
    vec3_t eye = vec3(0.0f, 0.0f, 3.0f); // Camera position
    vec3_t center = vec3(0.0f, 0.0f, 0.0f); // Point the camera is looking at
    vec3_t up = vec3(0.0f, 1.0f, 0.0f); // Up direction for the camera

    // Use the shader program for rendering
    glUseProgram(scene->model_program);

    // Create rotation matrices based on time
    float angle = (float)glfwGetTime() * 0.5f; // Rotation angle (changes over time)
    vec3_t axis = vec3(0.7071068f, 0.7071068f, 0.0f); // Rotation axis (normalized)
    mat4_t model = mat4_make_rotation(axis, angle); // Model matrix for rotation
    mat4_t view = look_at(eye, center, up); // View matrix
    mat4_t projection = perspective(deg2rad(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f); // Projection matrix

    // Set the matrices as uniforms in the shader
    GLuint model_loc = glGetUniformLocation(scene->model_program, "model");
    GLuint view_loc = glGetUniformLocation(scene->model_program, "view");
    GLuint proj_loc = glGetUniformLocation(scene->model_program, "projection");

    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (const GLfloat*)&model);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (const GLfloat*)&view);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (const GLfloat*)&projection);

    // Set the clear color and use the shader program
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glUseProgram(scene->model_program);

    // Bind the texture and render the model
    set_texture(scene);
    glBindVertexArray(scene->model_vao);
    glDrawElements(GL_TRIANGLES, mesh->triangle_count * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind the framebuffer to return to default framebuffer (the screen)
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

// Frame function - called on every frame, performs the rendering
void frame(SceneData* scene, MeshData* mesh_data) {
    // Clear the screen and set the background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3f, 0.3f, 0.45f, 1.0f); // Set the clear color to a dark blue

    // Define the camera and view parameters
    vec3_t eye = vec3(0.0f, 0.0f, 3.0f); // Camera position
    vec3_t center = vec3(0.0f, 0.0f, 0.0f); // Point the camera is looking at
    vec3_t up = vec3(0.0f, 1.0f, 0.0f); // Up direction for the camera

    // Use the shader program for rendering the cube
    glUseProgram(scene->basic_program);

    // Create rotation matrices for the cube
    float angle = (float)glfwGetTime() * 0.15f; // Rotation angle (changes over time)
    vec3_t axis = vec3(0.7071068f, 0.7071068f, 0.0f); // Rotation axis (normalized)
    mat4_t model = mat4_make_rotation(axis, angle); // Model matrix for rotation
    mat4_t view = look_at(eye, center, up); // View matrix for camera
    mat4_t projection = perspective(deg2rad(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f); // Projection matrix

    // Set uniform variables in the shader program
    GLuint model_loc = glGetUniformLocation(scene->basic_program, "model");
    GLuint view_loc = glGetUniformLocation(scene->basic_program, "view");
    GLuint proj_loc = glGetUniformLocation(scene->basic_program, "projection");
    GLuint textureLoc = glGetUniformLocation(scene->basic_program, "simple_texture");

    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (const GLfloat*)&model); // Set the model matrix
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (const GLfloat*)&view); // Set the view matrix
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (const GLfloat*)&projection); // Set the projection matrix
    glUniform1i(textureLoc, 0); // Set texture unit 0

    // Render the cube
    glBindVertexArray(scene->cube_vao); // Bind the VAO for the cube
    glBindTexture(GL_TEXTURE_2D, scene->texture); // Bind the texture for the cube
    glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the cube (assuming 36 vertices for a cube)
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    glBindVertexArray(0); // Unbind the VAO
}

void render_model(SceneData* scene, MeshData* mesh) {
    // Bind the framebuffer object (FBO) to render to it
    glBindFramebuffer(GL_FRAMEBUFFER, scene->framebuffer);

    // Attach the texture to the FBO as the color attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene->texture, 0);

    // Clear the framebuffer's color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set the clear color to a dark gray

    // Define the camera position and orientation
    vec3_t eye = vec3(0.0f, 0.0f, 3.0f);     // Camera position
    vec3_t center = vec3(0.0f, 0.0f, 0.0f);  // Point the camera is looking at
    vec3_t up = vec3(0.0f, 1.0f, 0.0f);      // Up direction for the camera

    // Use the shader program for rendering
    glUseProgram(scene->model_program);

    // Calculate the rotation angle based on elapsed time for animation
    float angle = (float)glfwGetTime() * 0.5f; // Rotate at 0.5 radians per second
    vec3_t axis = vec3(1.0f, 0.0f, 0.0f);     // Rotation around the X-axis

    // Create the transformation matrices
    mat4_t model = mat4_make_rotation(axis, angle); // Model matrix with rotation
    mat4_t view = look_at(eye, center, up);         // View matrix for camera
    mat4_t projection = perspective(deg2rad(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f); // Perspective projection matrix

    // Retrieve the locations of the uniform variables in the shader
    GLuint model_loc = glGetUniformLocation(scene->model_program, "model");
    GLuint view_loc = glGetUniformLocation(scene->model_program, "view");
    GLuint proj_loc = glGetUniformLocation(scene->model_program, "projection");

    // Set the transformation matrices in the shader
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (const GLfloat*)&model);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (const GLfloat*)&view);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (const GLfloat*)&projection);

    // Bind and set up the texture
    set_texture(scene);

    // Bind the vertex array object (VAO) for the model
    glBindVertexArray(scene->model_vao);

    // Draw the model using the element buffer
    glDrawElements(GL_TRIANGLES, mesh->triangle_count * 3, GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the framebuffer object to render to the default framebuffer (the screen)
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int32_t main(int32_t argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        // If GLFW fails to initialize, print an error message and terminate the application
        printf("Failed to initialize GLFW! Terminating\n");
        exit(EXIT_FAILURE);
    }

    // Set GLFW window hints for OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version of OpenGL to 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // Set the minor version of OpenGL to 1
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);       // Make the window non-resizable
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core profile of OpenGL
    glfwWindowHint(GLFW_SAMPLES, 4);                // Enable 4x multisampling for anti-aliasing

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Yembo", NULL, NULL);
    if (!window) {
        // If window creation fails, terminate GLFW and the application
        glfwTerminate();
        printf("Failed to create window! Terminating!\n");
        exit(EXIT_FAILURE);
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD to manage OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // If GLAD fails to load OpenGL functions, print an error message and return
        fprintf(stderr, "[ERROR] Failed to initialize OpenGL context!\n");
        return 1;
    }

    // Enable depth testing to ensure proper rendering of 3D objects
    glEnable(GL_DEPTH_TEST);

    // Load mesh data from file
    MeshData mesh = {0}; // Initialize mesh data structure
    if (!load_mesh_data("data/armadillo.bin", &mesh)) {
        // If mesh data is successfully loaded, print information about it
        printf("Loaded the mesh with %d vertices and %d triangles!\n", mesh.vertex_count, mesh.triangle_count);
        printf("Vertex Layout: %d bytes per vertex\n", mesh.vertex_size);
        printf("  Position Size: %d bytes | Offset: %d bytes\n", mesh.positions_size, mesh.positions_offset);
        printf("  Normal Size:   %d bytes | Offset: %d bytes\n", mesh.normals_size, mesh.normals_offset);
    }

    // Initialize scene data and resources
    SceneData scene = {0}; // Initialize scene data structure
    init_cube(&scene);     // Initialize cube data
    init_model(&scene, &mesh); // Initialize model with mesh data
    init_texture(&scene, &mesh); // Initialize texture for the model

    // Set the viewport size to match the window dimensions
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Run the rendering loop until the window is closed
    while (!glfwWindowShouldClose(window)) {
        render_model(&scene, &mesh); // Render the model
        frame(&scene, &mesh);        // Update the frame (for animation, etc.)
        
        // Swap the front and back buffers to display the rendered image
        glfwSwapBuffers(window);
        
        // Poll for and process events like input and window resize
        glfwPollEvents();
    }

    // Clean up resources before exiting
    glDeleteVertexArrays(1, &scene.cube_vao);  // Delete the cube's VAO
    glDeleteVertexArrays(1, &scene.model_vao); // Delete the model's VAO
    glDeleteProgram(scene.basic_program);      // Delete the basic shader program
    glDeleteProgram(scene.model_program);      // Delete the model shader program
    free(mesh.vertex_data);   // Free the vertex data memory
    free(mesh.triangles);     // Free the triangle index memory
    glfwDestroyWindow(window); // Destroy the GLFW window
    glfwTerminate();           // Terminate GLFW
    return 0; // Return success code

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
