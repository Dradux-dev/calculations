#ifndef tsdev_calculations_reference_h
#define tsdev_calculations_reference_h

#include "elementptr.h"
#include "variable.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct _Reference : public Element<T> {
            Variable<T>& var;
            bool dirty;

            _Reference(Variable<T>& var)
                : Element<T>(var->value.value, var->value.unit),
                  var(var),
                  dirty(true)
            {
                this->name = var.getName();
                var.ptr->execute();
                copyActualValue();
            }

            virtual bool isDirty() const {
                return (dirty || var.ptr->isDirty() || (var.ptr->value != this->value));
            }

            virtual void execute() {
                if(var.isDirty()) {
                    var.execute();
                    var.makeClean();
                }

                copyActualValue();
            }

            virtual void copyActualValue() {
                this->value = var.ptr->value;
                dirty = true;
            }

            virtual void makeClean() {
                dirty = false;
            }

            virtual int getMaxLevel() const {
                return 1;
            }
        };


        template <typename T>
        ElementPtr<T> Ref(Variable<T>& v) {
            return ElementPtr<T>(new _Reference<T>(v));
        }
    }
}

#endif
