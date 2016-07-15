#ifndef tsdev_calculations_trapz_h
#define tsdev_calculations_trapz_h

#include "elementptr.h"
#include "util.h"
#include "unaryoperator.h"

namespace tsdev {
    namespace calculations {
        template <typename T>
        struct _Trapz : public UnaryOperator<T, T> {
            ElementPtr<T> index;
            T min;
            T max;
            int steps;

            _Trapz(ElementPtr<T> base, ElementPtr<T> index, T min, T max, T stepSize)
                : index(index),
                  min(min),
                  max(max),
                  steps(stepSize)
            {
                this->children = base;
            }

            virtual void execute() {
                UnaryOperator<T, T>::execute();
                T result = 0;
                T stepSize = (max - min) / steps;

                for(T i = min; i <= max-stepSize; i += stepSize) {
                    index->setValue(i);
                    this->children->execute();
                    T y1 = this->children->value.value;

                    index->setValue(i+stepSize);
                    this->children->execute();
                    T y2 = this->children->value.value;

                    int s1 = sign(y1);
                    int s2 = sign(y2);

                    if(s1 == s2 || s1 == 0 || s2 == 0) {
                        if (y1 < y2) {
                            result += (y1 * stepSize + ((y2 - y1) * stepSize)/2);
                        }
                        else if (y2 < y1) {
                            result += (y2 * stepSize + ((y1 - y2) * stepSize)/2);
                        }
                        else {
                            result += (y1 * stepSize);
                        }
                    }
                    else {
                        T m = (y2 - y1)/stepSize;
                        T n = y1 - m*i;
                        T x0 = -n/m;

                        T lp = y1 * (x0 - i);
                        T rp = y2 * ((i+stepSize) - x0);

                        result += (lp + rp);
                    }
                }

                this->setValue(result);
                this->setUnit(this->children->value.unit.copy().add(this->index->value.unit));
            }

            virtual std::string symbol() const {
                return "integral";
            }

            virtual int getMaxLevel() const {
                return Element<T>::getMaxLevel();
            }

            virtual std::string getPrintCommands(int level, int maxLevel, bool showNames, Formatter &formatter) const {
                if (level > maxLevel) {
                    return "";
                }

                if (this->baseLevel == -1) {
                    this->baseLevel = level;
                }

                if (showNames) {
                    Replacer rep = getReplacer(formatter);
                    std::stringstream ss;

                    ss << min;
                    std::string minStr = ss.str();
                    ss.str("");

                    ss << max;
                    std::string maxStr = ss.str();
                    ss.str("");

                    std::string func = this->children.getPrintCommands(level+1, level+this->children->getMaxLevel(), true, formatter);
                    std::string indexName = index->getName();

                    ss << rep({minStr, maxStr, func, indexName});
                    return ss.str();
                }

                return Element<T>::getPrintCommands(level, maxLevel, showNames, formatter);
            }

            virtual Replacer getReplacer(Formatter& formatter) const {
                Replacer rep = formatter.replacer(this->symbol());
                if (!rep) {
                    rep = [&](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << "int(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
                        return ss.str();
                    };
                }

                return rep;
            }
        };

        template <typename T>
        ElementPtr<T> Trapz(ElementPtr<T> base, ElementPtr<T> index, T min, T max, int steps) {
            return ElementPtr<T>(new _Trapz<T>(base, index, min, max, steps));
        }
    }
}

#endif
