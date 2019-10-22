#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Texture.h"

namespace Engine {
    Texture::Texture(const std::string &path, GLint sWrap, GLint tWrap, GLint minFilter, GLint maxFilter)
    {
        glGenTextures(1, &m_ID);
        int width, height, nrComponents;
        //stbi_set_flip_vertically_on_load(true);     //flips orientation of image to be upright
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if(data) {
            GLenum format;
            if(nrComponents == 1)
                format = GL_RED;
            else if(nrComponents == 3)
                format = GL_RGB;
            else if(nrComponents == 4)
                format = GL_RGBA;
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_ID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
        }
        else {
            std::cout << "Failed to load texture at path: " << path << std::endl;
        }

        stbi_image_free(data);
    }

    void Texture::setType(const std::string& type) {
        m_type = type;
    }

    //get ID (unsigned int) of texture object
    unsigned int Texture::getID() const {
        return m_ID;
    }

    std::string Texture::getType() const {
        return m_type;
    }

    void Texture::bind() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }
}