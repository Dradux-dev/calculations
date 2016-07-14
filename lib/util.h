#ifndef tsdev_calculations_util_h
#define tsdev_calculations_util_h

namespace tsdev {
    namespace calculations {
        template <typename T>
        int sign(T value) {
            return (T(0) < value) - (value < T(0));
        }
    }
}

#endif
