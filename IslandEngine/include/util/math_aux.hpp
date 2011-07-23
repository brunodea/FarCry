#ifndef _FAR_CRY_MATH_AUX_HPP_
#define _FAR_CRY_MATH_AUX_HPP_

#include "islandengine_macros.h"

namespace util
{
    inline int factorial(unsigned int num)
    {
        int result = 1;
        for(unsigned int i = 1; i <= num; i++)
            result *= i;
        return result;
    }

    inline float radToDegree(float rad)
    {
        return (180.f*rad)/PI;
    }

    inline float degreeToRad(float d)
    {
        return (d*PI)/180.f;
    }
}

#endif
