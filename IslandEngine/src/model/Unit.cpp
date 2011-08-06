#include "model/Unit.h"
#include "util/math_aux.hpp"

using namespace model;

Unit::Unit(bool visible)
    : GameObject(visible), m_Direction(core::vector2f(1.f,0.f)), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(bool visible, const core::Vector2 &direction)
    : GameObject(visible), m_Direction(direction), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(bool visible, const core::Vector2 &direction, float max_speed, float accel)
    : GameObject(visible), m_Direction(direction), m_fMaxSpeed(max_speed), m_fSpeed(0.f), m_fAcceleration(accel)
{
}

void Unit::move()
{
    core::Point2 new_pos = pos() + (m_Direction*m_fSpeed);
    setPos(new_pos);

    animation()->setShapesCenter(new_pos);
}

void Unit::speedUp()
{
    m_fSpeed += m_fAcceleration;
    if(m_fSpeed > m_fMaxSpeed)
        m_fSpeed = m_fMaxSpeed;
}

void Unit::speedDown()
{
    m_fSpeed -= m_fAcceleration;
    if(m_fSpeed < 0.f)
        m_fSpeed = 0.f;
}

void Unit::rotate(float ang)
{
    setAngle(util::degreeToRad(angle())+ang);

    animation()->rotateShapes(ang);

    core::Matrix3 transf_mat = core::rotate2d(ang);
    core::Vector3 dir = core::toVector3f(m_Direction);
    dir = transf_mat*dir;

    m_Direction = core::toVector2f(dir);
}
