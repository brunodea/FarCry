#ifndef _FAR_CRY_DRAWABLEUNIT_H
#define _FAR_CRY_DRAWABLEUNIT_H

#include "model/Unit.h"
#include "model/CircleShape.h"
#include "view/Animation.hpp"

namespace view
{
    class DrawableUnit:public model::Unit
    {
    public:
        DrawableUnit(bool visible = true, GLuint image_id = -1);

        virtual ~DrawableUnit();

        void onRender();
        void onUpdate();

        void drawBounds();
        void drawDirection();
    };
}

#endif // _FAR_CRY_DRAWABLEUNIT_H
