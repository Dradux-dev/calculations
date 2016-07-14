#ifndef tsdev_calculations_exporter_h
#define tsdev_calculations_exporter_h

#include "formatter.h"
#include <initializer_list>
#include "replacer.h"
#include "variable.h"

namespace tsdev {
    namespace calculations {
        struct Exporter {
            std::shared_ptr<Formatter> formatter;

            Exporter(std::shared_ptr<Formatter> formatter)
                : formatter(formatter)
            {}

            template <typename T>
            void print(std::ostream& os, const std::vector<Variable<T>&>& list, bool verbose = false) {
                for(Variable<T>& var : list) {
                    print(os, var, verbose);
                }
            }

            template <typename T>
            void print(std::ostream& os, Variable<T>& var, bool verbose = false) {
                if (var.isDirty()) {
                    var.execute();
                    var.makeClean();
                }

                std::string formula;
                if (verbose) {
                    formula = printVerbose(var, var.getName());
                }
                else {
                    formula = printDetailed(var, var.getName());
                }

                os << formatter->begin() << formula << formatter->end();
            }

            template <typename T>
            std::string printDetailed(const Variable<T>& var, const std::string& prefix) {
                std::stringstream ss;
                int maxLevel = var->getMaxLevel();
                std::string lhs = prefix;
                std::string rhs;

                Replacer equal = getEqualReplacer();
                for(int i = maxLevel; i > 1; --i) {
                    if (i == maxLevel) {
                        ss.str("");
                        rhs = var.getPrintCommands(i, true, *formatter);
                        ss << equal({lhs, rhs}) << formatter->newline();
                        lhs = ss.str();
                    }

                    ss.str("");
                    rhs = var.getPrintCommands(i, false, *formatter);
                    ss << equal({lhs, rhs}) << formatter->newline();
                    lhs = ss.str();
                }

                rhs = var.getPrintCommands(1, false, *formatter);
                return equal({lhs, rhs});
            }

            template <typename T>
            std::string printVerbose(const Variable<T>& var, const std::string& prefix) {
                std::stringstream ss;
                int maxLevel = var->getMaxLevel();
                std::string lhs = prefix;
                std::string rhs;
                Replacer equal = getEqualReplacer();

                rhs = var.getPrintCommands(maxLevel, true, *formatter);
                ss << equal({lhs, rhs}) << formatter->newline();
                lhs = ss.str();

                ss.str("");
                rhs = var.getPrintCommands(1, false, *formatter);
                return equal({lhs, rhs});
            }

            Replacer getEqualReplacer() const {
                Replacer equal = formatter->replacer("=");
                if (!equal) {
                    equal = [](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << v[0] << " = " << v[1];
                        return ss.str();
                    };
                }

                return equal;
            }
        };
    }
}

#endif
