#ifndef _ISLAND_ENGINE_SINGLE_ANIM_HPP_
#define _ISLAND_ENGINE_SINGLE_ANIM_HPP_

#include <vector>
#include "glfw.h"
#include "view/AnimFrame.hpp"

namespace view
{
    class SingleAnim
    {
    public:
        enum Type
        {
            STANDING = 0,
            RUNNING,
            DYING
        }; //end of enum Type.
    public:
        SingleAnim(Type type)
            : m_iCurrentFrame(0), m_vFrames(), m_fLastTime(-1), m_Type(type)
        {}

        ~SingleAnim()
        {
            for(unsigned int i = 0; i < m_vFrames.size(); i++)
                delete m_vFrames.at(i);
            delete m_vFrames;
        }

        void addFrame(AnimFrame *frame) { m_vFrames.push_back(frame); }
        void nextFrame()
        {
            m_iCurrentFrame++;
            if(m_iCurrentFrame >= m_vFrames.size())
                m_iCurrentFrame = 0;
        }

        AnimFrame *currentFrame()
        {
            if(!m_vFrames.empty())
                return m_vFrames.at(m_iCurrentFrame);
        }

        void resetAnim()
        {

        }

        void render()
        {

        }

        Type type() { return m_Type; }

    private:
        void changeFrame()
        {
            if(!m_vFrames.empty())
            {
                double time = glfwGetTime();

                if(m_fLastTime < 0)
                    m_fLastTime = time;

                double diff = time - m_fLastTime;
                if(diff >= m_vFrames.at(m_iCurrentFrame).duration())
                {
                    nextFrame();
                    m_fLastTime = time;
                }
            }
        }

    private:
        int m_iCurrentFrame;
        std::vector<AnimFrame *> m_vFrames;

        double m_fLastTime; //time ellapsed since the animation started.

        Type m_Type;
    }; //end of class SingleAnim.
} //end of namespace view.

#endif
