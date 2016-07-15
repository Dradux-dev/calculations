#ifndef tsdev_calculations_anglefunction_h
#define tsdev_calculations_anglefunciton_h

#include <initializer_list>
#include <string>
#include <vector>

#include "function.h"

namespace tsdev {
    namespace calculations {
        /**
         * Base class for trigonometric functions, which contains a method to
         * convert degree to radians.
         *
         * @param T The result data type.
         * @param TIn The parameter data type.
         *
         * @author Tarek Schwarzinger
         */
        template <typename T, typename TIn>
        struct AngleFunction : public Function<T, TIn> {
            /**
             * @brief Name-parameter constructor
             *
             * Creates a trigonometric function with a specified name and a
             * parameter list.
             *
             * @param name The name of the trigonemtric function.
             * @param parameters The parameter list of the trigonometric function.
             */
            AngleFunction(const std::string& name, const std::vector<ElementPtr<TIn>>& parameters)
                : Function<T, TIn>(name, parameters)
            {}

            /**
             * @brief Radian conversion
             *
             * This function converts degree to radians. If param is already in
             * radians, nothing happens. Otherwise the function shows an error
             * and keeps the param as it is.
             *
             * @param param The element pointer to the parameter that shall
             * be converted.
             *
             * @return Returns the converted parameter in radians.
             */
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
