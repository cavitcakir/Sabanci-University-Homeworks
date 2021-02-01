static struct
{
    glm::dvec2 mouse_position;
    glm::ivec2 screen_dimensions = glm::ivec2(600, 600);
} Globals;

/* GLFW Callback functions */
static void ErrorCallback(int error, const char *description)
{
    std::cerr << "Error: " << description << std::endl;
}

static void CursorPositionCallback(GLFWwindow *window, double x, double y)
{
    Globals.mouse_position.x = x;
    Globals.mouse_position.y = y;
}

static void WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    Globals.screen_dimensions.x = width;
    Globals.screen_dimensions.y = height;

    glViewport(0, 0, width, height);
}
static void rotate_around_z(double x, double y, double z, double user_rover_dx)
{
    glm::vec4 old4(x, y, z, 1);
    auto old = glm::rotate(glm::radians(float(user_rover_dx)), glm::vec3(0, -1, 0)) * old4;
}

glm::mat4 turn_wheels(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_A))
    {
        auto transform = glm::rotate(glm::radians(float(glfwGetTime()) * 200), glm::vec3(1, 0, 0));
        transform *= glm::rotate(glm::radians(float(90)), glm::vec3(0, 0, 1));
        return transform;
    }
    else if (glfwGetKey(window, GLFW_KEY_D))
    {
        auto transform = glm::rotate(glm::radians(float(glfwGetTime()) * 200), glm::vec3(-1, 0, 0));
        transform *= glm::rotate(glm::radians(float(90)), glm::vec3(0, 0, -1));
        return transform;
    }
    else if (glfwGetKey(window, GLFW_KEY_W))
    {
        auto transform = glm::rotate(glm::radians(float(glfwGetTime()) * 200), glm::vec3(0, -1, 0));
        return transform;
    }
    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        auto transform = glm::rotate(glm::radians(float(glfwGetTime()) * 200), glm::vec3(0, 1, 0));
        return transform;
    }
    else{
        return glm::mat4(1.0);
    }
}
void activate_program(GLuint program,GLuint texture){
    
    glUseProgram(program);

    auto texture_locationwheel = glGetUniformLocation(program, "u_texture");
    glUniform1i(texture_locationwheel, 0);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
}
GLuint create_texture(const char *filename){
    
    int x, y, n;
    unsigned char *texture_data = stbi_load(filename, &x, &y, &n, 0);
    if (texture_data == NULL)
    {
        std::cout << "Texture " << filename << " failed to load." << std::endl;
        std::cout << "Error: " << stbi_failure_reason() << std::endl;
    }
    else
    {
        std::cout << "Texture " << filename << " is loaded, X:" << x << " Y:" << y << " N:" << n << std::endl;
    }
    GLuint texture;
    glGenTextures(1, &texture);

    if (x * n % 4 != 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glGenerateMipmap(GL_TEXTURE_2D);

    if (x * n % 4 != 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    stbi_image_free(texture_data);
    return texture;
}
void create_rover_at(double user_rover_x, double user_rover_y, double user_rover_z, GLFWwindow *window, double user_rover_rot_x, double user_rover_rot_y, VAO cubeVAO, VAO donutVAO, GLint model_location,bool is_human, GLuint texturebody, GLuint texturewheel ,GLuint program)
{
    activate_program(program,texturebody);
    glm::mat4 transform;
    glBindVertexArray(cubeVAO.id);
    transform = glm::translate(glm::vec3(user_rover_x, user_rover_y, user_rover_z + 0.1));
    transform *= glm::rotate(glm::radians(float(user_rover_rot_x)), glm::vec3(0, -1, 0));
    transform *= glm::rotate(glm::radians(float(user_rover_rot_y)), glm::vec3(1, 0, 0));
    transform = glm::scale(transform, glm::vec3(.6, 0.4, .2));
    auto checkpoint = transform;
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, cubeVAO.element_array_count, GL_UNSIGNED_INT, NULL);

    activate_program(program,texturewheel);
    glBindVertexArray(donutVAO.id);
    transform = checkpoint;
    transform *= glm::translate(glm::vec3(0.25 * 1 / 0.6, 0.16 * 1 / 0.4, -0.15 * 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(1 / 0.6, 1 / 0.4, 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(.07));
    if (is_human)
        transform *= turn_wheels(window);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(donutVAO.id);
    transform = checkpoint;
    transform *= glm::translate(glm::vec3(-0.25 * 1 / 0.6, -0.16 * 1 / 0.4, -0.15 * 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(1 / 0.6, 1 / 0.4, 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(.07));
    if (is_human)
        transform *= turn_wheels(window);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(donutVAO.id);
    transform = checkpoint;
    transform *= glm::translate(glm::vec3(-0.25 * 1 / 0.6, 0.16 * 1 / 0.4, -0.15 * 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(1 / 0.6, 1 / 0.4, 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(.07));
    if (is_human)
        transform *= turn_wheels(window);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(donutVAO.id);
    transform = checkpoint;
    transform *= glm::translate(glm::vec3(0.25 * 1 / 0.6, -0.16 * 1 / 0.4, -0.15 * 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(1 / 0.6, 1 / 0.4, 1 / 0.2));
    transform = glm::scale(transform, glm::vec3(.07));
    if(is_human)
        transform *= turn_wheels(window);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES, donutVAO.element_array_count, GL_UNSIGNED_INT, NULL);
}

bool CheckCollision(glm::dvec3 &one, glm::dvec3 &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.x + 0.7 >= two.x &&
                      two.x + 0.7 >= one.x;
    // collision y-axis?
    bool collisionY = one.y + 0.4 >= two.y &&
                      two.y + 0.4 >= one.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

int main(void)
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
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(
        Globals.screen_dimensions.x, Globals.screen_dimensions.y,
        "Hello Realtime Computer Graphics", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
    glClearColor(0, 0, 0, 0.4f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Creating OpenGL objects */
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<GLuint> indices;

    GenerateParametricShapeFrom2D(positions, normals, uvs, indices, ParametricHalfCircle, 256, 256);
    VAO sphereVAO(positions, normals, uvs, indices);

    positions.clear();
    normals.clear();
    indices.clear();
    uvs.clear();

    GenerateParametricShapeFrom2D(positions, normals, uvs, indices, ParametricCircle, 16, 16);
    VAO donutVAO(positions, normals, uvs, indices);

    VAO quadVAO(
        {{-1, -1, 0},
         {+1, -1, 0},
         {+1, +1, 0},
         {-1, +1, 0}},
        {{0, 0, -1},
         {0, 0, -1},
         {0, 0, -1},
         {0, 0, -1}},
        {{0, 0},
         {1, 0},
         {1, 1},
         {0, 1}},
        {0, 1, 2,
         0, 2, 3});

    VAO cubeVAO(
        {{-0.5f, -0.5f, -0.5f},
         {0.5f, -0.5f, -0.5f},
         {0.5f, 0.5f, -0.5f},
         {0.5f, 0.5f, -0.5f},
         {-0.5f, 0.5f, -0.5f},
         {-0.5f, -0.5f, -0.5f},
         {-0.5f, -0.5f, 0.5f},
         {0.5f, -0.5f, 0.5f},
         {0.5f, 0.5f, 0.5f},
         {0.5f, 0.5f, 0.5f},
         {-0.5f, 0.5f, 0.5f},
         {-0.5f, -0.5f, 0.5f},
         {-0.5f, 0.5f, 0.5f},
         {-0.5f, 0.5f, -0.5f},
         {-0.5f, -0.5f, -0.5f},
         {-0.5f, -0.5f, -0.5f},
         {-0.5f, -0.5f, 0.5f},
         {-0.5f, 0.5f, 0.5f},
         {0.5f, 0.5f, 0.5f},
         {0.5f, 0.5f, -0.5f},
         {0.5f, -0.5f, -0.5f},
         {0.5f, -0.5f, -0.5f},
         {0.5f, -0.5f, 0.5f},
         {0.5f, 0.5f, 0.5f},
         {-0.5f, -0.5f, -0.5f},
         {0.5f, -0.5f, -0.5f},
         {0.5f, -0.5f, 0.5f},
         {0.5f, -0.5f, 0.5f},
         {-0.5f, -0.5f, 0.5f},
         {-0.5f, -0.5f, -0.5f},
         {-0.5f, 0.5f, -0.5f},
         {0.5f, 0.5f, -0.5f},
         {0.5f, 0.5f, 0.5f},
         {0.5f, 0.5f, 0.5f},
         {-0.5f, 0.5f, 0.5f},
         {-0.5f, 0.5f, -0.5f}},
        {{0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, -1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {-1.0f, 0.0f, 0.0f},
         {-1.0f, 0.0f, 0.0f},
         {-1.0f, 0.0f, 0.0f},
         {-1.0f, 0.0f, 0.0f},
         {-1.0f, 0.0f, 0.0f},
         {-1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, -1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f}},
        {
            // x   y
            {0.0, 1.0}, // 1  left                  First Strip
            {1.0, 1.0}, // 3
            {0.0, 0.0}, // 0
            {1.0, 0.0}, // 2
            {0.0, 1.0}, // 4  back
            {1.0, 1.0}, // 6
            {0.0, 0.0}, // 5  right
            {1.0, 0.0}  // 7
        },
        {0, 1, 2,
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
         33, 34, 35});

    //GLubyte texture_data[] = {
    //    0, 255, 0,                0, 0, 255,        0, 0,
    //    255, 255, 255,            255, 0, 0
    //};


    GLuint program = CreateProgramFromSources(
        R"VERTEX(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

uniform mat4 u_model;
uniform mat4 u_projection_view;

out vec4 world_space_position;
out vec3 world_space_normal;
out vec2 vertex_uv;

void main()
{
    world_space_position = u_model * vec4(a_position, 1);
    world_space_normal = vec3(u_model * vec4(a_normal, 0));
    vertex_uv = a_uv;
    gl_Position = u_projection_view * world_space_position;
}
        )VERTEX",

        R"FRAGMENT(
#version 330 core



uniform vec2 u_mouse_position;
uniform sampler2D u_texture;
uniform vec3 u_surface_color;

in vec4 world_space_position;
in vec3 world_space_normal;
in vec2 vertex_uv;

out vec4 out_color;

void main()
{
    vec3 color = vec3(0);

    vec3 surface_position = world_space_position.xyz;
    vec3 surface_normal = normalize(world_space_normal);
    vec2 surface_uv = vertex_uv;
    surface_uv.x *= 1;
    vec3 surface_color = texture(u_texture, surface_uv).rgb;

    vec3 ambient_color = vec3(0.7);
    color += ambient_color * surface_color;
                                              
    vec3 light_direction = normalize(vec3(-150, -20, 1008));
    vec3 to_light = -light_direction;

    vec3 light_color = vec3(0.3);

    float diffuse_intensity = max(0, dot(to_light, surface_normal));
    color += diffuse_intensity * light_color * surface_color;

    vec3 view_dir = vec3(0, 0, -1);    //    Because we are using an orthograpic projection, and because of the direction of the projection
    vec3 halfway_dir = normalize(view_dir + to_light);
    float shininess = 4;
    float specular_intensity = max(0, dot(halfway_dir, surface_normal));
    color += pow(specular_intensity, shininess) * light_color;

    out_color = vec4(color, 1);
}
        )FRAGMENT");
    GLuint texture = create_texture("Assets/image1.jpg");
    GLuint texture4 = create_texture("Assets/sun.jpg");
    GLuint texturewheel = create_texture("Assets/wheel.jpg");
    GLuint texturebody = create_texture("Assets/image2.jpg");
    
    
    
    
    
    
    if (program == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glUseProgram(program);

    auto texture_location = glGetUniformLocation(program, "u_texture");
    glUniform1i(texture_location, 0);

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // auto mouse_location = glGetUniformLocation(program, "u_mouse_position");
    // auto transform_location = glGetUniformLocation(program, "u_transform");
    auto mouse_location = glGetUniformLocation(program, "u_mouse_position");
    auto model_location = glGetUniformLocation(program, "u_model");
    auto projection_view_location = glGetUniformLocation(program, "u_projection_view");
    auto surface_color_location = glGetUniformLocation(program, "u_surface_color");

    auto user_rover_x = 0.0;
    auto user_rover_y = 0.0;
    auto user_rover_z = 1000.1;
    auto user_rover_rot_x = 0.0;
    auto user_rover_rot_y = 0.0;
    auto user_rover_dx = 0.0; // y etrafında dönme açısı
    auto user_rover_dy = 0.0; // x etrafında dönme açısı


    auto mars_origin = glm::vec3(0, 0, 0);
    auto mars_r = 1000;

    auto eye_x = user_rover_x + 6;
    auto eye_y = user_rover_y;
    auto eye_z = user_rover_z + 4;

    auto old_mouseposx = 0.0;
    auto old_mouseposy = 0.0;

    auto first_iteration = 2;
    auto collided = false;
    
    auto pos_sun_x =0.0;
    auto pos_sun_y =0.0;
    auto pos_sun_z =0.0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        
        user_rover_dx = 0.0;
        user_rover_dy = 0.0;

        if (!collided && glfwGetKey(window, GLFW_KEY_W))
        {
            // std::cout <<"W"<< "\n";
            user_rover_dx += 0.01;
            user_rover_rot_x += 0.01;
        }
        else if (!collided && glfwGetKey(window, GLFW_KEY_S))
        {
            // std::cout <<"S"<< "\n";
            user_rover_dx -= 0.01;
            user_rover_rot_x -= 0.01;
        }
        if (!collided && glfwGetKey(window, GLFW_KEY_A))
        {
            //std::cout <<"A"<< "\n";
            user_rover_dy += 0.01;
            user_rover_rot_y += 0.01;
        }
        else if (!collided && glfwGetKey(window, GLFW_KEY_D))
        {
            //std::cout <<"D"<< "\n";
            user_rover_dy -= 0.01;
            user_rover_rot_y -= 0.01;
        }
        else if (collided && glfwGetKey(window, GLFW_KEY_K))
        {
            collided = false;
            user_rover_dx += 0.1;
            user_rover_rot_x += 0.1;
        }

        rotate_around_z(user_rover_x, user_rover_y, user_rover_z, user_rover_dx);

        /* Render here */
        auto roty = glm::rotate(glm::radians(float(user_rover_dx)), glm::vec3(0, -1, 0));
        auto rotx = glm::rotate(glm::radians(float(user_rover_dy)), glm::vec3(1, 0, 0));
        auto newrot = rotx * roty * glm::vec4(user_rover_x, user_rover_y, user_rover_z, 1);

        user_rover_x = newrot.x;
        user_rover_y = newrot.y;
        user_rover_z = newrot.z;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate mouse position
        auto mouse_position = Globals.mouse_position;
        mouse_position /= glm::dvec2(Globals.screen_dimensions);
        mouse_position.y = 1. - mouse_position.y;
        mouse_position = mouse_position * 2. - 1.;

        glUniform2fv(mouse_location, 1, glm::value_ptr(glm::vec2(mouse_position)));

        // Draw
        glBindVertexArray(sphereVAO.id);

        auto r = 4.;

        std::cout << mouse_position.x << " " << mouse_position.y << "\n";


        // Camera
            if( (mouse_position.x * mouse_position.x) + ( mouse_position.y * mouse_position.y) < 4 ){
                old_mouseposx = mouse_position.x;
                old_mouseposy = mouse_position.y;
            }
        
            eye_x = cos(3.14 * old_mouseposx / 2.2) * 3;
            eye_y = sin(3.14 * old_mouseposx / 2.2) * 3;
            eye_z = cos((3.14 / 2) * old_mouseposy / 2.2) * 3 - 2;
            if (eye_z < 0.1)
            {
                eye_z = 0.1;
            }
            if(old_mouseposy > 1.25){
                old_mouseposy = 1.25;
            }
            if (old_mouseposy > 0)
            {
                eye_z = tan((3.14 / 2) * old_mouseposy / 2.2) * 3 + 1;
            }
            glm::vec4 old(eye_x, eye_y, eye_z, 1);
            // auto a = glm::translate(glm::vec3(user_rover_x, user_rover_y, user_rover_z)) * old;
            auto a = glm::translate(glm::vec3(user_rover_x, user_rover_y, user_rover_z)) *
                                    glm::rotate(glm::radians(float(user_rover_rot_y)), glm::vec3(1, 0, 0)) *
                                    glm::rotate(glm::radians(float(user_rover_rot_x)), glm::vec3(0, -1, 0)) * old;
            eye_x = a.x;
            eye_y = a.y;
            eye_z = a.z;
            auto eye = glm::vec3(eye_x, eye_y, eye_z);                         //glm::vec3(user_rover_x+6 , eye_y , user_rover_z+6);//// glm::vec3(user_rover_x+6, user_rover_y+6, user_rover_z+3);
            auto center = glm::vec3(user_rover_x, user_rover_y, user_rover_z); // look at -> arabamiz
            auto up = glm::vec3(user_rover_x, user_rover_y, user_rover_z);     // degisiiiir -> normal -> arabanin dicki -> ne de olsa o da dik
            auto view = glm::lookAt(
                eye, center, up);
            auto projection = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 1000.f);
            glUniformMatrix4fv(projection_view_location, 1, GL_FALSE, glm::value_ptr(projection * view));

        activate_program(program,texture);
        
        //mars
            glBindVertexArray(sphereVAO.id);
            glm::mat4 transform;
            //transform = glm::translate(mars_origin);
            transform = glm::scale( glm::vec3(1000));
            glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
            glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        
        
        
        
        
        
        

        //our rover
        std::cout <<"x:"<< user_rover_x <<"  y:"<<user_rover_y<<"  z:"<<user_rover_z << "\n";
            create_rover_at(user_rover_x, user_rover_y, user_rover_z, window, user_rover_rot_x, user_rover_rot_y, cubeVAO, donutVAO, model_location,true,texturebody,texturewheel,program);

        //enemy_rover1
            glm::dvec3 chasing_pos;
            if(first_iteration){
                chasing_pos = glm::vec3(user_rover_x-3, user_rover_y-3, user_rover_z);
                first_iteration--;
            }
            chasing_pos = glm::mix(glm::dvec3(user_rover_x, user_rover_y, user_rover_z), chasing_pos, 0.98);
            transform = glm::translate(glm::vec3(chasing_pos.x, chasing_pos.y, chasing_pos.z));

            create_rover_at(chasing_pos.x, chasing_pos.y, chasing_pos.z, window, user_rover_rot_x, user_rover_rot_y, cubeVAO, donutVAO, model_location,false,texturebody,texturewheel,program);

            glm::dvec3 temp;
            temp = glm::vec3(user_rover_x, user_rover_y, user_rover_z);

        //enemy_rover2
            glm::dvec3 chasing_pos2;
            if (first_iteration)
            {
                chasing_pos2 = glm::vec3(user_rover_x - 4, user_rover_y + 3, user_rover_z);
                first_iteration--;
            }
            chasing_pos2 = glm::mix(glm::dvec3(user_rover_x, user_rover_y, user_rover_z), chasing_pos2, 0.99);
            transform = glm::translate(glm::vec3(chasing_pos2.x, chasing_pos2.y, chasing_pos2.z));

            create_rover_at(chasing_pos2.x, chasing_pos2.y, chasing_pos2.z, window, user_rover_rot_x, user_rover_rot_y, cubeVAO, donutVAO, model_location,false,texturebody,texturewheel,program);
        
        
        activate_program(program,texture4);
        
        
        
        // gunes
        pos_sun_x = cos(3.14 * float(glfwGetTime()/40) / 2.2) * 1008;
        pos_sun_y = sin(3.14 * float(glfwGetTime()/40) / 2.2) * 1008;
        pos_sun_y = cos((3.14 / 2) * float(glfwGetTime()) / 2.2) * 3 - 2;
        glBindVertexArray(sphereVAO.id);
        transform = glm::translate(glm::vec3(pos_sun_x, pos_sun_y, 1018));
        transform = glm::scale(transform, glm::vec3(5));
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, sphereVAO.element_array_count, GL_UNSIGNED_INT, NULL);
        //CheckCollision
            if (CheckCollision(temp, chasing_pos) || CheckCollision(temp, chasing_pos2))
            {
                collided = true;
                std::cout << "CARPIYOK"<< "\n";
            }


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
    
    }

    glfwTerminate();
    return 0;
}