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

        std::vector<counted_ptr<model::Shape> > *shapes() { return &m_Shapes; }
        void addShape(counted_ptr<model::Shape> shape) { m_Shapes.push_back(shape); }

        bool collided(AnimFrame *anim)
        {
            std::vector<counted_ptr<model::Shape> > *shapes = anim->shapes();
            for(std::vector<counted_ptr<model::Shape> >::iterator it = shapes->begin(); it != shapes->end(); it++)
            {
                counted_ptr<model::Shape> ss = *it;
                for(std::vector<counted_ptr<model::Shape> >::iterator mit = m_Shapes.begin(); mit != m_Shapes.end(); mit++)
                {
                    counted_ptr<model::Shape> s = *mit;
                    if(s.get()->collided(ss.get()))
                        return true;
                }
            }
            return false;
        }

    private:
        int m_iWidth;
        double m_fDuration;

        std::vector<counted_ptr<model::Shape> > m_Shapes;

    }; //end of class AnimFrame.
} //end of namespace view.

#endif
