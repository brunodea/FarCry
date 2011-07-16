#ifndef _FAR_CRY_UNIT_H_
#define _FAR_CRY_UNIT_H_

#include "core/matrix_functions.hpp"
#include "model/GameObject.hpp"

namespace model
{
    class Unit : public GameObject
    {
    public:
        Unit();
        Unit(const core::Vector2 &direction);
        Unit(const core::Vector2 &direction, float max_speed, float speed, float max_accel, float accel);

        /* Virtual Functions */
        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onKeyEvent(int key, int state) {}

        /* Setters & Getters */
        void setDirection(const core::Vector2 &dir) { m_Direction = dir; }
        core::Vector2 direction() { return m_Direction; }

        void setMaxSpeed(float mspeed) { m_fMaxSpeed = mspeed; }
        float maxSpeed() { return m_fMaxSpeed; }

        void setSpeed(float speed) { m_fSpeed = speed; }
        float speed() { return m_fSpeed; }

        void setMaxAccel(float maccel) { m_fMaxAcceleration = maccel; }
        float maxAccel() { return m_fMaxAcceleration; }

        void setAccel(float accel) { m_fAcceleration = accel; }
        float accel() { return m_fAcceleration; }

    private:
        core::Vector2 m_Direction;

        float m_fSpeed;
        float m_fMaxSpeed;

        float m_fAcceleration;
        float m_fMaxAcceleration;
    }; //fim da classe Unit.
} //fim do namespace model.
#endif // _FAR_CRY_UNIT_H_
