#ifndef _ISLAND_ENGINE_SINGLE_ANIM_HPP_
#define _ISLAND_ENGINE_SINGLE_ANIM_HPP_

#include <vector>
#include "glfw.h"
#include "view/AnimFrame.hpp"
#include "core/matrix_functions.hpp"

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
        SingleAnim(Type type, int height)
            : m_iCurrentFrame(0), m_vFrames(), m_fLastTime(-1), m_Type(type), m_iHeight(height), m_fAngle(0.f)
        {}

        ~SingleAnim()
        {
            for(unsigned int i = 0; i < m_vFrames.size(); i++)
                delete m_vFrames.at(i);
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

        void render(const core::Point2 &pos, int file_y, GLuint texture_id)
        {
            if(m_vFrames.empty())
                return;

            AnimFrame *curr_frame = m_vFrames.at(m_iCurrentFrame);
            int curr_width = curr_frame->width();

            core::Point2 v1 = core::point2f(curr_width/-2.f,m_iHeight/-2.f);
            core::Point2 v2 = core::point2f(curr_width/2.f,m_iHeight/-2.f);
            core::Point2 v3 = core::point2f(curr_width/2.f,m_iHeight/2.f);
            core::Point2 v4 = core::point2f(curr_width/-2.f,m_iHeight/2.f);

            v1 += pos;
            v2 += pos;
            v3 += pos;
            v4 += pos;

            int file_x = 0;
            for(unsigned int i = 0; i < m_iCurrentFrame; i++)
                file_x += curr_frame->width();

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glColor4f(1.f, 1.f, 1.f, 1.f);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id);

            glPushMatrix();
                glRotatef(m_fAngle, 0,0,1.f);
                glBegin(GL_QUADS);
                    glTexCoord2d(file_x,file_y);
                    glVertex2f(v1[0],v1[1]);

                    glTexCoord2d(file_x+curr_width, file_y);
                    glVertex2f(v2[0],v2[1]);

                    glTexCoord2d(file_x+curr_width, file_y+m_iHeight);
                    glVertex2f(v3[0],v3[1]);

                    glTexCoord2d(file_x, file_y+m_iHeight);
                    glVertex2f(v4[0],v4[1]);
                glEnd();

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            glPopMatrix();
        }

        Type type() { return m_Type; }
        int height() { return m_iHeight; }
        void setAngle(float degrees) { m_fAngle = degrees; }

    private:
        void changeFrame()
        {
            if(!m_vFrames.empty())
            {
                double time = glfwGetTime();

                if(m_fLastTime < 0)
                    m_fLastTime = time;

                double diff = time - m_fLastTime;
                if(diff >= m_vFrames.at(m_iCurrentFrame)->duration())
                {
                    nextFrame();
                    m_fLastTime = time;
                }
            }
        }

    private:
        unsigned int m_iCurrentFrame;
        std::vector<AnimFrame *> m_vFrames;

        double m_fLastTime; //time ellapsed since the animation started.

        Type m_Type;
        int m_iHeight;

        float m_fAngle;
    }; //end of class SingleAnim.
} //end of namespace view.

#endif
