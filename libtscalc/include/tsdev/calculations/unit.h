#ifndef tsdev_calculations_unit_h
#define tsdev_calculations_unit_h

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "util.h"

namespace tsdev {
    namespace calculations {
        struct Unit {
            using Map = std::map<std::string, int>;
            using Entry = std::pair<const std::string, int>;

            Map data;

            Unit() = default;
            Unit(const Unit& unit) = default;

            Unit(const Map& data)
                : data(data)
            {}

            Unit(const std::initializer_list<std::pair<const std::string, int>>& list)
                : data(list)
            {}

            Unit(const std::string& unitStr) {
                this->fromString(unitStr);
            }

            Unit& add(const Unit& unit) {
                for(std::pair<const std::string, int> p : unit.data) {
                    if (data.find(p.first) == data.end()) {
                        data[p.first] = 0;
                    }

                    data[p.first] += p.second;
                }

                return *this;
            }

            Unit& cleanup() {
                for(Map::iterator it = data.begin(); it != data.end(); ) {
                    if(it->second == 0) {
                        it = data.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                return *this;
            }

            Unit& inverse() {
                for(std::pair<const std::string, int>& p : data) {
                    p.second = -p.second;
                }

                return *this;
            }

            Unit copy() {
                return Unit(*this);
            }

            int matches(Unit compare) const {
                int score = 0;

                for(std::pair<const std::string, int> p : data) {
                    Map::iterator it = compare.data.find(p.first);
                    if(it != compare.data.end() && sign(p.second) == sign(it->second)) {
                        if (sign(p.second) == 1) {
                            score += std::min(p.second, it->second);
                        }
                        else if (sign(p.second) == -1) {
                            score += std::abs(std::max(p.second, it->second));
                        }
                    }
                }

                return score;
            }

            bool isEmpty() const {
                return (data.size() == 0);
            }

            int getCount() const {
                int count = 0;

                for(const std::pair<const std::string, int>& p : data) {
                    count+= std::abs(p.second);
                }

                return count;
            }

            bool hasNegativeExponent() const {
                for(const std::pair<const std::string, int>& p : data) {
                    if(p.second < 0) {
                        return true;
                    }
                }

                return false;
            }

            bool hasPositiveExponent() const {
                for(const std::pair<const std::string, int>& p : data) {
                    if(p.second > 0) {
                        return true;
                    }
                }

                return false;
            }

            Map::iterator begin() {
                return data.begin();
            }

            Map::iterator end() {
                return data.end();
            }

            Map::const_iterator begin() const {
                return data.begin();
            }

            Map::const_iterator end() const {
                return data.end();
            }

            int& operator[](const std::string& name) {
                return data[name];
            }

            const int& operator[](const std::string& name) const {
                return data.at(name);
            }

            std::string toString() const {
                std::stringstream ss;

                for(Map::const_iterator it = data.begin(); it != data.end(); ++it) {
                    if (it != data.begin()) {
                        ss << " ";
                    }

                    if(it->second == 1) {
                        ss << it->first;
                    }
                    else {
                        ss << it->first << "^" << it->second;
                    }
                }

                return ss.str();
            }

            void fromString(const std::string& unit) {
                // m kg
                // m kg s^-2
                // m kg / s^2

                static std::string allowUnitChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                bool negateExponent = false;
                std::string name = "";
                int exponent = 1;
                for(std::size_t i = 0; i < unit.length(); ++i) {
                    if(unit[i] == ' ') {
                        if (name.length() > 0) {
                            data[name] = negateExponent ? -exponent : exponent;
                            exponent = 1;
                            name = "";
                            continue;
                        }
                    }
                    else if(unit[i] == '/') {
                        negateExponent = true;
                        continue;
                    }
                    else if(unit[i] == '^') {
                        std::size_t spacePos = unit.find(' ', i);
                        std::string exponentStr = "";
                        bool addUnit = false;

                        if(spacePos == std::string::npos) {
                            exponentStr =  unit.substr(i+1);
                            addUnit = true;
                        }
                        else {
                            exponentStr = unit.substr(i+1, spacePos);
                        }

                        exponent = std::atoi(exponentStr.c_str());

                        if(addUnit && name.length() > 0) {
                            data[name] = negateExponent ? -exponent : exponent;
                            exponent = 1;
                            name = "";
                        }

                        continue;
                    }

                    if(allowUnitChars.find(unit[i]) != std::string::npos) {
                        name += unit[i];
                    }
                }

                if(name.length() > 0) {
                    data[name] = negateExponent ? -exponent : exponent;
                }
            }

            bool operator==(const Unit& rhs) const {
                for(std::pair<const std::string, int> element : data) {
                    std::map<std::string, int>::const_iterator it = rhs.data.find(element.first);
                    if(it == rhs.data.end() && it->second != 0)
                        return false;

                    if(it->second != element.second)
                        return false;
                }

                for(std::pair<const std::string, int> element : rhs.data) {
                    std::map<std::string, int>::const_iterator it = data.find(element.first);
                    if(it == data.end() && it->second != 0)
                        return false;

                    if(it->second != element.second)
                        return false;
                }

                return true;
            }

            bool operator!=(const Unit& rhs) const {
                return !(*this == rhs);
            }

            // Only for sorting in UnitTable required
            bool operator<(const Unit& rhs) const {
                return toString() < rhs.toString();
            }
        };

        std::ostream& operator<<(std::ostream& os, const Unit& unit);
    }
}

#endif
