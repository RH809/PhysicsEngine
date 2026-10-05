#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "object.h"
#include "sphere.h"
#include "object_manager.h"

const char* vertexShaderSource =
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
//"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"    color = aColor;\n"
"}\0";

const char* fragmentShaderSource =
"#version 460 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(color, 1.0);\n"
"}\0";

#define WINDOW_WIDTH (1200)
#define WINDOW_HEIGHT (900)

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*, float);
void mouse_callback(GLFWwindow* window, double, double);
//void processInput(GLFWwindow*, float&, float&, float&, double&, float&, float);

bool inFocus = true;
bool firstMouse = true;
glm::vec3 cameraPos;
float movementMultiplier = 3.0f;
float lastMouseX = WINDOW_WIDTH / 2.0f;
float lastMouseY = WINDOW_HEIGHT / 2.0f;
float mouseSensitivity = 0.10f;
float cameraYaw = 0.0f; 
float cameraPitch = 0.0f;

int main() {
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // OpenGL 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create glfw window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // set callback
    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // create VBO
    //unsigned int VBO;
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check vertex shader compile status
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check fragment shader compile status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // attach shaders to shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check shader program link status
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    glUseProgram(shaderProgram);
    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // create VAO
    //unsigned int VAO;
    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);

    // create EBO
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // set vertex data interpretation
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");


    // projection uniform will not change
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

    float boxVertices[] = {
        // position              // color
        -10.0f,  0.0f, -10.0f,   1.0f, 1.0f, 1.0f, // 0
         10.0f,  0.0f, -10.0f,   1.0f, 1.0f, 1.0f, // 1
         10.0f, 10.0f, -10.0f,   1.0f, 1.0f, 1.0f, // 2
        -10.0f, 10.0f, -10.0f,   1.0f, 1.0f, 1.0f, // 3

        -10.0f,  0.0f,  10.0f,   1.0f, 1.0f, 1.0f, // 4
         10.0f,  0.0f,  10.0f,   1.0f, 1.0f, 1.0f, // 5
         10.0f, 10.0f,  10.0f,   1.0f, 1.0f, 1.0f, // 6
        -10.0f, 10.0f,  10.0f,   1.0f, 1.0f, 1.0f  // 7
    };

    unsigned int boxIndices[] = {
        // bottom
        0, 1,
        1, 5,
        5, 4,
        4, 0,

        // top
        3, 2,
        2, 6,
        6, 7,
        7, 3,

        // vertical edges
        0, 3,
        1, 2,
        4, 7,
        5, 6
    };

    ObjectManager *manager = new ObjectManager();

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
    float prevTime = glfwGetTime();
	cameraPos = glm::vec3(5.0f, 20.0f, 20.0f);
    glm::vec3 direction = glm::normalize(glm::vec3(0.0f) - cameraPos);
    cameraYaw = glm::degrees(atan2(direction.z, direction.x));
    cameraPitch = glm::degrees(asin(direction.y));

    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();
        float deltaTime = time - prevTime;
        // input
        processInput(window, deltaTime);
        
		direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
		direction.y = sin(glm::radians(cameraPitch));
		direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        direction = glm::normalize(direction);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::lookAt(
            cameraPos, 
            cameraPos + direction,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        for (const auto& object : manager->getObjects()) {
            // Create model based on object's position and rotation
            glm::mat4 model = glm::translate(glm::mat4(1.0f), object->getPos()) * glm::mat4_cast(object->getRotation());

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(object->getVAO());
            glDrawElements(
                GL_TRIANGLES,
                static_cast<GLsizei>(object->getIndices().size()),
                GL_UNSIGNED_INT,
                nullptr
            );
        }
        glBindVertexArray(0);


        // check and call events + swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
        prevTime = time;
    }
    glfwTerminate();
    return 0;
}

/**
* Callback for window resizing
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        inFocus = false;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        inFocus = true;
    }
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += movementMultiplier * deltaTime * glm::normalize(glm::vec3(cos(glm::radians(cameraYaw)), 0.0f, sin(glm::radians(cameraYaw))));
	}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= movementMultiplier * deltaTime * glm::normalize(glm::vec3(cos(glm::radians(cameraYaw)), 0.0f, sin(glm::radians(cameraYaw))));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += movementMultiplier * deltaTime * glm::normalize(glm::vec3(cos(glm::radians(cameraYaw + 90.0f)), 0.0f, sin(glm::radians(cameraYaw + 90.0f))));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= movementMultiplier * deltaTime * glm::normalize(glm::vec3(cos(glm::radians(cameraYaw + 90.0f)), 0.0f, sin(glm::radians(cameraYaw + 90.0f))));
    }
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cameraPos += movementMultiplier * deltaTime * glm::vec3(0.0f, 1.0f, 0.0f);
	}
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos -= movementMultiplier * deltaTime * glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

void mouse_callback(GLFWwindow* window, double x, double y) {
    if (!inFocus) {
        firstMouse = true;
        return;
    }
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }
    float xOffset = (x - lastMouseX) * mouseSensitivity;
    float yOffset = (lastMouseY - y) * mouseSensitivity;

    lastMouseX = x;
    lastMouseY = y;

    cameraYaw += xOffset;
    cameraPitch += yOffset;

	cameraPitch = glm::clamp(cameraPitch, -89.0f, 89.0f);
}