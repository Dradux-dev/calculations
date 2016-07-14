#ifndef tsdev_calculations_unaryoperator_h
#define tsdev_calculations_unaryoperator_h

#include "elementptr.h"
#include "operator.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct UnaryOperator : public Operator<T> {
            ElementPtr<TIn> children;

            virtual void execute() {
                children->execute();
            }

            virtual void makeClean() { children->makeClean(); }
            virtual inline bool isDirty() const { return children->isDirty(); }

            virtual int getMaxLevel() const {
                return children->getMaxLevel() + 1;
            }
        };
    }
}

#endif
