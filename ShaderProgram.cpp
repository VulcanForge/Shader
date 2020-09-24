#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <utility>

#include <glm/gtc/type_ptr.hpp>

void ShaderProgram::LoadSource (GLuint shaderID, const std::string& filename) const
{
    std::ifstream stream (filename);

    if (!stream.is_open ())
    {
        std::cerr << "Could not open shader file: " << filename << "\n";
        exit (EXIT_FAILURE);
    }

    std::vector<std::string> lineVector;
    std::string line;

    while (std::getline (stream, line))
        lineVector.emplace_back (std::move (line));

    size_t linesCount = lineVector.size ();
    GLchar** cLineArray = new GLchar* [linesCount];

    for (size_t i = 0; i < linesCount; i++)
    {
        size_t lineLength = lineVector[i].length ();
        //lineLength + 2 for newline and null-terminator
        GLchar* cLine = new GLchar[lineLength + 2];
        lineVector[i].copy (cLine, lineLength, 0);
        cLine[lineLength] = '\n';
        cLine[lineLength + 1] = '\0';
        cLineArray[i] = cLine;
    }

    glShaderSource (shaderID, linesCount, cLineArray, NULL);

    for (size_t i = 0; i < linesCount; i++)
        delete[] cLineArray[i];

    delete[] cLineArray;
}

void ShaderProgram::CompileSource (GLuint shaderID, const std::string& filename) const
{
    glCompileShader (shaderID);
    int success;
    glGetShaderiv (shaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetShaderiv (shaderID, GL_INFO_LOG_LENGTH, &logLength);
        GLchar* log = new GLchar[logLength];
        glGetShaderInfoLog (shaderID, logLength, NULL, log);
        std::cerr << "Error compiling shader: " << filename << "\n" << log << "\n";
        delete[] log;
        exit (EXIT_FAILURE);
    }
}

void ShaderProgram::LinkBasicShaderProgram () const
{
    glAttachShader (programID, vertexShaderID);
    glAttachShader (programID, fragmentShaderID);
    glLinkProgram (programID);

    glDetachShader (programID, vertexShaderID);
    glDeleteShader (vertexShaderID);
    glDetachShader (programID, fragmentShaderID);
    glDeleteShader (fragmentShaderID);

    GLint success;
    glGetProgramiv (programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetProgramiv (programID, GL_INFO_LOG_LENGTH, &logLength);
        GLchar* log = new GLchar[logLength];
        glGetProgramInfoLog (programID, logLength, NULL, log);
        std::cerr << "Error linking shader: " << programName << "\n" << log << "\n";
        delete[] log;
        exit (EXIT_FAILURE);
    }
}

