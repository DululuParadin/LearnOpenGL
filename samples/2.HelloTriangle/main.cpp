#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

constexpr const char* const vertexShaderSrc = R"GLSL(
    #version 460 core
    out vec3 v_Color;
    out gl_PerVertex {
        vec4 gl_Position;
    };
    const vec2 positions[3] = vec2[](vec2(-0.5, -0.5), vec2(0.5, -0.5), vec2(0.0, 0.5));
    const vec3 colors[3] = vec3[](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));
    void main() {
        gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
        v_Color = colors[gl_VertexID];
    }
)GLSL";

constexpr const char* const fragmentShaderSrc = R"GLSL(
    #version 460 core
    in vec3 v_Color;
    out vec4 fragColor;
    void main() {
        fragColor = vec4(v_Color, 1.0);
    }
)GLSL";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        LGL_LOGF("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LGL_LOGF("Failed to initialize GLAD");
        return -1;
    }

    // create pipeline
    // ---------------------------------------
    auto vertexShader = lgl::CreateShader(GL_VERTEX_SHADER, vertexShaderSrc);
    auto fragmentShader = lgl::CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    auto vertexProgram = lgl::CreateSeparableProgram(vertexShader);
    auto fragmentProgram = lgl::CreateSeparableProgram(fragmentShader);
    lgl::DeleteShader(vertexShader);
    lgl::DeleteShader(fragmentShader);
    auto pipeline = lgl::CreatePipeline(vertexProgram, fragmentProgram);
    lgl::DeleteProgram(vertexProgram);
    lgl::DeleteProgram(fragmentProgram);

    // dont care
    // ---------------------------------------
    GLuint emptyVao;
    glCreateVertexArrays(1, &emptyVao);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // clear
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render
        // ------
        glBindProgramPipeline(pipeline);
        glBindVertexArray(emptyVao);

        // we request to draw 3 vertices, and the GPU will generate gl_VertexID = 0, 1, 2 for us.
        // ------
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // reset state
        // ------
        glBindVertexArray(0);
        glBindProgramPipeline(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // delete resource
    // ------------------------------------------------------------------
    glDeleteVertexArrays(1, &emptyVao);
    lgl::DeletePipeline(pipeline);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}