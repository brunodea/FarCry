#ifndef _FAR_CRY_GAMEOBJECT_HPP_
#define _FAR_CRY_GAMEOBJECT_HPP_

#include <vector>
#include "core/matrix_functions.hpp"
#include "util/math_aux.hpp"
#include "model/Shape.h"

namespace model
{
    class GameObject
    {
    public:
        GameObject(std::vector<Shape*> shape, bool visible)
            : m_Position(0), m_vShape(shape), m_bVisible(visible), m_bExists(true), m_fAngle(0.f), m_iType(-1)
        {}

        virtual ~GameObject()
        {
            m_vShape.clear();
        }

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent(int key, int state) {}
        virtual void onCollision(GameObject *obj) {}

        /* Setters & Getters */
        void setPos(const core::Point2 &pos) { m_Position = pos; }
        core::Point2 pos() { return m_Position; }

        void addShape(Shape *shape) { m_vShape.push_back(shape); }
        std::vector<Shape*> shapes() { return m_vShape; }
        Shape* shape(unsigned int index) { return (Shape*)m_vShape.at(index); }

        bool isVisible() { return m_bVisible; }
        void setVisible(bool visible) { m_bVisible = visible; }
        void toggleVisible() { m_bVisible = !m_bVisible; }

        bool exists() { return m_bExists; }
        void setExists(bool exists) { m_bExists = exists; }

        virtual void rotate(float ang)
        {
            m_fAngle += util::radToDegree(ang);

            for(unsigned int i = 0; i < m_vShape.size(); i++)
            {
                ((Shape*)m_vShape.at(i))->rotate(ang);
            }
        }

        float angle() { return m_fAngle; }
        virtual void setAngle(float angle) { m_fAngle = util::radToDegree(angle); }

        int type() { return m_iType; }
        void setType(int type) { m_iType = type; }

    private:
        core::Point2 m_Position;
        std::vector<Shape*> m_vShape;

        bool m_bVisible;
        bool m_bExists;

        float m_fAngle;

        int m_iType;
    };
}

#endif // _FAR_CRY_GAMEOBJECT_HPP_