void ShaderProgram::LinkShaderProgramWithGeometry () const
{
    glAttachShader (programID, vertexShaderID);
    glAttachShader (programID, geometryShaderID);
    glAttachShader (programID, fragmentShaderID);
    glLinkProgram (programID);

    glDetachShader (programID, vertexShaderID);
    glDeleteShader (vertexShaderID);
    glDetachShader (programID, geometryShaderID);
    glDeleteShader (geometryShaderID);
    glDetachShader (programID, fragmentShaderID);
    glDeleteShader (fragmentShaderID);

    GLint success;
    glGetProgramiv (programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetProgramiv (programID, GL_INFO_LOG_LENGTH, &logLength);
        GLchar* log = new GLchar[logLength];
        glGetProgramInfoLog (programID, logLength, NULL, log);
        std::cerr << "Error linking shader: " << programName << "\n" << log << "\n";
        delete[] log;
        exit (EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram ()
{
    glDeleteProgram (programID);
}

#pragma region Factory Constructors

std::unique_ptr<ShaderProgram> ShaderProgram::CreateBasicShaderProgram (const std::string& programName)
{
    std::unique_ptr<ShaderProgram> program (new ShaderProgram ());

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFilename = programName + ".vert";
    program->fragmentFilename = programName + ".frag";

    program->LoadSource (program->vertexShaderID, program->vertexFilename);
    program->CompileSource (program->vertexShaderID, program->vertexFilename);
    program->LoadSource (program->fragmentShaderID, program->fragmentFilename);
    program->CompileSource (program->fragmentShaderID, program->fragmentFilename);
    program->LinkBasicShaderProgram ();

    return program;
}

std::unique_ptr<ShaderProgram> ShaderProgram::CreateBasicShaderProgramWithNames (const std::string& programName, const std::string& vertexFilename, const std::string& fragmentFilename)
{
    std::unique_ptr<ShaderProgram> program (new ShaderProgram ());

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFilename = vertexFilename;
    program->fragmentFilename = fragmentFilename;

    program->LoadSource (program->vertexShaderID, vertexFilename);
    program->CompileSource (program->vertexShaderID, vertexFilename);
    program->LoadSource (program->fragmentShaderID, fragmentFilename);
    program->CompileSource (program->fragmentShaderID, fragmentFilename);
    program->LinkBasicShaderProgram ();

    return program;
}

std::unique_ptr<ShaderProgram> ShaderProgram::CreateShaderProgramWithGeometry (const std::string& programName)
{
    std::unique_ptr<ShaderProgram> program (new ShaderProgram ());

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->geometryShaderID = glCreateShader (GL_GEOMETRY_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFilename = programName + ".vert";
    program->geometryFilename = programName + ".geom";
    program->fragmentFilename = programName + ".frag";

    program->LoadSource (program->vertexShaderID, program->vertexFilename);
    program->CompileSource (program->vertexShaderID, program->vertexFilename);
    program->LoadSource (program->geometryShaderID, program->geometryFilename);
    program->CompileSource (program->geometryShaderID, program->geometryFilename);
    program->LoadSource (program->fragmentShaderID, program->fragmentFilename);
    program->CompileSource (program->fragmentShaderID, program->fragmentFilename);
    program->LinkShaderProgramWithGeometry ();

    return program;
}

std::unique_ptr<ShaderProgram> ShaderProgram::CreateShaderProgramWithGeometryWithNames (const std::string& programName, const std::string& vertexFilename, const std::string& geometryFilename, const std::string& fragmentFilename)
{
    std::unique_ptr<ShaderProgram> program (new ShaderProgram ());

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->geometryShaderID = glCreateShader (GL_GEOMETRY_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFilename = vertexFilename;
    program->geometryFilename = geometryFilename;
    program->fragmentFilename = fragmentFilename;

    program->LoadSource (program->vertexShaderID, vertexFilename);
    program->CompileSource (program->vertexShaderID, vertexFilename);
    program->LoadSource (program->geometryShaderID, geometryFilename);
    program->CompileSource (program->geometryShaderID, geometryFilename);
    program->LoadSource (program->fragmentShaderID, fragmentFilename);
    program->CompileSource (program->fragmentShaderID, fragmentFilename);
    program->LinkShaderProgramWithGeometry ();

    return program;
}

#pragma endregion

GLint ShaderProgram::GetUniformLocation (const std::string& uniformName) const
{
    return glGetUniformLocation (programID, uniformName.c_str ());
}

#pragma region Float / Vec Uniform Setters

void ShaderProgram::SetUniformFloat (const std::string& uniformName, GLfloat value) const
{
    glUniform1f (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformVec2 (const std::string& uniformName, const glm::vec2& vector) const
{
    glUniform2f (GetUniformLocation (uniformName), vector[0], vector[1]);
}

void ShaderProgram::SetUniformVec3 (const std::string& uniformName, const glm::vec3& vector) const
{
    glUniform3f (GetUniformLocation (uniformName), vector[0], vector[1], vector[2]);
}

void ShaderProgram::SetUniformVec4 (const std::string& uniformName, const glm::vec4& vector) const
{
    glUniform4f (GetUniformLocation (uniformName), vector[0], vector[1], vector[2], vector[3]);
}

#pragma endregion

#pragma region Int / IVec Uniform Setters

void ShaderProgram::SetUniformInt (const std::string& uniformName, GLint value) const
{
    glUniform1i (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformIVec2 (const std::string& uniformName, const glm::ivec2& vector) const
{
    glUniform2i (GetUniformLocation (uniformName), vector[0], vector[1]);
}

void ShaderProgram::SetUniformIVec3 (const std::string& uniformName, const glm::ivec3& vector) const
{
    glUniform3i (GetUniformLocation (uniformName), vector[0], vector[1], vector[2]);
}

void ShaderProgram::SetUniformIVec4 (const std::string& uniformName, const glm::ivec4& vector) const
{
    glUniform4i (GetUniformLocation (uniformName), vector[0], vector[1], vector[2], vector[3]);
}

#pragma endregion

#pragma region UInt / UVec Uniform Setters

void ShaderProgram::SetUniformUInt (const std::string& uniformName, GLuint value) const
{
    glUniform1ui (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformUVec2 (const std::string& uniformName, const glm::uvec2& vector) const
{
    glUniform2ui (GetUniformLocation (uniformName), vector[0], vector[1]);
}

void ShaderProgram::SetUniformUVec3 (const std::string& uniformName, const glm::uvec3& vector) const
{
    glUniform3ui (GetUniformLocation (uniformName), vector[0], vector[1], vector[2]);
}

void ShaderProgram::SetUniformUVec4 (const std::string& uniformName, const glm::uvec4& vector) const
{
    glUniform4ui (GetUniformLocation (uniformName), vector[0], vector[1], vector[2], vector[3]);
}

#pragma endregion

#pragma region Float / Vec Array Uniform Setters

void ShaderProgram::SetUniformFloatArray (const std::string& uniformName, const std::vector<GLfloat>& array) const
{
    glUniform1fv (GetUniformLocation (uniformName), array.size (), array.data ());
}

void ShaderProgram::SetUniformVec2Array (const std::string& uniformName, const std::vector<glm::vec2>& array) const
{
    glUniform2fv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformVec3Array (const std::string& uniformName, const std::vector<glm::vec3>& array) const
{
    glUniform3fv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformVec4Array (const std::string& uniformName, const std::vector<glm::vec4>& array) const
{
    glUniform4fv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

#pragma endregion

#pragma region Int / IVec Array Uniform Setters

void ShaderProgram::SetUniformIntArray (const std::string& uniformName, const std::vector<GLint>& array) const
{
    glUniform1iv (GetUniformLocation (uniformName), array.size (), array.data ());
}

void ShaderProgram::SetUniformIVec2Array (const std::string& uniformName, const std::vector<glm::ivec2>& array) const
{
    glUniform2iv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformIVec3Array (const std::string& uniformName, const std::vector<glm::ivec3>& array) const
{
    glUniform3iv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformIVec4Array (const std::string& uniformName, const std::vector<glm::ivec4>& array) const
{
    glUniform4iv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

#pragma endregion

#pragma region UInt / UVec Array Uniform Setters

void ShaderProgram::SetUniformUIntArray (const std::string& uniformName, const std::vector<GLuint>& array) const
{
    glUniform1uiv (GetUniformLocation (uniformName), array.size (), array.data ());
}

void ShaderProgram::SetUniformUVec2Array (const std::string& uniformName, const std::vector<glm::uvec2>& array) const
{
    glUniform2uiv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformUVec3Array (const std::string& uniformName, const std::vector<glm::uvec3>& array) const
{
    glUniform3uiv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformUVec4Array (const std::string& uniformName, const std::vector<glm::uvec4>& array) const
{
    glUniform4uiv (GetUniformLocation (uniformName), array.size (), glm::value_ptr (array[0]));
}

#pragma endregion

#pragma region Matrix Uniform Setters

void ShaderProgram::SetUniformMat2 (const std::string& uniformName, const glm::mat2& matrix) const
{
    glUniformMatrix2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat2x3 (const std::string& uniformName, const glm::mat2x3& matrix) const
{
    glUniformMatrix2x3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat2x4 (const std::string& uniformName, const glm::mat2x4& matrix) const
{
    glUniformMatrix2x4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat3x2 (const std::string& uniformName, const glm::mat3x2& matrix) const
{
    glUniformMatrix3x2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat3 (const std::string& uniformName, const glm::mat3& matrix) const
{
    glUniformMatrix3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat3x4 (const std::string& uniformName, const glm::mat3x4& matrix) const
{
    glUniformMatrix3x4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat4x2 (const std::string& uniformName, const glm::mat4x2& matrix) const
{
    glUniformMatrix4x2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat4x3 (const std::string& uniformName, const glm::mat4x3& matrix) const
{
    glUniformMatrix4x3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

void ShaderProgram::SetUniformMat4 (const std::string& uniformName, const glm::mat4& matrix) const
{
    glUniformMatrix4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (matrix));
}

#pragma endregion

#pragma region Matrix Array Uniform Setters

void ShaderProgram::SetUniformMat2Array (const std::string& uniformName, const std::vector<glm::mat2>& array) const
{
    glUniformMatrix2fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat2x3Array (const std::string& uniformName, const std::vector<glm::mat2x3>& array) const
{
    glUniformMatrix2x3fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat2x4Array (const std::string& uniformName, const std::vector<glm::mat2x4>& array) const
{
    glUniformMatrix2x4fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat3x2Array (const std::string& uniformName, const std::vector<glm::mat3x2>& array) const
{
    glUniformMatrix3x2fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat3Array (const std::string& uniformName, const std::vector<glm::mat3>& array) const
{
    glUniformMatrix3fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat3x4Array (const std::string& uniformName, const std::vector<glm::mat3x4>& array) const
{
    glUniformMatrix3x4fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat4x2Array (const std::string& uniformName, const std::vector<glm::mat4x2>& array) const
{
    glUniformMatrix4x2fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat4x3Array (const std::string& uniformName, const std::vector<glm::mat4x3>& array) const
{
    glUniformMatrix4x3fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

void ShaderProgram::SetUniformMat4Array (const std::string& uniformName, const std::vector<glm::mat4>& array) const
{
    glUniformMatrix4fv (GetUniformLocation (uniformName), array.size (), GL_FALSE, glm::value_ptr (array[0]));
}

#pragma endregion

void ShaderProgram::SetUniformSampler (const std::string& uniformName, GLint value) const
{
    glUniform1i (GetUniformLocation (uniformName), value);
}

void ShaderProgram::UseProgram () const
{
    glUseProgram (programID);
}
