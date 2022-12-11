/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-06-20
 */

#include <GL/glew.h>
#include <GL/glut.h>
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

#include "utils/TestScene.hpp"
#include "movement/movement.hpp"

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;

    Vertex(glm::vec3 vertexPos, glm::vec3 vertexColor)
        : pos(vertexPos), color(vertexColor)
    { }
};

constexpr auto WINDOW_HEIGHT = 480.0f;
constexpr auto WINDOW_WIDTH = 640.0f;

GLuint instantiateScene()
{
    GLuint VAO; // Vertex Array Object0
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

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

int main(int argc, char *argv[])
{
    smort::movement::Kinetic player {
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.0f,
    };
    smort::movement::Kinetic enemy {
        glm::vec3(-0.8f, 0.8f, 0.0f),
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.0f,
    };

    smort::movement::Steering playerSteering {
        {0.0f, 0.0f, 0.0f}, 0.0f,
    };
    smort::movement::Steering enemySteering {
        {0.0f, 0.0f, 0.0f}, 0.0f,
    };

    smort::movement::Flee flee(enemy, player);
    smort::movement::Seek seek(enemy, player);

    float maxSpeed = 1.0f;
    bool useFlee = false;

    TestScene scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    scene.init();
    if (!scene.setUpShader("../examples/movement/shaders/SimpleVertexShader.vert", "../examples/movement/shaders/SimpleFragmentShader.frag"))
    {
        return (1);
    }

    auto VAO = instantiateScene();

    /* view and projection matrices */
    glm::mat4 view = glm::mat4(1.0f);
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -3.0f);
    view = glm::translate(view, camPos);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    scene.drawCallBack = [&](GLuint shaderId, float deltaTime){
        glBindVertexArray(VAO);
        // draw player
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, player.position);
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
            model = glm::translate(model, enemy.position);
            model = glm::rotate(model, glm::radians(enemy.rotation), glm::vec3(0.0f, 0.1f, 0.0f));

            unsigned int transformLoc = glGetUniformLocation(shaderId, "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
            transformLoc = glGetUniformLocation(shaderId, "view");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
            transformLoc = glGetUniformLocation(shaderId, "projection");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }        
    };
    scene.inputCallBack = [&](GLFWwindow *window){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            playerSteering.linear.y += maxSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            playerSteering.linear.y -= maxSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            playerSteering.linear.x -= maxSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            playerSteering.linear.x += maxSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            maxSpeed += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            maxSpeed -= 0.01;
            maxSpeed = maxSpeed * (maxSpeed > 0);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            useFlee = !useFlee;
        }
    };

    scene.processCallBack = [&](float deltaTime) {
        // reduce velocity of player and enemy
        player.velocity *= 0.99f;
        enemy.velocity *= 0.99f;

        if (useFlee)
        {
            enemySteering = flee.getSteering();
        }
        else
        {
            enemySteering = seek.getSteering();
        }

        enemy.update(enemySteering, deltaTime);
        player.update(playerSteering, deltaTime);
        // reset steering for next frame
        playerSteering = {
            {0.0f, 0.0f, 0.0f}, 0.0f,
        };
        enemySteering = {
            {0.0f, 0.0f, 0.0f}, 0.0f,
        };
    };
    scene.start();
    return 0;
}