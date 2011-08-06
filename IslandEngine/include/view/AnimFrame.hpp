#ifndef _ISLAND_ENGINE_ANIM_FRAME_HPP_
#define _ISLAND_ENGINE_ANIM_FRAME_HPP_

#include "counted_ptr.h"
#include "model/Shape.h"

namespace view
{
    class AnimFrame
    {
    public:
        AnimFrame(int width, double duration, counted_ptr<Shape> shape)
            : m_iWidth(width), m_fDuration(duration), m_Shape(shape)
        {}

        int width() { return m_iWidth; }
        double duration() { return m_fDuration; }

        counted_ptr shape() { return m_Shape; }

    private:
        int m_iWidth;
        double m_fDuration;

        counted_ptr<Shape> m_Shape;

    }; //end of class AnimFrame.
} //end of namespace view.

#endif
