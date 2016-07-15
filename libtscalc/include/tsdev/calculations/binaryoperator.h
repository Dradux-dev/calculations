#ifndef tsdev_calculations_binaryoperator_h
#define tsdev_calculations_binaryoperator_h

#include "elementptr.h"
#include "formatter.h"
#include "operator.h"
#include "replacer.h"
#include "stack.h"

namespace tsdev {
    namespace calculations {
        /**
         * This describes the base class of an operator that has
         * a left hand side (lhs) operand and an right hand side
         * operand (rhs).
         *
         * @param T Describes the result type of this operation.
         * @param TLhs Describes the type of the left hand side operand.
         * @param TRhs Describes the type of the right hand side operand.
         */
        template <typename T, typename TLhs, typename TRhs>
        struct BinaryOperator : public Operator<T> {
            /// Left hand side operand
            ElementPtr<TLhs> lhs;
            /// Right hand side operand
            ElementPtr<TRhs> rhs;

            /**
             * @brief BinaryOperator Constructor with both operands
             *
             * Constructs the BinaryOperator with both, the left hand side
             * and the right hand side, operands.
             *
             * @param lhs The left hand side operand
             * @param rhs The right hand side operand
             */
            BinaryOperator(ElementPtr<TLhs> lhs, ElementPtr<TRhs> rhs)
                : lhs(lhs),
                  rhs(rhs)
            {}

            /**
             * @brief Default execution
             *
             * This method is called to execute the operator. By default it executes
             * the left hand side and the right hand side operands to resolve them.
             *
             * @attention This basic implementation, does not know how to process the
             * real operation with both operands and needs to be implemented in specific
             * operator implementations.
             */
            virtual void execute() {
                Element<T>::execute();

                if (lhs->isDirty()) {
                    lhs->execute();
                }

                if (rhs->isDirty()) {
                    rhs->execute();
                }
            }

            /**
             * @brief Check if this operator needs to be executed.
             *
             * @return Returns true if the left hand side or right hand side operand is
             * dirty, what means that this operation has to be reexecuted. If it is not
             * required, to reexecute this operation, this method will return false.
             */
            virtual inline bool isDirty() const {
                return this->dirty || lhs->isDirty() || rhs->isDirty();
            }

            /**
             * @brief Removes the dirty flag
             *
             * Removes the dirty flag for it's both operands.
             */
            virtual inline void makeClean() {
                Element<T>::makeClean();
                lhs->makeClean();
                rhs->makeClean();
            }

            /**
             * @brief Retrieve max Depth from tree.
             *
             * This method retrieves how depth the most depth children
             * of this node ist.
             *
             * @return Returns the maximum depth of any node, which is a
             * children of this node.
             */
            virtual int getMaxLevel() const {
                return std::max(lhs->getMaxLevel(), rhs->getMaxLevel()) + Element<T>::getMaxLevel();
            }

            /**
             * @brief getPrintCommands Builds the node string.
             *
             * This method builds the string for this operation. It also includes building
             * all children of it.
             *
             * @param level Contains the actual tree depth.
             * @param maxLevel Contains the maximum tree depth allowed for the string building.
             * @param showNames Defines if the variable names shall be displayed (true) or not (false).
             * @param formatter Defines how the string shall be formatted.
             *
             * @return Returns a string representation of this operator and it's operands.
             */
            virtual std::string getPrintCommands(int level, int maxLevel, bool showNames, Formatter& formatter) const {
                if (level > maxLevel) {
                    return "";
                }

                if (this->baseLevel == -1) {
                    this->baseLevel = level;
                }

                if(!showNames && (level == maxLevel || maxLevel < (this->baseLevel+Element<T>::getMaxLevel()))) {
                    return Element<T>::getPrintCommands(level, maxLevel, showNames, formatter);
                }

                Replacer rep = getReplacer(formatter);
                Replacer brlhs = (bracketLHS() && !showNames) ? getRoundbracketReplacer(formatter) : [](const std::vector<std::string>& v) { return v[0]; };
                Replacer brrhs = (bracketRHS() && !showNames) ? getRoundbracketReplacer(formatter) : [](const std::vector<std::string>& v) { return v[0]; };
                std::string l = lhs.getPrintCommands(level+Element<T>::getMaxLevel(), maxLevel, showNames, formatter);
                std::string r = rhs.getPrintCommands(level+Element<T>::getMaxLevel(), maxLevel, showNames, formatter);
                return rep({brlhs({l}), brrhs({r})});
            }

            /**
             * @return Returns true, if the left hand side operand shall be
             * encapsulated within paranthesis. Otherwise it returns false.
             */
            virtual bool bracketLHS() const {
                return false;
            }

            /**
             * @return Returns true, if the right hand side operand shall be
             * encapsulated within paranthesis. Otherwise it returns false.
             */
            virtual bool bracketRHS() const {
                return false;
            }

            /**
             * @brief Reqeusts the operation replacement.
             *
             * Reqeusts the replacer function for this operator from the
             * formatter. If no replacer function exists in the
             * formatter, a default replacer function is generated.
             *
             * @param formatter The output formatter.
             *
             * @return Returns a replacer function for formatting.
             */
            Replacer getReplacer(Formatter& formatter) const {
                Replacer rep = formatter.replacer(this->symbol());
                if (!rep) {
                    rep = [&](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << v[0] << this->symbol() << v[1];
                        return ss.str();
                    };
                }

                return rep;
            }

            /**
             * @brief Requests the bracket replacement.
             *
             * Requests the replacer function for bracketing an operand from
             * the formatter. If no replacer function exists in the formatter, a
             * default replacer function is generated.
             *
             * @param formatter The output formatter.
             *
             * @return Returns a replacer function for formatting.
             */
            Replacer getRoundbracketReplacer(Formatter& formatter) const {
                Replacer rep = formatter.replacer("()");
                if (!rep) {
                    rep = [](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << "(" << v[0] << ")";
                        return ss.str();
                    };
                }

                return rep;
            }
        };
    }
}

#endif
