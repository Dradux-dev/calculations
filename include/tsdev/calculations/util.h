#ifndef tsdev_calculations_util_h
#define tsdev_calculations_util_h

namespace tsdev {
    namespace calculations {
        /**
         * @param T The data type of the element that shall be checked.
         * @param value The actual value of that element.
         *
         * @return Returns -1, if the value is below zero. If the value is
         * above zero, this function will return 1. If the value is zero, this
         * funciton returns 0.
         */
        template <typename T>
        int sign(T value) {
            return (T(0) < value) - (value < T(0));
        }
    }
}

#endif
