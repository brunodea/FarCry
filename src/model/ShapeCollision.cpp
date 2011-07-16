#include "model/ShapeCollision.h"

using namespace model;

ShapeCollision::ShapeCollision()
{
}

ShapeCollision::~ShapeCollision()
{
}

static bool ShapeCollision(Shape *shape1, Shape *shape2)
{
    if(shape1->type() == Shape::LINE)
    {
        LineShape *line = (LineShape*)shape1;

        switch(shape2->type())
        {
            case Shape::LINE:
            {
                LineShape *line2 = (LineShape*)shape2;

                return ShapeCollision::testLineLineCollision(line, line2);
            }

            case Shape::POLYGON:
            {
                PolygonShape *polygon = (PolygonShape*)shape2;

                return ShapeCollision::testLinePolygonCollision(line, polygon);
            }

            case Shape::CIRCLE:
            {
                CircleShape *circle = (CircleShape*)shape2;

                return ShapeCollision::testLineCircleCollision(line, circle);
            }
        }
    }
    else if(shape1->type() == Shape::POLYGON)
    {
        PolygonShape *polygon = (PolygonShape*)shape1;

        switch(shape2->type())
        {
            case Shape::LINE:
            {
                LineShape *line = (LineShape*)shape2;

                return ShapeCollision::testLinePolygonCollision(line, polygon);
            }

            case Shape::POLYGON:
            {
                PolygonShape *polygon2 = (PolygonShape*)shape2;

                return ShapeCollision::testPolygonPolygonCollision(polygon2, polygon);
            }

            case Shape::CIRCLE:
            {
                CircleShape *circle = (CircleShape*)shape2;

                return ShapeCollision::testCirclePolygonCollision(circle, polygon);
            }
        }
    }
    else if(shape1->type() == Shape::CIRCLE)
    {
        CircleShape *circle = (CircleShape*)shape1;

        switch(shape2->type())
        {
            case Shape::LINE:
            {
                LineShape *line = (LineShape*)shape2;

                return ShapeCollision::testLineCircleCollision(line, circle);
            }

            case Shape::POLYGON:
            {
                PolygonShape *polygon = (PolygonShape*)shape2;

                return ShapeCollision::testCirclePolygonCollision(circle, polygon);
            }

            case Shape::CIRCLE:
            {
                CircleShape *circle2 = (CircleShape*)shape2;

                return ShapeCollision::testCircleCircleCollision(circle2, circle);
            }
        }
    }
}

bool ShapeCollision::testLineLineCollision(LineShape *line1, LineShape *line2)
{

}

bool ShapeCollision::testLineCircleCollision(LineShape *line, CircleShape *circle)
{

}

bool ShapeCollision::testLinePolygonCollision(LineShape *line, PolygonShape *polygon)
{

}

bool ShapeCollision::testCircleCircleCollision(CircleShape *circle1, CircleShape *circle2)
{

}

bool ShapeCollision::testCirclePolygonCollision(CircleShape *circle, PolygonShape *polygon)
{

}

bool ShapeCollision::testPolygonPolygonCollision(PolygonShape *polygon1, PolygonShape *polygon2)
{

}
