#ifndef tsdev_calculations_formatter_h
#define tsdev_calculations_formatter_h

#include <initializer_list>
#include <map>
#include <string>

#include "replacer.h"
#include "physicalvalue.h"

namespace tsdev {
    namespace calculations {
        struct Formatter {
            std::map<std::string, Replacer> translations;

            Formatter() = default;
            Formatter(const Formatter& formatter) = default;

            Formatter(const std::initializer_list<std::pair<const std::string, Replacer>>& list)
                : translations(list)
            {}

            virtual std::string begin() const = 0;
            virtual std::string end() const = 0;
            virtual std::string newline() const = 0;
            virtual std::string value(const std::string& value, Unit unit) const = 0;

            virtual Replacer replacer(const std::string& str) const {
                Replacer r = nullptr;

                std::map<std::string, Replacer>::const_iterator it = translations.find(str);
                if (it != translations.end()) {
                    r = it->second;
                }

                return r;
            }
        };
    }
}

#endif
