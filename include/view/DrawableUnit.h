#ifndef _FAR_CRY_DRAWABLEUNIT_H
#define _FAR_CRY_DRAWABLEUNIT_H

#include "view/Drawable.h"
#include "model/Unit.h"
#include "model/CircleShape.h"

namespace view
{
    class DrawableUnit:public Drawable
    {
        public:
            DrawableUnit();

            virtual ~DrawableUnit();

            void draw();
            void drawBounds();
            void drawDirection();
            void setCollisionShape(model::Shape *shape);

        private:
            model::Unit m_Unit;
            model::Shape* m_CollisionBounds;
    };
}

#endif // _FAR_CRY_DRAWABLEUNIT_H
