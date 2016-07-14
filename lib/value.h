#ifndef tsdev_calculations_value_h
#define tsdev_calculations_value_h

#include "element.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct Value : public Element<T> {
            Value()
                : Element<T>()
            {}

            Value(const T& value, Unit unit)
                : Element<T>(value, unit)
            {}

            Value<T>& operator=(const Value<T>& v) {
                this->value = v;
                this->makeDirty();
                return *this;
            }

            Value<T>& operator=(const T& v) {
                this->value.value = v;
                this->makeDirty();
                return *this;
            }

            Value<T>& operator=(const Unit& unit) {
                this->value.unit = unit;
                this->makeDirty();
                return *this;
            }
        };
    }
}

#endif
