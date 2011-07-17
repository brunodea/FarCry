#ifndef _FAR_CRY_DRAWABLE_H_
#define _FAR_CRY_DRAWABLE_H_

namespace view
{
    class Drawable
    {
        public:
            Drawable() {}
            virtual ~Drawable() {}
            virtual void draw() = 0;
    };
}

#endif // _FAR_CRY_DRAWABLE_H_
