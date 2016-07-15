#ifndef tsdev_calculations_unittable_h
#define tsdev_calculations_unittable_h

#include "unit.h"

namespace tsdev {
    namespace calculations {
        struct UnitTable {
            std::map<Unit, Unit> table;

            static UnitTable& instance() {
                static UnitTable ut;
                return ut;
            }

            void add(Unit from, Unit to) {
                from.cleanup();
                to.cleanup();

                table[from] = to;
            }

            std::pair<Unit, Unit> findBestMatch(Unit source) {
                std::pair<Unit, Unit> dest;
                int score = 0;

                for(std::pair<const Unit, Unit> p : table) {
                    int actualScore = source.matches(p.first);

                    if (actualScore > score) {
                        score = actualScore;
                        dest.first = p.first;
                        dest.second = p.second;
                    }

                    actualScore = source.matches(p.second);
                    if (actualScore > score) {
                        score = actualScore;
                        dest.first = p.second;
                        dest.second = p.first;
                    }
                }

                return dest;
            }
        };
    }
}

#endif
