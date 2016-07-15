#ifndef tsdev_calculations_latex_h
#define tsdev_calculations_latex_h

#include <sstream>
#include <string>

#include "formatter.h"
#include "replacer.h"

namespace tsdev {
    namespace calculations {
        struct LatexFormatter : public Formatter  {
            LatexFormatter()
                : Formatter({
                    std::make_pair<std::string, Replacer>("=", [](const std::vector<std::string>& v){
                        std::stringstream ss;
                        ss << v[0] << " &= " << v[1];
                        return ss.str();
                    }),
                    std::make_pair<std::string, Replacer>("*", [](const std::vector<std::string>& v){
                        std::stringstream ss;
                        ss << v[0] << " \\cdot " << v[1];
                        return ss.str();
                    }),
                    std::make_pair<std::string, Replacer>("^", [](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << v[0] << "^{" << v[1] << "}";
                        return ss.str();
                    }),
                    std::make_pair<std::string, Replacer>("/", [](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << "\\frac{" << v[0] << "}{" << v[1] << "}";
                        return ss.str();
                    }),
                    std::make_pair<std::string, Replacer>("()", [](const std::vector<std::string>& v) {
                        std::stringstream ss;
                        ss << "\\left(" << v[0] << "\\right)";
                        return ss.str();
                    }),
                    std::make_pair<std::string, Replacer>("(a,b,...)", [](const std::vector<std::string>& v) {
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
                    })
                  })
            {}

            virtual std::string begin() const {
                std::stringstream ss;
                ss << "\\begin{equation}" << std::endl
                   << "  \\begin{split}" << std::endl
                   << "    ";

                return ss.str();
            }

            virtual std::string end() const {
                std::stringstream ss;
                ss << std::endl
                   << "  \\end{split}" << std::endl
                   << "\\end{equation}" << std::endl << std::endl;

                return ss.str();
            }

            virtual std::string newline() const {
                std::stringstream ss;
                ss << "\\\\" << std::endl << "    ";
                return ss.str();
            }

            virtual std::string value(const std::string& value, Unit unit) const {
                std::stringstream ss;

                if (unit.isEmpty()) {
                    ss << value;
                }
                else {
                    ss << "\\unit[" << value << "]{";

                    if (unit.hasNegativeExponent()) {
                        ss << "\\frac{";
                        if (unit.hasPositiveExponent()) {
                            bool first = true;
                            for(const Unit::Entry& entry : unit) {
                                if (entry.second > 0) {
                                    if(!first) {
                                        ss << " \\cdot ";
                                    }

                                    if(entry.second == 1) {
                                        ss << entry.first;
                                    }
                                    else {
                                        ss << entry.first << "^" << entry.second;
                                    }

                                    first = false;
                                }
                            }
                        }
                        else {
                            ss << "1";
                        }
                        ss << "}{";
                        bool first = true;
                        for(const Unit::Entry& entry : unit) {
                            if (entry.second < 0) {
                                if(!first) {
                                    ss << " \\cdot ";
                                }

                                int exp = -entry.second;
                                if(exp == 1) {
                                    ss << entry.first;
                                }
                                else {
                                    ss << entry.first << "^" << exp;
                                }

                                first = false;
                            }
                        }
                        ss << "}";
                    }
                    else {
                        bool first = true;
                        for(const Unit::Entry& entry : unit) {
                            if(!first) {
                                ss << " \\cdot ";
                            }

                            if(entry.second == 1) {
                                ss << entry.first;
                            }
                            else {
                                ss << entry.first << "^" << entry.second;
                            }

                            first = false;
                        }
                    }

                    ss << "}";
                }

                return ss.str();
            }
        };
    }
}

#endif
