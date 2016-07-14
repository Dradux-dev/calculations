#ifndef tsdev_calculations_h
#define tsdev_calculations_h

#include "elementptr.h"

namespace tsdev {
    namespace calculations {
        template <typename T, typename TIn>
        struct Function : public Element<T> {
            std::vector<ElementPtr<TIn>> parameters;

            Function(const std::string& name, const std::vector<ElementPtr<TIn>>& parameters)
                : Element<T>(name),
                  parameters(parameters)
            {}

            virtual int getMaxLevel() const {
                int maxParamLevel = 0;
                for(ElementPtr<TIn> ptr : parameters) {
                    maxParamLevel = std::max(ptr->getMaxLevel(), maxParamLevel);
                }

                return maxParamLevel + 1;
            }

            virtual void execute() {
                Element<T>::execute();

                for(ElementPtr<TIn> ptr : parameters) {
                    if (ptr->isDirty()) {
                        ptr->execute();
                    }
                }
            }

            virtual bool isDirty() const {
                if (this->dirty) {
                    return true;
                }

                for(ElementPtr<TIn> ptr : parameters) {
                    if (ptr->isDirty())
                        return true;
                }

                return false;
            }

            virtual std::string getPrintCommands(int level, int maxLevel, bool showNames, Formatter &formatter) const {
                if(level > maxLevel) {
                    return "";
                }

                if (this->baseLevel == -1) {
                    this->baseLevel = level;
                }

                if (!showNames && (level == maxLevel || maxLevel <= this->baseLevel)) {
                    return Element<T>::getPrintCommands(level, maxLevel, showNames, formatter);
                }


                std::vector<std::string> paramStrings;
                for(ElementPtr<TIn> ptr : parameters) {
                        paramStrings.push_back(ptr.getPrintCommands(level+1, maxLevel, showNames, formatter));
                }

                Replacer functionReplacer = getReplacer(formatter);
                Replacer parameterReplacer = getParameterReplacer(formatter);
                std::stringstream ss;
                ss << functionReplacer({this->name}) << parameterReplacer(paramStrings);
                return ss.str();
            }

            virtual Replacer getReplacer(Formatter& formatter) const {
                Replacer rep = formatter.replacer(this->name);
                if (!rep) {
                    rep = [&](const std::vector<std::string>& v) {
                        return v[0];
                    };
                }

                return rep;
            }

            virtual Replacer getParameterReplacer(Formatter& formatter) const {
                Replacer rep = formatter.replacer("(a,b,...)");
                if (!rep) {
                    rep = [](const std::vector<std::string>& v) {
                        bool first = true;
                        std::stringstream ss;

                        ss << "(";
                        for(const std::string& str : v) {
                            if(!first) {
                                ss << ",";
                            }

                            ss << str;
                            first = false;
                        }

                        ss << ")";
                        return ss.str();
                    };
                }

                return rep;
            }
        };
    }
}

#endif
