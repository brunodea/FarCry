#ifndef _ISLAND_ENGINE_ANIMATION_HPP_
#define _ISLAND_ENGINE_ANIMATION_HPP_

#include <vector>
#include <string>
#include "glfw.h"
#include "view/SingleAnim.hpp"
#include "core/matrix_functions.hpp"

#include <iostream>

namespace view
{
    class Animation
    {
    public:
        Animation(const core::Point2 &pos, GLuint image_id = -1)
            : m_vAnimations(), m_Pos(pos), m_iImageID(image_id), m_fAngle(0.f), m_iTextureWidth(1), m_iTextureHeight(1)
        {
        }

        ~Animation()
        {
            for(unsigned int i = 0; i < m_vAnimations.size(); i++)
                delete m_vAnimations.at(i);
        }

        void addAnim(SingleAnim *anim)
        {
            std::vector<SingleAnim *>::iterator it;
            for(it = m_vAnimations.begin(); it != m_vAnimations.end(); it++)
            {
                SingleAnim *a = *it;
                if(a->type() == anim->type())
                {
                    m_vAnimations.erase(it);
                    delete a;
                    break;
                }
            }
            m_CurrentType = anim->type();
            m_vAnimations.push_back(anim);
        }

        SingleAnim *getAnimation(SingleAnim::Type type)
        {
            std::vector<SingleAnim *>::iterator it;
            for(it = m_vAnimations.begin(); it != m_vAnimations.end(); it++)
            {
                SingleAnim *anim = *it;
                if(anim->type() == type)
                    return anim;
            }
            return NULL;
        }

        bool setCurrentType(SingleAnim::Type type)
        {
            if(getAnimation(type) == NULL)
                return false;
            m_CurrentType = type;
            return true;
        }

        void render()
        {
            if(m_vAnimations.size() > 0)
            {
                int file_y = 0;
                for(unsigned int i = 0; i < m_vAnimations.size(); i++)
                {
                    SingleAnim *sanim = m_vAnimations.at(i);
                    if(sanim->type() == m_CurrentType)
                        break;
                    file_y += sanim->height();
                }
                glPushMatrix();
                    glTranslatef(m_Pos[0],m_Pos[1],0);
                    glRotatef(m_fAngle, 0.f,0.f,1.f);
                    glTranslatef(-1*m_Pos[0],-1*m_Pos[1],0);
                    getAnimation(m_CurrentType)->render(m_Pos, file_y, m_iImageID, m_iTextureWidth, m_iTextureHeight);
                glPopMatrix();
            }
        }

        void rotateShapes(float rad)
        {
            for(unsigned int i = 0; i < m_vAnimations.size(); i++)
                m_vAnimations.at(i)->rotateShapes(rad);
        }

        void setShapesCenter(const core::Point2 &center)
        {
            for(unsigned int i = 0; i < m_vAnimations.size(); i++)
                m_vAnimations.at(i)->setShapesCenter(center);
        }

        void setPos(const core::Point2 &pos) { m_Pos = pos; }
        void setAngle(float degrees) { m_fAngle = degrees; }

        SingleAnim *currentSingleAnim()
        {
            if(m_vAnimations.empty())
                return NULL;
            return getAnimation(m_CurrentType);
        }

        void setImageID(GLuint image_id) { m_iImageID = image_id; }
        void setTextureWidth(int w) { m_iTextureWidth = w; }
        void setTextureHeight(int h) { m_iTextureHeight = h; }
        void setTextureSize(int w, int h)
        {
            setTextureWidth(w);
            setTextureHeight(h);
        }

    private:
        std::vector<SingleAnim *> m_vAnimations;
        SingleAnim::Type m_CurrentType;
        core::Point2 m_Pos;
        GLuint m_iImageID;

        float m_fAngle;
        int m_iTextureWidth;
        int m_iTextureHeight;
    }; //end of class Animation.
} //end of namespace view.

#endif
