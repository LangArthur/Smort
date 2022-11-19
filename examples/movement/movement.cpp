/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-06-20
 */

#include <GL/glew.h>
#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// debugging mat
#include <glm/gtx/string_cast.hpp>

#include <shader/Shader.hpp>
#include <shader/ShaderProgram.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;

    Vertex(glm::vec3 vertexPos, glm::vec3 vertexColor)
        : pos(vertexPos), color(vertexColor)
    { }
};

struct GameObject {
    glm::vec2 pos {0, 0};
    float rotation {0.0f};
    float speed {0.3f};
};

// global variable (to simplify example)
constexpr auto WINDOW_HEIGHT = 480.0f;
constexpr auto WINDOW_WIDTH = 640.0f;
bool lineMode = false;

GameObject player;
GameObject enemy;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        lineMode = !lineMode;
        glPolygonMode(GL_FRONT_AND_BACK, lineMode ? GL_LINE : GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.pos.y += player.speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.pos.y -= player.speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.pos.x -= player.speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.pos.x += player.speed * deltaTime;
}

GLuint setUpShader()
{
    Shader vertexShader (GL_VERTEX_SHADER, "../examples/movement/shaders/SimpleVertexShader.vert");
    Shader fragmentShader (GL_FRAGMENT_SHADER, "../examples/movement/shaders/SimpleFragmentShader.frag");
    ShaderProgram linker({
        vertexShader,
        fragmentShader,
    });
    return (linker.ready() ? linker.id() : 0);
}

GLuint instantiateScene()
{
    GLuint VAO; // Vertex Array Object0
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    // arrow object
    // const Vertex vertices[] = {
    //     { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.01f} },
    //     { {-0.05f, 0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
    //     { {0.2f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.01f} },
    //     { {-0.05f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
    // };
    const Vertex vertices[] = {
        { {0.1f, 0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
        { {0.1f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
        { {-0.1f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
        { {-0.1f, 0.1f, 0.0f}, {1.0f, 1.0f, 1.01f} },
    };
    unsigned int indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3, // second triangle
    };

	GLuint VBO; // Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    GLuint EBO; // element buffer object
    glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);  
    return VAO;
}

GLFWwindow* init(int argc, char **argv) {
    GLFWwindow* window;
    // init glfw
    if (!glfwInit())
    {
        std::cerr << "Failed to instantiate glfw\n";
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: cannot instantiate window." << std::endl;
        return nullptr;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwMakeContextCurrent(window);
    // setup glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Cannot init glew library: " << glewGetErrorString(err) << std::endl;
        return nullptr;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    return window;
    
}

int clear(int status) {
    glfwTerminate();
    return status;
}

int main(int argc, char *argv[])
{
    GLFWwindow* window = init(argc, argv);
    /* Create a windowed mode window and its OpenGL context */
    if (!window)
    {
        return clear(1);
    }
    glEnable(GL_DEPTH_TEST);

    GLuint shaderId = setUpShader();
    if (shaderId == 0)
    {
        std::cerr << "Cannot setup shaders" << std::endl;
        return clear(1);
    }
    auto VAO = instantiateScene();

    // time variables
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glm::mat4 view = glm::mat4(1.0f);
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -3.0f);
    view = glm::translate(view, camPos);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    enemy.pos = {-0.5f, 0.5f};

    glClearColor(0,1,0,0);
    while (!glfwWindowShouldClose(window))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glUseProgram(shaderId);

        // draw player
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(player.pos, 1.0));
            model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 0.1f, 0.0f));

            unsigned int transformLoc = glGetUniformLocation(shaderId, "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
            transformLoc = glGetUniformLocation(shaderId, "view");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
            transformLoc = glGetUniformLocation(shaderId, "projection");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // draw enemy
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(enemy.pos, 1.0));
            model = glm::rotate(model, glm::radians(enemy.rotation), glm::vec3(0.0f, 0.1f, 0.0f));

            unsigned int transformLoc = glGetUniformLocation(shaderId, "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
            transformLoc = glGetUniformLocation(shaderId, "view");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
            transformLoc = glGetUniformLocation(shaderId, "projection");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(VAO);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        processInput(window, deltaTime);
        /* Poll for and process events */
        glfwPollEvents();
    }
    return clear(0);
}


//         // MVP matrix
//         glm::mat4 model = glm::mat4(1.0f);
//         // model = glm::translate(model, cubePositions[i]);
//         // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3((1.5f + i * 0.3), (0.3f + i * 0.5), 0.0f));  

//         unsigned int transformLoc = glGetUniformLocation(shader.id(), "model");
//         glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
//         transformLoc = glGetUniformLocation(shader.id(), "view");
//         glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
//         transformLoc = glGetUniformLocation(shader.id(), "projection");
//         glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         /* Swap front and back buffers */
//         glfwSwapBuffers(window);

//         // processInput(window, cam, deltaTime);
//         /* Poll for and process events */
//         glfwPollEvents();
//     }
//     return clear(0);
// }