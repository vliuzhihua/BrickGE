#pragma once

#include <glad/glad.h>;

#include <string>
#include <map>

#define SHADER_MAP_PARI(ShaderType) {ShaderType, #ShaderType}

class FShader
{
public:
    // Shader Program ID
    unsigned int ID = -1;

    // ��������ȡ��������ɫ��
    FShader(const GLchar* VertexPath, const GLchar* FragmentPath);
    ~FShader();
    // ʹ��/�������
    void Use();
    // uniform���ߺ���
    void SetBool(const std::string& Name, bool Value) const;
    void SetInt(const std::string& Name, int Value) const;
    void SetFloat(const std::string& Name, float Value) const;

private:
    bool CreateShader(GLuint ShaderType, const char* Path, GLuint& ShaderId);
    void DeleteShader(GLuint Shader);

    std::map<GLuint, std::string> ShaderTypeName = {
        SHADER_MAP_PARI(GL_VERTEX_SHADER),
        SHADER_MAP_PARI(GL_FRAGMENT_SHADER),
        SHADER_MAP_PARI(GL_GEOMETRY_SHADER),
        SHADER_MAP_PARI(GL_TESS_CONTROL_SHADER),
        SHADER_MAP_PARI(GL_COMPUTE_SHADER)
    };
};
