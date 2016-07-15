#ifndef tsdev_calculations_element_h
#define tsdev_calculations_element_h

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "formatter.h"
#include "physicalvalue.h"
#include "unittable.h"

namespace tsdev {
    namespace calculations {
        /**
         * Base class every element of the tree.
         *
         * @param T Data type of the stored value.
         *
         * @author Tarek Schwarzinger
         */
        template <typename T>
        struct Element {
            using Ptr = std::shared_ptr<Element<T>>;

            /// Value with unit
            PhysicalValue<T> value;
            /// Name
            std::string name;
            /// List of unit substitutions
            std::vector<Unit> substitutions;
            /// Dirty flag
            bool dirty;
            /// Base level in execution tree
            mutable int baseLevel;

            /**
             * @brief Default constructor
             *
             * Creates an element with a default value and marks the
             * element as dirty.
             */
            Element()
                : value(),
                  dirty(true)
            {}

            /**
             * @brief Value constructor
             *
             * Creates an element with a specified value and marks the
             * element as dirty.
             *
             * @param value The value of the element.
             */
            Element(const T& value)
                : value(value, {}),
                  dirty(true)
            {}

            /**
             * @brief Value unit constructor
             *
             * Creates an element with a specified value and a specified unit. Also
             * marks the element as dirty.
             *
             * @param value The specified value for that element.
             * @param unit The specified unit of the element.
             */
            Element(const T& value, Unit unit)
                : value(value, unit),
                  dirty(true)
            {}

            /**
             * @brief Name constructor
             *
             * Creates an alement with a specific name and marks that element
             * as dirty.
             *
             * @param name The name of the element.
             */
            Element(const std::string& name)
                : name(name),
                  dirty(true)
            {}

            /**
             * @brief Value setter
             *
             * Sets a new value for this element.
             *
             * @param val The new value for this element.
             *
             * @return Returns a reference to this element.
             */
            virtual Element<T>& setValue(const T& val) {
                value.value = val;
                return *this;
            }

            /**
             * @brief Unit setter
             *
             * Sets a new unit for this element and tries to optimize the
             * unit.
             *
             * @param unit The new unit for this element.
             *
             * @return Returns a reference to this element.
             */
            virtual Element<T>& setUnit(Unit unit) {
                value.unit = unit;
                optimizeUnit();
                return *this;
            }

            /**
             * @brief Execute
             *
             * Executes the actual operation to this element.
             */
            virtual void execute() {
                baseLevel = -1;
                substitutions.clear();
            }

            /**
             * @brief Unit optimization
             *
             * Tries to optimize the actual unit of this element and stores all
             * optimization steps in Element::substitutions.
             */
            virtual void optimizeUnit() {
                if (this->value.unit.isEmpty()) {
                    return;
                }

                bool optimizationFound = false;

                do {
                    optimizationFound = false;

                    value.unit.cleanup();
                    substitutions.push_back(value.unit);

                    std::pair<Unit,Unit> dest = UnitTable::instance().findBestMatch(value.unit);
                    if(dest.first.isEmpty() || dest.second.isEmpty()) {
                        break;
                    }

                    Unit optimized = value.unit.copy().add(dest.first.inverse()).add(dest.second).cleanup();
                    if(optimized.getCount() < value.unit.getCount()) {
                        optimizationFound = true;
                        value.unit = optimized;
                    }

                    value.unit.cleanup();
                } while(optimizationFound == true);


                if (substitutions.size() > 0) {
                    std::vector<Unit>::iterator it = substitutions.begin() + (substitutions.size()-1);
                    substitutions.erase(it);
                }
            }

            /**
             * Remove the dirty flag of this element.
             */
            virtual inline void makeClean() { dirty = false; }

            /**
             * Marks this element as dirty.
             */
            virtual inline void makeDirty() { dirty = true; }

            /**
             * @return Returns the actual dirty flag of this element.
             */
            virtual inline bool isDirty() const { return dirty; }

            /**
             * @brief String conversion
             *
             * Converts this element into a string.
             *
             * @param level The actual level in the tree.
             * @param maxLevel The maximum level of the tree.
             * @param formatter The formatter for the string conversion.
             *
             * @return Returns the created string.
             */
            virtual std::string getPrintCommands(int level, int maxLevel, bool, Formatter& formatter) const {
                if (level > maxLevel)
                    return "";

                if (baseLevel == -1) {
                    baseLevel = level;
                }

                std::stringstream ss;
                ss << value.value;
                return formatter.value(ss.str(), getActualUnit(maxLevel));
            }

            /**
             * @return Returns the maximum level for this element. This contains all unit
             * substitutions plus one.
             */
            virtual int getMaxLevel() const {
                return substitutions.size()+1;
            }

            /**
             * @return Returns the name of this element.
             */
            virtual const std::string& getName() const {
                return name;
            }

            /**
             * Returns the unit depending on the given maxLevel. This could be a unit of the
             * substitutions list or the actual unit of this element.
             *
             * @param maxLevel Defines for which level the unit is required.
             *
             * @return Returns the requested unit.
             */
            virtual Unit getActualUnit(int maxLevel) const {
                int index = substitutions.size() - (maxLevel - baseLevel);

                if (static_cast<unsigned int>(index) >= substitutions.size()) {
                    return value.unit;
                }

                return substitutions[index];
            }
        };
    }
}

#endif
