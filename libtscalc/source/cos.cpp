#include "../include/tsdev/calculations/cos.h"

#include "../include/tsdev/calculations/stack.h"

namespace tsdev {
    namespace calculations {
        ElementPtr<double> Cos(double in) {
            ElementPtr<double> eIn = Stack<double>::instance().createElement(new Element<double>(in));
            return ElementPtr<double>(new _Cos<double, double>(eIn));
        }
    }
}
