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
        bool collided(Shape*);
        void addLine(const LineShape&);
        std::vector<LineShape>* lines();

    private:
        std::vector<LineShape> m_vLines;
    };
}

#endif // _FAR_CRY_POLYGONSHAPE_H_
