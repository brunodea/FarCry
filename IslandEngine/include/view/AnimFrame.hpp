#ifndef _ISLAND_ENGINE_ANIM_FRAME_HPP_
#define _ISLAND_ENGINE_ANIM_FRAME_HPP_

#include <vector>
#include "counted_ptr.h"
#include "model/Shape.h"

namespace view
{
    class AnimFrame
    {
    public:
        AnimFrame(int width, double duration)
            : m_iWidth(width), m_fDuration(duration), m_Shapes()
        {}

        int width() { return m_iWidth; }
        double duration() { return m_fDuration; }

        std::vector<model::Shape *> *shapes() { return &m_Shapes; }
        void addShape(model::Shape *shape) { m_Shapes.push_back(shape); }

        bool collided(AnimFrame *anim)
        {
            std::vector<model::Shape *> *shapes = anim->shapes();
            for(std::vector<model::Shape *>::iterator it = shapes->begin(); it != shapes->end(); it++)
            {
                model::Shape *ss = *it;
                for(std::vector<model::Shape *>::iterator mit = m_Shapes.begin(); mit != m_Shapes.end(); mit++)
                {
                    model::Shape *s = *mit;
                    if(s->collided(ss))
                        return true;
                }
            }
            return false;
        }

        void rotateShapes(float rad)
        {
            for(std::vector<model::Shape *>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); it++)
            {
                model::Shape *s = *it;
                s->rotate(rad);
            }
        }

        void setShapesCenter(const core::Point2 &center)
        {
            for(std::vector<model::Shape *>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); it++)
            {
                model::Shape *s = *it;
                s->setCenter(center);
            }
        }

        void drawShapes()
        {
            for(std::vector<model::Shape *>::iterator it = m_Shapes.begin(); it != m_Shapes.end(); it++)
            {
                model::Shape *s = *it;
                s->draw();
            }
        }

    private:
        int m_iWidth;
        double m_fDuration;

        std::vector<model::Shape *> m_Shapes;

    }; //end of class AnimFrame.
} //end of namespace view.

#endif
