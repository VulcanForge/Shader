#pragma once

#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/matrix.hpp>

/// <summary>
/// Represents a GLSL shader program.
/// </summary>
class ShaderProgram
{
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint geometryShaderID;
    GLuint fragmentShaderID;

    std::string programName;
    std::string vertexFilename;
    std::string geometryFilename;
    std::string fragmentFilename;

    void LoadSource (GLuint shaderID, const std::string& filename) const;
    void CompileSource (GLuint shaderID, const std::string& filename) const;
    void LinkBasicShaderProgram () const;
    void LinkShaderProgramWithGeometry () const;

    ShaderProgram () = default;

public:
    ~ShaderProgram ();

#pragma region Factory Constructors

    /// <summary>
    /// Creates a shader program with vertex and fragment shaders.
    /// </summary>
    /// <param name="programName">
    /// The name of the program. The vertex shader file should be named programName + ".vert" and the fragment shader file should be named programName + ".frag".
    /// </param>
    static std::unique_ptr<ShaderProgram> CreateBasicShaderProgram (const std::string& programName);

    /// <summary>
    /// Creates a shader program with vertex and fragment shaders, with custom filenames.
    /// </summary>
    /// <param name="programName">The name of the program.</param>
    /// <param name="vertexFilename">The vertex shader file.</param>
    /// <param name="fragmentFilename">The fragment shader file.</param>
    static std::unique_ptr<ShaderProgram> CreateBasicShaderProgramWithNames (const std::string& programName, const std::string& vertexFilename, const std::string& fragmentFilename);

    /// <summary>
    /// Creates a shader program with vertex, geometry, and fragment shaders.
    /// </summary>
    /// <param name="programName">
    /// The name of the program. The vertex shader file should be named programName + ".vert", the geometry shader file should be  named programName + ".geom, and the fragment shader file should be named programName + ".frag".
    /// </param>
    static std::unique_ptr<ShaderProgram> CreateShaderProgramWithGeometry (const std::string& programName);

    /// <summary>
    /// Creates a shader program with vertex, geometry, and fragment shaders, with custom filenames.
    /// </summary>
    /// <param name="programName">The name of the program.</param>
    /// <param name="vertexFilename">The vertex shader file.</param>
    /// <param name="geometryFilename">The geometry shader file.</param>
    /// <param name="fragmentFilename">The fragment shader file.</param>
    static std::unique_ptr<ShaderProgram> CreateShaderProgramWithGeometryWithNames (const std::string& programName, const std::string& vertexFilename, const std::string& geometryFilename, const std::string& fragmentFilename);

#pragma endregion

    /// <summary>
    /// Returns the GL location of a uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    GLint GetUniformLocation (const std::string& uniformName) const;

#pragma region Float / Vec Uniform Setters

    /// <summary>
    /// Sets a floating-point uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="value">The value to pass to the uniform.</param>
    void SetUniformFloat (const std::string& uniformName, GLfloat value) const;

    /// <summary>
    /// Sets a vec2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformVec2 (const std::string& uniformName, const glm::vec2& vector) const;

    /// <summary>
    /// Sets a vec3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformVec3 (const std::string& uniformName, const glm::vec3& vector) const;

    /// <summary>
    /// Sets a vec4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformVec4 (const std::string& uniformName, const glm::vec4& vector) const;

#pragma endregion

#pragma region Int / IVec Uniform Setters

    /// <summary>
    /// Sets an integer uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="value">The value to pass to the uniform.</param>
    void SetUniformInt (const std::string& uniformName, GLint value) const;

    /// <summary>
    /// Sets an ivec2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformIVec2 (const std::string& uniformName, const glm::ivec2& vector) const;

    /// <summary>
    /// Sets an ivec3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformIVec3 (const std::string& uniformName, const glm::ivec3& vector) const;

    /// <summary>
    /// Sets an ivec4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformIVec4 (const std::string& uniformName, const glm::ivec4& vector) const;

#pragma endregion

#pragma region UInt / UVec Uniform Setters

    /// <summary>
    /// Sets an unsigned integer uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="value">The value to pass to the uniform.</param>
    void SetUniformUInt (const std::string& uniformName, GLuint value) const;

    /// <summary>
    /// Sets an uvec2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformUVec2 (const std::string& uniformName, const glm::uvec2& vector) const;

    /// <summary>
    /// Sets an uvec3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformUVec3 (const std::string& uniformName, const glm::uvec3& vector) const;

    /// <summary>
    /// Sets an uvec4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="vector">The vector to pass to the uniform.</param>
    void SetUniformUVec4 (const std::string& uniformName, const glm::uvec4& vector) const;

#pragma endregion

#pragma region Float / Vec Array Uniform Setters

    /// <summary>
    /// Sets an array uniform of floating point values in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformFloatArray (const std::string& uniformName, const std::vector<GLfloat>& array) const;

    /// <summary>
    /// Sets an array uniform of vec2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformVec2Array (const std::string& uniformName, const std::vector<glm::vec2>& array) const;

