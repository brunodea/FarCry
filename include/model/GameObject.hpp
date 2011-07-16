#ifndef _FAR_CRY_GAMEOBJECT_HPP_
#define _FAR_CRY_GAMEOBJECT_HPP_

#include "core/matrix_functions.hpp"

namespace model
{
    class GameObject
    {
    public:
        GameObject() {}

        void setPos(const core::Point2 &pos) { m_Position = pos; }
        core::Point2 pos() { return m_Position; }

    protected:
    private:
        core::Point2 m_Position;
    };
}

#endif // _FAR_CRY_GAMEOBJECT_HPP_
