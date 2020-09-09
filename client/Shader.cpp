#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

FShader::FShader(const char* VertexPath, const char* FragmentPath)
{
    GLuint VertexShader, FragShader;

    if (!CreateShader(GL_VERTEX_SHADER, VertexPath, VertexShader)) {
        std::cout << "Shader Create Failed " << VertexPath << " :::: " << FragmentPath << std::endl;
        return;
    }

    if (!CreateShader(GL_FRAGMENT_SHADER, FragmentPath, FragShader)) {
        std::cout << "Shader Create Failed " << VertexPath << " :::: " << FragmentPath << std::endl;
        DeleteShader(VertexShader);
        return;
    }
    GLint Success;
    ID = glCreateProgram();
    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        char InfoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << InfoLog << std::endl;
    }

    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
    glDeleteShader(VertexShader);
    glDeleteShader(FragShader);
}

FShader::~FShader() {
    if (ID != -1)
        glDeleteProgram(ID);
}

void FShader::Use()
{
    glUseProgram(ID);
}

void FShader::SetBool(const std::string& Name, bool Value) const
{
    glUniform1i(glGetUniformLocation(ID, Name.c_str()), (int)Value);
}
void FShader::SetInt(const std::string& Name, int Value) const
{
    glUniform1i(glGetUniformLocation(ID, Name.c_str()), Value);
}
void FShader::SetFloat(const std::string& Name, float Value) const
{
    glUniform1f(glGetUniformLocation(ID, Name.c_str()), Value);
}

bool FShader::CreateShader(GLuint ShaderType, const char* Path, GLuint& ShaderId) {
    std::string ShaderCode;
    std::ifstream vShaderFile;
    // ��֤ifstream��������׳��쳣��
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        vShaderFile.open(Path);
        std::stringstream vShaderStream, fShaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        vShaderStream << vShaderFile.rdbuf();
        // �ر��ļ�������
        vShaderFile.close();
        // ת����������string
        ShaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n " << "ShaderType: " << ShaderTypeName[ShaderType] << "\nPath: " << Path << std::endl;
        return false;
    }
    const char* vShaderCode = ShaderCode.c_str();

    // 2. ������ɫ��
    int success;
    char infoLog[512];
    // ������ɫ��
    ShaderId = glCreateShader(ShaderType);
    glShaderSource(ShaderId, 1, &vShaderCode, NULL);
    glCompileShader(ShaderId);
    // ��ӡ�����������еĻ���
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "ShaderType:: " << ShaderTypeName[ShaderType] << "\nInfo:: " << infoLog << std::endl;
        return false;
    };
    return true;
}

void FShader::DeleteShader(GLuint ShaderId) {
    glDeleteShader(ShaderId);
}