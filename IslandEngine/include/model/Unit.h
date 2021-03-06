#ifndef _FAR_CRY_UNIT_H_
#define _FAR_CRY_UNIT_H_

#include <vector>
#include "core/matrix_functions.hpp"
#include "model/GameObject.hpp"
#include "model/Shape.h"

namespace model
{
    class Unit : public GameObject
    {
    public:
        Unit(bool visible);
        Unit(bool visible, const core::Vector2 &direction);
        Unit(bool visible, const core::Vector2 &direction, float max_speed, float accel);

        void rotate(float ang);

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent(int key, int state) {}

        virtual void move();
        virtual void speedUp();
        virtual void speedDown();

        /* Setters & Getters */
        void setDirection(const core::Vector2 &dir) { m_Direction = dir; }
        core::Vector2 direction() { return m_Direction; }

        void setMaxSpeed(float mspeed) { m_fMaxSpeed = mspeed; }
        float maxSpeed() { return m_fMaxSpeed; }

        void setSpeed(float speed) { m_fSpeed = speed; }
        float speed() { return m_fSpeed; }

        void setAccel(float accel) { m_fAcceleration = accel; }
        float accel() { return m_fAcceleration; }

    private:
        core::Vector2 m_Direction;

        float m_fMaxSpeed;
        float m_fSpeed;

        float m_fAcceleration;

    }; //fim da classe Unit.
} //fim do namespace model.
#endif // _FAR_CRY_UNIT_H_
