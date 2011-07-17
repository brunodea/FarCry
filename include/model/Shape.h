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

        virtual void draw() = 0;

        virtual bool collided(Shape* shape) = 0;

        virtual core::Point2 center() = 0;
        virtual void setCenter(const core::Point2 &pos) = 0;

        virtual void rotate(float angle) = 0;

        Type type() { return m_Type; }

    private:
        Type m_Type;
    };
}

#endif // ___SHAPE_H___
