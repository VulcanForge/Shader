#pragma once
#pragma warning (disable:4251)

#ifdef SHADER_EXPORTS
#define SHADER_API __declspec(dllexport)
#else
#define SHADER_API __declspec(dllimport)
#endif

typedef std::pair<std::string, int> Uniform;

///<summary>
///Represents a GLSL shader program.
///</summary>
class SHADER_API ShaderProgram
{
private:
    unsigned int programID = -1;
    unsigned int vertexShaderID = -1;
    unsigned int geometryShaderID = -1;
    unsigned int fragmentShaderID = -1;

    std::string programName;
    std::string vertexFileName;
    std::string geometryFileName;
    std::string fragmentFileName;

    std::unordered_map<std::string, int> uniformMap;

    void LoadSource (int shaderID, const std::string& fileName) const;
    void CompileSource (int shaderID, const std::string& fileName) const;
    void LinkBasicShaderProgram () const;
    void LinkShaderProgramWithGeometry () const;

public:
    ~ShaderProgram ();

    ///<summary>
    ///Creates a shader program with vertex and fragment shaders.
    ///</summary>
    ///<param name="programName">
    ///The name of the program.
    ///The vertex shader file should be named <c>programName + ".vert"</c> and the fragment shader file should be 
    ///named <c>programName + ".frag"</c>.
    ///</param>
    static ShaderProgram* CreateBasicShaderProgram (const std::string& programName);

    ///<summary>
    ///Creates a shader program with vertex and fragment shaders, with custom filenames.
    ///</summary>
    ///<param name="programName">The name of the program.</param>
    ///<param name="vertexFileName">The vertex shader file.</param>
    ///<param name="fragmentFileName">The fragment shader file.</param>
    static ShaderProgram* CreateBasicShaderProgramWithNames
    (
        const std::string& programName,
        const std::string& vertexFileName,
        const std::string& fragmentFileName
    );

    ///<summary>
    ///Creates a shader program with vertex, geometry, and fragment shaders.
    ///</summary>
    ///<param name="programName">
    ///The name of the program.
    ///The vertex shader file should be named <c>programName + ".vert"</c>, the geometry shader file should be 
    ///named <c>programName + ".geom</c>, and the fragment shader file should be named <c>programName + ".frag"</c>.
    ///</param>
    static ShaderProgram* CreateShaderProgramWithGeometry (const std::string& programName);

    ///<summary>
    ///Creates a shader program with vertex, geometry, and fragment shaders, with custom filenames.
    ///</summary>
    ///<param name="programName">The name of the program.</param>
    ///<param name="vertexFileName">The vertex shader file.</param>
    ///<param name="geometryFileName">The geometry shader file.</param>
    ///<param name="fragmentFileName">The fragment shader file.</param>
    static ShaderProgram* CreateShaderProgramWithGeometryWithNames
    (
        const std::string& programName,
        const std::string& vertexFileName,
        const std::string& geometryFileName,
        const std::string& fragmentFileName
    );

    ///<summary>
    ///Returns the program name.
    ///</summary>
    std::string ProgramName () const;

    ///<summary>
    ///Returns the program GL ID.
    ///</summary>
    unsigned int ProgramID () const;

    ///<summary>
    ///Returns a list of uniforms in the program.
    ///</summary>
    std::vector<Uniform> UniformList () const;

    ///<summary>
    ///Returns the GL location of a uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    int GetUniformLocation (const std::string& uniformName);

    ///<summary>
    ///Sets a boolean uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformBool (const std::string& uniformName, bool value);

    ///<summary>
    ///Sets a <c>bvec2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformBVec2 (const std::string& uniformName, const glm::bvec2& value);

    ///<summary>
    ///Sets a <c>bvec3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformBVec3 (const std::string& uniformName, const glm::bvec3& value);

    ///<summary>
    ///Sets a <c>bvec4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformBVec4 (const std::string& uniformName, const glm::bvec4& value);

    ///<summary>
    ///Sets a boolean array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformBoolArray (const std::string& uniformName, int count, const bool* values);

    ///<summary>
    ///Sets a <c>bvec2</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformBVec2Array (const std::string& uniformName, int count, const glm::bvec2* values);

    ///<summary>
    ///Sets a <c>bvec3</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformBVec3Array (const std::string& uniformName, int count, const glm::bvec3* values);

    ///<summary>
    ///Sets a <c>bvec4</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformBVec4Array (const std::string& uniformName, int count, const glm::bvec4* values);

    ///<summary>
    ///Sets an integer uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformInt (const std::string& uniformName, int value);

