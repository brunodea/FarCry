#ifndef _FAR_CRY_SHAPE_H_
#define _FAR_CRY_SHAPE_H_

#include "core/matrix_functions.hpp"

namespace model
{
    class Shape
    {
    public:
        enum Type
        {
            LINE = 0,
            CIRCLE,
            POLYGON
        };

    public:
        Shape(Type type) : m_Type(type) {}

        virtual bool collided(Shape*) = 0;
        virtual core::Point2 center() = 0;


        Type type() { return m_Type; }

    private:
        Type m_Type;
    };
}

#endif // ___SHAPE_H___
