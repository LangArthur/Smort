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

#include <shader/Shader.hpp>
#include <shader/ShaderLinker.hpp>

constexpr auto WINDOW_HEIGHT = 480;
constexpr auto WINDOW_WIDTH = 640;

GLuint setUpShader() {
    Shader vertexShader (GL_VERTEX_SHADER, "../GLToolbox/shaders/SimpleVertexShader.vert");
    Shader fragmentShader (GL_FRAGMENT_SHADER, "../GLToolbox/shaders/SimpleFragmentShader.frag");
    ShaderLinker linker({
        vertexShader,
        fragmentShader,
    });
    return (linker.ready() ? linker.id() : 0);
}

void instantiateScene() {
    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

GLFWwindow* init(int argc, char **argv) {
    GLFWwindow* window;
    // init glfw
    if (!glfwInit()) {
        std::cerr << "Failed to instantiate glfw\n";
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
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
    glm::vec4 vec4;

    GLuint shaderId = setUpShader();
    if (shaderId == 0) {
        std::cerr << "Cannot setup shaders" << std::endl;
        return clear(1);
    }
    instantiateScene();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear (GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    return clear(0);
}