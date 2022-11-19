/**
 * @file TestScene.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief general purpose test scene
 * @date 2022-11-19
 */

#pragma once

#include <string>
#include <iostream>
#include <functional>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <shader/Shader.hpp>
#include <shader/ShaderProgram.hpp>

class TestScene
{
    public:
        TestScene(const int winWidth, const int winHeight);
        ~TestScene();

        inline GLFWwindow *window() const { return m_windows; };
        inline GLuint shaderId() const { return m_shaderId; };

        bool init();
        bool setUpShader(const char *vertexShaderPath, const char *fragShaderPath);
        void start();
        void processInput();

        std::function<void(GLuint, float)> drawCallBack;
        std::function<void(float)> processCallBack;
        std::function<void(GLFWwindow *)> inputCallBack;
    private:
        GLFWwindow* m_windows;
        GLuint m_shaderId {0};
        GLuint m_VAO;

        std::string m_winTitle {"Test scene"};
        int m_winWidth {0};
        int m_winHeight {0};
        bool m_isInit {false};
        bool m_lineMode {false};
};