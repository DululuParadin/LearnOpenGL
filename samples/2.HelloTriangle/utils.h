#include <vector>
#include "glad/glad.h"
#include "mlog.h"

namespace lgl {
/**
 * @brief Creates a compiled shader object from a source string.
 * @param shaderType The type of the shader to create (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
 * @param source A null-terminated string containing the GLSL shader source code.
 * @return The OpenGL handle (GLuint) to the compiled shader object on success, or 0 on failure.
 * @note The returned shader object should be deleted with DeleteShader when no longer needed.
 */
GLuint CreateShader(GLenum shaderType, const char* const source) {
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        LGL_LOGE("glCreateShader failed for type %d", shaderType);
        return 0;
    }
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> infoLog(infoLogLength);
            glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());
            const char* typeStr = (shaderType == GL_VERTEX_SHADER) ? "Vertex" : 
                                  (shaderType == GL_FRAGMENT_SHADER) ? "Fragment" : "Other";
            LGL_LOGE("Shader compilation failed for %s shader:\n%s", typeStr, infoLog.data());
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

/**
 * @brief Deletes a shader object.
 * @param shader The handle of the shader object to delete.
 * @note A shader object can be safely deleted after it has been attached to and linked
 *       in a program object, as the program will retain the compiled binary code.
 */
void DeleteShader(GLuint shader) {
    if (glIsShader(shader)) {
        glDeleteShader(shader);
    } else {
        LGL_LOGE("DeleteShader failed");
    }
}

/**
 * @brief Creates a separable program object for a single shader stage.
 * @param shader The handle of a single compiled shader object (e.g., a vertex or fragment shader).
 * @return The handle to the linked, separable program object on success, or 0 if linking fails.
 * @note This function creates a program that represents a single pipeline stage. These individual
 *       program objects are then bound to a Program Pipeline Object using glUseProgramStages.
 */
GLuint CreateSeparableProgram(GLuint shader) {
    GLuint program = glCreateProgram();
    if (program == 0) {
        LGL_LOGE("glCreateProgram() failed.");
        return 0;
    }

    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glAttachShader(program, shader);
    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> infoLog(infoLogLength);
            glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());
            LGL_LOGE("Separable Program Linker Failure:\n%s", infoLog.data());
        } else {
            LGL_LOGE("Separable Program Linker Failure, but no Info Log available.");
        }

        glDeleteProgram(program);
        return 0;
    }
    glDetachShader(program, shader);
    return program;
}

/**
 * @brief Deletes a program object.
 * @param program The handle of the program object to delete.
 * @note This can be used for both separable program objects created for a single stage
 *       and traditional monolithic program objects.
 */
void DeleteProgram(GLuint program) {
    if (glIsProgram(program)) {
        glDeleteProgram(program);
    } else {
        LGL_LOGE("DeleteProgram failed");
    }
}

/**
 * @brief Creates a program pipeline object and binds vertex and fragment shader stages to it.
 * @param vsProgram The handle to a separable program object containing the vertex shader stage.
 * @param fsProgram The handle to a separable program object containing the fragment shader stage.
 * @return The handle to the configured program pipeline object on success, or 0 on failure.
 * @note This pipeline object represents the complete programmable graphics pipeline for rendering.
 *       It should be bound with glBindProgramPipeline before a draw call. This helper only handles
 *       VS and FS; a more general implementation could handle other stages (Geometry, Tessellation, etc.).
 */
GLuint CreatePipeline(GLuint vsProgram, GLuint fsProgram) {
    GLuint pipeline;
    glCreateProgramPipelines(1, &pipeline);
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vsProgram);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, fsProgram);
    return pipeline;
}

/**
 * @brief Deletes a program pipeline object.
 * @param pipeline The handle of the program pipeline object to delete.
 */
void DeletePipeline(GLuint pipeline) {
    if (glIsProgramPipeline(pipeline)) {
        glDeleteProgramPipelines(1, &pipeline);
    } else {
        LGL_LOGE("DeletePipeline failed");
    }
}
} // namespace lgl