#ifndef tsdev_calculations_operator_h
#define tsdev_calculations_operator_h

#include "element.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct Operator : public Element<T> {
            virtual std::string symbol() const = 0;
        };
    }
}

#endif
