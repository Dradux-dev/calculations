#ifndef tsdev_calculations_integrate_h
#define tsdev_calculations_integrate_h

#include "unaryoperator.h"
#include "value.h"
#include "pow.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct _Integrate : public UnaryOperator<T, TIn> {
            double min;
            double max;
            std::string target;

            _Integrate(ElementPtr<TIn> source, double min, double max, const std::string& target)
                : UnaryOperator<T, TIn>(source),
                  min(min),
                  max(max),
                  target(target)
            {}

            std::shared_ptr<Value<TIn>> retrieveValue(ElementPtr<TIn> p) {
                std::shared_ptr<Value<TIn>> pvalue = p.dynamic_pointer_cast<Value<TIn>>();
                if (!pvalue)
                    return nullptr;

                if (pvalue->name != target)
                    return nullptr;

                return pvalue;
            }

            ElementPtr<T> retrieveBasePow(ElementPtr<T> p) {
                std::shared_ptr<_Pow<TIn, TIn, TIn>> pbase = p.dynamic_pointer_cast<_Pow<TIn, TIn, TIn>();
                if (!pbase)
                    return nullptr;

                return pbase->lhs;
            }
        };
    }
}

#endif
