#include "model/Unit.h"

using namespace model;

Unit::Unit(Shape *shape, bool visible)
    : GameObject(shape, visible), m_Direction(core::vector2f(1.f,0.f)), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(Shape *shape, bool visible, const core::Vector2 &direction)
    : GameObject(shape, visible), m_Direction(direction), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(Shape *shape, bool visible, const core::Vector2 &direction, float max_speed, float accel)
    : GameObject(shape, visible), m_Direction(direction), m_fMaxSpeed(max_speed), m_fSpeed(0.f), m_fAcceleration(accel)
{
}

void Unit::move()
{
    core::Point2 new_pos = pos() + (m_Direction*m_fSpeed);
    setPos(new_pos);
    m_Shape->setCenter(new_pos);
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

