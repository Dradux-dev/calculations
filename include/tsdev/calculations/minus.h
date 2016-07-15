#ifndef tsdev_calculations_minus_h
#define tsdev_calculations_minus_h

#include <iostream>

#include "binaryoperator.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TLhs, typename TRhs>
        struct _Minus : BinaryOperator<T, TLhs, TRhs> {
            _Minus(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs)
                : BinaryOperator<T, TLhs, TRhs>(lhs, rhs)
            {}

            virtual void execute() {
                BinaryOperator<T, TLhs, TRhs>::execute();

                if(this->lhs.ptr->value.unit != this->rhs.ptr->value.unit) {
                    std::cerr << "Minus: " << this->lhs.ptr->value.unit << " does not matches " << this->rhs.ptr->value.unit << std::endl;
                }

                this->value.value = this->lhs->value.value - this->rhs->value.value;
                this->value.unit = this->lhs->value.unit;
            }

            virtual std::string symbol() const {
                return "-";
            }
        };

        template <typename TLhs, typename TRhs>
        ElementPtr<double> operator-(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs) {
            return ElementPtr<double>(new _Minus<double, TLhs, TRhs>(lhs, rhs));
        }

        template <typename TLhs>
        ElementPtr<double> operator-(ElementPtr<TLhs> lhs, double rhs) {
            ElementPtr<double> erhs = Stack<double>::instance().createElement(new Element<double>(rhs));
            return ElementPtr<double>(new _Minus<double, TLhs, double>(lhs, erhs));
        }

        template <typename TRhs>
        ElementPtr<double> operator-(double lhs, ElementPtr<TRhs> rhs) {
            ElementPtr<double> elhs = Stack<double>::instance().createElement(new Element<double>(lhs));
            return ElementPtr<double>(new _Minus<double, double, TRhs>(elhs, rhs));
        }
    }
}

#endif
