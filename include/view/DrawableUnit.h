#ifndef _FAR_CRY_DRAWABLEUNIT_H
#define _FAR_CRY_DRAWABLEUNIT_H

#include "model/Unit.h"
#include "model/CircleShape.h"

namespace view
{
    class DrawableUnit:public model::Unit
    {
    public:
        DrawableUnit(model::Shape *shape, bool visible);

        virtual ~DrawableUnit();

        void onRender();
        void onUpdate();

        void drawBounds();
        void drawDirection();
    };
}

#endif // _FAR_CRY_DRAWABLEUNIT_H
