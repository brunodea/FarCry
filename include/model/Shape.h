#ifndef _FAR_CRY_SHAPE_H_
#define _FAR_CRY_SHAPE_H_

namespace model
{
    class Shape
    {
        public:
            virtual bool collided(Shape*) = 0;
        protected:
        private:
    };
}

#endif // ___SHAPE_H___
