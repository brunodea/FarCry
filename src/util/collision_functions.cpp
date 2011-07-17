#include "util/collision_functions.h"

using namespace util;

bool util::testCollision(model::Shape *shape1, model::Shape *shape2)
{
    if(shape1->type() == model::Shape::LINE)
    {
        model::LineShape *line = (model::LineShape*)shape1;

        switch(shape2->type())
        {
            case model::Shape::LINE:
            {
                model::LineShape *line2 = (model::LineShape*)shape2;

                return testLineLineCollision(line, line2);
            }

            case model::Shape::POLYGON:
            {
                model::PolygonShape *polygon = (model::PolygonShape*)shape2;

                return testLinePolygonCollision(line, polygon);
            }

            case model::Shape::CIRCLE:
            {
                model::CircleShape *circle = (model::CircleShape*)shape2;

                return testLineCircleCollision(line, circle);
            }
        }
    }
    else if(shape1->type() == model::Shape::POLYGON)
    {
        model::PolygonShape *polygon = (model::PolygonShape*)shape1;

        switch(shape2->type())
        {
            case model::Shape::LINE:
            {
                model::LineShape *line = (model::LineShape*)shape2;

                return testLinePolygonCollision(line, polygon);
            }

            case model::Shape::POLYGON:
            {
                model::PolygonShape *polygon2 = (model::PolygonShape*)shape2;

                return testPolygonPolygonCollision(polygon2, polygon);
            }

            case model::Shape::CIRCLE:
            {
                model::CircleShape *circle = (model::CircleShape*)shape2;

                return testCirclePolygonCollision(circle, polygon);
            }
        }
    }
    else if(shape1->type() == model::Shape::CIRCLE)
    {
        model::CircleShape *circle = (model::CircleShape*)shape1;

        switch(shape2->type())
        {
            case model::Shape::LINE:
            {
                model::LineShape *line = (model::LineShape*)shape2;

                return testLineCircleCollision(line, circle);
            }

            case model::Shape::POLYGON:
            {
                model::PolygonShape *polygon = (model::PolygonShape*)shape2;

                return testCirclePolygonCollision(circle, polygon);
            }

            case model::Shape::CIRCLE:
            {
                model::CircleShape *circle2 = (model::CircleShape*)shape2;

                return testCircleCircleCollision(circle2, circle);
            }
        }
    }

    return false;

}

bool util::testLineLineCollision(model::LineShape *line1, model::LineShape *line2)
{
    core::Point2 o1 = line1->origin();
    core::Point2 e1 = line1->ending();
    core::Point2 o2 = line2->origin();
    core::Point2 e2 = line2->ending();

    float det = (e2[0] * e1[1]) - (e2[1] * e1[0]);

    core::Point2 diff = o2 - o1;

    if(det * det > 0.001 * core::norm(e1) * core::norm(e2))
    {
        double invDet = 1.0/det;

        float s;
        float t;

        s = (e2[0] * diff[1] - e2[1] * diff[0]) * invDet;
        t = (e1[0] * diff[1] - e1[1] * diff[0]) * invDet;

        if(t > 0 && t < 1 && s > 0 && s < 1)
        {
            return true;
        }
    }

    return false;
}

bool util::testLineCircleCollision(model::LineShape *line, model::CircleShape *circle)
{
    float a, b, c, r2, delta;

    core::Point2 p = line->origin();
    core::Point2 d = line->ending();
    core::Point2 circleCenter = circle->center();
    core::Point2 center = p - circleCenter;

    r2 = circle->radius() * circle->radius();

    a = d[0] * d[0] + d[1] * d[1];
    b = 2 * (circleCenter[0] * d[0] + circleCenter[1] * d[1]);
    c = circleCenter[0] * circleCenter[0] + circleCenter[1] * circleCenter[1] - r2;

    delta  = b * b - 4*a*c;

    if(delta < 0)
    {
        return false;
    }

    float s = ((-b)+sqrt(delta)) / (2*a);
    float t = ((-b)-sqrt(delta)) / (2*a);

    if((t > 0 && t < 1) || (s > 0 && s < 1))
    {
        return true;
    }

    return false;
}

bool util::testLinePolygonCollision(model::LineShape *line, model::PolygonShape *polygon)
{
    for(unsigned int i = 0; i < polygon->lines()->size(); i++)
    {
        model::LineShape *l = &polygon->lines()->at(i);

        if(testLineLineCollision(line, l))
        {
            return true;
        }
    }

    return false;
}

bool util::testCircleCircleCollision(model::CircleShape *circle1, model::CircleShape *circle2)
{
    core::Point2 c1 = circle1->center();
    core::Point2 c2 = circle2->center();

    float distance = sqrt(pow((c1[0] - c2[0]), 2) + pow((c1[1] - c2[1]), 2));

    return distance <= circle1->radius() + circle2->radius();
}

bool util::testCirclePolygonCollision(model::CircleShape *circle, model::PolygonShape *polygon)
{
    for(unsigned int i = 0; i < polygon->lines()->size(); i++)
    {
        model::LineShape *l = &polygon->lines()->at(i);

        if(testLineCircleCollision(l, circle))
        {
            return true;
        }
    }

    return true;
}

bool util::testPolygonPolygonCollision(model::PolygonShape *polygon1, model::PolygonShape *polygon2)
{
    for(unsigned int i = 0; i < polygon1->lines()->size(); i++)
    {
        model::LineShape *l1 = &polygon1->lines()->at(i);

        for(unsigned int j = 0; j < polygon2->lines()->size(); j++)
        {
            model::LineShape *l2 = &polygon2->lines()->at(j);

            if(testLineLineCollision(l1, l2))
            {
                return true;
            }
        }
    }

    return false;
}