    ///<summary>
    ///Sets an <c>ivec2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformIVec2 (const std::string& uniformName, const glm::ivec2& value);

    ///<summary>
    ///Sets an <c>ivec3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformIVec3 (const std::string& uniformName, const glm::ivec3& value);

    ///<summary>
    ///Sets an <c>ivec4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformIVec4 (const std::string& uniformName, const glm::ivec4& value);

    ///<summary>
    ///Sets an integer array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformIntArray (const std::string& uniformName, int count, const int* values);

    ///<summary>
    ///Sets an <c>ivec2</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformIVec2Array (const std::string& uniformName, int count, const glm::ivec2* values);

    ///<summary>
    ///Sets an <c>ivec3</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformIVec3Array (const std::string& uniformName, int count, const glm::ivec3* values);

    ///<summary>
    ///Sets an <c>ivec4</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformIVec4Array (const std::string& uniformName, int count, const glm::ivec4* values);

    ///<summary>
    ///Sets an unsigned integer uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformUnsignedInt (const std::string& uniformName, unsigned int value);

    ///<summary>
    ///Sets a <c>uvec2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformUVec2 (const std::string& uniformName, const glm::uvec2& value);

    ///<summary>
    ///Sets a <c>uvec3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformUVec3 (const std::string& uniformName, const glm::uvec3& value);

    ///<summary>
    ///Sets a <c>uvec4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformUVec4 (const std::string& uniformName, const glm::uvec4& value);

    ///<summary>
    ///Sets an unsigned integer array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformUnsignedIntArray (const std::string& uniformName, int count, const unsigned int* values);

    ///<summary>
    ///Sets a <c>uvec2</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformUVec2Array (const std::string& uniformName, int count, const glm::uvec2* values);

    ///<summary>
    ///Sets a <c>uvec3</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformUVec3Array (const std::string& uniformName, int count, const glm::uvec3* values);

    ///<summary>
    ///Sets a <c>uvec4</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformUVec4Array (const std::string& uniformName, int count, const glm::uvec4* values);

    ///<summary>
    ///Sets a floating-point uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformFloat (const std::string& uniformName, float value);

    ///<summary>
    ///Sets a <c>vec2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformVec2 (const std::string& uniformName, const glm::vec2& value);

    ///<summary>
    ///Sets a <c>vec3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformVec3 (const std::string& uniformName, const glm::vec3& value);

    ///<summary>
    ///Sets a <c>vec4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformVec4 (const std::string& uniformName, const glm::vec4& value);

    ///<summary>
    ///Sets a floating-point array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformFloatArray (const std::string& uniformName, int count, const float* values);

    ///<summary>
    ///Sets a <c>vec2</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformVec2Array (const std::string& uniformName, int count, const glm::vec2* values);

    ///<summary>
    ///Sets a <c>vec3</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformVec3Array (const std::string& uniformName, int count, const glm::vec3* values);

    ///<summary>
    ///Sets a <c>vec4</c> array uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="values">The array to pass to the uniform.</param>
    void SetUniformVec4Array (const std::string& uniformName, int count, const glm::vec4* values);

    ///<summary>
    ///Sets a <c>mat2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat2 (const std::string& uniformName, const glm::mat2& value);

    ///<summary>
    ///Sets a <c>mat2x3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat2x3 (const std::string& uniformName, const glm::mat2x3& value);

    ///<summary>
    ///Sets a <c>mat2x4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat2x4 (const std::string& uniformName, const glm::mat2x4& value);

    ///<summary>
    ///Sets a <c>mat3x2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat3x2 (const std::string& uniformName, const glm::mat3x2& value);

    ///<summary>
    ///Sets a <c>mat3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat3 (const std::string& uniformName, const glm::mat3& value);

    ///<summary>
    ///Sets a <c>mat3x4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat3x4 (const std::string& uniformName, const glm::mat3x4& value);

    ///<summary>
    ///Sets a <c>mat4x2</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat4x2 (const std::string& uniformName, const glm::mat4x2& value);

    ///<summary>
    ///Sets a <c>mat4x3</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat4x3 (const std::string& uniformName, const glm::mat4x3& value);

    ///<summary>
    ///Sets a <c>mat4</c> uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformMat4 (const std::string& uniformName, const glm::mat4& value);

    ///<summary>
    ///Sets a sampler uniform in the program.
    ///</summary>
    ///<param name="uniformName">The name of the uniform as it appears in the shader code.</param>
    ///<param name="value">The value to pass to the uniform.</param>
    void SetUniformSampler (const std::string& uniformName, int value);

    ///<summary>
    ///Sets the program to the active program.
    ///</summary>
    void UseProgram () const;
};
