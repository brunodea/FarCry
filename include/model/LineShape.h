#ifndef _FAR_CRY_LINESHAPE_H_
#define _FAR_CRY_LINESHAPE_H_

#include "core/matrix_functions.hpp"
#include "core/Vector.hpp"
#include "model/Shape.h"
//#include "model/ShapeCollision.h"

namespace model
{
    class LineShape:public Shape
    {
    public:
        LineShape();
        virtual ~LineShape();
        bool collided(Shape*);

        void setOrigin(core::Point2&);
        void setEnding(core::Point2&);

        core::Point2 origin();
        core::Point2 ending();

        core::Point2 center();
        void setCenter(const core::Point2 &pos);

    private:
        core::Point2 m_Origin;
        core::Point2 m_Ending;
    };
}

#endif
