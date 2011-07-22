#ifndef _FAR_CRY_GAMEOBJECT_HPP_
#define _FAR_CRY_GAMEOBJECT_HPP_

#include "core/matrix_functions.hpp"
#include "util/math_aux.hpp"
#include "model/Shape.h"

namespace model
{
    class GameObject
    {
    public:
        GameObject(Shape *shape, bool visible)
            : m_Position(0), m_Shape(shape), m_bVisible(visible), m_bExists(true), m_fAngle(0.f)
        {}

        virtual ~GameObject()
        {
            delete m_Shape;
        }

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent(int key, int state) {}
        virtual void onCollision(GameObject *obj) = 0;

        /* Setters & Getters */

        void setPos(const core::Point2 &pos) { m_Position = pos; }
        core::Point2 pos() { return m_Position; }

        void setShape(Shape *shape) { m_Shape = shape; }
        Shape *shape() { return m_Shape; }

        bool isVisible() { return m_bVisible; }
        void setVisible(bool visible) { m_bVisible = visible; }
        void toggleVisible() { m_bVisible = !m_bVisible; }

        bool exists() { return m_bExists; }
        void setExists(bool exists) { m_bExists = exists; }

        virtual void rotate(float ang)
        {
            m_fAngle += util::radToDegree(ang);
            m_Shape->rotate(ang);
        }

        float angle() { return m_fAngle; }
        virtual void setAngle(float angle) { m_fAngle = util::radToDegree(angle); }

    private:
        core::Point2 m_Position;
        Shape *m_Shape;

        bool m_bVisible;
        bool m_bExists;

        float m_fAngle;
    };
}

#endif // _FAR_CRY_GAMEOBJECT_HPP_
