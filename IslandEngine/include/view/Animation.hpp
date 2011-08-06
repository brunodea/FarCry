#ifndef _ISLAND_ENGINE_ANIMATION_HPP_
#define _ISLAND_ENGINE_ANIMATION_HPP_

#include <vector>
#include <string>
#include "glfw.h"
#include "view/SingleAnim.hpp"
#include "core/matrix_functions.hpp"

namespace view
{
    class Animation
    {
    public:
        Animation(const core::Point2 &pos, GLuint image_id = -1)
            : m_vAnimations(), m_Pos(pos), m_iImageID(image_id)
        {
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
                getAnimation(m_CurrentType)->render(m_Pos, file_y, m_iImageID);
            }
        }

        void setPos(const core::Point2 &pos) { m_Pos = pos; }

    private:
        std::vector<SingleAnim *> m_vAnimations;
        SingleAnim::Type m_CurrentType;
        core::Point2 m_Pos;
        GLuint m_iImageID;
    }; //end of class Animation.
} //end of namespace view.

#endif
