#include <iostream>
#include <vector>

#include "GLM/glm.hpp"
#include "GLM/common.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "opengl_utilities.h"
#include "mesh_generation.h"

// Keep the global state inside this struct
static struct {
    glm::dvec2 mouse_position;
    glm::ivec2 screen_dimensions = glm::ivec2(960, 960);
} Globals;

/* GLFW Callback functions */
static void ErrorCallback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

static void CursorPositionCallback(GLFWwindow* window, double x, double y)
{
    Globals.mouse_position.x = x;
    Globals.mouse_position.y = y;
}

static void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Globals.screen_dimensions.x = width;
    Globals.screen_dimensions.y = height;

    glViewport(0, 0, width, height);
}


int main(int argc, char* argv[])
{
    /* Set GLFW error callback */
    glfwSetErrorCallback(ErrorCallback);

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(
        Globals.screen_dimensions.x, Globals.screen_dimensions.y,
        "<cavitcakir>", NULL, NULL
    );
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* Move window to a certain position [do not change] */
    glfwSetWindowPos(window, 10, 50);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Enable VSync */
    glfwSwapInterval(1);

    /* Load OpenGL extensions with GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Set GLFW Callbacks */
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetWindowSizeCallback(window, WindowSizeCallback);

    /* Configure OpenGL */
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);


    /* Creating OpenGL objects */

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<GLuint> indices;

    GenerateParametricShapeFrom2D(positions, normals, indices, ParametricCircle, 16, 16);
    VAO donutVAO(positions, normals, indices);
    
    
    positions.clear();
    normals.clear();
    indices.clear();
    GenerateParametricShapeFrom2D(positions, normals, indices, ParametricHalfCircle, 16, 16);
    VAO sphereVAO(positions, normals, indices);
    
    positions.clear();
    normals.clear();
    indices.clear();
    GenerateParametricShapeFrom2D(positions, normals, indices, ParametricSpikes, 64, 32);
    VAO torusVAO(positions, normals, indices);

    
    VAO cubeVAO(
            {
                {-0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                {-0.5f,  0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f, -0.5f,  0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                {-0.5f, -0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f, -0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                {-0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f, -0.5f},
                { 0.5f, -0.5f,  0.5f},
                { 0.5f, -0.5f,  0.5f},
                {-0.5f, -0.5f,  0.5f},
                {-0.5f, -0.5f, -0.5f},
                {-0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f, -0.5f},
                { 0.5f,  0.5f,  0.5f},
                { 0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f,  0.5f},
                {-0.5f,  0.5f, -0.5f}
            },
            {
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f, -1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                { 0.0f,  0.0f,  1.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                {-1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 1.0f,  0.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f, -1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f},
                { 0.0f,  1.0f,  0.0f}
            },
            {
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11,
                12, 13, 14,
                15, 16, 17,
                18, 19, 20,
                21, 22, 23,
                24, 25, 26,
                27, 28, 29,
                30, 31, 32,
                33, 34, 35
            }
            );
    

    GLuint program_first_scene = CreateProgramFromSources(
        R"VERTEX(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_transform;

out vec3 vertex_position;
out vec3 vertex_normal;

void main()
{
    gl_Position = u_transform * vec4(a_position, 1);
    vertex_normal = vec3(u_transform * vec4(a_normal, 0));
    vertex_position = vec3(gl_Position);
}
        )VERTEX",

        R"FRAGMENT(
#version 330 core

uniform vec2 u_mouse_position;

in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 out_color;

void main()
{
    out_color = vec4(vec3(1, 1, 1), 1);
}
        )FRAGMENT");
    
    
    
    GLuint program_second_scene = CreateProgramFromSources(
        R"VERTEX(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

uniform mat4 u_transform;

out vec3 vertex_position;
out vec3 vertex_normal;

void main()
{
    gl_Position = u_transform * vec4(a_position, 1);
    vertex_normal = vec3(u_transform * vec4(a_normal, 0));
    vertex_position = vec3(gl_Position);
}
        )VERTEX",

        R"FRAGMENT(
#version 330 core

uniform vec2 u_mouse_position;

in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 out_color;

void main()
{
   vec3 color = vertex_normal;
   vec3 light_direction = normalize(vec3(-1,-1, 1));
   vec3 to_light = -light_direction;
   vec3 light_color =  vec3(1);
    float diffuse_intensity = max(0, dot(to_light, vertex_normal));
    color += diffuse_intensity * light_color * vec3(1);
   vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
   vec3 halfway_dir = normalize(view_dir);
   float shininess = 256;
   float specular_intensity = max(0, dot(halfway_dir, vertex_normal));
   color += pow(specular_intensity, shininess) * light_color;
    out_color = vec4(color, 1);
}
        )FRAGMENT");
    
    GLuint program_third_scene = CreateProgramFromSources(
          R"VERTEX(
  #version 330 core

  layout(location = 0) in vec3 a_position;
  layout(location = 1) in vec3 a_normal;

  uniform mat4 u_transform;

  out vec3 vertex_position;
  out vec3 vertex_normal;

  void main()
  {
      gl_Position = u_transform * vec4(a_position, 1);
      vertex_normal = vec3(u_transform * vec4(a_normal, 0));
      vertex_position = vec3(gl_Position);
  }
          )VERTEX",

          R"FRAGMENT(
  #version 330 core

  uniform vec2 u_mouse_position;

  in vec3 vertex_position;
  in vec3 vertex_normal;

  out vec4 out_color;

  void main()
  {

      vec3 color = vec3(0);

      vec3 surface_color = vec3(0.5, 0.5, 0.5);
      vec3 surface_position = vertex_position;
      vec3 surface_normal = normalize(vertex_normal);

      float ambient = 1;
      vec3 ambient_color = vec3(0.5, 0.5, 0.5);
      color += ambient * ambient_color * surface_color;

      vec3 light_direction = normalize(vec3(-1,-1, 1));
      vec3 to_light = -light_direction;
      vec3 light_color =  vec3(0.4, 0.4, 0.4);

      float diffuse_k = 1;
      float diffuse_intensity = max(0, dot(to_light, surface_normal));
      color += diffuse_k * diffuse_intensity * light_color * surface_color;

      vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
      vec3 halfway_dir = normalize(view_dir + to_light);
      float specular_k = 1;
      float shininess = 64;
      float specular_intensity = max(0, dot(halfway_dir, surface_normal));
      color += specular_k * pow(specular_intensity, shininess) * light_color;

      out_color = vec4(color, 1);
  }
          )FRAGMENT");
    
    
    GLuint program_forth_scene = CreateProgramFromSources(
          R"VERTEX(
  #version 330 core

  layout(location = 0) in vec3 a_position;
  layout(location = 1) in vec3 a_normal;

  uniform mat4 u_transform;

  out vec3 vertex_position;
  out vec3 vertex_normal;

  void main()
  {
      gl_Position = u_transform * vec4(a_position, 1);
      vertex_normal = vec3(u_transform * vec4(a_normal, 0));
      vertex_position = vec3(gl_Position);
  }
          )VERTEX",

          R"FRAGMENT(
  #version 330 core

  uniform vec2 u_mouse_position;
  uniform vec3 u_color;
  uniform float u_brightness;

  in vec3 vertex_position;
  in vec3 vertex_normal;

  out vec4 out_color;

  void main()
  {

      vec3 color = vec3(0);

      vec3 surface_color = u_color;
      vec3 surface_position = vertex_position;
      vec3 surface_normal = normalize(vertex_normal);

      float ambient = 1;
      vec3 ambient_color = vec3(0.5, 0.5, 0.5);
      color += ambient * ambient_color * surface_color;


      vec3 light_direction = normalize(vec3(-1,-1, 1));
      vec3 to_light = -light_direction;
      vec3 light_color =  vec3(0.4, 0.4, 0.4);
                                                          
      vec3 light_position = vec3(u_mouse_position, -1);
      vec3 to_light2 = normalize(light_position - vertex_position);
      vec3 light_color2 =  vec3(0.5, 0.5, 0.5);
                                                          

      float diffuse_k = 1;
      float diffuse_intensity = max(0, dot(to_light, surface_normal));
      color += diffuse_k * diffuse_intensity * light_color * surface_color;

      float diffuse_intensity2 = max(0, dot(to_light2, surface_normal));
      color += diffuse_k * diffuse_intensity2 * light_color2 * surface_color;
                                                          
                                                          
      vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
      vec3 halfway_dir = normalize(view_dir + to_light);
      float specular_k = 1;
      float shininess = u_brightness;
      float specular_intensity = max(0, dot(halfway_dir, surface_normal));
      color += specular_k * pow(specular_intensity, shininess) * light_color;

    
      vec3 halfway_dir2 = normalize(view_dir + to_light2);
      float specular_intensity2 = max(0, dot(halfway_dir2, surface_normal));
      color += specular_k * pow(specular_intensity2, shininess) * light_color2;
                                                          
      out_color = vec4(color, 1);
  }
          )FRAGMENT");
    
    GLuint program_fifth_scene = CreateProgramFromSources(
          R"VERTEX(
  #version 330 core

  layout(location = 0) in vec3 a_position;
  layout(location = 1) in vec3 a_normal;

  uniform mat4 u_transform;

  out vec3 vertex_position;
  out vec3 vertex_normal;

  void main()
  {
      gl_Position = u_transform * vec4(a_position, 1);
      vertex_normal = vec3(u_transform * vec4(a_normal, 0));
      vertex_position = vec3(gl_Position);
  }
          )VERTEX",

          R"FRAGMENT(
  #version 330 core

  uniform vec2 u_mouse_position;
  uniform vec3 u_color;
  uniform float u_brightness;

  in vec3 vertex_position;
  in vec3 vertex_normal;

  out vec4 out_color;

  void main()
  {

      vec3 color = vec3(0);

      vec3 surface_color = u_color;
      vec3 surface_position = vertex_position;
      vec3 surface_normal = normalize(vertex_normal);

      float ambient = 1;
      vec3 ambient_color = vec3(0.5, 0.5, 0.5);
      color += ambient * ambient_color * surface_color;

      vec3 light_direction = normalize(vec3(-1,-1, 1));
      vec3 to_light = -light_direction;
      vec3 light_color =  vec3(0.4, 0.4, 0.4);


      float diffuse_k = 1;
      float diffuse_intensity = max(0, dot(to_light, surface_normal));
      color += diffuse_k * diffuse_intensity * light_color * surface_color;

      vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
      vec3 halfway_dir = normalize(view_dir + to_light);
      float specular_k = 1;
      float shininess = u_brightness;
      float specular_intensity = max(0, dot(halfway_dir, surface_normal));
      color += specular_k * pow(specular_intensity, shininess) * light_color;

      out_color = vec4(color, 1);
  }
          )FRAGMENT");

    GLuint program_sixth_scene = CreateProgramFromSources(
        R"VERTEX(
  #version 330 core

  layout(location = 0) in vec3 a_position;
  layout(location = 1) in vec3 a_normal;

  uniform mat4 u_transform;

  out vec3 vertex_position;
  out vec3 vertex_normal;

  void main()
  {
      gl_Position = u_transform * vec4(a_position, 1);
      vertex_normal = vec3(u_transform * vec4(a_normal, 0));
      vertex_position = vec3(gl_Position);
  }
          )VERTEX",

        R"FRAGMENT(
  #version 330 core

  uniform vec2 u_mouse_position;
  uniform vec3 u_color;
  uniform float u_brightness;

  in vec3 vertex_position;
  in vec3 vertex_normal;

  out vec4 out_color;

  void main()
  {

      vec3 color = vertex_normal;

      vec3 surface_color = vertex_normal;
      vec3 surface_position = vertex_position;
      vec3 surface_normal = normalize(vertex_normal);

      float ambient = 1;
      vec3 ambient_color = vertex_normal;
      color += ambient * ambient_color * surface_color;


      vec3 light_direction = normalize(vec3(-1,-1, 1));
      vec3 to_light = -light_direction;
      vec3 light_color =  vec3(1, 1, 1);
                                                          
      vec3 light_position = vec3(u_mouse_position, -1);
      vec3 to_light2 = normalize(light_position - vertex_position);
      vec3 light_color2 =  vec3(1, 1, 1);
                                                          

      float diffuse_k = 1;
      float diffuse_intensity = max(0, dot(to_light, surface_normal));
      color += diffuse_k * diffuse_intensity * light_color * surface_color;

      float diffuse_intensity2 = max(0, dot(to_light2, surface_normal));
      color += diffuse_k * diffuse_intensity2 * light_color2 * surface_color;
                                                          
                                                          
      vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
      vec3 halfway_dir = normalize(view_dir + to_light);
      float specular_k = 1;
      float shininess = u_brightness;
      float specular_intensity = max(0, dot(halfway_dir, surface_normal));
      color += specular_k * pow(specular_intensity, shininess) * light_color;

    
      vec3 halfway_dir2 = normalize(view_dir + to_light2);
      float specular_intensity2 = max(0, dot(halfway_dir2, surface_normal));
      color += specular_k * pow(specular_intensity2, shininess) * light_color2;
                                                          
      out_color = vec4(color, 1);
  }
          )FRAGMENT");

    if (program_first_scene == NULL || program_second_scene == NULL || program_third_scene == NULL || program_forth_scene == NULL || program_fifth_scene == NULL || program_sixth_scene == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glUseProgram(program_first_scene);
    int mode = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate mouse position
        auto mouse_position = Globals.mouse_position / glm::dvec2(Globals.screen_dimensions);
        mouse_position.y = 1. - mouse_position.y;
        mouse_position = mouse_position * 2. - 1.;

        
        if(glfwGetKey(window, GLFW_KEY_Q)){
            mode = 0;
        }
        else if(glfwGetKey(window, GLFW_KEY_W)){
            mode = 1;
        }
        else if(glfwGetKey(window, GLFW_KEY_E)){
            mode = 2;
        }
        else if(glfwGetKey(window, GLFW_KEY_R)){
            mode = 3;
        }
        else if(glfwGetKey(window, GLFW_KEY_T)){
            mode = 4;
        }
        else if(glfwGetKey(window, GLFW_KEY_Y)){
            mode = 5;
        }
        
        if(mode == 0)
        { //program_first_scene
            auto mouse_location = glGetUniformLocation(program_first_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_first_scene, "u_transform");
            glUseProgram(program_first_scene);
            glm::mat4 transform;

            // Draw
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBindVertexArray(donutVAO.id);
            transform = glm::translate(glm::vec3(0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(-0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(cubeVAO.id);
            transform = glm::translate(glm::vec3(0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, cubeVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            
            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(-0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
        else if(mode == 1)
        { //program_second_scene
            auto mouse_location = glGetUniformLocation(program_second_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_second_scene, "u_transform");
            glUseProgram(program_second_scene);
            glm::mat4 transform;

            // Draw
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBindVertexArray(donutVAO.id);
            transform = glm::translate(glm::vec3(0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(-0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(cubeVAO.id);
            transform = glm::translate(glm::vec3(0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, cubeVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            
            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(-0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        }
        else if(mode == 2)
        { //program_third_scene
            auto mouse_location = glGetUniformLocation(program_third_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_third_scene, "u_transform");
            glUseProgram(program_third_scene);
            glm::mat4 transform;

            // Draw
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBindVertexArray(donutVAO.id);
            transform = glm::translate(glm::vec3(0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(-0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(cubeVAO.id);
            transform = glm::translate(glm::vec3(0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, cubeVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            
            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(-0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        }
        else if(mode == 3)
        { // program_forth_scene
            auto mouse_location = glGetUniformLocation(program_forth_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_forth_scene, "u_transform");
            auto color_location = glGetUniformLocation(program_forth_scene, "u_color");
            auto brightness_location = glGetUniformLocation(program_forth_scene, "u_brightness");
            
            glUniform2fv(mouse_location, 1, glm::value_ptr(glm::vec2(mouse_position)));
            glUseProgram(program_forth_scene);
            glm::mat4 transform;

            // Draw
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBindVertexArray(donutVAO.id);
            transform = glm::translate(glm::vec3(0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1,0,0)));
            glUniform1f(brightness_location, 32);
            glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(-0.5, 0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(0.5,0.5,0.5)));
            glUniform1f(brightness_location, 128);
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(cubeVAO.id);
            transform = glm::translate(glm::vec3(0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(0,0,1)));
            glUniform1f(brightness_location, 256);
            glDrawElements(GL_TRIANGLES, cubeVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            
            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(-0.5, -0.5, 0));
            transform = glm::scale(transform, glm::vec3(0.45));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(0,1,0)));
            glUniform1f(brightness_location, 256);
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        }
        else if(mode == 4)
        { //program_fifth_scene
            auto mouse_location = glGetUniformLocation(program_fifth_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_fifth_scene, "u_transform");
            auto color_location = glGetUniformLocation(program_fifth_scene, "u_color");
            auto brightness_location = glGetUniformLocation(program_fifth_scene, "u_brightness");
            
            glUniform2fv(mouse_location, 1, glm::value_ptr(glm::vec2(mouse_position)));
            glUseProgram(program_fifth_scene);
            glm::mat4 transform;

            // Draw
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        
            glBindVertexArray(sphereVAO.id);
            glm::dvec2 chasing_pos;
            chasing_pos = glm::mix(mouse_position, chasing_pos, 0.99);
            transform = glm::translate(glm::vec3(chasing_pos.x,chasing_pos.y,0));
            transform = glm::scale(transform, glm::vec3(0.3));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(0.5,0.5,0.5)));
            glUniform1f(brightness_location, 128);
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
            
            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(mouse_position.x, mouse_position.y, 0));
            transform = glm::scale(transform, glm::vec3(0.3));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 10), glm::vec3(1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            if(glm::distance(mouse_position,chasing_pos)<0.6){
                glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1,0,0)));
            }else{
                glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(0,1,0)));
            }
            glUniform1f(brightness_location, 128);
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        }
        else if(mode == 5)
        {   //program_sixth_scene
            auto mouse_location = glGetUniformLocation(program_sixth_scene, "u_mouse_position");
            auto transform_location = glGetUniformLocation(program_sixth_scene, "u_transform");
            auto color_location = glGetUniformLocation(program_sixth_scene, "u_color");
            auto brightness_location = glGetUniformLocation(program_sixth_scene, "u_brightness");

            glUniform2fv(mouse_location, 1, glm::value_ptr(glm::vec2(mouse_position)));
            glUseProgram(program_sixth_scene);
            glm::mat4 transform;

            // Draw

            glBindVertexArray(sphereVAO.id);
            transform = glm::translate(glm::vec3(0, 0, 0));
            transform = glm::scale(transform, glm::vec3(0.05));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 600), glm::vec3(1, 0, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
            glUniform1f(brightness_location, 5);
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(0, 0, 0));
            transform = glm::scale(transform, glm::vec3(0.15));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 250), glm::vec3(1, 0, 1));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
            glUniform1f(brightness_location, 32);
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(0, 0, 0));
            transform = glm::scale(transform, glm::vec3(0.35));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 150), glm::vec3(-1, 0, -1));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
            glUniform1f(brightness_location, 64);
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);

            glBindVertexArray(torusVAO.id);
            transform = glm::translate(glm::vec3(0, 0, 0));
            transform = glm::scale(transform, glm::vec3(1));
            transform = transform * glm::rotate(glm::radians(float(glfwGetTime()) * 50), glm::vec3(-1, 1, 0));
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(transform));
            glUniform3fv(color_location, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
            glUniform1f(brightness_location, 128);
            glDrawElements(GL_TRIANGLES, torusVAO.element_array_count, GL_UNSIGNED_INT, NULL);
            
        }

//        glUniform2fv(mouse_location, 1, glm::value_ptr(glm::vec2(mouse_position)));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
