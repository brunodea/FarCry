#ifndef _FAR_CRY_GAMEOBJECT_HPP_
#define _FAR_CRY_GAMEOBJECT_HPP_

#include <vector>
#include "core/matrix_functions.hpp"
#include "util/math_aux.hpp"
#include "view/Animation.hpp"
#include "view/SingleAnim.hpp"

namespace model
{
    class GameObject
    {
    public:
        GameObject(bool visible = true)
            : m_Position(0), m_bVisible(visible), m_bExists(true), m_fAngle(0.f), m_iType(-1)
        {
            m_Animation = new view::Animation(m_Position);
        }

        virtual ~GameObject()
        {
            delete m_Animation;
        }

        virtual void rotate(float ang)
        {
            m_fAngle += util::radToDegree(ang);

            m_Animation->rotateShapes(ang);
            m_Animation->setAngle(m_fAngle);
        }

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent(int key, int state) {}
        virtual void onCollision(GameObject *obj) {}

        /* Setters & Getters */
        void setPos(const core::Point2 &pos)
        {
            m_Position = pos;
            m_Animation->setPos(pos);
        }
        core::Point2 pos() { return m_Position; }

        bool isVisible() { return m_bVisible; }
        void setVisible(bool visible) { m_bVisible = visible; }
        void toggleVisible() { m_bVisible = !m_bVisible; }

        bool exists() { return m_bExists; }
        void setExists(bool exists) { m_bExists = exists; }

        float angle() { return m_fAngle; }
        virtual void setAngle(float angle)
        {
            m_fAngle = util::radToDegree(angle);
            m_Animation->setAngle(m_fAngle);
        }

        int type() { return m_iType; }
        void setType(int type) { m_iType = type; }

        view::Animation *animation() { return m_Animation; }

    private:
        view::Animation *m_Animation;
        core::Point2 m_Position;

        bool m_bVisible;
        bool m_bExists;

        float m_fAngle;

        int m_iType;
    };
}

#endif // _FAR_CRY_GAMEOBJECT_HPP_
