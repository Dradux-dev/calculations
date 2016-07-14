#ifndef tsdev_calculations_anglefunction_h
#define tsdev_calculations_anglefunciton_h

#include <initializer_list>
#include <string>
#include <vector>

#include "function.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct AngleFunction : public Function<T, TIn> {
            AngleFunction(const std::string& name, const std::vector<ElementPtr<TIn>>& parameters)
                : Function<T, TIn>(name, parameters)
            {}

            T asRadians(ElementPtr<TIn> param) const {
                static double pi = std::acos(-1);
                static Unit deg = Unit({std::make_pair<std::string, int>("deg", 1)});
                static Unit rad = Unit({std::make_pair<std::string, int>("rad", 1)});

                if (param->value.unit == deg) {
                    return (param->value.value / 360) * 2 * pi;
                }
                else if(param->value.unit == rad) {
                    return param->value.value;
                }

                std::cerr << "AngleFunction: Don't know how to convert " << param->value.unit
                          << " to " << rad << std::endl;

                return param->value.value;
            }
        };
    }
}

#endif
