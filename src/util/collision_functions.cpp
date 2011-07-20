#include <iostream>
#include "util/collision_functions.h"

#define Nmax 10

struct point { int x, y; char c; };
struct line { struct point p1, p2; };
struct point polygon[Nmax];

int ccw(struct point p0,
        struct point p1,
        struct point p2 )
{
    int dx1, dx2, dy1, dy2;
    dx1 = p1.x - p0.x; dy1 = p1.y - p0.y;
    dx2 = p2.x - p0.x; dy2 = p2.y - p0.y;
    if (dx1*dy2 > dy1*dx2) return +1;
    if (dx1*dy2 < dy1*dx2) return -1;
    if ((dx1*dx2 < 0) || (dy1*dy2 < 0)) return -1;
    if ((dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2))
                                        return +1;
    return 0;
}

int intersect(struct line l1, struct line l2)
{
    return ((ccw(l1.p1, l1.p2, l2.p1)
            *ccw(l1.p1, l1.p2, l2.p2)) <= 0)
        && ((ccw(l2.p1, l2.p2, l1.p1)
            *ccw(l2.p1, l2.p2, l1.p2)) <= 0);
}

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
    struct point po1;
    struct point pe1;
    struct point po2;
    struct point pe2;

    po1.x = line1->origin()[0];
    po1.y = line1->origin()[1];
    pe1.x = line1->ending()[0];
    pe1.y = line1->ending()[1];

    po2.x = line2->origin()[0];
    po2.y = line2->origin()[1];
    pe2.x = line2->ending()[0];
    pe2.y = line2->ending()[1];

    struct line l1;
    l1.p1 = po1;
    l1.p2 = pe1;

    struct line l2;
    l2.p1 = po2;
    l2.p2 = pe2;

    return intersect(l1, l2);
}

bool util::testLineCircleCollision(model::LineShape *line, model::CircleShape *circle)
{
    float aQuad, bQuad, cQuad, r2, delta;

    core::Vector2 pi1_2;
    pi1_2[0] = line->origin()[0] - circle->center()[0];
    pi1_2[1] = line->origin()[1] - circle->center()[1];

    r2 = circle->radius() * circle->radius();

    aQuad = line->ending()[0]*line->ending()[0] + line->ending()[1];
    bQuad = 2 * (pi1_2[0] * line->ending()[0] + pi1_2[1] * line->ending()[1]);
    cQuad = pi1_2[0] * pi1_2[0] + pi1_2[1]*pi1_2[1] - r2;

    delta = bQuad*bQuad - 4*aQuad*cQuad;

    if(delta < 0)
    {
        return false;
    }
    else
    {
        float s = ((-bQuad)+sqrt(delta)) / (2*aQuad);
        float t = ((-bQuad)-sqrt(delta)) / (2*aQuad);

        if( (t > 0 && t < 1) || (s > 0 && s < 1) )
        {
            return true;
        }
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
