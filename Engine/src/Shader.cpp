#include "Engine/Shader.h"

namespace Engine {
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) 
    : m_ID(glCreateProgram())
    {
        //1. Retrieve vertex/fragment source code from files
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            //Read file's buffer contents into streams
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            //close file handlers
            vShaderFile.close();
            fShaderFile.close();
            //convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } 
        catch(std::ifstream::failure e) {
            std::cout << "ERROR::ENGINE::SHADER::UNSUCCESSFUL_FILE_READ" << std::endl;		
        }
        
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();

        //2. Compile shaders
        unsigned int vertex, fragment;
        int success;
        char infolog[512];

        //vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);	
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        
        //print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infolog);
            std::cout << "ERROR::ENGINE::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
        }
        
        //fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        
        //print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infolog);
            std::cout << "ERROR::ENGINE::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
        }

        //3. Shader program
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_ID, 512, NULL, infolog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
        }

        //delete shaders, no longer necessary after linked to program
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use() const {
        glUseProgram(m_ID);
    }

    void Shader::setBool(const std::string name, const bool value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);	
    }

    void Shader::setInt(const std::string name, const int value) const {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string name, const float value) const {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void Shader::setVec3(const std::string name, const glm::vec3 &vec) const {
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(vec));
    }

    void Shader::setMat4(const std::string name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
}