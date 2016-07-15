#ifndef tsdev_calculations_variable_h
#define tsdev_calculations_variable_h

#include <string>
#include <vector>

#include "elementptr.h"
#include "stack.h"
#include "value.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct Variable : public ElementPtr<T> {
            using ValuePtr = std::shared_ptr<Value<T>>;
            std::string name;

            Variable(const std::string& name, const T& value, Unit unit)
                : ElementPtr<T>(Stack<T>::instance().createElement(new Value<T>(value, unit))),
                  name(name)
            {
                this->ptr->name = name;
            }

            Variable(const std::string& name, const T& value, const std::string& unit)
                : ElementPtr<T>(Stack<T>::instance().createElement(new Value<T>(value, Unit(unit)))),
                  name(name)
            {
                this->ptr->name = name;
            }

            Variable(const std::string& name, const T& value)
                : ElementPtr<T>(Stack<T>::instance().createElement(new Value<T>(value, {}))),
                  name(name)
            {
                this->ptr->name = name;
            }

            Variable(const std::string& name)
                : ElementPtr<T>(Stack<T>::instance().createElement(new Value<T>(T(), {}))),
                  name(name)
            {
                this->ptr->name = name;
            }

            virtual void execute() {
                if(this->ptr->isDirty()) {
                    this->ptr->execute();
                    this->ptr->makeClean();
                }
            }

            virtual void makeClean() {
                this->ptr->makeClean();
            }

            virtual inline bool isDirty() const {
                return this->ptr->isDirty();
            }

            Variable<T>& operator=(ElementPtr<T> value) {
                this->ptr = value.ptr;
                return *this;
            }

            Variable<T>& operator=(const T& value) {
                ValuePtr v = getValuePtr();
                if(v) {
                    *v = value;
                }
                else {
                    this->ptr = Stack<T>::instance().createElement(new Value<T>(value, {})).ptr;
                }

                return *this;
            }

            operator ElementPtr<T>() const {
                return this->ptr;
            }

            ValuePtr getValuePtr() {
                return std::dynamic_pointer_cast<Value<T>>(this->ptr);
            }

            virtual std::string getName() const {
                return name;
            }

            virtual int getMaxLevel() const {
                return this->ptr->getMaxLevel();
            }

            virtual std::string getPrintCommands(int maxLevel, bool showNames, Formatter& formatter) const {
                return this->ptr->getPrintCommands(1, maxLevel, showNames, formatter);
            }
        };

        template <typename T>
        std::ostream& operator<<(std::ostream& os, const Variable<T>& v) {
            return os << v.getName() << " = " << v.ptr->value.value << " " << v.ptr->value.unit;
        }
    }
}

#endif
