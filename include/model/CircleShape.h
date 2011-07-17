#ifndef _FAR_CRY_CIRCLESHAPE_H_
#define _FAR_CRY_CIRCLESHAPE_H_

#include "core/matrix_functions.hpp"
#include "core/Vector.hpp"
#include "model/Shape.h"
#include "model/LineShape.h"
#include "model/PolygonShape.h"

namespace model
{
    class CircleShape:public Shape
    {
    public:
        CircleShape();
        virtual ~CircleShape();

        bool collided(Shape* shape);

        void setRadius(float radius);
        float radius();

        void setCenter(const core::Point2 &center);
        core::Point2 center();

    private:
        float m_Radius;
        core::Point2 m_Center;
    };
}

#endif // _FAR_CRY_CIRCLESHAPE_H_
