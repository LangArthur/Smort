/**
 * @file TestScene.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief implementation of the TestScene object
 * @date 2022-11-19
 */

#include "utils/TestScene.hpp"

TestScene::TestScene(const int winWidth, const int winHeight)
    : m_winWidth(winWidth), m_winHeight(winHeight)
{

}

TestScene::~TestScene()
{
    glfwTerminate();
}

// TODO: move this into the TestScene object
void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


bool TestScene::init()
{
    // init glfw
    if (!glfwInit())
    {
        std::cerr << "Failed to instantiate glfw\n";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windows = glfwCreateWindow(m_winWidth, m_winHeight, m_winTitle.c_str(), NULL, NULL);
    if (!m_windows)
    {
        std::cerr << "Error: cannot instantiate window." << std::endl;
        return false;
    }

    glViewport(0, 0, m_winWidth, m_winHeight);
    glfwMakeContextCurrent(m_windows);
    // setup glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Cannot init glew library: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    glfwSetFramebufferSizeCallback(m_windows, frameBufferSizeCallback);
    m_isInit = true;
    return true;
}

bool TestScene::setUpShader(const char *vertexShaderPath, const char *fragShaderPath) {
    Shader vertexShader (GL_VERTEX_SHADER, vertexShaderPath);
    Shader fragmentShader (GL_FRAGMENT_SHADER, fragShaderPath);
    ShaderProgram linker({
        vertexShader,
        fragmentShader,
    });
    m_shaderId = linker.id();
    return linker.ready();
}

void TestScene::processInput() {
    if (glfwGetKey(m_windows, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_windows, true);
    }
    if (glfwGetKey(m_windows, GLFW_KEY_T) == GLFW_PRESS)
    {
        m_lineMode = !m_lineMode;
        glPolygonMode(GL_FRONT_AND_BACK, m_lineMode ? GL_LINE : GL_FILL);
    }
}

void TestScene::start() {
    /* Create a windowed mode window and its OpenGL context */
    if (!m_isInit || !m_windows)
    {
        throw std::runtime_error("Cannot start the scene");
    }
    glEnable(GL_DEPTH_TEST);

    if (m_shaderId == 0)
    {
        throw std::runtime_error("Shaders are not set-up");
    }
    // time variables
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
    while (!glfwWindowShouldClose(m_windows))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glUseProgram(m_shaderId);

        drawCallBack(m_shaderId, deltaTime);
        /* Swap front and back buffers */
        glfwSwapBuffers(m_windows);

        /* Poll for and process events */
        glfwPollEvents();
        processInput();
        inputCallBack(m_windows);

        /* process needed data */
        processCallBack(deltaTime);
    }
}
