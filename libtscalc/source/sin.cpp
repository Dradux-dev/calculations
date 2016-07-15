#include "../include/tsdev/calculations/sin.h"

#include "../include/tsdev/calculations/stack.h"

namespace tsdev {
    namespace calculations {
        ElementPtr<double> Sin(double in) {
            ElementPtr<double> eIn = Stack<double>::instance().createElement(new Element<double>(in));
            return ElementPtr<double>(new _Sin<double, double>(eIn));
        }
    }
}
