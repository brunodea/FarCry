#include <iostream>
#include <math.h>
#include "util/collision_functions.h"

#define Nmax 10

float min(float a, float b)
{
    return (a < b) ? a : b;
}

float max(float a, float b)
{
    return (a > b) ? a : b;
}

bool lineInCircle(float ax, float ay, float bx, float by, float cx, float cy, float cr)
{
    float vx = bx - ax;
    float vy = by - ay;
    float xdiff = ax - cx;
    float ydiff = ay - cy;
    float a = pow(vx, 2) + pow(vy, 2);
    float b = 2 * ((vx * xdiff) + (vy * ydiff));
    float c = pow(xdiff, 2) + pow(ydiff, 2) - pow(cr, 2);
    float quad = (b*b) - (4*a*c);

    if (quad >= 0)
    {
        std::cout << "foi\n";
        // An infinite collision is happening, but let's not stop here
        float quadsqrt = sqrt(quad);

        for (unsigned int i = -1; i <= 1; i += 2)
        {
            // Returns the two coordinates of the intersection points
            float t = (i * -b + quadsqrt) / (2 * a);
            float x = ax + (i * vx * t);
            float y = ay + (i * vy * t);

            // If one of them is in the boundaries of the segment, it collides
            if (x >= min(ax, bx) && x <= max(ax, bx) && y >= min(ay, by) && y <= max(ay, by))
            {
                return true;
            }
        }
    }

    return false;
}

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
    return lineInCircle(line->origin()[0], line->origin()[1], line->ending()[0], line->ending()[1], circle->center()[0], circle->center()[1], circle->radius());
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
    float dx = circle1->center()[0] - circle2->center()[0];
    float dy = circle1->center()[1] - circle2->center()[1];
    float radSum = circle1->radius() + circle2->radius();

    return ((dx*dx) + (dy*dy)) <= (radSum*radSum);
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
