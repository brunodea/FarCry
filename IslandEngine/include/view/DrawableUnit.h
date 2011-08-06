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
        DrawableUnit(std::vector<model::Shape*> shapes, bool visible = true, GLuint image_id = -1);

        virtual ~DrawableUnit();

        void onRender();
        void onUpdate();

        void drawBounds();
        void drawDirection();
    protected:
        Animation *m_Animation;
    };
}

#endif // _FAR_CRY_DRAWABLEUNIT_H
