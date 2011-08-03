#include "model/Unit.h"
#include "util/math_aux.hpp"

using namespace model;

Unit::Unit(std::vector<Shape*> shapes, bool visible)
    : GameObject(shapes, visible), m_Direction(core::vector2f(1.f,0.f)), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(std::vector<Shape*> shapes, bool visible, const core::Vector2 &direction)
    : GameObject(shapes, visible), m_Direction(direction), m_fMaxSpeed(0.f), m_fSpeed(0.f), m_fAcceleration(0.f)
{
}

Unit::Unit(std::vector<Shape*> shapes, bool visible, const core::Vector2 &direction, float max_speed, float accel)
    : GameObject(shapes, visible), m_Direction(direction), m_fMaxSpeed(max_speed), m_fSpeed(0.f), m_fAcceleration(accel)
{
}

void Unit::move()
{
    core::Point2 new_pos = pos() + (m_Direction*m_fSpeed);
    setPos(new_pos);

    for(unsigned int i = 0; i < shapes().size(); i++)
    {
        shapes().at(i)->setCenter(new_pos);
    }

    //shape()->setCenter(new_pos);
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

    for(unsigned int i = 0; shapes().size(); i++)
    {
        shapes().at(i)->rotate(ang);
    }
    //shape()->rotate(ang);

    core::Matrix3 transf_mat = core::rotate2d(ang);
    core::Vector3 dir = core::toVector3f(m_Direction);
    dir = transf_mat*dir;

    m_Direction = core::toVector2f(dir);
}
