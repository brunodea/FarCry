#ifndef _ISLAND_ENGINE_ANIMATION_HPP_
#define _ISLAND_ENGINE_ANIMATION_HPP_

#include <vector>
#include "view/SingleAnim.hpp"

namespace view
{
    class Animation
    {
    public:
        Animation()
            : m_vAnimations()
        {}

        void addAnim(SingleAnim *anim)
        {
            std::vector<SingleAnim *>::iterator *it;
            for(it = m_vAnimations.begin(); it != m_vAnimations.end(); it++)
            {
                SingleAnim *a = it;
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
            std::vector<SingleAnim *>::iterator *it;
            for(it = m_vAnimations.begin(); it != m_vAnimations.end(); it++)
            {
                SingleAnim *anim = it;
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
                getAnimation(m_CurrentType)->render();
            }
        }

    private:
        std::vector<SingleAnim *> m_vAnimations;
        SingleAnim::Type m_CurrentType;
    }; //end of class Animation.
} //end of namespace view.

#endif
