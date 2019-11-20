#pragma warning (disable:4267)

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <glew.h>

#include <gtc/type_ptr.hpp>

#include "ShaderProgram.h"

void ShaderProgram::LoadSource (int shaderID, const std::string& fileName) const
{
    std::ifstream stream (fileName);

    if (!stream.is_open ())
    {
        std::cerr << "Could not open shader file: " << fileName << std::endl;
        exit (EXIT_FAILURE);
    }

    std::vector<std::string> lineVector;
    std::string line;

    while (getline (stream, line))
        lineVector.push_back (line);

    int linesCount = lineVector.size ();
    char** lineArray = new char* [linesCount];

    for (int i = 0; i < linesCount; i++)
    {
        int lineLength = lineVector[i].length ();
        //lineLength + 2 for newline and null-terminator
        char* lineCharArray = new char[lineLength + 2];
        lineVector[i].copy (lineCharArray, lineLength, 0);
        lineCharArray[lineLength] = '\n';
        lineCharArray[lineLength + 1] = 0;
        lineArray[i] = lineCharArray;
    }

    glShaderSource (shaderID, linesCount, lineArray, nullptr);

    for (int i = 0; i < linesCount; i++)
        delete[] lineArray[i];

    delete[] lineArray;
}

void ShaderProgram::CompileSource (int shaderID, const std::string& fileName) const
{
    glCompileShader (shaderID);
    int success;
    glGetShaderiv (shaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        int logLength;
        glGetShaderiv (shaderID, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog (shaderID, logLength, NULL, log);
        std::cerr << "Error compiling shader: " << fileName << std::endl << log << std::endl;
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

    int success;
    glGetProgramiv (programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        int logLength;
        glGetProgramiv (programID, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog (programID, logLength, NULL, log);
        std::cerr << "Error linking shader: " << programName << std::endl << log << std::endl;
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

    int success;
    glGetProgramiv (programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        int logLength;
        glGetProgramiv (programID, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog (programID, logLength, NULL, log);
        std::cerr << "Error linking shader: " << programName << std::endl << log << std::endl;
        exit (EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram ()
{
    glDeleteProgram (programID);
}

ShaderProgram* ShaderProgram::CreateBasicShaderProgram (const std::string& programName)
{
    ShaderProgram* program = new ShaderProgram ();

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFileName = programName + ".vert";
    program->fragmentFileName = programName + ".frag";

    program->LoadSource (program->vertexShaderID, program->vertexFileName);
    program->CompileSource (program->vertexShaderID, program->vertexFileName);
    program->LoadSource (program->fragmentShaderID, program->fragmentFileName);
    program->CompileSource (program->fragmentShaderID, program->fragmentFileName);
    program->LinkBasicShaderProgram ();

    return program;
}

ShaderProgram* ShaderProgram::CreateBasicShaderProgramWithNames
(
    const std::string& programName,
    const std::string& vertexFileName,
    const std::string& fragmentFileName
)
{
    ShaderProgram* program = new ShaderProgram ();

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFileName = vertexFileName;
    program->fragmentFileName = fragmentFileName;

    program->LoadSource (program->vertexShaderID, vertexFileName);
    program->CompileSource (program->vertexShaderID, vertexFileName);
    program->LoadSource (program->fragmentShaderID, fragmentFileName);
    program->CompileSource (program->fragmentShaderID, fragmentFileName);
    program->LinkBasicShaderProgram ();

    return program;
}

ShaderProgram* ShaderProgram::CreateShaderProgramWithGeometry (const std::string& programName)
{
    ShaderProgram* program = new ShaderProgram ();

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->geometryShaderID = glCreateShader (GL_GEOMETRY_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFileName = programName + ".vert";
    program->geometryFileName = programName + ".geom";
    program->fragmentFileName = programName + ".frag";

    program->LoadSource (program->vertexShaderID, program->vertexFileName);
    program->CompileSource (program->vertexShaderID, program->vertexFileName);
    program->LoadSource (program->geometryShaderID, program->geometryFileName);
    program->CompileSource (program->geometryShaderID, program->geometryFileName);
    program->LoadSource (program->fragmentShaderID, program->fragmentFileName);
    program->CompileSource (program->fragmentShaderID, program->fragmentFileName);
    program->LinkShaderProgramWithGeometry ();

    return program;
}

ShaderProgram* ShaderProgram::CreateShaderProgramWithGeometryWithNames
(
    const std::string& programName,
    const std::string& vertexFileName,
    const std::string& geometryFileName,
    const std::string& fragmentFileName
)
{
    ShaderProgram* program = new ShaderProgram ();

    program->programID = glCreateProgram ();
    program->vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    program->geometryShaderID = glCreateShader (GL_GEOMETRY_SHADER);
    program->fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    program->programName = programName;
    program->vertexFileName = vertexFileName;
    program->geometryFileName = geometryFileName;
    program->fragmentFileName = fragmentFileName;

    program->LoadSource (program->vertexShaderID, vertexFileName);
    program->CompileSource (program->vertexShaderID, vertexFileName);
    program->LoadSource (program->geometryShaderID, geometryFileName);
    program->CompileSource (program->geometryShaderID, geometryFileName);
    program->LoadSource (program->fragmentShaderID, fragmentFileName);
    program->CompileSource (program->fragmentShaderID, fragmentFileName);
    program->LinkShaderProgramWithGeometry ();

    return program;
}

std::string ShaderProgram::ProgramName () const
{
    return programName;
}

unsigned int ShaderProgram::ProgramID () const
{
    return programID;
}

std::vector<Uniform> ShaderProgram::UniformList () const
{
    std::vector<Uniform> uniformList;

    for (auto i = uniformMap.cbegin (); i != uniformMap.cend (); i++)
    {
        Uniform uniform (i->first, i->second);
        uniformList.push_back (uniform);
    }

    return uniformList;
}

int ShaderProgram::GetUniformLocation (const std::string& uniformName)
{
    auto locationIterator = uniformMap.find (uniformName);

    if (locationIterator == uniformMap.end ())
    {
        int location = glGetUniformLocation (programID, uniformName.c_str ());

        if (location == -1)
        {
            std::cerr << "Error: Uniform does not exist: " << uniformName << std::endl;
            exit (EXIT_FAILURE);
        }

        uniformMap[uniformName] = location;

        return location;
    }
    else
        return locationIterator->second;
}

void ShaderProgram::SetUniformBool (const std::string& uniformName, bool value)
{
    glUniform1i (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformBVec2 (const std::string& uniformName, const glm::bvec2& value)
{
    glUniform2i (GetUniformLocation (uniformName), value[0], value[1]);
}

void ShaderProgram::SetUniformBVec3 (const std::string& uniformName, const glm::bvec3& value)
{
    glUniform3i (GetUniformLocation (uniformName), value[0], value[1], value[2]);
}

void ShaderProgram::SetUniformBVec4 (const std::string& uniformName, const glm::bvec4& value)
{
    glUniform4i (GetUniformLocation (uniformName), value[0], value[1], value[2], value[3]);
}

void ShaderProgram::SetUniformBoolArray (const std::string& uniformName, int count, const bool* values)
{
    int* intermediateValues = new int[count];

    for (int i = 0; i < count; i++)
        intermediateValues[i] = int (values[i]);

    glUniform1iv (GetUniformLocation (uniformName), count, intermediateValues);

    delete[] intermediateValues;
}

void ShaderProgram::SetUniformBVec2Array (const std::string& uniformName, int count, const glm::bvec2* values)
{
    int* intermediateValues = new int[2 * count];

    for (int i = 0; i < count; i++)
    {
        intermediateValues[2 * i] = int (values[i][0]);
        intermediateValues[2 * i + 1] = int (values[i][1]);
    }

    glUniform2iv (GetUniformLocation (uniformName), count, intermediateValues);

    delete[] intermediateValues;
}

void ShaderProgram::SetUniformBVec3Array (const std::string& uniformName, int count, const glm::bvec3* values)
{
    int* intermediateValues = new int[3 * count];

    for (int i = 0; i < count; i++)
    {
        intermediateValues[3 * i] = int (values[i][0]);
        intermediateValues[3 * i + 1] = int (values[i][1]);
        intermediateValues[3 * i + 2] = int (values[i][2]);
    }

    glUniform3iv (GetUniformLocation (uniformName), count, intermediateValues);

    delete[] intermediateValues;
}

void ShaderProgram::SetUniformBVec4Array (const std::string& uniformName, int count, const glm::bvec4* values)
{
    int* intermediateValues = new int[4 * count];

    for (int i = 0; i < count; i++)
    {
        intermediateValues[4 * i] = int (values[i][0]);
        intermediateValues[4 * i + 1] = int (values[i][1]);
        intermediateValues[4 * i + 2] = int (values[i][2]);
        intermediateValues[4 * i + 3] = int (values[i][3]);
    }

    glUniform4iv (GetUniformLocation (uniformName), count, intermediateValues);

    delete[] intermediateValues;
}

void ShaderProgram::SetUniformInt (const std::string& uniformName, int value)
{
    glUniform1i (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformIVec2 (const std::string& uniformName, const glm::ivec2& value)
{
    glUniform2i (GetUniformLocation (uniformName), value[0], value[1]);
}

void ShaderProgram::SetUniformIVec3 (const std::string& uniformName, const glm::ivec3& value)
{
    glUniform3i (GetUniformLocation (uniformName), value[0], value[1], value[2]);
}

void ShaderProgram::SetUniformIVec4 (const std::string& uniformName, const glm::ivec4& value)
{
    glUniform4i (GetUniformLocation (uniformName), value[0], value[1], value[2], value[3]);
}

void ShaderProgram::SetUniformIntArray (const std::string& uniformName, int count, const int* values)
{
    glUniform1iv (GetUniformLocation (uniformName), count, values);
}

void ShaderProgram::SetUniformIVec2Array (const std::string& uniformName, int count, const glm::ivec2* values)
{
    glUniform2iv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformIVec3Array (const std::string& uniformName, int count, const glm::ivec3* values)
{
    glUniform3iv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformIVec4Array (const std::string& uniformName, int count, const glm::ivec4* values)
{
    glUniform4iv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformUnsignedInt (const std::string& uniformName, unsigned int value)
{
    glUniform1ui (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformUVec2 (const std::string& uniformName, const glm::uvec2& value)
{
    glUniform2ui (GetUniformLocation (uniformName), value[0], value[1]);
}

void ShaderProgram::SetUniformUVec3 (const std::string& uniformName, const glm::uvec3& value)
{
    glUniform3ui (GetUniformLocation (uniformName), value[0], value[1], value[2]);
}

void ShaderProgram::SetUniformUVec4 (const std::string& uniformName, const glm::uvec4& value)
{
    glUniform4ui (GetUniformLocation (uniformName), value[0], value[1], value[2], value[3]);
}

void ShaderProgram::SetUniformUnsignedIntArray (const std::string& uniformName, int count, const unsigned int* values)
{
    glUniform1uiv (GetUniformLocation (uniformName), count, values);
}

void ShaderProgram::SetUniformUVec2Array (const std::string& uniformName, int count, const glm::uvec2* values)
{
    glUniform2uiv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformUVec3Array (const std::string& uniformName, int count, const glm::uvec3* values)
{
    glUniform3uiv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformUVec4Array (const std::string& uniformName, int count, const glm::uvec4* values)
{
    glUniform4uiv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformFloat (const std::string& uniformName, float value)
{
    glUniform1f (GetUniformLocation (uniformName), value);
}

void ShaderProgram::SetUniformVec2 (const std::string& uniformName, const glm::vec2& value)
{
    glUniform2f (GetUniformLocation (uniformName), value[0], value[1]);
}

void ShaderProgram::SetUniformVec3 (const std::string& uniformName, const glm::vec3& value)
{
    glUniform3f (GetUniformLocation (uniformName), value[0], value[1], value[2]);
}

void ShaderProgram::SetUniformVec4 (const std::string& uniformName, const glm::vec4& value)
{
    glUniform4f (GetUniformLocation (uniformName), value[0], value[1], value[2], value[3]);
}

void ShaderProgram::SetUniformFloatArray (const std::string& uniformName, int count, const float* values)
{
    glUniform1fv (GetUniformLocation (uniformName), count, values);
}

void ShaderProgram::SetUniformVec2Array (const std::string& uniformName, int count, const glm::vec2* values)
{
    glUniform2fv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformVec3Array (const std::string& uniformName, int count, const glm::vec3* values)
{
    glUniform3fv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformVec4Array (const std::string& uniformName, int count, const glm::vec4* values)
{
    glUniform4fv (GetUniformLocation (uniformName), count, glm::value_ptr (values[0]));
}

void ShaderProgram::SetUniformMat2 (const std::string& uniformName, const glm::mat2& value)
{
    glUniformMatrix2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat2x3 (const std::string& uniformName, const glm::mat2x3& value)
{
    glUniformMatrix2x3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat2x4 (const std::string& uniformName, const glm::mat2x4& value)
{
    glUniformMatrix2x4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat3x2 (const std::string& uniformName, const glm::mat3x2& value)
{
    glUniformMatrix3x2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat3 (const std::string& uniformName, const glm::mat3& value)
{
    glUniformMatrix3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat3x4 (const std::string& uniformName, const glm::mat3x4& value)
{
    glUniformMatrix3x4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat4x2 (const std::string& uniformName, const glm::mat4x2& value)
{
    glUniformMatrix4x2fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat4x3 (const std::string& uniformName, const glm::mat4x3& value)
{
    glUniformMatrix4x3fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformMat4 (const std::string& uniformName, const glm::mat4& value)
{
    glUniformMatrix4fv (GetUniformLocation (uniformName), 1, GL_FALSE, glm::value_ptr (value));
}

void ShaderProgram::SetUniformSampler (const std::string& uniformName, int value)
{
    glUniform1i (GetUniformLocation (uniformName), value);
}

void ShaderProgram::UseProgram () const
{
    glUseProgram (programID);
}
