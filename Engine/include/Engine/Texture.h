#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "stb_image.h"

#include <string>
#include <iostream>

namespace Engine {
    class Texture {
    public:
        Texture(const std::string &path, 
                GLint sWrap = GL_REPEAT, 
                GLint tWrap = GL_REPEAT, 
                GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, 
                GLint maxFilter = GL_LINEAR);

        void setType(const std::string& type);
        unsigned int getID() const;    //get ID (unsigned int) of texture object
        std::string getType() const;
        void bind() const;

    private:
        unsigned int m_ID;
        std::string m_type;
    };
}