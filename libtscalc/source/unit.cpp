#include "../include/tsdev/calculations/unit.h"

namespace tsdev {
    namespace calculations {
        std::ostream& operator<<(std::ostream& os, const Unit& unit) {
            os << "[" << unit.toString() << "]";
            return os;
        }
    }
}
