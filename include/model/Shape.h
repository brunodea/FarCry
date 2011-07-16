#ifndef _FAR_CRY_SHAPE_H_
#define _FAR_CRY_SHAPE_H_

namespace model
{
    class Shape
    {
    public:
        enum Type
        {
            LINE = 0,
            CIRCLE,
            POLYGON
        };

    public:
        Shape(Type type) : m_Type(type) {}
        virtual bool collided(Shape*) = 0;
        Type type() { return m_Type; }

    private:
        Type m_Type;
    };
}

#endif // ___SHAPE_H___
