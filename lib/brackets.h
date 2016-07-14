#ifndef tsdev_calculations_brackets_h
#define tsdev_calculations_brackets_h

#include "unaryoperator.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct Brackets : public UnaryOperator<T, TIn> {

        };
    }
}

#endif
