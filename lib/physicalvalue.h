#ifndef tsdev_calculations_singlevaluewithunit_h
#define tsdev_calculations_singlevaluewithunit_h

#include "unit.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct PhysicalValue {
            T value;
            Unit unit;

            PhysicalValue()
                : value()
            {}

            PhysicalValue(const T& value, Unit unit)
                : value(value),
                  unit(unit)
            {}

            bool operator!=(const PhysicalValue<T>& rhs) const {
                return (value != rhs.value || unit != rhs.unit);
            }
        };

        template <typename T>
        PhysicalValue<T> operator*(const T& lhs, const Unit& rhs) {
            return PhysicalValue<T>(lhs, rhs);
        }
    }
}

#endif
