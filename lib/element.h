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
        template <typename T>
        struct Element {
            using Ptr = std::shared_ptr<Element<T>>;
            PhysicalValue<T> value;
            std::string name;
            std::vector<Unit> substitutions;
            bool dirty;
            mutable int baseLevel;

            Element()
                : value(),
                  dirty(true)
            {}

            Element(const T& value)
                : value(value, {}),
                  dirty(true)
            {}

            Element(const T& value, Unit unit)
                : value(value, unit),
                  dirty(true)
            {}

            Element(const std::string& name)
                : name(name),
                  dirty(true)
            {}

            virtual Element<T>& setValue(const T& val) {
                value.value = val;
                return *this;
            }

            virtual Element<T>& setUnit(Unit unit) {
                value.unit = unit;
                optimizeUnit();
                return *this;
            }

            virtual void execute() {
                baseLevel = -1;
                substitutions.clear();
            }

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

            virtual inline void makeClean() { dirty = false; }
            virtual inline void makeDirty() { dirty = true; }
            virtual inline bool isDirty() const { return dirty; }

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

            virtual int getMaxLevel() const {
                return substitutions.size()+1;
            }

            virtual const std::string& getName() const {
                return name;
            }

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