    /// <summary>
    /// Sets an array uniform of vec3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformVec3Array (const std::string& uniformName, const std::vector<glm::vec3>& array) const;

    /// <summary>
    /// Sets an array uniform of vec4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformVec4Array (const std::string& uniformName, const std::vector<glm::vec4>& array) const;

#pragma endregion

#pragma region Int / IVec Array Uniform Setters

    /// <summary>
    /// Sets an array uniform of integer values in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformIntArray (const std::string& uniformName, const std::vector<GLint>& array) const;

    /// <summary>
    /// Sets an array uniform of ivec2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformIVec2Array (const std::string& uniformName, const std::vector<glm::ivec2>& array) const;

    /// <summary>
    /// Sets an array uniform of ivec3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformIVec3Array (const std::string& uniformName, const std::vector<glm::ivec3>& array) const;

    /// <summary>
    /// Sets an array uniform of ivec4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformIVec4Array (const std::string& uniformName, const std::vector<glm::ivec4>& array) const;

#pragma endregion

#pragma region UInt / UVec Array Uniform Setters

    /// <summary>
    /// Sets an array uniform of unsigned integer values in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformUIntArray (const std::string& uniformName, const std::vector<GLuint>& array) const;

    /// <summary>
    /// Sets an array uniform of uvec2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformUVec2Array (const std::string& uniformName, const std::vector<glm::uvec2>& array) const;

    /// <summary>
    /// Sets an array uniform of uvec3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformUVec3Array (const std::string& uniformName, const std::vector<glm::uvec3>& array) const;

    /// <summary>
    /// Sets an array uniform of uvec4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformUVec4Array (const std::string& uniformName, const std::vector<glm::uvec4>& array) const;

#pragma endregion

#pragma region Matrix Uniform Setters

    /// <summary>
    /// Sets a mat2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat2 (const std::string& uniformName, const glm::mat2& matrix) const;

    /// <summary>
    /// Sets a mat2x3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat2x3 (const std::string& uniformName, const glm::mat2x3& matrix) const;

    /// <summary>
    /// Sets a mat2x4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat2x4 (const std::string& uniformName, const glm::mat2x4& matrix) const;

    /// <summary>
    /// Sets a mat3x2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat3x2 (const std::string& uniformName, const glm::mat3x2& matrix) const;

    /// <summary>
    /// Sets a mat3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat3 (const std::string& uniformName, const glm::mat3& matrix) const;

    /// <summary>
    /// Sets a mat3x4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat3x4 (const std::string& uniformName, const glm::mat3x4& matrix) const;

    /// <summary>
    /// Sets a mat4x2 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat4x2 (const std::string& uniformName, const glm::mat4x2& matrix) const;

    /// <summary>
    /// Sets a mat4x3 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat4x3 (const std::string& uniformName, const glm::mat4x3& matrix) const;

    /// <summary>
    /// Sets a mat4 uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="matrix">The matrix to pass to the uniform.</param>
    void SetUniformMat4 (const std::string& uniformName, const glm::mat4& matrix) const;

#pragma endregion

#pragma region Matrix Array Uniform Setters

    /// <summary>
    /// Sets an array uniform of mat2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat2Array (const std::string& uniformName, const std::vector<glm::mat2>& array) const;

    /// <summary>
    /// Sets an array uniform of mat2x3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat2x3Array (const std::string& uniformName, const std::vector<glm::mat2x3>& array) const;

    /// <summary>
    /// Sets an array uniform of mat2x4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat2x4Array (const std::string& uniformName, const std::vector<glm::mat2x4>& array) const;

    /// <summary>
    /// Sets an array uniform of mat3x2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat3x2Array (const std::string& uniformName, const std::vector<glm::mat3x2>& array) const;

    /// <summary>
    /// Sets an array uniform of mat3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat3Array (const std::string& uniformName, const std::vector<glm::mat3>& array) const;

    /// <summary>
    /// Sets an array uniform of mat3x4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat3x4Array (const std::string& uniformName, const std::vector<glm::mat3x4>& array) const;

    /// <summary>
    /// Sets an array uniform of mat4x2's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat4x2Array (const std::string& uniformName, const std::vector<glm::mat4x2>& array) const;

    /// <summary>
    /// Sets an array uniform of mat4x3's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat4x3Array (const std::string& uniformName, const std::vector<glm::mat4x3>& array) const;

    /// <summary>
    /// Sets an array uniform of mat4's in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="array">The array to pass to the uniform.</param>
    void SetUniformMat4Array (const std::string& uniformName, const std::vector<glm::mat4>& array) const;

#pragma endregion

    /// <summary>
    /// Sets a sampler uniform in the program.
    /// </summary>
    /// <param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    /// <param name="samplerID">The sampler ID to pass to the uniform.</param>
    void SetUniformSampler (const std::string& uniformName, GLint samplerID) const;

    /// <summary>
    /// Sets the program to the active program.
    /// </summary>
    void UseProgram () const;
};
