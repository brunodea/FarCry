#ifndef _ISLAND_ENGINE_TEXTURE_HPP
#define _ISLAND_ENGINE_TEXTURE_HPP

#include <map>
#include <string>
#include "glfw.h"

#include <iostream>

namespace view
{
    class Texture
    {
    public:

        static GLuint addTexture(const std::string &path, const std::string &name = path)
        {
            std::map<std::string, int>::iterator it = m_sTexturesMap.find(name);
            GLuint tex = -1;
            if(it == m_sTexturesMap::end())
            {
                tex = loadTexture(path.c_str());
                if(tex != -1)
                    m_sTexturesMap.insert(std::pair<std::string, int>(name, tex));
            }
            else
                tex = it->second;

            return tex;
        }

        static GLuint texture(const std::string &name)
        {
            std::map<std::string, int>::iterator it = m_sTexturesMap.find(name);
            if(it == m_sTexturesMap::end())
                return -1;
            return it->second;
        }

        static void remove(const std::string &name)
        {
            GLuint id = texture(name);
            if(id != -1)
                glDeleteTextures(1, &id);
        }

        static void clear()
        {
            std::map<std::string, int>::iterator it;
            for(it = m_sTexturesMap.begin(); it != m_sTexturesMap.end(); it++)
                glDeleteTextures(1, &it->second);
        }

    private:
        static GLuint loadTexture(const char *path)
        {
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            if(glfwLoadTexture2D(path, GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT))
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                std::cout << "Image " << path << " successfully loaded." << std::endl;
                return texture;
            }

            std::cout << "Image " << path << " couldn't be loaded." << std::endl;
            return -1;
        }
    private:
        static std::map<std::string, int> m_sTexturesMap;
    }; //end of class Texture.
} //end of namespace view.

#endif
