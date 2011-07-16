#ifndef _FAR_CRY_GAMEOBJECT_HPP_
#define _FAR_CRY_GAMEOBJECT_HPP_

#include "core/matrix_functions.hpp"
#include "model/Shape.h"

namespace model
{
    class GameObject
    {
    public:
        GameObject(const Shape &shape)
            : m_Position(0), m_Shape(shape)
        {}

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent() {}

        /* Setters & Getters */

        void setPos(const core::Point2 &pos) { m_Position = pos; }
        core::Point2 pos() { return m_Position; }

        void setShape(const Shape &shape) { m_Shape = shape; }
        Shape shape() { return m_Shape; }

    private:
        core::Point2 m_Position;
        Shape m_Shape;
    };
}

#endif // _FAR_CRY_GAMEOBJECT_HPP_
