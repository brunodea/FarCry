#ifndef _FAR_CRY_POLYGONSHAPE_H_
#define _FAR_CRY_POLYGONSHAPE_H_

#include <vector>
#include "core/Vector.hpp"
#include "model/Shape.h"
#include "model/LineShape.h"

namespace model
{
    class PolygonShape:public Shape
    {
    public:
        PolygonShape();
        virtual ~PolygonShape();

        bool collided(Shape* shape);
        void addLine(const LineShape &line);
        std::vector<LineShape>* lines();

        core::Point2 center();
        void setCenter(const core::Point2 &pos);

    private:
        std::vector<LineShape> m_vLines;
    };
}

#endif // _FAR_CRY_POLYGONSHAPE_H_
