#include "Unit.h"

using namespace model;

Unit::Unit()
    : m_Direction(core::vector2f(1.f,0.f)), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fMaxAcceleration(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(const core::Vector2 &direction)
    : m_Direction(direction), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fMaxAcceleration(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(const core::Vector2 &direction, float max_speed, float speed, float max_accel, float accel)
    : m_Direction(direction), m_fMaxSpeed(max_speed), m_fSpeed(speed),
      m_fMaxAcceleration(max_accel), m_fAcceleration(accel)
{
}
