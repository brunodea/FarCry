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

        void draw();

        bool collided(Shape* shape);
        void addLine(const LineShape &line);
        void rotate(float angle);

        std::vector<LineShape>* lines();

        core::Point2 center();
        void setCenter(const core::Point2 &pos);

    private:
        void adjustCenter();

    private:
        std::vector<LineShape> m_vLines;

        core::Point2 m_Center;
    };
}

#endif // _FAR_CRY_POLYGONSHAPE_H_
