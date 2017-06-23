#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

namespace utilities
{
    //template <typename T> int sgn(T val)
    inline int sgn(int val)
    {
        //return (T(0) < val) - (val < T(0));
        return (0 < val) - (val < 0);
    }

}

#endif // UTILITIES_H_INCLUDED
