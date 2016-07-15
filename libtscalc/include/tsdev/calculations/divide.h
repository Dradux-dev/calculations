#ifndef tsdev_calculations_divide_h
#define tsdev_calculations_divide_h

#include "binaryoperator.h"

namespace tsdev {
    namespace calculations {
        /**
         * This element creates a division operation.
         *
         * @param T The result data type of the division operation.
         * @param TLhs The left hand side operand.
         * @param TRhs The right hand side operand.
         *
         * @author Tarek Schwarzinger
         */
        template <typename T, typename TLhs, typename TRhs>
        struct _Divide : public BinaryOperator<T, TLhs, TRhs> {
            /**
             * @brief Operand constructor
             *
             * Creates an element for a division with both operands
             * specified.
             *
             * @param lhs The left hand side operand.
             * @param rhs The right hand side operand.
             */
            _Divide(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs)
                : BinaryOperator<T, TLhs, TRhs>(lhs, rhs)
            {}

            /**
             * @brief Division execution
             *
             * Executes the division operation and calculates the
             * new unit for this element.
             */
            virtual void execute() {
                BinaryOperator<T, TLhs, TRhs>::execute();

                this->setValue(this->lhs->value.value / this->rhs->value.value);
                this->setUnit(this->lhs->value.unit.copy().add(this->rhs->value.unit.copy().inverse()));
            }

            /**
             * @brief Operation symbol
             *
             * @return Returns the symbol of this operation.
             */
            virtual std::string symbol() const {
                return "/";
            }
        };

        /**
         * Overloads the division operator for two element pointer.
         *
         * @param TLhs The data type of the left hand side operand.
         * @param TRhs The data type of the right hand side operand.
         * @param lhs The left hand side operand.
         * @param rhs The right hand side operand.
         */
        template <typename TLhs, typename TRhs>
        ElementPtr<double> operator/(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs) {
            return ElementPtr<double>(new _Divide<double, TLhs, TRhs>(lhs, rhs));
        }

        /**
         * Overloads the division operator for an element pointer and a double.
         *
         * @param TLhs The data type of the left hand side operand.
         * @param lhs The left hand side operand.
         * @param rhs The right hand side operand.
         */
        template <typename TLhs>
        ElementPtr<double> operator/(ElementPtr<TLhs> lhs, double rhs) {
            ElementPtr<double> erhs = Stack<double>::instance().createElement(new Element<double>(rhs));
            return ElementPtr<double>(new _Divide<double, TLhs, double>(lhs, erhs));
        }

        /**
         * Overloads the division operator for a double and an element pointer.
         *
         * @param TRhs The data type of the right hand side operand.
         * @param lhs The left hand side operand.
         * @param rhs The right hand side operand.
         */
        template <typename TRhs>
        ElementPtr<double> operator/(double lhs, ElementPtr<TRhs> rhs) {
            ElementPtr<double> elhs = Stack<double>::instance().createElement(new Element<double>(lhs));
            return ElementPtr<double>(new _Divide<double, double, TRhs>(elhs, rhs));
        }
    }
}

#endif
