#ifndef tsdev_calculations_sin_h
#define tsdev_calculations_sin_h

#include "anglefunction.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct _Sin : public AngleFunction<T, TIn> {
            _Sin(ElementPtr<TIn> parameter)
                : AngleFunction<T, TIn>("sin", {parameter})
            {}

            virtual void execute() {
                Function<T, TIn>::execute();

                T val = this->asRadians(this->parameters[0]);
                this->setValue(std::sin(val));
                this->setUnit(Unit());
            }
        };

        template <typename TIn>
        ElementPtr<double> Sin(const ElementPtr<TIn>& in) {
            return ElementPtr<double>(new _Sin<double, TIn>(in));
        }

        ElementPtr<double> Sin(double in);
    }
}

#endif
