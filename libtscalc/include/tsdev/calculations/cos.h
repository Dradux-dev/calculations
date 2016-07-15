#ifndef tsdev_calculations_cos_h
#define tsdev_calculations_cos_h

#include "anglefunction.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct _Cos : public AngleFunction<T, TIn> {
            _Cos(ElementPtr<TIn> parameter)
                : AngleFunction<T, TIn>("cos", {parameter})
            {}

            virtual void execute() {
                Function<T, TIn>::execute();

                T val = this->asRadians(this->parameters[0]);
                this->setValue(std::cos(val));
                this->setUnit(Unit());
            }
        };

        template <typename TIn>
        ElementPtr<double> Cos(const ElementPtr<TIn>& in) {
            return ElementPtr<double>(new _Cos<double, TIn>(in));
        }

        ElementPtr<double> Cos(double in);
    }
}

#endif
